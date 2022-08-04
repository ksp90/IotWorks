#define BLYNK_TEMPLATE_ID "TMPLlwTHsCZC"
#define BLYNK_DEVICE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "81jH_gyIDeD8E1g1Cuqc8Yn2oOWzjS29"

#define BLYNK_PRINT Serial  //this need to be before Blynk

#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <DHT.h>

#include <Adafruit_BMP280.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

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

#define LedPin D5

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "HomeWifi";
char pass[] = "StanfordMedicine@2015";

DHT dht(DHTPin, DHTType);

Adafruit_MPU6050 mpu;

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

BlynkTimer timer;

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  //Blynk.virtualWrite(V5, millis() / 1000);

  Serial.println("Timer event executing..");

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

  sensors_event_t accelarometer_event, gyro_event, mpu_temp_event;
  mpu.getEvent(&accelarometer_event, &gyro_event, &mpu_temp_event);

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
  display.print(" hPa");

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

//gyro value
/* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(accelarometer_event.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(accelarometer_event.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(accelarometer_event.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(gyro_event.gyro.x);
  Serial.print(", Y: ");
  Serial.print(gyro_event.gyro.y);
  Serial.print(", Z: ");
  Serial.print(gyro_event.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(mpu_temp_event.temperature);
  Serial.println(" degC");

  Serial.println();

  Blynk.virtualWrite(V1, t); //DHT Temperature
  Blynk.virtualWrite(V2, h); //DHT Humidity
  
  Blynk.virtualWrite(V3, temp_event.temperature); //BMP Temperature
  Blynk.virtualWrite(V4, pressure_event.pressure); //BMP Pressure
  
  Blynk.virtualWrite(V5, mpu_temp_event.temperature); //MPU Temp
  Blynk.virtualWrite(V6, accelarometer_event.acceleration.x); //Acc X
  Blynk.virtualWrite(V7, accelarometer_event.acceleration.y); //Acc Y
  Blynk.virtualWrite(V8, accelarometer_event.acceleration.z); //Acc Z
  Blynk.virtualWrite(V9, gyro_event.gyro.x); //Gyro X
  Blynk.virtualWrite(V10, gyro_event.gyro.y); //Gyro Y
  Blynk.virtualWrite(V11, gyro_event.gyro.z); //Gyro Z
}

void setupGyro()
{
  // Try to initialize!
  Serial.println("Searching MPU6050...");
  
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  delay(1000);

  Serial.println("Starting the program");
  
  Blynk.begin(auth, ssid, pass);
  pinMode(LedPin,OUTPUT);
  
  //start DHT
  dht.begin();

  //start gyro mpu6050
  setupGyro();

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

  // Setup a function to be called every second
  timer.setInterval(3000L, myTimerEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
