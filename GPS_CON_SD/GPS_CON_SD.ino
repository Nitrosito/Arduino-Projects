/* Conexiones SD:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 5
 */

 /*Conexiones GPS:
  * RX - Pin4
  * TX - Pin3
  */

#include <SPI.h>
#include <SD.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
int estadogps =8;
int estadosd=9;

TinyGPSPlus gps;
File myFile;

// Conexion serial para GPS
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  pinMode(estadosd,OUTPUT);
  pinMode(estadogps,OUTPUT);
  
  if (!SD.begin(5)) { //ERROR INICIALIZANDO SD
    Serial.println("Inicializacion fallida!");
    digitalWrite(estadosd,HIGH);
  }
  
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read())){
      escribirdatos();
      delay(3000);
    }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    digitalWrite(estadogps,HIGH);
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void escribirdatos(){
  //Serial.println(F("Localizacion: ")); 
  if (gps.location.isValid()){
      myFile = SD.open("GPS2.txt", FILE_WRITE);
       if (myFile){
          myFile.print(gps.location.lat(), 6);
          myFile.print(F(","));
          myFile.print(gps.location.lng(), 6);
          myFile.print(F(","));
          digitalWrite(estadosd,LOW);
          digitalWrite(estadogps,LOW);
      }
      else{
          digitalWrite(estadosd,HIGH);
          Serial.println(F("Fallo al abrir archivo"));
          delay(1000);
      }
    
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    
  }
  else{
    Serial.print(F("Localizacion invalida"));
    digitalWrite(estadogps,HIGH);
    delay(1000);
  }

  Serial.print(F("  Fecha/hora: "));
  if (gps.date.isValid())
  {
    myFile.print(gps.date.day());
    myFile.print(F("/"));
    myFile.print(gps.date.month());
    myFile.print(F("/"));
    myFile.print(gps.date.year());
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
     
  }
  else
  {
    Serial.print(F("Fecha invalida"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    myFile.print(F(","));
    myFile.print(gps.time.hour());
    myFile.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    myFile.print(gps.time.minute());
    myFile.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    myFile.print(gps.time.second());
    myFile.print(F("."));
    //if (gps.time.centisecond() < 10) Serial.print(F("0"));
    //Serial.print(gps.time.centisecond());
    //myFile.print("Velocidad: ");
    //myFile.print(gps.speed.kmph());
    //myFile.print(" Satelites: ");
    myFile.print(F(","));
    myFile.print(gps.satellites.value());
    
  }
  else{
    Serial.print(F("Hora invalida"));
  }

  myFile.println(" ");
  myFile.close();
}

