#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// -------- SENSOR PINS --------
#define DHTPIN 4
#define DHTTYPE DHT11
#define MQ2_PIN 35

// -------- WIFI DETAILS --------
const char* ssid = "United PG 402";
const char* password = "United402";

// -------- THINGSPEAK --------
String apiKey = "LMDBP9G29OE5LJNX";
const char* server = "http://api.thingspeak.com/update";

// -------- OBJECTS --------
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int gas = analogRead(MQ2_PIN);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor");
    delay(2000);
    return;
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = String(server) +
                 "?api_key=" + apiKey +
                 "&field1=" + String(temperature) +
                 "&field2=" + String(humidity) +
                 "&field3=" + String(gas);

    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.println("Data sent to ThingSpeak");
      Serial.println("Temp: " + String(temperature));
      Serial.println("Hum: " + String(humidity));
      Serial.println("Gas: " + String(gas));
    } else {
      Serial.println("HTTP request failed");
    }

    http.end();
  }

  delay(15000); // ThingSpeak minimum delay
}
