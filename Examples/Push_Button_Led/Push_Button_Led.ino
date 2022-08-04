#define PushPin D3
#define LedPin D5

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(PushPin, INPUT_PULLUP);
  pinMode(LedPin, OUTPUT);
  
  digitalWrite(LedPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pushState = digitalRead(PushPin); //LOW means button pushed
  if(pushState == LOW)
  {
    digitalWrite(LedPin, HIGH);
  }
  else
  {
    digitalWrite(LedPin, LOW);
  }
  
  Serial.print("Button State: ");
  Serial.println(pushState);
}
