#include <SoftwareSerial.h>

#define trigpin 3
#define echopin 2

int led1 = A2;
int led2 = A1;
int led3 = A0;
int count0 = 0, count1 = 0, count2 = 0;
SoftwareSerial myGSM(8, 9);

void setup(){
  Serial.begin(9600);
  myGSM.begin(19200);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  delay(1000);
}

void loop(){
  double duration, 
  distance;
  digitalWrite(trigpin, HIGH);
  delay(100);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin,HIGH);
  distance = ( duration / 2) / 29.1;
  Serial.println("cm:");
  Serial.println(distance);
  if( (distance > 0) &&  (distance <= 15) ){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    count0++;
    count1 = 0;
    count2 = 0;
    if (count0 == 1){
      SendMessage("Warning! The water level is ABOVE NORMAL.");
      }
    
  } else if( (distance > 16) && (distance <= 30) ){ 
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    count0 = 0;
    count1++;
    count2 = 0;
    if (count1 == 1){
      SendMessage("Good Day, The water level is normal.");
      }
    } else if(distance > 31){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    count0 = 0;
    count1 = 0;
    count2++;
    if (count2 == 1){
      SendMessage("Warning! The water level is BELOW NORMAL.");
      }
    
  } 
}

void SendMessage(String message){
  myGSM.println("AT+CMGF=1");
  delay(100);
  myGSM.println("AT+CMGS=\"09462743741\"\r");
  delay(100);
  myGSM.println(message);
  delay(100);
  myGSM.println((char)26);
  delay(100);
  
 }
