int analogPin=A0; //Pin analogico 0 de arduino
void setup()
{
    Serial.begin(9600);
}
void loop()
{
 int valorLuz= analogRead(analogPin);
 Serial.println(valorLuz);
 delay(500);
}
    
