#define ledPin D5
#define pirPin D2

int pirValue;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);

  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  pirValue = digitalRead(pirPin);
  digitalWrite(ledPin, pirValue);
  Serial.println(pirValue);
}
