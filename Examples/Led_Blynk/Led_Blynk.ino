#define BLYNK_TEMPLATE_ID "TMPLlwTHsCZC"
#define BLYNK_DEVICE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "81jH_gyIDeD8E1g1Cuqc8Yn2oOWzjS29"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define LedPin D5

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "HomeWifi";
char pass[] = "StanfordMedicine@2015";

BLYNK_WRITE(V0)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 1)
  {
    digitalWrite(LedPin, HIGH);
    Serial.println("LED ON");
  }
  if(value == 0)
  {
     digitalWrite(LedPin, LOW);
     Serial.println("LED OFF");
  }
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(LedPin,OUTPUT);
}

void loop()
{
  Blynk.run();
}
