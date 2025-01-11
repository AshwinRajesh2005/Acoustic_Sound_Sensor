#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ThingSpeak.h>

const char* ssid = "Gg";
const char* password = "123123132";
const char* server = "api.thingspeak.com";
const unsigned long channelID = 2676400; // Replace with your ThingSpeak channel ID
const char* apiKey = "ZJ836EYJSK9I7F6Y"; // Replace with your ThingSpeak API key

WiFiClient client;
Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, pressure);

  int httpCode = ThingSpeak.writeFields(channelID, apiKey);
  if (httpCode == 200) {
    Serial.println("Data sent successfully!");
  } else {
    Serial.println("Error sending data to ThingSpeak.");
  }

  delay(15000); // Send data every 15 seconds
}