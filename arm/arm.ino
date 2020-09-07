

#include <Servo.h>

Servo base;
Servo arm;
Servo forarm;
int pos1,pos2,pos3,pos4,pos5,pos6;

const int analogInPin1 = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin2 = A1;
const int analogInPin3 = A2;
////////////////////////////
int sensorValue1  = 0;        // value read from the pot
int sensorValue2  = 0;
int sensorValue3  = 0;
////////////////////////////
int outputValue1 = 0;        // value output to the PWM (analog out)
int outputValue2 = 0;
int outputValue3 = 0;
////////////////////////////
int switchPin=2;            //pins for buttons
int startPin=3;
int endPin=4;
int goPin=5;
////////////////////////////
int prevSwitchState=0;
int switchState=0;

int startState=0;
int prevStart=0;

int endState=0;
int prevEnd=0;

int goState=0;//use to switch between execute routine mode and free movement mode
int prevGo=0;
int modeToggle=0;

int armPos=0;// the current arm in use, from 0-2

int armRecordings[6]={pos1,pos2,pos3,pos4,pos5,pos6};  //array for arm recordings
void setup() {
  base.attach(10);
  arm.attach(11);
  forarm.attach(12);
  pinMode(switchPin,INPUT);
  pinMode(startPin,INPUT);
  pinMode(endPin,INPUT);
  pinMode(goPin,INPUT);
  Serial.begin(9600);
}

void loop() {
switchState=digitalRead(switchPin);
startState=digitalRead(startPin);
endState=digitalRead(endPin);
goState=digitalRead(goPin);

if(goState != prevGo){
  if(goState==HIGH){
    modeToggle++;
    if(modeToggle>1){
      modeToggle=0;
    }
  }

  if(modeToggle==0){//free movement mode
if(switchState != prevSwitchState){
if(switchState== HIGH){
  armPos++;//increment the stack
  Serial.print("press");
  if(armPos==3){
    armPos=0;//rotate to the beginning
  }
}
}

if(startState !=  prevStart){
  if(startState ==  HIGH){
    Serial.print("Start position recorded");
    pos1=outputValue1;
    pos2=outputValue2;
    pos3=outputValue3;
  }
}

if(endState !=  prevEnd){
  if(endState ==  HIGH){
    Serial.print("End position recorded");
    pos4=outputValue1;
    pos5=outputValue2;
    pos6=outputValue3;
  }
}


 prevStart  = startState;
 prevEnd  = endState;
 prevSwitchState  = switchState; 


  Serial.print("sensor = ");
  Serial.print(sensorValue1);
  Serial.print("\t output = ");
  Serial.println(outputValue1);
  Serial.print(armPos);
  if(armPos==0){
      sensorValue1 = analogRead(analogInPin1);
        outputValue1 = map(sensorValue1, 0, 1023, 23, 180);
          base.write(outputValue1);
  }else if(armPos ==1){
      sensorValue2 = analogRead(analogInPin2);
        outputValue2 = map(sensorValue2, 0, 1023, 23, 180);
          arm.write(outputValue2);
  }else if(armPos ==2){
      sensorValue3 = analogRead(analogInPin3);
        outputValue3 = map(sensorValue3, 0, 1023, 23, 180);
          forarm.write(outputValue3);
  }
  delay(2);

  }else if(modeToggle==1){//execute routine mode
    loop(){
    delay(100);
      base.write(pos1);
    delay(100);
      arm.write(pos2);
    delay(100);
      forarm.write(pos3)
    delay(1000);//delay between start and end
        base.write(pos4);
    delay(100);
        arm.write(pos5);
    delay(100);
        forarm.write(pos6)
    }
  }
}
prevGo=goState;

}
