#include <Adafruit_NeoPixel.h>

#define RGB_PIN 23   // Change to your board's RGB pin
#define NUMPIXELS 1  // Only 1 LED onboard

Adafruit_NeoPixel pixels(NUMPIXELS, RGB_PIN, NEO_RGB + NEO_KHZ800);

int r, g, b;

#include <Joystick.h>

int pots[3] = { A1, A0, A2 };

int rxUpper = 820;  // 810;
int rxLower = 180;  // 200;

int ryUpper = 690;
int ryLower = 270;

// int rzUpper = 1023;
// int rzLower = 0;


// 16 bit integer for holding input values
int val1, val2, val3;

void setup() {
  Joystick.begin();
  Joystick.useManualSend(true);

  pixels.begin();

  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(pots[1], INPUT);
  }
}

void loop() {

  val1 = analogRead(pots[0]);

  Serial.print("RX: ");
  Serial.print(val1);
  Serial.print(", ");
  Serial.print("RX Mod: ");
  Serial.print(constrain(val1, rxLower, rxUpper));

  // Map analog 0-1023 value from pin to max HID range 0 - 1023
  val1 = map(constrain(val1, rxLower, rxUpper), rxLower, rxUpper, 1023, 0);  // Throttle
  g = map(val1, 0, 1023, 0, 255);


  val2 = analogRead(pots[1]);

  Serial.print("\tRY: ");
  Serial.print(val2);
  Serial.print(", ");
  Serial.print("RY Mod: ");
  Serial.print(constrain(val2, ryLower, ryUpper));

  // Map analog 0-1023 value from pin to max HID range 0 - 1023
  val2 = map(constrain(val2, ryLower, ryUpper), ryLower, ryUpper, 1023, 0);  // Brake
  r = map(val2, 0, 1023, 0, 255);


  // val3 = analogRead(pots[2]);

  // Serial.print("\tRZ: ");
  // Serial.print(val3);
  // Serial.print(", ");
  // Serial.print("RZ Mod: ");
  // Serial.print(constrain(val3, rzLower, rzUpper));

  // // Map analog 0-1023 value from pin to max HID range 0 - 1023
  // val3 = map(constrain(val3, rzLower, rzUpper), rzLower, rzUpper, 1023, 0);
  // b = map(val3, 0, 1023, 0, 255)



  Serial.println();


  // Send value to HID object
  Joystick.Zrotate(val1);
  Joystick.Z(val2);
  // gamepad.SetRz(val3);
  pixels.setPixelColor(0, pixels.Color(r, g, b));


  //  gamepad.SetZ(val);
  //  gamepad.SetS0(val);
  //  gamepad.SetS1(val);

  // Set hat direction, 4 hats available. direction is clockwise 0=N 1=NE 2=E 3=SE 4=S 5=SW 6=W 7=NW 8=CENTER
  // gamepad.SetHat(0, 8);

  Joystick.send_now();
  pixels.show();
}
