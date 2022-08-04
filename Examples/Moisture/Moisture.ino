#define moistAnalogPin A0

void setup() {
  // put your setup code here, to run once:
  pinMode(moistAnalogPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int moisture = analogRead(moistAnalogPin);
  Serial.println(moisture);

  delay(100);
}
