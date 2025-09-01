#include <Adafruit_NeoPixel.h>
#include <Joystick.h>

// RGB LED setup
#define RGB_PIN 23   // Change to your board's RGB pin
#define NUMPIXELS 1  // Only 1 LED onboard
Adafruit_NeoPixel pixels(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

// Rotary encoder pins for steering
const int ENCODER_A_PIN = 18;  // GPIO18 - Connect to encoder channel A
const int ENCODER_B_PIN = 19;  // GPIO20 - Connect to encoder channel B

// Additional button pins
const int STEERING_RESET = 22;  // GPIO19 - Reset steering button
const int BUTTON_9_PIN = 20;    // GPIO16 - Button 9
const int BUTTON_10_PIN = 21;   // GPIO17 - Button 10

// Steering parameters
const int STEERING_CENTER = 512;     // Center position for X axis
const int STEERING_MAX_RANGE = 512;  // Maximum deviation from center
int ENCODER_SENSITIVITY = 8;         // Steps per steering increment (changeable)
int currentSteeringPos = STEERING_CENTER;

// Potentiometer pins for throttle/brake
int pots[3] = { A1, A2, A3 };

// Calibration values for potentiometers
int throttleUpper = 720;  // Throttle upper
int throttleLower = 320;  // Throttle lower
int brakeUpper = 810;     // Brake upper
int brakeLower = 140;     // Brake lower

// Variables for encoder steering
volatile int encoderPos = 0;
volatile int lastEncoded = 0;


// Reset button debouncing
bool lastResetState = HIGH;
unsigned long lastResetTime = 0;
const unsigned long resetDebounceDelay = 50;

// Button debouncing for new buttons
bool lastButton9State = HIGH;
bool lastButton10State = HIGH;
unsigned long lastButton9Time = 0;
unsigned long lastButton10Time = 0;
const unsigned long buttonDebounceDelay = 50;

// RGB color values
int r, g, b;
int val1, val2, val3;

void setup() {
  // Initialize joystick
  Joystick.begin();
  Joystick.useManualSend(true);

  // Initialize RGB LED
  pixels.begin();

  // Initialize serial communication
  Serial.begin(9600);

  // Configure potentiometer pins
  for (int i = 0; i < 2; i++) {  // Fixed: was pots[1], now i
    pinMode(pots[i], INPUT);
  }

  // Configure encoder pins as inputs with pull-up resistors
  pinMode(ENCODER_A_PIN, INPUT_PULLUP);
  pinMode(ENCODER_B_PIN, INPUT_PULLUP);
  pinMode(STEERING_RESET, INPUT_PULLUP);  // Reset button with pull-up

  // Configure additional button pins with pull-up resistors
  pinMode(BUTTON_9_PIN, INPUT_PULLUP);
  pinMode(BUTTON_10_PIN, INPUT_PULLUP);

  // Attach interrupts for encoder channels
  attachInterrupt(digitalPinToInterrupt(ENCODER_A_PIN), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B_PIN), updateEncoder, CHANGE);

  // Set initial steering position
  Joystick.X(currentSteeringPos);

  Serial.println("Joystick with Rotary Encoder Steering Ready");
  Serial.println("Encoder controls X-axis (steering)");
  Serial.println("Pin 19 resets steering to center");
  Serial.println("Pin 16 is Button 9, Pin 17 is Button 10");
  Serial.println("Potentiometers control Z-rotation (throttle) and Z-axis (brake)");
}

void loop() {
  // Check for reset button press
  checkResetButton();

  // Check for additional button presses
  checkButton9();
  checkButton10();

  // Update steering based on encoder position
  updateSteering();


  // Read throttle potentiometer (val1)
  val1 = analogRead(pots[0]);
  // Serial.print("Throttle: ");
  // Serial.print(val1);
  // Serial.print(", Constrained: ");
  // Serial.print(constrain(val1, throttleLower, throttleUpper));

  // Map and invert throttle value
  val1 = map(constrain(val1, throttleLower, throttleUpper), throttleLower, throttleUpper, 1023, 0);
  g = map(val1, 0, 1023, 0, 255);  // Green component for LED


  // Read brake potentiometer (val2)
  val2 = analogRead(pots[1]);
  // Serial.print("\tBrake: ");
  // Serial.print(val2);
  // Serial.print(", Constrained: ");
  // Serial.print(constrain(val2, brakeLower, brakeUpper));

  // Map and invert brake value
  val2 = map(constrain(val2, brakeLower, brakeUpper), brakeLower, brakeUpper, 1023, 0);
  r = map(val2, 0, 1023, 0, 255);  // Red component for LED


  // Set blue component based on steering position (for visual feedback)
  b = map(abs(currentSteeringPos - STEERING_CENTER), 0, STEERING_MAX_RANGE, 0, 255);

  // Serial.print("\tSteering: ");
  // Serial.print(currentSteeringPos);
  // Serial.print(" (Encoder: ");
  // Serial.print(encoderPos);
  // Serial.println(")");


  // Send joystick values
  Joystick.X(currentSteeringPos);  // Steering wheel (rotary encoder)
  Joystick.Y(val1);                // Throttle
  Joystick.Z(val2);                // Brake

  // Update RGB LED
  pixels.setPixelColor(0, pixels.Color(r, g, b));

  // Send all updates
  Joystick.send_now();
  pixels.show();

  delay(10);  // Small delay for stability
}

