#include <NECIRrcv.h>
#define IRPIN 4    // Pin donde esta conectado el sensor IR
#define n1 0xF30CFF00
#define n2 0xE718FF00
int valor = 0;                    // Variable para leer el estado del pin de entrada
int pir = 2;               // Pin de Entrada del sensor
int estadoSensor = LOW;             // Comenzamos asumiendo que no hay movimiento
long DO=523.25;
long RE=587.33;
long MI=659.26;
long FA=698.46;
long SOL=783.99;
long LA=880;
int speaker=8;
 NECIRrcv ir(IRPIN) ;
 
void setup() {
  pinMode(pir, INPUT);     // Se declara el sensor como entrada
  pinMode (13,OUTPUT);
  Serial.begin(9600);  //Iniciamos comunicacion serie con el pc para indicar los movimientos
  Serial.println("Test sensor movimiento");
  ir.begin() ;
 

}
 
void loop(){
  
  unsigned long ircode ;
  while (ir.available()) {
    ircode = ir.read() ;
    //Serial.println(ircode);
    switch(ircode)
    {
        case n1: // ALARMA ACTIVADA
        {
         valor = digitalRead(pir);  
         while (valor == HIGH) {
          digitalWrite (13,HIGH);
           tone(speaker, LA,500);
           delay (350);
           tone(speaker, DO,500);
           if (ir.read()=n2){
           valor=LOW;                            }
                              }
        }

        }
        case n2: // ALARMA NO ACTIVADA
        {
                digitalWrite (13,LOW);
                break;
        }
  
  
  }

