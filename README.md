# 🏍️ Smart Helmet – Blind Spot & Lane Change Alert System for Two-Wheelers

## 📌 Introduction
Road accidents during lane changes are common among two-wheelers due to blind spots and delayed reaction time.  
This project presents a **Smart Helmet–Integrated Blind Spot and Lane Change Alert System** that enhances rider safety by providing **real-time haptic feedback** when a potential collision risk is detected.

The system detects **approaching vehicles from behind** and checks **lane change intent** using motion sensing before alerting the rider through vibration motors embedded in the helmet.

---

## 🎯 Objective
- Detect vehicles approaching from the blind spot
- Identify lane change intent using bike lean angle
- Provide non-distracting haptic alerts to the rider
- Reduce lane-change and blind-spot accidents in two-wheelers

---

## 🧠 System Overview
The project is divided into two modules:

### 🚲 Bike Module
- Detects approaching vehicles using a radar sensor
- Monitors bike lean angle using a gyroscope sensor
- Processes data using ESP32
- Sends alert wirelessly to the helmet
- LED indicates system ON/OFF status

### ⛑️ Helmet Module
- Receives alert signal via ESP8266
- Activates vibration motors for haptic feedback
- Alerts rider without visual or audio distraction

---

## ⚙️ Working Principle
1. Radar sensor detects a fast-approaching vehicle from behind.
2. MPU6050 gyroscope checks the bike’s lean angle.
3. If:
   - Lean angle ≥ 15° (lane change intent)
   - Vehicle is present in blind spot  
4. ESP32 sends an alert signal wirelessly.
5. ESP8266 receives the signal in the helmet.
6. Vibration motors activate to warn the rider.

---

## 🧩 Hardware Components
- ESP32 Development Board
- ESP8266 Wi-Fi Module
- Radar Sensor
- MPU6050 Gyroscope Sensor
- Vibration Motors
- LED Indicator
- Voltage Regulator
- Breadboard
- Custom PCB
- 9V Battery

---

## 💻 Software & Technologies
- Embedded C / Arduino IDE
- ESP32 & ESP8266 Libraries
- I2C Communication Protocol
- Wireless Data Transmission

---

## 🔋 Power Supply
- **Current:** 9V battery (prototype stage)
- **Future Upgrade:**
  - 1080 mAh rechargeable lithium-ion battery
  - Target backup of approximately 15 days
  - Improved power efficiency using optimized voltage regulation

---

## 🚦 Alert Logic
```text
IF (Bike Lean Angle ≥ 15°)
AND (Vehicle Detected in Blind Spot)
THEN
Send Alert to Helmet
Activate Vibration Motor
