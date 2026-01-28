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
#include "S_RGB.h"
#include "Pedal.h"

// ======================================= PEDALS ==========================================
//{"name", pin, axis, invert, min, max, deadzone(%), responseCurve}
Pedal Throttle("THROTTLE", A1, 1, 0, 320, 680, 0, 1);
Pedal Brake("BRAKE", A2, 2, 0, 160, 750, 0, 1);
Pedal Clutch("CLUTCH", A3, 1, 0, 250, 700, 0, 1);

Pedal pedals[3] = { Throttle, Brake, Clutch };
uint8_t potAxisAssignment[5] = { 1, 2, 3, 4, 5 };  // 1=Y(throttle), 2=Z(brake), 3=RZ(clutch) 4-RX(), 5=RY()
// ==========================================================================================

S_RGB myRGB;
int r, g, b;

void setup() {
  Joystick.begin();
  Joystick.useManualSend(true);

}

void loop() {
  myRGB.testing();
  // Update pedals with the Pedal.update() method, map pedal readings to RGB
  updatePedals();

  Joystick.send_now();
}


void updatePedals() {
  // Read throttle potentiometer (val1)
  Throttle.update();
  // g = map(Throttle.getValue(), 0, 1023, 0, 255);  // Green component for LED
  // DEBUGGER
  // Serial.println("Green component of RGB LED is " + g);

  // Read brake potentiometer (val2)
  Brake.update();
  // r = map(Brake.getValue(), 0, 1023, 0, 255);  // Red component for LED
  // DEBUGGER
  // Serial.println("Red component of RGB LED is " + r);

  // // Read clutch potentiometer (val3)
  // Clutch.update();
  // val3 = map(constrain(val3, clutchLower, clutchUpper), clutchLower, clutchUpper, 1023, 0);
}

  } else if (stage == 2) {

    if (micros() - RGB_timer >= timeoff * 1000) {
      stage = 3;
    }
  } else if (stage == 4) {

    if (micros() - RGB_timer >= timeoff * 1000) {
      stage = 1;
      sel++;
    }

  }
}


