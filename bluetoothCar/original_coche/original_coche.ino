/*
  Front Motor (Steering) => Channel A
  Back Motor => Channel B
 
  Since the motor shield hijacks 6 pins for the motors'
  control, they are declared in the MotorShieldR3 library.
*/
#include <MotorShieldR3.h>
MotorShieldR3 yellowCar;
#define pinfrontLights    7    //Pin that activates the Front lights.
#define pinbackLights     4    //Pin that activates the Back lights.  
char command = 'S';
char prevCommand = 'A';
int velocity = 0;  
unsigned long timer0 = 2000;  //Stores the time (in millis since execution started)
unsigned long timer1 = 0;  //Stores the time when the last command was received from the phone

void setup()
{      
  Serial.begin(9600);  //Set the baud rate to that of your Bluetooth module.
  pinMode(pinfrontLights , OUTPUT);
  pinMode(pinbackLights , OUTPUT);
}

void loop(){
  if(Serial.available() > 0){
    timer1 = millis();  
    prevCommand = command;
    command = Serial.read();
    //Change pin mode only if new command is different from previous.  
    if(command!=prevCommand){
      //Serial.println(command);
      switch(command){
      case 'F': 
        yellowCar.Forward_4W(velocity);
        break;
      case 'B': 
        yellowCar.Back_4W(velocity);
        break;
      case 'L': 
        yellowCar.Left_4W();
        break;
      case 'R':
        yellowCar.Right_4W(); 
        break;
      case 'S': 
        yellowCar.Stopped_4W();
        break;
      case 'I':  //FR 
        yellowCar.ForwardRight_4W(velocity);
        break;
      case 'J':  //BR 
        yellowCar.BackRight_4W(velocity);
        break;       
      case 'G':  //FL 
        yellowCar.ForwardLeft_4W(velocity);
        break;
      case 'H':  //BL
        yellowCar.BackLeft_4W(velocity);
        break;
      case 'W':  //Font ON
        digitalWrite(pinfrontLights, HIGH);
        break;
      case 'w':  //Font OFF
        digitalWrite(pinfrontLights, LOW);
        break;
      case 'U':  //Back ON
        digitalWrite(pinbackLights, HIGH);
        break;
      case 'u':  //Back OFF
        digitalWrite(pinbackLights, LOW);
        break;
      case 'D':  //Everything OFF
        digitalWrite(pinfrontLights, LOW);
        digitalWrite(pinbackLights, LOW);
        yellowCar.Stopped_4W();
        break;        
      default:  //Get velocity
        if(command=='q'){
          velocity = 255;  //Full velocity
          yellowCar.SetSpeed_4W(velocity);
        }
        else{
          //Chars '0' - '9' have an integer equivalence of 48 - 57, accordingly.
          if((command >= 48) && (command <= 57)){
            //Subtracting 48 changes the range from 48-57 to 0-9.
            //Multiplying by 25 changes the range from 0-9 to 0-225.
            velocity = (command - 48)*25;      
            yellowCar.SetSpeed_4W(velocity);
          }
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
      digitalWrite(pinfrontLights, LOW);
      digitalWrite(pinbackLights, LOW);
      yellowCar.Stopped_4W();
    }
  } 
}
