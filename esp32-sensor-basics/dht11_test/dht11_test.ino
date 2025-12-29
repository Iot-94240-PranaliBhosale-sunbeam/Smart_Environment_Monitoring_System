#include"DHT.h"


#define DHT_PIN 4
#define DHT_TYPE  DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  dht.begin();

  Serial.println("DHT setup is done");
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  

  Serial.printf("Temperature = %f, Humidity = %f\n", temp, humidity);

  delay(3000);

}







