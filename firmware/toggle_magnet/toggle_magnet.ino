#include <cstddef>
#include <cstdint>

#include <algorithm>
#include <array>
#include <limits>

#include <Arduino.h>

#include <Adafruit_PWMServoDriver.h>
#include <SdFat.h>

constexpr std::uint8_t COLS_OF_BOARDS = 1, ROWS_OF_BOARDS = 1;
constexpr std::uint8_t NUM_BOARDS = COLS_OF_BOARDS * ROWS_OF_BOARDS;

constexpr std::uint8_t COLS_OF_MAGNETS = 4, ROWS_OF_MAGNETS = 4;
constexpr std::uint8_t NUM_MAGNETS_PER_BOARD =
    COLS_OF_MAGNETS * ROWS_OF_MAGNETS;
constexpr std::uint8_t NUM_MAGNETS = NUM_BOARDS * NUM_MAGNETS_PER_BOARD;

constexpr std::uint8_t BOARDS_ID_BASE = 0x40;

std::array<Adafruit_PWMServoDriver *, NUM_BOARDS> drivers;
SdFs sd;
FsFile animation_file;

void drive_output(std::uint8_t magnet_idx, std::uint16_t duty_cycle) {
  const std::uint8_t board_idx = magnet_idx / NUM_MAGNETS_PER_BOARD;
  // Need to subtract here because images start from top left indexes
  const std::uint8_t local_magnet_idx = magnet_idx % NUM_MAGNETS_PER_BOARD;

  drivers[board_idx]->setPin(local_magnet_idx, duty_cycle);
}

void drive_output(std::uint8_t x_coord, std::uint8_t y_coord,
                  std::uint16_t duty_cycle) {
  // Convert coordinate to board and magnet number
  // Assumes board 0 is in bottom left, and boards are
  // numbered going right and up (row major)
  const std::uint8_t board_x = x_coord / COLS_OF_MAGNETS;
  const std::uint8_t board_y = y_coord / ROWS_OF_MAGNETS;

  const std::uint8_t board_idx = board_x + board_y * COLS_OF_BOARDS;

  const std::uint8_t magnet_x = x_coord % COLS_OF_MAGNETS;
  const std::uint8_t magnet_y = y_coord % ROWS_OF_MAGNETS;

  const std::uint8_t magnet_idx = magnet_x + magnet_y * COLS_OF_MAGNETS;

  drivers[board_idx]->setPin(magnet_idx, duty_cycle);
}

// Returns true if the SD card is ok or false otherwise
bool try_open_sd() {
  if (!sd.sdErrorCode()) return true;
  
  Serial.println("Trying to open SD card via SDIO in FIFO mode");
  if (!sd.begin(SdioConfig(FIFO_SDIO))) {
    Serial.println("Failed to open SD card");
    return false;
  }
  return true;
}

class discrete_driver {
public:
  discrete_driver(unsigned long frame_period) : frame_period{frame_period} {}

  void set_magnet(std::uint8_t magnet_idx, std::uint16_t duty_cycle) {
    duty_cycles_current[magnet_idx] = duty_cycle;
  }

  bool ready_for_new_frame() { return ready_for_frame; }

  void update_display() {
    if (millis() - last_frame_time >= frame_period) {
      for (std::size_t i = 0; i < NUM_MAGNETS; i++) {
        drive_output(i, duty_cycles_current[i]);
      }

      ready_for_frame = true;
      last_frame_time = millis();
    } else
      ready_for_frame = false;
  }

protected:
  unsigned long frame_period;

  std::array<std::uint16_t, NUM_MAGNETS> duty_cycles_current{};
  unsigned long last_frame_time = 0;
  bool ready_for_frame = true;
};

class interpolating_driver : public discrete_driver {
public:
  interpolating_driver(unsigned long frame_period)
      : discrete_driver{frame_period} {}

  // User is expected to set all values, or array contents might be undefined or
  // previous values
  void set_magnet(std::uint8_t magnet_idx, std::uint16_t duty_cycle) {
    duty_cycles_next[magnet_idx] = duty_cycle;
  }

  bool ready_for_new_frame() { return ready_for_frame; }

