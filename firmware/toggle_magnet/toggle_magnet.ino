#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver* ic_1;

// Serial input command buffer
uint16_t cmd_buffer_pos = 0;
const uint8_t CMD_BUFFER_LEN = 20;
char cmd_buffer[CMD_BUFFER_LEN];

const uint8_t BOARDS_PER_ROW = 3;
const uint8_t LEDS_PER_ROW = 4;
const uint8_t BOARDS_ID_BASE = 0x40;

void setup() {
  Serial.begin(9600);

  ic_1 =  new Adafruit_PWMServoDriver();
  Serial.println("Connecting to Adafruit servo board");
  ic_1->begin();
  Serial.println("Adafruit servo board connected");
}

void loop() {
  // put your main code here, to run repeatedly:
  detectSerial();
}

// Read from serial input buffer to command buffer
// Clear command buffer if newline detected or buffer full
// Read from serial input buffer otherwise
void detectSerial() {
  if (Serial.available()) {
    char ch = Serial.read(); // Read character

    if (ch == '\r') {
      // New line detected - end of entered command
      cmd_buffer[cmd_buffer_pos] = '\0'; // Null terminate command string

      parseCommandBuffer(); // Parse and execute command

      cmd_buffer_pos = 0; // Reset index back to 0
      memset(cmd_buffer, 0, sizeof(cmd_buffer)); // Set buffer to be all zero

    } else if (cmd_buffer_pos == CMD_BUFFER_LEN - 1) {
      // Command buffer is full and needs to be reset to read the new character
      cmd_buffer_pos = 0; // Reset index back to 0
      memset(cmd_buffer, 0, sizeof(cmd_buffer)); // Set command to 0

      cmd_buffer[cmd_buffer_pos] = ch; // Save the new character
      cmd_buffer_pos++; // Increment counter position

    } else {
      cmd_buffer[cmd_buffer_pos] = ch; // Save the new character
      cmd_buffer_pos++; // Increment counter position
    }
  }
}

// Parse and execute commands sent over serial:
void parseCommandBuffer() {
  Serial.print("Command read: ");
  Serial.println(cmd_buffer);
  for (int i = 0; i < cmd_buffer_pos; i++) {
    // Find separator between X and Y val
    if (strncmp(cmd_buffer + i, ",", 1) == 0) {

    }
  }
  if (strncmp(cmd_buffer, "XY", 2) == 0) {
    String cmd(cmd_buffer);

    cmd.trim(); // Remove trailing whitespace
    cmd = cmd.substring(2); // Crop out command header
    auto i_separator = cmd.lastIndexOf(",");
    auto i_colon = cmd.lastIndexOf(":");

    auto cmd_x = cmd.substring(0, i_separator);
    auto cmd_y = cmd.substring(i_separator + 1, i_colon);
    auto cmd_val = cmd.substring(i_colon + 1);

    cmd_x.trim();
    cmd_y.trim();
    cmd_val.trim();

    toggle_led(cmd_x.toInt(), cmd_y.toInt(), cmd_val.toInt());
  }
}

void toggle_led(int x_coord, int y_coord, uint16_t value) {
  // Convert coordinate to board and LED number

  // Board id
  // Assumes board 0 is in bottom left, and boards are
  // numbered going right and up (row major)
  int board_x = (int) x_coord / 4;
  int board_y = (int) y_coord / 4;

  int board_id = board_x + board_y * BOARDS_PER_ROW;

  int led_x = x_coord % 4;
  int led_y = y_coord % 4;

  uint8_t led_id = 0;
  led_id = led_x + led_y * LEDS_PER_ROW;

  Serial.print("Toggling LED at ");
  Serial.print(x_coord);
  Serial.print(", ");
  Serial.print(y_coord);
  Serial.print(" with board id: ");
  Serial.print(board_id);
  Serial.print(" and led id: ");
  Serial.print(led_id);
  Serial.print(" with value ");
  Serial.println(value);

  ic_1->setPin(led_id, value);
}
