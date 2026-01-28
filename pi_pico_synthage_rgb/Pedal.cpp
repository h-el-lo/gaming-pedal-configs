#include "Pedal.h"
#include <Joystick.h>

// Constructor
Pedal::Pedal(const char* name, uint16_t pin, uint8_t axis, bool invert, uint16_t min, uint16_t max, uint16_t deadzone, uint8_t responseCurve) {
  _name = name;
  _pin = pin;
  _axis = axis;
  setAxisName();
  _inverted = invert;
  _min = min;
  _max = max;
  _deadzone = deadzone;
  _responseCurve = responseCurve;

  // Define pinMode
  pinMode(_pin, INPUT);
}

// Getters
const char* Pedal::getName() {
  return _name;
}

uint16_t Pedal::getValue() {
  return _value;
}

uint8_t Pedal::getAxis() {
  return _axis;
}

String Pedal::getAxisName() {
  return _axisName;
}

uint16_t Pedal::getMin() {
  return _min;
}

uint16_t Pedal::getMax() {
  return _max;
}

// Setters
void Pedal::setAxis(uint8_t axis) {
  resetAxis();
  _axis = axis;
  setAxisName();
}

void Pedal::setAxisName() {
  _axisName = (_axis == 1) ? "Y" : (_axis == 2) ? "Z"
                                 : (_axis == 3) ? "RZ"
                                 : (_axis == 4) ? "RX"
                                                : "RY";
}

void Pedal::setPin(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, INPUT);
}

void Pedal::setMin(uint16_t value) {
  _min = value;
}

void Pedal::setMax(uint16_t value) {
  _max = value;
}

// Methods
void Pedal::invertAxis() {
  _inverted = !_inverted;
  uint16_t temp;
  _max = temp;
  _max = _min;
  _min = temp;
}

void Pedal::resetAxis() {
  switch (_axis) {
    case 1:
      Joystick.Y(0);
    case 2:
      Joystick.Z(0);
    case 3:
      Joystick.Zrotate(0);
    case 4:
      Joystick.Xrotate(0);
    case 5:
      Joystick.Yrotate(0);
  }
}

void Pedal::update() {
  _value = constrain(analogRead(_pin), _min, _max);

  if (_value != _previousValue) {

    _value = map(_value, _min, _max, 0, 1023);
    // // DEBUGGER
    // Serial.print(_name + " value is " + _value + ", axis is ");

    switch (_axis) {
      case 1:  // Y axis (typically throttle)
        Joystick.Y(_value);
        // Serial.println("Y-Axis");
        break;
      case 2:  // Z axis (typically brake)
        Joystick.Z(_value);
        // Serial.println("Z-Axis");
        break;
      case 3:  // RZ axis (typically clutch)
        Joystick.Zrotate(_value);
        // Serial.println("RZ-Axis");
        break;
      case 4:
        Joystick.Xrotate(_value);
        // Serial.println("RX-Axis");
        break;
      case 5:
        Joystick.Yrotate(_value);
        // Serial.println("RY-Axis");
        break;
      default:
        // Serial.println("Not available!");
        break;
    }
    _previousValue = _value;
  }
}

void Pedal::autoCalibrate() {
  // Come back to this
}
