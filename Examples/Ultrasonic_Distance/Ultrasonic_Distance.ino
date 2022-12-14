#define echoPin D2
#define trigPin D3

long duration;
int distance;
 
void setup() {
  // put your setup code here, to run once:
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034/2; //s=t*v

  Serial.print("Distance : ");
  Serial.println(distance);

  delay(1000);
}
