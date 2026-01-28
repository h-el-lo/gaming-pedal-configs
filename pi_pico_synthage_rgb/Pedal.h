#ifndef PEDAL_H
#define PEDAL_H

#include <Arduino.h>

class Pedal {
private:
  const char* _name;
  uint8_t _pin;
  uint8_t _axis;
  String _axisName;
  bool _inverted;
  uint16_t _min;
  uint16_t _max;
  uint16_t _deadzone;  // in %
  uint8_t _responseCurve;
  uint16_t _value;
  uint16_t _previousValue;

public:
  // Constructors
  Pedal(const char* name, uint16_t pin, uint8_t axis, bool invert, uint16_t min, uint16_t max, uint16_t deadzone, uint8_t responseCurve);

  // getters
  const char* getName();
  uint16_t getValue();
  uint8_t getAxis();
  String getAxisName();
  uint16_t getMin();
  uint16_t getMax();

  // setters
  void setAxis(uint8_t axis);
  void setAxisName();
  void setPin(uint8_t pin);
  void setMin(uint16_t value);
  void setMax(uint16_t value);

  // methods
  void invertAxis();
  void resetAxis();  // Called during axis change/ to reset value of initial axis before reassigning new axis to pedal
  void autoCalibrate();
  void update();
};

// Pedal pedals[3] = {
//   //{"name", pin, axis, invert, min, max, deadzone(%), responseCurve}
//   { "Throttle", A1, 1, 0, 320, 680, 0, 1 },
//   { "Brake", A2, 2, 0, 160, 750, 0, 1 },
//   { "Clutch", A3, 3, 0, 250, 700, 0, 1 },
// };


#endif