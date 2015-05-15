int led=8;
int potenciometro=0;

void setup()
{
  pinMode(led,OUTPUT);

}

void loop()
{
  digitalWrite(led,HIGH);
  delay(analogRead(potenciometro));
  digitalWrite(led,LOW);
  delay(analogRead(potenciometro));
}
