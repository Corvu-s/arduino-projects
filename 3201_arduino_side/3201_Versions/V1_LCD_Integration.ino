int p1CounterPin=9;//pin 8 holds the p1 counter signal
int p2CounterPin=9;//pin 9 holds the p2 counter signal

int p1Count=0;
int p2Count=0;


int p2State=0;
int p2Prev=0;

int p1Score=0;
int p2Score=0;
int equalPin=10;
int equalState=0;

int scoreCap=5;
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
void setup() {

//   lcd.begin(16,2); 

  Serial.begin(9600);
  pinMode(p1CounterPin,INPUT);
  pinMode(equalPin,INPUT);
}

void loop() {//setCursor(rows,index)

//////////////////////Intro
//  lcd.print("High Low Game,by");
//  delay(2000);  
//  lcd.setCursor(0,1);  
//  lcd.print("Luke and Nourin"); 
//  delay(4000); 
//  lcd.clear();
////////////////////////Instruction
//  lcd.setCursor(0,0);
//  lcd.print("P1=top button");
//  lcd.setCursor(0,1);
//  lcd.print("P2=bottom button");
//  delay(4000);
//  lcd.clear();
/////////////////////////Scores
//  lcd.setCursor(0,0);
//  lcd.print("P1 Score:");
//  lcd.setCursor(10,0);
//  lcd.print(p1Score);
//  
//  lcd.setCursor(0,1);
//  lcd.print("P2 Score:");
//  lcd.setCursor(10,1);
//  lcd.print(p2Score);
//  
//  delay(4000);
//  lcd.clear();
/////////////////////
   p2State=digitalRead(p1CounterPin);
   equalState=digitalRead(equalPin);
    //Serial.print(equalState);
   if(p2State != p2Prev){
      if(p2State == HIGH){
        p2Count++;
      }
   }
   p2Prev=p2State;


  if(p2Count <5 && equalState == HIGH){
    p2Score++;
    p2Count=0;
  }else if(p2Count >= 5){
    p1Score++;
    p2Count=0;
   }
      Serial.println(p1Score);
}
