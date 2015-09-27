#include <SoftwareSerial.h>

#define RxD 11
#define TxD 10

SoftwareSerial BTSerial(RxD, TxD);

void setup(){
  BTSerial.begin(38400);
  Serial.begin(9600);
  BTSerial.print("AT\r\n");
  Serial.println("Si a continuacion pone OK ->> El dispositivo esta listo.");
  Serial.println("En caso contrario ->> El dispositivo no esta en modo AT.");
  Serial.println("Realice el siguiente procedimiento:");
  Serial.println("- Pulse el boton y mantengalo.");
  Serial.println("- Quite VCC del modulo.");
  Serial.println("- Vuelva a alimentar el modulo.");
  Serial.println("- Suelte el boton.");
  Serial.println("- El modulo parapadeara lentamente, indicando que esta en modo AT.");
  Serial.println("- Resetee Arduino.");
  Serial.println("-------------------------------------------------------------------");
}

void loop(){

  if (BTSerial.available())
    Serial.write(BTSerial.read());

  if (Serial.available())
    BTSerial.write(Serial.read());

}
