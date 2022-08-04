# IoT Works
In this repository we will be using NodeMCU 8266 Lua Amica board and Arduino IDE. Lua Amica nodeMCU uses CH340 driver. Driver library is already attahced in this repo [here](/Library). Following are all sample projects which can be clubbed together and extended for mroe interesting IoT projects.

Before starting using the example please install the driver for the MCU and required board in Arduino IDE
Board manager link: 
- NodeMCU https://arduino.esp8266.com/stable/package_esp8266com_index.json
- ESP32 https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

Hardware required for Project:
- Breadboard (Please note Lua board might not leave pins left in the board for connection, use two boards together or Connect to MCU pin directly using Jumper Wires)
- Jumper Wires - Male to Male, Male to Female and Female to Female
- Micro USB for connecting to laptop/computer
- 5V 1amp Power bank if power supplied from power bank, Power also can be supplied from laptop/computer using usb or from power supply module
- Required sensors

Sensors Used:
- DHT11 : Temperature and Humidity 
- MPU 6050: IMU/Gyro Accelerometer and Gyroscope
- MP280: Air Pressure, Barometer, Altitude


Folowing are the examples:
- [Audio_Sensor_HW_484](/Examples/Audio_Sensor_HW_484) : Audio Sensor 484 usage
- [Buzzer_Tone](/Examples/Buzzer_Tone) : Usage of active buzzer
- [I2C_Scanner](/Examples/I2C_Scanner) : Scan I2C address connected to MCU
- [IR_Blink](/Examples/IR_Blink) : Blink Led using IR Sensor
- [Led_Blink](/Examples/Led_Blink) : Hello World Led Blink
- [Led_Blynk](/Examples/Led_Blynk) : Hello World Led Blink app using Blynk Iot app
- [Moisture](/Examples/Moisture) : Soil moisture sensor example
- [Pir_Motion](/Examples/Pir_Motion) : Passive IR Sensor for motion detection
- [Push_Button_Led](/Examples/Push_Button_Led) : Usage of push button to turn on Led
- [Rain](/Examples/Rain) : Rain detection Sensor usage
- [Temperature_and_Humidity](/Examples/Temperature_and_Humidity) : Detect Temperature and Humidity using DHT11
- [Temperature_Display](/Examples/Temperature_Display) : Display temperature to OLED Display
- [Temperature_Humidity_Monitoring_System](/Examples/Temperature_Humidity_Monitoring_System) : Monitor Temperature and Humidity from DHT11 to ThingsSpeak
- [Temperature_Pressure_Display](/Examples/Temperature_Pressure_Display) : Display temperature and air pressure in OLED display
- [Temperature_Pressure_Display_Blynk_Led](/Examples/Temperature_Pressure_Display_Blynk_Led) : Display temperature and air pressure in OLED display and send to Blynk IoT
- [Temperature_Pressure_Gyro_Display_Blynk_Led](/Examples/Temperature_Pressure_Gyro_Display_Blynk_Led) :  Display temperature, humidity, air pressure and gyro(accelerometer, gyro) in OLED display and send to Blynk IoT
- [Ultrasonic_Distance](/Examples/Ultrasonic_Distance) : Measure distance of object using Ultrasonic Sensor
- [WhoAmI](/Examples/WhoAmI) : Query Address of Register

Additional sample: Blynk IoT API [Postman Collection](/Postman%20API%20Blynk).
