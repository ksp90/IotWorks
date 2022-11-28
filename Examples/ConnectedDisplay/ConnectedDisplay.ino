#define BLYNK_TEMPLATE_ID "TMPLlwTHsCZC"
#define BLYNK_DEVICE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "81jH_gyIDeD8E1g1Cuqc8Yn2oOWzjS29"

#define BLYNK_PRINT Serial  //this need to be before Blynk

#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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

double price=0;
int stock=0;

BLYNK_WRITE(V15)
{
  double value = param.asDouble();
  Serial.print("Price update request received: ");
  Serial.println(value);
  price = value;
  displayPriceStockText(price, stock);
}

BLYNK_WRITE(V16)
{
  int value = param.asInt();
  Serial.print("Stock update request received: ");
  Serial.println(value);
  stock = value;
  displayPriceStockText(price, stock);
}

BlynkTimer timer;

void displayPriceStockText(double price, int stock)
{
 
  //clear display
  display.clearDisplay();

  //display Product Name
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Product: ");

  //display.setTextSize(1);
  display.setCursor(0, 10);
  display.print("Lay's Classic Potato Cihps");

  //display Price
  //display.setTextSize(1);
  //display.setCursor(0, 22);
  display.setCursor(0, 32);
  display.print("Price: ");

  //display.setTextSize(1);
  //display.setCursor(0, 32);
  display.print("$");
  display.print(price);

  //display Stock
  //display.setTextSize(1);
  display.setCursor(0, 44);
  display.print("Stock: ");

  //display.setTextSize(1);
  //display.setCursor(0, 54);
  display.print(stock);

  display.display(); 
}

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  //Blynk.virtualWrite(V5, millis() / 1000);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  delay(1000);

  Serial.println("Starting the program");
  
  Blynk.begin(auth, ssid, pass);
  pinMode(LedPin,OUTPUT);
  
  Serial.println("Strating Display");
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.println("Display initialised");

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
  
  // Clear the buffer
  display.clearDisplay();

  display.setTextColor(WHITE);

  // Setup a function to be called every second
  timer.setInterval(3000L, myTimerEvent);
  displayPriceStockText(price, stock);
  Blynk.syncVirtual(V15, V16);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
