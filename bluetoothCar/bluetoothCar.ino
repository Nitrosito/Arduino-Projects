 #include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,11); // RX | TX

char command = 'S';
char prevCommand = 'A';
int velocity = 0;  
unsigned long timer0 = 2000;  //Stores the time (in millis since execution started)
unsigned long timer1 = 0;  //Stores the time when the last command was received from the phone

int IN3 = 5;    // Input3 conectada al pin 5
int IN4 = 4;    // Input4 conectada al pin 4 
int IN2 = 7;
int IN1 = 6;
int pinfrontLights = 8;

void setup()
{      
  Serial.begin(9600);  //Set the baud rate to that of your Bluetooth module.
  BTSerial.begin(38400);  // HC-05 vitesse par défaut pour la commande AT
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (pinfrontLights, OUTPUT);
}

void loop(){
 // if(Serial.available() > 0){
 if (BTSerial.available()){
    Serial.write(BTSerial.read());
    timer1 = millis();  
    prevCommand = command;
    command = BTSerial.read();
    //Change pin mode only if new command is different from previous.  
    if(command!=prevCommand){
      digitalWrite (IN4, LOW);
      digitalWrite (IN1,LOW); 
            digitalWrite (IN2,LOW); 

      digitalWrite (IN3,LOW); 

      Serial.println(command);
      switch(command){
      case 'F': 
        digitalWrite (IN4, LOW);
        digitalWrite (IN3, HIGH); 
        digitalWrite (IN2, HIGH);
        digitalWrite (IN1, LOW);
        //yellowCar.Forward_4W(velocity);
        break;
      case 'B': 
        digitalWrite (IN4, HIGH);
        digitalWrite (IN3, LOW); 
        digitalWrite (IN2, LOW);
        digitalWrite (IN1, HIGH);
        break;
      case 'L': 
        digitalWrite (IN4, LOW);
        digitalWrite (IN3, HIGH);
        break;
      case 'R':
        digitalWrite (IN2, HIGH);
        digitalWrite (IN1, LOW);

        break;
      case 'S': 
        //yellowCar.Stopped_4W();
        break;
      case 'I':  //FR 
        //yellowCar.ForwardRight_4W(velocity);
        break;
      case 'J':  //BR 
        //yellowCar.BackRight_4W(velocity);
        break;       
      case 'G':  //FL 
        //yellowCar.ForwardLeft_4W(velocity);
        break;
      case 'H':  //BL
        //yellowCar.BackLeft_4W(velocity);
        break;
      case 'W':  //Font ON
        digitalWrite(pinfrontLights, HIGH);
        break;
      case 'w':  //Font OFF
        digitalWrite(pinfrontLights, LOW);
        break;
      case 'U':  //Back ON
        //digitalWrite(pinbackLights, HIGH);
        break;
      case 'u':  //Back OFF
       // digitalWrite(pinbackLights, LOW);
        break;
      case 'D':  //Everything OFF
        //digitalWrite(pinfrontLights, LOW);
        //digitalWrite(pinbackLights, LOW);
        //yellowCar.Stopped_4W();
        break;        
      default:  //Get velocity
        if(command=='q'){
          velocity = 255;  //Full velocity
         // yellowCar.SetSpeed_4W(velocity);
        }
        else{
          //Chars '0' - '9' have an integer equivalence of 48 - 57, accordingly.
          if((command >= 48) && (command <= 57)){
            //Subtracting 48 changes the range from 48-57 to 0-9.
            //Multiplying by 25 changes the range from 0-9 to 0-225.
            velocity = (command - 48)*25;      
            //yellowCar.SetSpeed_4W(velocity);
          }
        }
      }
    }
  else{
    timer0 = millis();  //Get the current time (millis since execution started).
    //Check if it has been 500ms since we received last command.
    if((timer0 - timer1)>500){ 
      //More tan 500ms have passed since last command received, car is out of range.
      //Therefore stop the car and turn lights off.
   }
  } 
        //digitalWrite (IN4, LOW); 

}
else{
	digitalWrite (IN4, LOW);
	digitalWrite (IN3, LOW);
	digitalWrite (IN2, LOW);
	digitalWrite (IN1, LOW);
}
 }
