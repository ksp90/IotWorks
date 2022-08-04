#define AudioAnalogPin A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(3000);
  Serial.println("Starting Audio Sensor");
   pinMode(AudioAnalogPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(AudioAnalogPin);
  Serial.println(sensorValue);
  delay(250);
}
