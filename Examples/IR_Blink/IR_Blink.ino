#define ledPin D5
#define irPin D3

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(irPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorUpdate();
  delay(500);
}

void sensorUpdate()
{
  int value = digitalRead(irPin);

  digitalWrite(ledPin, value);

  Serial.println(value);
}
