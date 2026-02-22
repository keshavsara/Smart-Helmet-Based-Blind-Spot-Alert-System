#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// ---- WiFi must match ESP32 ----
const char* ssid     = "BikeAP";
const char* password = "bikepass123";
const unsigned int udpPort = 4210;

WiFiUDP Udp;

// ---- Motors ----
const int motorLeft  = 4;   // GPIO4 (D2)
const int motorRight = 5;   // GPIO5 (D1)

const unsigned long vibrateTime = 700;

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("\n=== HELMET ESP8266 STARTED ===");

  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);

  digitalWrite(motorLeft, LOW);
  digitalWrite(motorRight, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to BikeAP");
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
    Serial.print(".");
    delay(300);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to Bike Module");
    Serial.print("Helmet IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFAILED to connect! Check bike module power & AP ON");
  }

  Udp.begin(udpPort);
  Serial.printf("Listening for UDP on port %u\n", udpPort);
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize > 0) {
    char incoming[64];
    int len = Udp.read(incoming, sizeof(incoming)-1);
    if (len > 0) incoming[len] = 0;

    Serial.print("Received: ");
    Serial.println(incoming);

    if (strcmp(incoming, "LEFT") == 0) {
      vibrateLeft();
    }
    else if (strcmp(incoming, "RIGHT") == 0) {
      vibrateRight();
    }
  }

  delay(10);
}

void vibrateLeft() {
  Serial.println("LEFT – Left motor ON");
  digitalWrite(motorLeft, HIGH);
  delay(vibrateTime);
  digitalWrite(motorLeft, LOW);
}

void vibrateRight() {
  Serial.println("RIGHT – Right motor ON");
  digitalWrite(motorRight, HIGH);
  delay(vibrateTime);
  digitalWrite(motorRight, LOW);
}
