#include <SoftwareSerial.h> //this library allows serial communication via digital pins
#include <Servo.h>          //this library allows arduino board to control servo motor
Servo myServo;              //created servo object to control the servo
int servoPin = 10;  //control signal is connected to Pin10
int echoPin = 11;   //echo is connected to Pin11
int trigPin = 12;   //trigger is connected to Pin12
int ledPin = 13;    //buzzer is on Pin13
int servoPos = 180; //initializing servo to 180
int pingTravelTime;     //it stores the total time travelled by the ultasonic wave
String authorised;      //variable to store the user's fingerprint

void setup() {
  Serial.begin(9600);         //Sets the data rate in bits per second to communicate with Serial Monitor
  myServo.attach(servoPin);   // attaches the servo object to pin10
  myServo.write(servoPos);    //this funct rotates the servo motor; 
  pinMode(echoPin,INPUT);     //it will receive ultasonic waves
  pinMode(trigPin,OUTPUT);    //it will emit ultasonic waves
  pinMode(ledPin,OUTPUT);     //for LED and Buzzer
  int ultra();                //this funct generates the waves
  Serial.println("   --  Initially DOOR is CLOSED  --  ");
}

void loop() {
  //first we generates utrasonic waves 
  ultra();
  delay(1000);

  //here if pingTravelTime is less then threshold(implies door is closed)
  //Then we check for servo angle value 
  
  if(pingTravelTime<4215)
  {
    if(servoPos == 180)     //180 => door is locked
    {
      //This code do the authentication and unlocks the door
      Serial.println(" ** Only AUTHORIZED can be accessed. Please VERIFY!!! first. ** ");
        authorised = Serial.readString();    //reads & stores the string data send from the android application
        Serial.println(authorised); 
        if(authorised == "f success")
        {
          servoPos = 90;              //90 => varible stores the servo position as 90
          myServo.write(servoPos);    //this function rotates the servo motor 
          delay(1250);
          Serial.println(" DOOR is UNLOCKED ");
          delay(1000);
          Serial.println(" DOOR is UNLOCKED ");
          delay(1000);
          Serial.println(" DOOR is UNLOCKED ");
          delay(1000);
          Serial.println(" OPEN the DOOR ");
          delay(5000);
       
        }    
     }
  }
  delay(500);
  ultra();
  delay(1000);
  Serial.println(pingTravelTime);
  delay(1000);
  
  //here if pingTravelTime is less then threshold (implies door is closed)
    if(pingTravelTime<4215)
    {
     if(servoPos == 90)           //90 => door is unlocked
      {
        //This code locks the dooor automatically when the door is in closed position
        Serial.println(" DOOR is LOCKED ");
        delay(1250);        
        servoPos = 180;             //180 => varible stores the servo position as 180
        myServo.write(servoPos);   //this function rotates the servo motor 
        delay(1250);
        Serial.println(" DOOR is LOCKED ");
        delay(1250);
        Serial.println(" DOOR is LOCKED ");
        delay(1250);
      }
    }
  
//here if pingTravelTime is greater then threshold (implies door is opened)
//Then we check for servo angle value 
  if(pingTravelTime>4215)
  {
    if(servoPos == 90)                    //90 => door is unlocked
    {
      //this code detects that the door is in opened position
      delay(1000);
      Serial.println(" DOOR is OPENED ");
      delay(1250);
      Serial.println(" DOOR is OPENED ");
      delay(1250);
      Serial.println(" DOOR is OPENED ");
      delay(1250);
    }

   
    if(servoPos == 180)                   //180 => door is locked
    {
      //This code is the working condition for buzzer
      for(int i=0;i<=18;i++){
      digitalWrite(ledPin,HIGH);
      delay(100);
      digitalWrite(ledPin,LOW);
      delay(100);
      Serial.println("ALERT!! Forcefully Door is Opened.[LED and BUZZER ON]");
      }
      delay(3000);
      servoPos = 90;
      myServo.write(servoPos);
      delay(1000);
      Serial.println("Now u should close your door.");
      delay(3000);
    }
  }
}

int ultra()
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  pingTravelTime=pulseIn(echoPin,HIGH);     //this function it measures the time for how long is the echo pin is high 
  Serial.println(pingTravelTime);           //displays the total travel time by the wave(hitting+receiving)in serial monitor
  
}
