#include "DHT.h"
#define DHTTYPE DHT11

DHT dht(D1,DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  dht.begin();
  Serial.begin(115200);
  Serial.println("Humidity and Temperature \n\n");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Current Humidity : ");
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Temperature : ");
  Serial.println(t);
  
  delay(1000);
}
