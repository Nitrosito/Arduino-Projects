#include <NECIRrcv.h>
#define IRPIN 4    // Pin donde esta conectado el sensor IR

#define n1 0xF30CFF00
#define n2 0xE718FF00

NECIRrcv ir(IRPIN) ;

void setup()
{
  pinMode(13,OUTPUT);
  Serial.begin(9600) ;
  ir.begin() ;
}

void loop()
{
  unsigned long ircode ;

  while (ir.available()) {
    ircode = ir.read() ;
    //Serial.println(ircode);
    switch(ircode)
    {
        case n1:
        {
                digitalWrite(13,HIGH);
                Serial.println("Se encendió el led");
                break;
        }
        case n2:
        {
                digitalWrite(13,LOW);
                Serial.println("Se apagó el led");
                break;
        }
       
    }    
  }
} 
