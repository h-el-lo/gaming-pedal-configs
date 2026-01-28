#include "S_RGB.h"
#include <Adafruit_NeoPixel.h>

S_RGB::S_RGB()
  : pixels(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800) {
  pixels.begin();
  setSynthageColor(1);
  pixels.setPixelColor(0, pixels.Color(100, 200, 225));
  pixels.show();
}

S_RGB::S_RGB(uint8_t numpixel, uint8_t rgb_pin)
  : pixels(numpixel, rgb_pin, NEO_GRB + NEO_KHZ800) {
  RGB_PIN = rgb_pin;
  NUMPIXELS = numpixel;
  pixels.begin();
  setSynthageColor(1);
  pixels.setPixelColor(0, pixels.Color(100, 200, 225));
  pixels.show();
}

void S_RGB::testing() {
  pixels.setPixelColor(0, pixels.Color(200, 100, 155));
  pixels.show();
}


void S_RGB::setColor(uint8_t R, uint8_t G, uint8_t B) {
  r = R;
  g = G;
  b = B;
}

void S_RGB::setSynthageColor(uint8_t COLOR_NUM) {
  // COLOR_NUM from 1- 12
  COLOR_NUM = constrain(COLOR_NUM, 1, 12);
  COLOR_NUM--;
  uint8_t* color = colors[(sel % 12) - 1];
  setColor(color[0], color[1], color[2]);
}

void S_RGB::linear_stepper_forward_backward() {
  // This pattern is in four stages, increment, hold, decrement, hold.

  if (stage == 1) {

    if (RGB_count <= steps) {
      if (micros() - RGB_timer >= threshold) {
        for (int i = 0; i < NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(((r * RGB_count) / steps), ((g * RGB_count) / steps), ((b * RGB_count) / steps)));
        }
        pixels.show();
        RGB_timer = micros();
        RGB_count += 1;
      }
    }

    if (RGB_count == steps) {
      RGB_count = 0;
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(0, pixels.Color(r, g, b));
      }
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
        for (int i = 0; i < NUMPIXELS; i++) {
          pixels.setPixelColor(0, pixels.Color(((r * (steps - RGB_count)) / steps), ((g * (steps - RGB_count)) / steps), ((b * (steps - RGB_count)) / steps)));
        }
        pixels.show();
        RGB_timer = micros();
        RGB_count += 1;
      }
    }

    if (RGB_count == steps) {
      RGB_count = 0;
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      }
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

void S_RGB::linear_stepper_forward_backward(int steps, int timeon, int timeoff) {
  // This pattern is in four stages, increment, hold, decrement, hold.

  if (stage == 1) {

    if (RGB_count <= steps) {
      if (micros() - RGB_timer >= threshold) {
        for (int i = 0; i < NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(((r * RGB_count) / steps), ((g * RGB_count) / steps), ((b * RGB_count) / steps)));
        }
        pixels.show();
        RGB_timer = micros();
        RGB_count += 1;
      }
    }

    if (RGB_count == steps) {
      RGB_count = 0;
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(0, pixels.Color(r, g, b));
      }
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
        for (int i = 0; i < NUMPIXELS; i++) {
          pixels.setPixelColor(0, pixels.Color(((r * (steps - RGB_count)) / steps), ((g * (steps - RGB_count)) / steps), ((b * (steps - RGB_count)) / steps)));
        }
        pixels.show();
        RGB_timer = micros();
        RGB_count += 1;
      }
    }

    if (RGB_count == steps) {
      RGB_count = 0;
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      }
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

void S_RGB::linear_stepper_forward_backward(uint8_t r, uint8_t g, uint8_t b, int steps, int timeon, int timeoff) {
  // This pattern is in four stages (increment, hold, decrement, hold)

  if (stage == 1) {

    if (RGB_count <= steps) {
      if (micros() - RGB_timer >= threshold) {
        for (int i = 0; i < NUMPIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(((r * RGB_count) / steps), ((g * RGB_count) / steps), ((b * RGB_count) / steps)));
        }
        pixels.show();
        RGB_timer = micros();
        RGB_count += 1;
      }
    }

    if (RGB_count == steps) {
      RGB_count = 0;
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(0, pixels.Color(r, g, b));
      }
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
        for (int i = 0; i < NUMPIXELS; i++) {
          pixels.setPixelColor(0, pixels.Color(((r * (steps - RGB_count)) / steps), ((g * (steps - RGB_count)) / steps), ((b * (steps - RGB_count)) / steps)));
        }
        pixels.show();
        RGB_timer = micros();
        RGB_count += 1;
      }
    }

    if (RGB_count == steps) {
      RGB_count = 0;
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      }
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
