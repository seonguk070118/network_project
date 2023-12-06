#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>
int cost = 0;
int cds1 = A1;
int cds2 = A0;
int led1 = 4;
int led2 = 3;
int led3 = 2;
int sw1 = 7;
int sw2 = 6;
int sw3 = 5;
int lg1 = 13;
int lg2 = 12;
int APrice = 500;
int BPrice = 700;
int CPrice = 1000;

LiquidCrystal_I2C lcd(0x3F, 16, 2);
Servo servo1;
Servo servo2;
Servo servo3;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  servo1.attach(11);
  servo2.attach(10);
  servo3.attach(9);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(lg1, OUTPUT);
  digitalWrite(lg1, HIGH);
  pinMode(lg2, OUTPUT);
  digitalWrite(lg2, HIGH);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
}
void loop()
{
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  lcd.print("Auto CAN Machine");
  lcd.setCursor(3, 1);
  lcd.print(cost);
  lcd.print(" Won");
  int cdsx = analogRead(cds1);
  int cdsy = analogRead(cds2);
  Serial.println(cost);
  lcd.backlight();
  if (cdsx > 300)
  {
    cost = cost + 500;
    delay(1000);
  }
  if (cdsy > 300)
  {
    cost = cost + 100;
    delay(1000);
  }
  if (cost >= APrice)
  {
    digitalWrite(led1, HIGH);
    if (digitalRead(sw1) == LOW)
    {
      Serial.println("A");
      lcd.clear();
      servo1.write(0);
      delay(1000);
      servo1.write(90);
      delay(100);
      cost = cost - APrice;
    }
  }
  if (cost >= BPrice)
  {
    digitalWrite(led2, HIGH);
    if (digitalRead(sw2) == LOW)
    {
      Serial.println("B");
      lcd.clear();
      servo2.write(0);
      delay(1000);
      servo2.write(90);
      delay(100);
      cost = cost - BPrice;
    }
  }
  if (cost >= CPrice)
  {
    digitalWrite(led3, HIGH);
    if (digitalRead(sw3) == LOW)
    {
      Serial.println("C");
      servo3.write(0);
      delay(1000);
      servo3.write(90);
      delay(100);
      cost = cost - CPrice;
      lcd.clear();
    }
  }
  if (cost < CPrice)
  {
    digitalWrite(led3, LOW);
  }
  if (cost < BPrice)
  {
    digitalWrite(led2, LOW);
  }
  if (cost < APrice)
  {
    digitalWrite(led1, LOW);
  }
  if (Serial.available() > 0)
  {
    String data = Serial.readStringUntil('\n');
    if (data.startsWith("A:"))
    {
      String new_price = data.substring(2);
      APrice = new_price.toInt();
    }
    else if (data.startsWith("B:"))
    {
      String new_price = data.substring(2);
      BPrice = new_price.toInt();
    }
    else if (data.startsWith("C:"))
    {
      String new_price = data.substring(2);
      CPrice = new_price.toInt();
    }
  }
}