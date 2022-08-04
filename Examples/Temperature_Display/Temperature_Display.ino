#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPin D3 //DHT11 connected to D3 pin

#define DHTType DHT11 //current DHT is type DHT11

DHT dht(DHTPin, DHTType);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //start DHT
  dht.begin();

  delay(3000);
  
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
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);

  //read temperature and humidity
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if(isnan(t) || isnan(h))
  {
    Serial.println("Failed to read temperature and humidity from DHT sensor!");
  }

  //clear display
  display.clearDisplay();

  //display temperature
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temperature: ");

  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print(t);
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");

  //display humidity
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humidity: ");

  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(h);
  display.print(" %");

  display.display();

  Serial.print("Temperature : ");
  Serial.println(t);
  
  Serial.print("Current Humidity : ");
  Serial.print(h);
  Serial.println(" %");
}
