# 🏍️ Smart Helmet – Blind Spot & Lane Change Alert System for Two-Wheelers

## 📌 Introduction
Road accidents during lane changes are common among two-wheelers due to blind spots and delayed rider reaction time.  
This project presents a **Smart Helmet–Integrated Blind Spot and Lane Change Alert System** that enhances rider safety by providing **real-time haptic feedback** when a potential collision risk is detected.

The system detects **approaching vehicles from behind** and determines **lane change intent** using motion sensing before alerting the rider through vibration motors embedded in the helmet.

---

## 🎯 Objective
- Detect vehicles approaching from the blind spot
- Identify lane change intent using bike lean angle
- Provide non-distracting, real-time haptic alerts
- Reduce lane-change and blind-spot accidents in two-wheelers

---

## 🧠 System Overview
The project is divided into two independent modules communicating wirelessly.

### 🚲 Bike Module (ESP32)
- Detects approaching vehicles using a radar sensor
- Monitors bike lean angle using an MPU6050 gyroscope
- Determines lane-change intent (≥ 15° tilt)
- Broadcasts alert signals using UDP over Wi-Fi
- LED indicates system power / activity status

### ⛑️ Helmet Module (ESP8266)
- Connects wirelessly to the bike module
- Receives alert packets via UDP
- Activates vibration motors for haptic feedback
- Supports **directional vibration** (left / right) for better rider awareness
- Alerts rider without visual or audio distraction

---

## ⚙️ Working Principle
1. Radar sensor detects a fast-approaching vehicle from behind.
2. MPU6050 gyroscope measures bike lean angle.
3. If:
   - Lean angle ≥ **15°** (lane-change intent), **and**
   - A vehicle is detected in the blind spot  
4. ESP32 (bike module) sends an alert wirelessly using UDP.
5. ESP8266 (helmet module) receives the alert.
6. Corresponding vibration motor(s) activate to warn the rider.

---

## 🚦 Alert Logic
```text
IF (Bike Lean Angle ≥ 15°)
AND (Vehicle Detected in Blind Spot)
THEN
Send Alert to Helmet
Trigger Directional Vibration
