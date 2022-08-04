#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <DHT.h>

#include <Adafruit_BMP280.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPin D3 //DHT11 connected to D3 pin

#define DHTType DHT11 //current DHT is type DHT11

Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

#define BMP_ADDRESS 0x76

DHT dht(DHTPin, DHTType);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  delay(3000);
  
  //start DHT
  dht.begin();

  if(!bmp.begin(BMP_ADDRESS))
  {
    Serial.println("Failed to start BMP280 sensor");
    delay(500);
    for(;;); // Don't proceed, loop forever
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  bmp_temp->printSensorDetails();
  
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

  sensors_event_t temp_event, pressure_event;
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);

  //clear display
  display.clearDisplay();

  //display temperature
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temperature: ");

  display.setTextSize(1);
  display.setCursor(0, 10);
  display.print(t);
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(1);
  display.print("C");

  //display humidity
  display.setTextSize(1);
  display.setCursor(0, 22);
  display.print("Humidity: ");

  display.setTextSize(1);
  display.setCursor(0, 32);
  display.print(h);
  display.print(" %");

  //display pressure
  display.setTextSize(1);
  display.setCursor(0, 44);
  display.print("Pressure: ");

  display.setTextSize(1);
  display.setCursor(0, 54);
  display.print(pressure_event.pressure);
  display.print(" %");

  display.display();

  Serial.print("DHT Temperature : ");
  Serial.print(t);
  Serial.println(" *C");
  
  Serial.print("Current Humidity : ");
  Serial.print(h);
  Serial.println(" %");

  Serial.print(F("BMP Temperature = "));
  Serial.print(temp_event.temperature);
  Serial.println(" *C");

  Serial.print(F("BMP Pressure = "));
  Serial.print(pressure_event.pressure);
  Serial.println(" hPa");

  Serial.println();
}
