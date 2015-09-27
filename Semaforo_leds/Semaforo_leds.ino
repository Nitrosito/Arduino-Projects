
int verde = 11;
int rojo = 12;
int blanco = 10;
int interruptor=8;


void setup() {                

  pinMode(verde, OUTPUT);   
  pinMode(rojo, OUTPUT);  
  pinMode(blanco, OUTPUT);    
  pinMode(interruptor,INPUT);
  Serial.begin(9600);
}

void loop() {

if(digitalRead(interruptor)==HIGH)
{
        Serial.print("Alguien va a cruzar la calle");

   digitalWrite (verde,LOW);
    digitalWrite (blanco,HIGH);
delay(1000);
    digitalWrite (blanco,LOW);
delay(1000);
 digitalWrite (blanco,HIGH);
delay(1000);
    digitalWrite (blanco,LOW);
delay(1000);
 digitalWrite (blanco,HIGH);
delay(1000);
    digitalWrite (blanco,LOW);
delay(1000);
 digitalWrite (blanco,HIGH);
delay(1000);
    digitalWrite (blanco,LOW);
delay(1000);
   digitalWrite (rojo,HIGH);
   delay(10000);
  digitalWrite (rojo,HIGH);
    digitalWrite (verde,LOW);
    delay(5000);
}
else
{
   digitalWrite (rojo,LOW);
 digitalWrite (verde,HIGH);

 
}

 
}
