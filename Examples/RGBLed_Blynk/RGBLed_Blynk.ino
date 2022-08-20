#define BLYNK_TEMPLATE_ID "TMPLlwTHsCZC"
#define BLYNK_DEVICE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "81jH_gyIDeD8E1g1Cuqc8Yn2oOWzjS29"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define RedLedPin D5
#define GreenLedPin D6
#define BlueLedPin D7

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "HomeWifi";
char pass[] = "StanfordMedicine@2015";

BLYNK_WRITE(V12)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 1)
  {
    digitalWrite(RedLedPin, HIGH);
    Serial.println("Red LED ON");
  }
  if(value == 0)
  {
     digitalWrite(RedLedPin, LOW);
     Serial.println("Red LED OFF");
  }
}
BLYNK_WRITE(V13)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 1)
  {
    digitalWrite(GreenLedPin, HIGH);
    Serial.println("Green LED ON");
  }
  if(value == 0)
  {
     digitalWrite(GreenLedPin, LOW);
     Serial.println("Green LED OFF");
  }
}
BLYNK_WRITE(V14)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 1)
  {
    digitalWrite(BlueLedPin, HIGH);
    Serial.println("Blue LED ON");
  }
  if(value == 0)
  {
     digitalWrite(BlueLedPin, LOW);
     Serial.println("Blue LED OFF");
  }
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(RedLedPin,OUTPUT);
  pinMode(GreenLedPin,OUTPUT);
  pinMode(BlueLedPin,OUTPUT);
}

void loop()
{
  Blynk.run();
}
