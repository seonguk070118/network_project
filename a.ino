#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include<Servo.h>
int cost=0;
int cds1=A1;
int cds2=A2;
int led1=4;
int led2=5;
int led3=6;
int sw1=A0;
int sw2=2;
int sw3=3;
int lg1=7;
int lg2=8;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo1;
Servo servo2;
Servo servo3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  pinMode(sw1,INPUT_PULLUP);
  pinMode(sw2,INPUT_PULLUP);
  pinMode(sw3,INPUT_PULLUP);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
 pinMode(lg1, OUTPUT);
 digitalWrite(lg1, HIGH);
 pinMode(lg2, OUTPUT);
 digitalWrite(lg2, HIGH);
 servo1.write(180);
 servo2.write(180);
 servo3.write(180);
  }
void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(3, 0);
  lcd.print(cost);
int cdsx=analogRead(cds1);
int cdsy=analogRead(cds2); 
Serial.println(cost);
lcd.backlight();
if(cdsx>80) {
  cost=cost+500;
  delay(1000);
}
if(cdsy>70){
 cost=cost+100;
 delay(1000);
}
if(cost>=500){
  digitalWrite(led1, HIGH);
  if (digitalRead(sw1)==LOW){
   lcd.clear();
   servo1.write(70);
   delay(1000);
   servo1.write(180);
   delay(100);
   cost=cost-500;
  }
  if(cost>=700){
   digitalWrite(led2, HIGH);
    if (digitalRead(sw2)==LOW){
     lcd.clear();
     servo2.write(70);
     delay(1000);
     servo2.write(180);
     delay(100);
     cost=cost-700;
    }
    if (cost>=1000){
     digitalWrite(led3, HIGH);
     if (digitalRead(sw3)==LOW){
      servo3.write(70);
      delay(1000);
      servo3.write(180);
      delay(100);
      cost=cost-1000;
      lcd.clear();
     }
    }
   }
}
if(cost<1000){
  digitalWrite(led3, LOW);
  if(cost<700){
    digitalWrite(led2, LOW);
    if(cost<500){
      digitalWrite(led1, LOW);
    }
  }
}
}