  void update_display() {
    if (millis() - last_frame_time >= frame_period) {
      std::copy(duty_cycles_current.begin(), duty_cycles_current.end(),
                duty_cycles_last.begin());
      std::copy(duty_cycles_next.begin(), duty_cycles_next.end(),
                duty_cycles_current.begin());

      //        for (size_t i = 0; i < NUM_MAGNETS; i++) {
      //          Serial.printf("cur[%d]: %d, last[%d]: %d, next[%d]: %d\n", i,
      //          duty_cycles_current[i], i, duty_cycles_last[i], i,
      //          duty_cycles_next[i]);
      //        }

      ready_for_frame = true;
      last_frame_time = millis();
    } else {
      ready_for_frame = false;
    }

    for (std::size_t i = 0; i < NUM_MAGNETS; i++) {
      std::uint16_t slerped =
          duty_cycles_current[i] +
          max(static_cast<std::int32_t>(duty_cycles_last[i]) -
                  static_cast<std::int32_t>(duty_cycles_current[i]),
              0) *
              (1.0 -
               static_cast<double>(millis() - last_frame_time) / frame_period);
      drive_output(i, slerped);
    }
  }

private:
  std::array<std::uint16_t, NUM_MAGNETS> duty_cycles_next{};
  std::array<std::uint16_t, NUM_MAGNETS> duty_cycles_last{};
};

enum control_mode {
  manual,
  sd_card,
};
control_mode mode = control_mode::manual;
auto driver = interpolating_driver{2000};

void setup() {
  Serial.begin(9600);

  Serial.println("Connecting to servo boards");
  for (std::size_t i = 0; i < NUM_BOARDS; i++) {
    Serial.print("Connecting to board ");
    Serial.println(BOARDS_ID_BASE + i);
    drivers[i] = new Adafruit_PWMServoDriver(BOARDS_ID_BASE + i);
    drivers[i]->begin();
    drivers[i]->setOutputMode(true);
  }
  Serial.println("Servo boards connected");

  try_open_sd();
}

void loop() {
  constexpr int min_command_length = 3;
  if (Serial.available() >= min_command_length) {
    const auto command = Serial.readStringUntil(':');
    if (command == "XY") {
      mode = control_mode::manual;

      const int x = Serial.parseInt();
      Serial.find(',');
      const int y = Serial.parseInt();
      Serial.find(',');
      const int duty_cycle = Serial.parseInt();
      // Wishing for std::clamp and std::numeric_limits right now
      drive_output(x, y, min(max(duty_cycle, 0), UINT16_MAX));
    } else if (command == "OFF") {
      mode = control_mode::manual;
      for (int i = 0; i < NUM_BOARDS; i++) {
        drivers[i]->reset();
      }
    } else if (command == "SD") {
      if (!try_open_sd()) {
        mode = control_mode::manual;
        return;
      }

      mode = control_mode::sd_card;
      const String file_name = Serial.readStringUntil('\n');
      if (!animation_file.open(file_name.c_str(), O_RDONLY)) {
        Serial.println("Couldn't open file; does it exist?");
        mode = control_mode::manual;
        return;
      }

      const int magnet_rows = animation_file.parseInt();
      if (animation_file.read() != ',') {
        Serial.println("Malformed separator");
        mode = control_mode::manual;
        return;
      }
      const int magnet_cols = animation_file.parseInt();

      if (magnet_rows != ROWS_OF_MAGNETS || magnet_cols != COLS_OF_MAGNETS) {
        Serial.println("Mismatched number of magnets per row or column");
        mode = control_mode::manual;
        return;
      }

      Serial.printf("Running animation '%s' for %dx%d magnet grid\n", file_name.c_str(), magnet_cols, magnet_rows);
    } else {
      Serial.println("Unknown command");
    }
  }

  if (mode == control_mode::sd_card) {
    std::uint8_t magnet_idx = 0;
    while (driver.ready_for_new_frame()) {
      const int duty_cycle = animation_file.parseInt();
      const char separator = animation_file.read();
      driver.set_magnet(
          magnet_idx++,
          std::min(std::max(duty_cycle, 0),
                   static_cast<decltype(duty_cycle)>(
                       std::numeric_limits<std::uint16_t>::max())));

      if (separator == ',')
        continue;
      else if (separator == '\n')
        break;
      else if (separator == 0xFF) {
        // End of file (not actually the nbsp character)
        mode = control_mode::manual;
        Serial.println("Animation done.");
        return;
      } else {
        Serial.printf("Malformed separator byte %#02x\n", separator);
        mode = control_mode::manual;
        return;
      }
    }

    driver.update_display();
  }
}
