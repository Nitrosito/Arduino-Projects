#include <Servo.h>

Servo myservo;  // Creación del objeto servo para poder controlarlo
int interruptor=4;

void setup(){
  Serial.begin(9600);
  myservo.attach(3);  //Inicializa servo en pin3
  pinMode(interruptor,INPUT);
}

void loop() { 
  if(digitalRead(interruptor)==0){
    myservo.write(90);
    delay(250);
    myservo.write(1);
    delay(250);
  }

  else{
   myservo.write(1);
   delay(100);
  }
} 
