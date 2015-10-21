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
 
void setup() {
  pinMode(pir, INPUT);     // Se declara el sensor como entrada
  pinMode (13,OUTPUT);
  Serial.begin(9600);  //Iniciamos comunicacion serie con el pc para indicar los movimientos
  Serial.println("Test sensor movimiento");
 

}
 
void loop(){
  valor = digitalRead(pir);  
  while (valor == HIGH) {
    digitalWrite (13,HIGH);
     tone(speaker, LA,500);
     delay (350);
     tone(speaker, DO,500);
     delay (350);
  }
  
    digitalWrite (13,LOW);
  }

