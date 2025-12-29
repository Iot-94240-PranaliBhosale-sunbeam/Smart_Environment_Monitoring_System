#define MQ2_PIN 35

void setup() {
  Serial.begin(9600);
}

void loop() {
  int gasValue = analogRead(MQ2_PIN);
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  if (gasValue > 2000) {
    Serial.println("⚠️ Gas / Smoke Detected!");
  }

  delay(1000);
}
