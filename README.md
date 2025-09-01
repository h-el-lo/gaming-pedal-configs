# Gaming Pedal Configs

A collection of Raspberry Pi Pico projects for gaming peripherals with RGB feedback. This repository contains Arduino sketches for creating custom gaming controllers and pedals with visual feedback.

## 🎮 Main Project: Pi Pico Pedals Controlling RGB

The primary project in this repository is a **custom gaming pedal controller** that transforms a Raspberry Pi Pico into a USB joystick device with RGB LED feedback. Perfect for racing games, flight simulators, or any game that benefits from analog pedal input.

### ✨ Features

- **Rotary Encoder Steering**: Precise steering control with configurable sensitivity
- **Analog Pedals**: Throttle and brake pedals using potentiometers
- **RGB Visual Feedback**: Real-time color changes based on pedal positions
  - **Green**: Throttle position (brighter = more throttle)
  - **Red**: Brake position (brighter = more brake)
  - **Blue**: Steering deviation from center (brighter = more steering)
- **USB Joystick**: Recognized as a standard HID device by your computer
- **Additional Buttons**: Two programmable buttons for extra functionality
- **Steering Reset**: Button to quickly center the steering wheel

### 🔧 Hardware Requirements

- **Raspberry Pi Pico** (or Pico W)
- **Rotary Encoder** for steering wheel
- **2x Potentiometers** for throttle and brake pedals
- **3x Push Buttons** (steering reset + 2 programmable)
- **RGB LED** (or NeoPixel strip)
- **Breadboard and jumper wires**
- **USB-C cable** for power and data

### 📍 Pin Connections

| Component | Pin | Description |
|-----------|-----|-------------|
| RGB LED | GPIO 23 | RGB feedback LED |
| Encoder A | GPIO 18 | Rotary encoder channel A |
| Encoder B | GPIO 19 | Rotary encoder channel B |
| Steering Reset | GPIO 22 | Reset steering to center |
| Button 9 | GPIO 20 | Programmable button 9 |
| Button 10 | GPIO 21 | Programmable button 10 |
| Throttle Pot | A1 | Throttle pedal input |
| Brake Pot | A2 | Brake pedal input |

### 🚀 Installation & Setup

1. **Install Arduino IDE** with Raspberry Pi Pico support
2. **Install Required Libraries**:
   - `Adafruit_NeoPixel`
   - `Joystick` (included with Arduino)
3. **Connect Hardware** according to pin diagram above
4. **Upload Code** to your Pico
5. **Connect via USB** - your computer will recognize it as a joystick

### 🎯 Calibration

The code includes built-in calibration for potentiometers:

```cpp
// Throttle calibration
int throttleUpper = 730;  // Upper limit
int throttleLower = 320;  // Lower limit

// Brake calibration  
int brakeUpper = 810;     // Upper limit
int brakeLower = 210;     // Lower limit
```

Adjust these values based on your specific potentiometer range for optimal response.

### ⚙️ Configuration

#### Steering Sensitivity
Adjust the steering sensitivity by modifying:
```cpp
int ENCODER_SENSITIVITY = 8;  // Steps per steering increment
```

- **Lower values (1-5)**: More sensitive steering
- **Higher values (6-10)**: Less sensitive steering

#### RGB Animation Speed
Control the RGB update rate:
```cpp
delay(10);  // Milliseconds between updates
```

### 🎮 Game Compatibility

This controller works with any game that supports:
- **DirectInput** devices
- **Generic USB joysticks**
- **XInput** (with additional software)

Tested with:
- Assetto Corsa
- Project CARS
- Dirt Rally
- Microsoft Flight Simulator
- Any racing or flight game

### 🔍 Troubleshooting

#### Common Issues:

1. **Controller not recognized**: Check USB connection and drivers
2. **Erratic steering**: Verify encoder connections and sensitivity settings
3. **Pedals not responding**: Check potentiometer connections and calibration values
4. **RGB not working**: Verify LED pin connection and power

#### Serial Debug Output:
The code includes extensive serial output for debugging. Open Serial Monitor at 9600 baud to see:
- Pedal values
- Steering position
- Button presses
- Encoder readings

### 📁 Other Projects

#### Pi Pico Synthage RGB
A secondary project featuring:
- **128 buttons** support
- **8 analog axes**
- **4 hat switches**
- **Synthage-style RGB animations**
- **12 predefined color schemes**

### 🤝 Contributing

Feel free to submit issues, feature requests, or pull requests to improve these projects!

### 📄 License

This project is open source. Feel free to modify and distribute as needed.

### 🙏 Acknowledgments

- Built for Raspberry Pi Pico
- Uses Adafruit NeoPixel library for RGB control
- Inspired by custom gaming controller communities

---

**Happy Gaming! 🎮✨**