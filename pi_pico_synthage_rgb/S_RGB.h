#ifndef S_RGB_H
#define S_RGB_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class S_RGB {
private:
  Adafruit_NeoPixel pixels;

  uint8_t RGB_PIN = 23;   // Change to your board's RGB pin
  uint8_t NUMPIXELS = 1;  // Only 1 LED onboard
  uint8_t r, g, b;

  // Synthage default colors
  uint8_t colors[12][3] = {
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


public:
  // Constructors
  S_RGB();
  S_RGB(uint8_t numpixels, uint8_t rgb_pin);

  // Methods
  void testing();
  void setColor(uint8_t R, uint8_t G, uint8_t B);
  void setSynthageColor(uint8_t COLOR_NUM);
  void linear_stepper_forward_backward();
  void linear_stepper_forward_backward(int steps, int timeon, int timeoff);
  void linear_stepper_forward_backward(uint8_t r, uint8_t g, uint8_t b, int steps, int timeon, int timeoff);
};


#endif