#define BLYNK_TEMPLATE_ID "TMPLlwTHsCZC"
#define BLYNK_DEVICE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "81jH_gyIDeD8E1g1Cuqc8Yn2oOWzjS29"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define Relay1 D3
#define Relay2 D4

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "HomeWifi";
char pass[] = "StanfordMedicine@2015";

BLYNK_WRITE(V12)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 1)
  {
    digitalWrite(Relay1, HIGH);
    Serial.println("Relay1 ON");
  }
  if(value == 0)
  {
     digitalWrite(Relay1, LOW);
     Serial.println("Relay1 OFF");
  }
}
BLYNK_WRITE(V13)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 1)
  {
    digitalWrite(Relay2, HIGH);
    Serial.println("Relay2 ON");
  }
  if(value == 0)
  {
     digitalWrite(Relay2, LOW);
     Serial.println("Relay2 OFF");
  }
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
}

void loop()
{
  Blynk.run();
}