// Check reset button with debouncing
void checkResetButton() {
  bool currentResetState = digitalRead(STEERING_RESET);
  unsigned long currentTime = millis();

  // // Check if button state changed and enough time has passed (debouncing)
  // if (currentResetState != lastResetState && (currentTime - lastResetTime) > resetDebounceDelay) {


  //   lastResetState = currentResetState;
  //   lastResetTime = currentTime;
  // }

  // Button pressed (LOW because of pull-up resistor)
  if (currentResetState == LOW) {
    Serial.println("Reset button pressed - centering steering");
    resetSteering();
  }
}

// Check button 9 with debouncing
void checkButton9() {
  bool currentButton9State = digitalRead(BUTTON_9_PIN);
  unsigned long currentTime = millis();

  // Check if button state changed and enough time has passed (debouncing)
  if (currentButton9State != lastButton9State && (currentTime - lastButton9Time) > buttonDebounceDelay) {

    // Button pressed (LOW because of pull-up resistor)
    if (currentButton9State == LOW) {
      Serial.println("Button 9 pressed");
      Joystick.button(9, true);
    } else {
      Serial.println("Button 9 released");
      Joystick.button(9, false);
    }

    lastButton9State = currentButton9State;
    lastButton9Time = currentTime;
  }
}

// Check button 10 with debouncing
void checkButton10() {
  bool currentButton10State = digitalRead(BUTTON_10_PIN);
  unsigned long currentTime = millis();

  // Check if button state changed and enough time has passed (debouncing)
  if (currentButton10State != lastButton10State && (currentTime - lastButton10Time) > buttonDebounceDelay) {

    // Button pressed (LOW because of pull-up resistor)
    if (currentButton10State == LOW) {
      Serial.println("Button 10 pressed");
      Joystick.button(10, true);
    } else {
      Serial.println("Button 10 released");
      Joystick.button(10, false);
    }

    lastButton10State = currentButton10State;
    lastButton10Time = currentTime;
  }
}

// Update steering position based on encoder
void updateSteering() {
  static int lastEncoderPos = 0;

  if (encoderPos != lastEncoderPos) {
    // Calculate encoder change
    int encoderChange = encoderPos - lastEncoderPos;

    // Apply sensitivity and update steering position
    int steeringChange = encoderChange * ENCODER_SENSITIVITY;
    currentSteeringPos += steeringChange;

    // Constrain steering to valid range
    currentSteeringPos = constrain(currentSteeringPos,
                                   STEERING_CENTER - STEERING_MAX_RANGE,
                                   STEERING_CENTER + STEERING_MAX_RANGE);

    lastEncoderPos = encoderPos;

    Serial.print("\tSteering: ");
    Serial.print(currentSteeringPos);
    Serial.print(" (Encoder: ");
    Serial.print(encoderPos);
    Serial.println(")");
  }
}

// Interrupt service routine for encoder
void updateEncoder() {
  int MSB = digitalRead(ENCODER_A_PIN);  // Most significant bit
  int LSB = digitalRead(ENCODER_B_PIN);  // Least significant bit

  int encoded = (MSB << 1) | LSB;          // Convert to single number
  int sum = (lastEncoded << 2) | encoded;  // Add it to previous encoded value

  // Determine direction based on state changes
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderPos++;
  }
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderPos--;
  }

  lastEncoded = encoded;  // Store this value for next time
}

// Function to reset steering to center
void resetSteering() {
  encoderPos = 0;
  currentSteeringPos = STEERING_CENTER;
  Joystick.X(currentSteeringPos);
}

// Function to set steering sensitivity
void setSteeringSensitivity(int sensitivity) {
  // Sensitivity should be 1-10, where 1 is least sensitive
  ENCODER_SENSITIVITY = constrain(sensitivity, 1, 10);
}