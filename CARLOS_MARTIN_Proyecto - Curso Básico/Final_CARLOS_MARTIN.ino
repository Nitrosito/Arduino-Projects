////////20-NOV-2012//////////////
/////////////////////////////////
///////// C R E A T E D /////////
/////////////////////////////////
/////////////B Y ////////////////
/// C A R L O S//M A R T I N ////
/////////////////////////////////
////////@NITROSITOLINUX//////////
/////////////////////////////////
/*Las variables solucionc y solucionz las voy a usar para arreglar un inconveniente que tiene el nunchuck al hacer
chuckupdate por primera vez. Al hacer chuckupdate la primera vez, nose porque, siempre le da valor 1, hasta que vuelve
a hacer otro update. por eso le doi valor 0 a esa variable, y con un if, le digo que si solucionc es mayor que 1, si puede
ejecutar su codigo correspondiente (encender led y sumar 1, o reproducir el tono).
Si usted quita estas variables y su correspondiente if, se dara cuenta de que nada mas encender el arduino , sonara la cancion
acto seguido se encendera el led y se sumara 1 al contador*/
#include <LiquidCrystal.h> //libreria para la pantalla LCD
#include "Wire.h"       //Libreria I2C
#include "WiiChuck.h"   //Libreria WiiChuck
#include <EEPROM.h>	//Libreria EEPROM
WiiChuck chuck = WiiChuck();  //Instancia de WiiChuck
#include "/home/nitrosito/Escritorio/PROYECTO FINAL/pitches.h" //si no doi la ruta desde raiz, a mi no me funciona
int led=8;  //pin del led
int val=0;  //valor del led
int old_val=0;  //valor antiguo
int state=0; //estado del led
int contadorencendido=0; //contador para saber cuantas veces se ha encendido
int valor = EEPROM.read(0);
int solucionc=0; 
int solucionz=0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // iniciamos la libreria con los numeros de los pines de la interfaz
# define do 262 // definimos las notas musicales
# define re 293
# define mi 329
# define fa 349
# define sol 392
# define la 440
# define si 494
# define do1 510

// definimos las notas de la melodia
int melody[] = {
si, si, si, si, do};

// duracion de notas 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {  8, 8, 4, 4, 3,};

void setup()

{
  lcd.begin(16,2);   // configuramos el numero de columnas y filas del LCD: 
  Serial.begin(9600);    //Iniciamos comunicacion serie
  chuck.begin();         //Iniciamos WiiChuck
  pinMode(led,OUTPUT);

  lcd.setCursor(0, 0);    // Colocamos el cursor en la columna 0, linea 0
  lcd.print("Contador led");
  lcd.setCursor(5, 1); // Colocamos el cursor en la columna 5, el espacio 5 vamos y la parte de abajo, para escribir la palabra veces
  lcd.print("Pulse Boton");
}
void loop(){
  chuck.update(); 
       //Actualizamos los valores y los imprimimos por pantalla.
   
  if (solucionc>1){
  if((int)chuck.cPressed()==1)
  {
    for (int thisNote = 0; thisNote < 5; thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(9, melody[thisNote],noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // Detener speaker
    noTone(9);}}
  }
    
    if (solucionz>1){
  if((int)chuck.zPressed()==0)
    {val=LOW;}
  else
    {val=HIGH;
      chuck.update();
      contadorencendido= EEPROM.read(0)+ 1; //incrementamos el ultimo guardado
      EEPROM.write(0, contadorencendido);  // escribimos el nuevo valor
      valor = EEPROM.read(0); //actualizamos la variable valor
      Serial.println("------------------------------------------------------------------------"); 
      Serial.print("El boton se ha pulsado "); Serial.print(valor); Serial.println(" veces");
      Serial.print("El led se ha apagado y encendido "); Serial.print(valor/2); Serial.println(" veces");
      Serial.println("------------------------------------------------------------------------"); 
      lcd.setCursor(0, 2);
      lcd.print(valor/2);
      lcd.setCursor(5, 1); // Colocamos el cursor en la columna 5, el espacio 5 vamos y la parte de abajo, para escribir la palabra veces
      lcd.print("Veces       ");

}

  if ((val==HIGH) && (old_val== LOW)){
    state = 1-state;
    delay(10);
    }
  old_val=val;
  if (state==1){
    digitalWrite(led,HIGH);}
  else
    {
     digitalWrite (led,LOW); 
    }}
  delay(10);
  solucionc=solucionc+1;
  solucionz=solucionz+1;

}
