#include "DHT.h"
#include <ESP8266WiFi.h>

#define DHTTYPE DHT11

#ifndef STASSID
#define STASSID "KiranWifiShare"
#define STAPSK "123456789"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

String api_key = "HC5NLV2S5U933PT1";     //  Enter your Write API key from ThingSpeak
const char* server = "api.thingspeak.com";

WiFiClient client;

DHT dht(D1,DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  dht.begin();
  delay(3000);
  ConnectWifi();
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  Serial.print("Current Humidity : ");
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Temperature : ");
  Serial.println(t);
  
  SendData(t,h);
  
  Serial.println("Waiting...");
  delay(3000); 
}

void ConnectWifi()
{
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  delay(500);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void SendData(float temperature, float humidity)
{
  Serial.println("Sending data to server");
  if (client.connect(server,80))   //   api.thingspeak.com
  {  
    String data_to_send = api_key;
    data_to_send += "&field1=";
    data_to_send += String(temperature);
    data_to_send += "&field2=";
    data_to_send += String(humidity);
    data_to_send += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data_to_send.length());
    client.print("\n\n");
    client.print(data_to_send);
    
    Serial.println("Data Sent to Thingspeak.");
  }
  client.stop();
}
