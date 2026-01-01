#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11
#define MQ2_PIN 35

const char* ssid = "Shambhuraje";
const char* password = "tanaji1234";

const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* topic = "env/esp32/data";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  client.setServer(mqtt_server, mqtt_port);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting MQTT...");
    if (client.connect("ESP32_Publisher")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int gas = analogRead(MQ2_PIN);

  if (isnan(t) || isnan(h)) {
    Serial.println("DHT error");
    return;
  }

  String payload = "{";
  payload += "\"temperature\":" + String(t) + ",";
  payload += "\"humidity\":" + String(h) + ",";
  payload += "\"gas\":" + String(gas);
  payload += "}";

  client.publish(topic, payload.c_str());
  Serial.println("Published: " + payload);

  delay(5000);
}
