# ESP32 Automated Chrome Dino Player 🦖🤖

[![Arduino](https://img.shields.io/badge/Platform-Arduino-blue.svg)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

## Connect with TechTadka360

- YouTube: [@techtadka360official](https://youtube.com/@techtadka360official?si=GdlIntZKv30kPgBk)
- Instagram: [@techtadka360official](https://www.instagram.com/techtadka360official?igsh=cWR4bnhjdWw1MHdh)
- Facebook: [TechTadka360](https://www.facebook.com/share/1EkKAJNLdB/)
  
A hardware-based, zero-software-hack bot that physically plays the Google Chrome Dinosaur (T-Rex) game (`chrome://dino`). By utilizing an ESP32 microcontroller, a bare Light Dependent Resistor (LDR)[cite: 1], and a servo motor, this project detects moving obstacles on the screen and mechanically presses the spacebar to jump.

## 🌟 Features

*   **Non-Invasive Physical Automation:** Does not rely on browser scripts, memory injection, or software macros. It plays exactly like a human would—by looking at the screen and pressing a physical key.
*   **High-Speed Analog Detection:** Uses the ESP32's ADC (Analog-to-Digital Converter) for high-resolution contrast detection between the white background and dark cacti.
*   **Zero-Delay Loop Execution:** The main operational loop is stripped of artificial delays, allowing microsecond scanning for instant reaction times against fast-moving obstacles.

---

## 🛠️ Hardware Requirements

| Component | Quantity | Purpose |
| :--- | :--- | :--- |
| **ESP32 Development Board** | 1 | Main microcontroller processing sensor logic and PWM control. |
| **SG90 Servo Motor** | 1 | 180-degree standard servo to physically strike the spacebar. |
| **Bare LDR (Photoresistor)** | 1 | Light sensor to detect the contrast of the passing cactus[cite: 1]. |
| **10kΩ Resistor** | 1 | Pairs with the LDR to create a voltage divider circuit. |
| **Jumper Wires & Tape** | Multiple | For connections and mounting components to the monitor/keyboard. |

---

## ⚡ Circuit & Wiring Diagram

To accurately read the light values from the bare LDR[cite: 1], a voltage divider circuit is required. Wire the components to the ESP32 exactly as shown below:

### Sensor Wiring (Voltage Divider)
| ESP32 Pin | Component Connection | Notes |
| :--- | :--- | :--- |
| **3.3V** | LDR Leg 1 | LDRs have no polarity; either leg works[cite: 1]. |
| **GPIO 32** | LDR Leg 2 **AND** 10kΩ Resistor (End 1) | This is an ADC-capable pin to read analog voltage. |
| **GND** | 10kΩ Resistor (End 2) | Completes the voltage divider circuit. |

### Servo Motor Wiring
| ESP32 Pin | Servo Wire Color | Notes |
| :--- | :--- | :--- |
| **VIN (5V)** | Red (Power) | The servo requires 5V for sufficient torque to press the key. |
| **GND** | Brown/Black (Ground) | Common ground with the ESP32. |
| **GPIO 15** | Orange/Yellow (Signal) | Outputs the PWM signal to control servo angles. |

---

## 💻 Software Installation

1.  Download and install the [Arduino IDE](https://www.arduino.cc/en/software).
2.  Install the ESP32 board manager in Arduino IDE (`Tools > Board > Boards Manager > search "ESP32"`).
3.  Install the required Servo library: Go to `Sketch > Include Library > Manage Libraries`, search for **ESP32Servo** (by Kevin Harrington), and click Install.
4.  Clone this repository or copy the `dino_bot.ino` code.
5.  Connect your ESP32 via USB and click **Upload**.

---

## 🔧 Physical Setup & Calibration

### 1. Mounting the Hardware
*   **The Sensor:** Use clear tape to mount the LDR completely flat against your computer monitor[cite: 1]. Place it on the track level where the cactus appears. 
*   **The Actuator:** Clamp or heavily tape the servo motor next to your keyboard. Attach the servo arm so that at `90°` it hovers safely above the spacebar, and at `110°` it makes firm contact with the key.

### 2. Tuning the Light Threshold
Every monitor has different brightness levels. You must calibrate the `darkThreshold` variable in the code.
1. Open the Arduino IDE **Serial Monitor** (Baud rate: 115200).
2. Open the white Chrome Dino screen and note the standard light value (e.g., `2100`).
3. Place a finger over the LDR[cite: 1] to simulate a cactus and note the dropped value (e.g., `1700`).
4. Set the `darkThreshold` in your code to the midpoint (e.g., `1900`).

### 3. Adjusting for Game Speed
As the game progresses, the speed increases. 
*   **Mechanical Delay:** The servo takes milliseconds to physically move. 
*   **The Fix:** Do not place the sensor directly next to the dinosaur. Place the LDR[cite: 1] **1 to 2 inches to the right (ahead)** of the dinosaur. This gives the ESP32 and servo time to react before the fast-moving cactus reaches the collision box.

---

## ⚠️ Troubleshooting

*   **Servo continuously presses the spacebar:** The `darkThreshold` is set too high, or ambient room light is interfering. Lower the threshold value or maximize your monitor's brightness.
*   **Dino crashes into the cactus without jumping:** The `darkThreshold` is set too low, meaning the contrast of the cactus isn't triggering the drop. Increase the threshold slightly.
*   **Dino jumps too late:** Move the physical LDR sensor further to the right on your monitor to give the servo more lead time[cite: 1].
