#include <Adafruit_NeoPixel.h>

#define RGB_PIN 23   // Change to your board's RGB pin
#define NUMPIXELS 1  // Only 1 LED onboard

Adafruit_NeoPixel pixels(NUMPIXELS, RGB_PIN, NEO_RGB + NEO_KHZ800);

int r, g, b;

// Synthage default colors
int colors[12][3] = {
  { 51, 86, 255 },   // Color 1 - LightBlue // Done
  { 0, 0, 100 },     // Color 2 - Blue // Done
  { 101, 0, 205 },   // Color 3 - Indigo/Purple // Done
  { 80, 0, 87 },     // Color 4 - Violet // Done
  { 195, 0, 60 },    // Color 5 - Magenta // Done
  { 50, 3, 0 },      // Color 6 - Red // Done
  { 245, 65, 2 },    // Color 7 - Orange // Done
  { 255, 190, 0 },   // Color 8 - Yellow // Done
  { 180, 255, 0 },   // Color 9 - Lawn Green // Done
  { 120, 255, 0 },   // Color 10 - Green // Done
  { 72, 255, 51 },   // Color 11- Mint Green // Done
  { 75, 155, 214 },  // Color 12 - Cyan Done // Done
};


// Animation variables (Very similar to Synthage)
int timeon = 435;  // milliseconds
int timeoff = 0;   // milliseconds
int steps = 240;   // 240 frames in about a second
unsigned long RGB_timer = 0;
int threshold = (timeon * 1000) / steps;
int RGB_count = 0;
int stage = 1;          // Begin animation at stage 1
unsigned long sel = 1;  // Color index selection from color list // Begins animation at color "sel"
// ==========================================================

#include <Joystick.h>

int pots[3] = { A1, A0, A2 };

int rxUpper = 840;  // 810;
int rxLower = 170;  // 200;

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

  int* color = colors[(sel % 12) - 1];
  rgb(color[0], color[1], color[2]);
  linear_stepper_forward_backward(r, g, b, steps, timeon, timeoff);

  val1 = analogRead(pots[0]);

  Serial.print("RX: ");
  Serial.print(val1);
  Serial.print(", ");
  Serial.print("RX Mod: ");
  Serial.print(constrain(val1, rxLower, rxUpper));

  // Map analog 0-1023 value from pin to max HID range -32767 - 32767
  val1 = map(constrain(val1, rxLower, rxUpper), rxLower, rxUpper, 0, 1023);


  val2 = analogRead(pots[1]);

  Serial.print("\tRY: ");
  Serial.print(val2);
  Serial.print(", ");
  Serial.print("RY Mod: ");
  Serial.print(constrain(val2, ryLower, ryUpper));

  // Map analog 0-1023 value from pin to max HID range -32767 - 32767
  val2 = map(constrain(val2, ryLower, ryUpper), ryLower, ryUpper, 0, 1023);


  // val3 = analogRead(pots[2]);

  // Serial.print("\tRZ: ");
  // Serial.print(val3);
  // Serial.print(", ");
  // Serial.print("RZ Mod: ");
  // Serial.print(constrain(val3, rzLower, rzUpper));

  // // Map analog 0-1023 value from pin to max HID range -32767 - 32767
  // val3 = map(constrain(val3, rzLower, rzUpper), rzLower, rzUpper, 32767, -32767);



  Serial.println();


  // Send value to HID object
  Joystick.Zrotate(val1);
  Joystick.Z(val2);
  // gamepad.SetRz(val3);


  //  gamepad.SetZ(val);
  //  gamepad.SetS0(val);
  //  gamepad.SetS1(val);

  // Set hat direction, 4 hats available. direction is clockwise 0=N 1=NE 2=E 3=SE 4=S 5=SW 6=W 7=NW 8=CENTER
  // gamepad.SetHat(0, 8);

  Joystick.send_now();
}


void rgb(int R, int G, int B) {
  r = R;
  g = G;
  b = B;
}

void linear_stepper_forward_backward(int r, int g, int b, int steps, int timeon, int timeoff) {
  // This pattern is in four stages, increment, hold, decrement, hold.

  if (stage == 1) {

    if (RGB_count <= steps) {
      if (micros() - RGB_timer >= threshold) {
        pixels.setPixelColor(0, pixels.Color(((r * RGB_count) / steps), ((g * RGB_count) / steps), ((b * RGB_count) / steps)));
        pixels.show();
        RGB_timer = micros();
        RGB_count += 1;
      }
    }

    if (RGB_count == steps) {
      RGB_count = 0;
      pixels.setPixelColor(0, pixels.Color(r, g, b));
      pixels.show();
      RGB_timer = micros();  // Reset the RGB_timer variable
      stage = 2;
    }


  } else if (stage == 2) {

    if (micros() - RGB_timer >= timeoff * 1000) {
      stage = 3;
    }

  } else if (stage == 3) {

    if (RGB_count <= steps) {
      if (micros() - RGB_timer >= threshold) {
        pixels.setPixelColor(0, pixels.Color(((r * (steps - RGB_count)) / steps), ((g * (steps - RGB_count)) / steps), ((b * (steps - RGB_count)) / steps)));
        pixels.show();
        RGB_timer = micros();
        RGB_count += 1;
      }
    }

    if (RGB_count == steps) {
      RGB_count = 0;
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.show();
      RGB_timer = micros();  // Reset the RGB_timer variable
      stage = 4;
    }

  } else if (stage == 4) {

    if (micros() - RGB_timer >= timeoff * 1000) {
      stage = 1;
      sel++;
    }

  }
}
