#define LED 19

void setup()
{
  pinMode(LED,OUTPUT);
}

void loop()
{
  digitalWrite(LED,LOW);
  delay(1000);
  digitalWrite(LED,HIGH);
  delay(1000);
}
