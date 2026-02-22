#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>

// ---- WiFi / UDP settings ----
const char* apSSID = "BikeAP";
const char* apPASS = "bikepass123";
const unsigned int udpPort = 4210;
WiFiUDP Udp;
IPAddress broadcastIp(192,168,4,255); // ESP32 AP broadcast

// ---- Pin Connections ----
const int radarPin = 4;    // RCWL-0516 OUT pin
const int tipPin   = 17;   // TIP120 (optional for LED test)

// ---- MPU6050 ----
const int MPU_addr = 0x68;
float ax = 0, ay = 0, az = 0;

const float rollThreshold = 15.0;     // degrees tilt
unsigned long lastSend = 0;
const unsigned long sendInterval = 500; // ms

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("\n=== ESP32 BIKE MODULE STARTING ===");

  pinMode(radarPin, INPUT);
  pinMode(tipPin, OUTPUT);
  digitalWrite(tipPin, LOW);

  // ---- Start MPU6050 ----
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);  
  Wire.endTransmission(true);

  // ---- Start WiFi Access Point ----
  bool started = WiFi.softAP(apSSID, apPASS);
  Serial.printf("SoftAP start: %s\n", started ? "OK" : "FAILED");
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  Udp.begin(udpPort);
  Serial.printf("UDP ready on port %u\n\n", udpPort);
}

void loop() {
  readMPU();
  float roll = getRoll();

  int radarState = digitalRead(radarPin);
  bool radarDetected = (radarState == HIGH);

  // Debug print
  static unsigned long lastDbg = 0;
  if (millis() - lastDbg > 500) {
    Serial.printf("Radar:%d  Roll:%.1f deg\n", radarState, roll);
    lastDbg = millis();
  }

  // Trigger rule: radar HIGH + tilt > threshold
  if (radarDetected && fabs(roll) > rollThreshold) {
    if (millis() - lastSend > sendInterval) {
      sendVibrateSignal();
      pulseTip(200);  // Optional small LED pulse
      lastSend = millis();
    }
  }

  delay(20);
}

// ---- Read MPU6050 accelerometer ----
void readMPU() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true);

  if (Wire.available() >= 6) {
    int16_t AcX = Wire.read() << 8 | Wire.read();
    int16_t AcY = Wire.read() << 8 | Wire.read();
    int16_t AcZ = Wire.read() << 8 | Wire.read();
    ax = AcX / 16384.0;
    ay = AcY / 16384.0;
    az = AcZ / 16384.0;
  }
}

// ---- Convert accel to roll in degrees ----
float getRoll() {
  return atan2(ay, az) * 57.295779513;
}

// ---- UDP Broadcast ----
void sendVibrateSignal() {
  const char* msg = "VIBRATE";
  Udp.beginPacket(broadcastIp, udpPort);
  Udp.write((uint8_t*)msg, strlen(msg));
  Udp.endPacket();
  Serial.println("-> Sent UDP: VIBRATE");
}

// ---- LED test pulse ----
void pulseTip(int ms) {
  digitalWrite(tipPin, HIGH);
  delay(ms);
  digitalWrite(tipPin, LOW);
}

  
