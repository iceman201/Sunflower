#include "Reading.h"
#include "Motor.h"
#include "FlowerRotation.h"

int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;

const int READING_INTERVAL = 10000;
const int COMPARE_INTERVAL = 20000;
int sensors[4][10];
int averages[4];
Motor motor;

void setup(){
  Serial.begin(9600);
  Serial.println("start...");
  for(int i=2; i<6; i++){
    pinMode(i,OUTPUT);
  }
  motor.config(5,8,9,10,11);
}

void loop(){
  //according to new design
  Reading reading(averages);
  FlowerRotation fr(reading, motor);
  fr.rotate();
  //ledTest();
  popSensor();
//   //ADD AVS TO AVERAGES
   for(int i=0; i<4; i++){
    //Serial.println("-----8");
    averages[i] = getAverage(sensors[i]);
   }
//   ledFollow(Reading.returnTopThree()[0],
//    Reading.returnTopThree()[1]);
}

void popSensor(){
  Serial.println("-----7");
  for(int s=0; s<4; s++){
    for(int r=0; r<10; r++){
      sensors[s][r] = mappedReading(analogRead(s));
    }
  }
}

int getAverage(int sensor[10]){
  Serial.println("-----6");
  int average = 0;
  for(int i=0; i<10; i++){
    average += sensor[i];
  }
  return average/10;
}

int mappedReading(int reading){
  return map(reading,0,1023,0,255);
}

void ledFollow(int second, int first){
  lightsOff();
  Serial.println("TOP BIRDS");
  Serial.println(first);Serial.println(second);
  digitalWrite(second+2,HIGH);  //led pins startin from 2
  digitalWrite(first+2,HIGH);
  delay(10);
  digitalWrite(first+2 ,LOW);
  delay(10);
}
void lightsOff(){
  for(int i=2; i<6; i++){
    digitalWrite(i,LOW);
  }
}
//----------------Tests--------------
void ledTest(){
  for(int i=2; i<6; i++){
    digitalWrite(i,HIGH);
    delay(10);
    digitalWrite(i,LOW);
  }
}
void testMotor(){
  motor.clockwise();
  delay(1000);
  motor.untiClockwise();
  delay(1000);
}
