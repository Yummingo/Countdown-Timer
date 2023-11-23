#include <RTClib.h>
#include <Wire.h>

RTC_DS3231 rtc;

int burnTime = 200;
int lastMotion = 0;
int diffTimer = lastMotion - millis();
int offNoMotion = 300000;

DateTime nowdt = rtc.now();
unsigned long now = nowdt.unixtime(); //converts time from RTC to unixtime epoch
unsigned long retireTime = 2542140000; //enter unixtime epoch for retirement date here
unsigned long tdiff = abs(retireTime - now); //abs() allows timer to count up from retireTime
unsigned long tdiffMin = tdiff / 60; //coverts unixtime from seconds to minutes
unsigned long tdiffHr  = tdiffMin / 60; //converts unixtime from minutes to hours
float tdiffDays = tdiffHr / 24; //converts unixtime from whole hours to fractional days
String difference = String(tdiffDays); //convers to string for further processing later

//K155ID1 #1
#define yrX000A 29
#define yrX000B 25
#define yrX000C 23
#define yrX000D 27
//K155ID1 #2
#define yr0X00A 37
#define yr0X00B 33
#define yr0X00C 31
#define yr0X00D 35
//K155ID1 #3
#define yr00X0B 41
#define yr00X0C 39
#define yr00X0D 43
#define yr00X0A 45
//K155ID1 #4
#define yr000XA 53
#define yr000XB 49
#define yr000XC 47
#define yr000XD 51
//K155ID1 #5
#define hrX0A 3
#define hrX0B 1
#define hrX0C 0
#define hrX0D 2
//K155ID1 #6
#define hr0XA 12
#define hr0XB 10
#define hr0XC 9
#define hr0XD 11

#define interruptPin 2
#define relay 3

void setup() {
  Wire.begin();

  pinMode(yrX000A, OUTPUT);
  pinMode(yrX000B, OUTPUT);
  pinMode(yrX000C, OUTPUT);
  pinMode(yrX000D, OUTPUT);

  pinMode(yr0X00A, OUTPUT);
  pinMode(yr0X00B, OUTPUT);
  pinMode(yr0X00C, OUTPUT);
  pinMode(yr0X00D, OUTPUT);

  pinMode(yr00X0A, OUTPUT);
  pinMode(yr00X0B, OUTPUT);
  pinMode(yr00X0C, OUTPUT);
  pinMode(yr00X0D, OUTPUT);

  pinMode(yr000XA, OUTPUT);
  pinMode(yr000XB, OUTPUT);
  pinMode(yr000XC, OUTPUT);
  pinMode(yr000XD, OUTPUT);

  pinMode(hrX0A, OUTPUT);
  pinMode(hrX0B, OUTPUT);
  pinMode(hrX0C, OUTPUT);
  pinMode(hrX0D, OUTPUT);

  pinMode(hr0XA, OUTPUT);
  pinMode(hr0XB, OUTPUT);
  pinMode(hr0XC, OUTPUT);
  pinMode(hr0XD, OUTPUT);
  
  pinMode(relay, OUTPUT);
//  attachInterrupt(digitalPinToInterrupt(interruptPin),timerReset(), HIGH);
}

void loop() {
  if (diffTimer < offNoMotion){
    digitalWrite(relay, HIGH);
  }
  else {
    digitalWrite(relay, LOW);
  }
  cathodePoisoning();
  countdown();
}

//Calls digit function for DDDD HH nixie display
void countdown() {
  digit(1, yrX000A, yrX000B, yrX000C, yrX000D);
  digit(2, yr0X00A, yr0X00B, yr0X00C, yr0X00D);
  digit(3, yr00X0A, yr00X0B, yr00X0C, yr00X0D);
  digit(4, yr000XA, yr000XB, yr000XC, yr000XD);
  digit(6, hrX0A, hrX0B, hrX0C, hrX0D);
  digit(7, hr0XA, hr0XB, hr0XC, hr0XD);
  delay(burnTime * 300);//this makes sure our ratio is always right to prevent cathode poisoning.
}

//Determines the value of the digith in the nth position from left and calls the corresponding display function.
void digit(int pos, int inputA, int inputB, int inputC, int inputD) {
  int digitChar = difference.charAt(pos);
  if (digitChar = 0){
    display0(inputA, inputB, inputC, inputD);
  }
  else if (digitChar = 1){
    display1(inputA, inputB, inputC, inputD);
  }
  else if (digitChar = 2){
    display2(inputA, inputB, inputC, inputD);
  }
  else if (digitChar = 3){
    display3(inputA, inputB, inputC, inputD);
  }
  else if (digitChar = 4){
    display4(inputA, inputB, inputC, inputD);
  }
  else if (digitChar = 5){
    display5(inputA, inputB, inputC, inputD);
  }
  else if (digitChar = 6){
    display6(inputA, inputB, inputC, inputD);
  }
  else if (digitChar = 7){
    display7(inputA, inputB, inputC, inputD);
  }
  else if (digitChar = 8){
    display8(inputA, inputB, inputC, inputD);
  }
  else {
    display9(inputA, inputB, inputC, inputD);
  }
}

//Cycles through each digit in nixie tube to prevent cathode poisoning.
void cathodePoisoning() { //cycle all nixies 0-9
  display0(yrX000A, yrX000B, yrX000C, yrX000D);
  display0(yr0X00A, yr0X00B, yr0X00C, yr0X00D);
  display0(yr00X0A, yr00X0B, yr00X0C, yr00X0D);
  display0(yr000XA, yr000XB, yr000XC, yr000XD);
  display0(hrX0A, hrX0B, hrX0C, hrX0D);
  display0(hr0XA, hr0XB, hr0XC, hr0XD);
  delay(burnTime);

  display1(yrX000A, yrX000B, yrX000C, yrX000D);
  display1(yr0X00A, yr0X00B, yr0X00C, yr0X00D);
  display1(yr00X0A, yr00X0B, yr00X0C, yr00X0D);
  display1(yr000XA, yr000XB, yr000XC, yr000XD);
  display1(hrX0A, hrX0B, hrX0C, hrX0D);
  display1(hr0XA, hr0XB, hr0XC, hr0XD);
  delay(burnTime);

  display2(yrX000A, yrX000B, yrX000C, yrX000D);
  display2(yr0X00A, yr0X00B, yr0X00C, yr0X00D);
  display2(yr00X0A, yr00X0B, yr00X0C, yr00X0D);
  display2(yr000XA, yr000XB, yr000XC, yr000XD);
  display2(hrX0A, hrX0B, hrX0C, hrX0D);
  display2(hr0XA, hr0XB, hr0XC, hr0XD);
  delay(burnTime);

  display3(yrX000A, yrX000B, yrX000C, yrX000D);display5(yr0X00A, yr0X00B, yr0X00C, yr0X00D);
  display5(yr00X0A, yr00X0B, yr00X0C, yr00X0D);
  display5(yr000XA, yr000XB, yr000XC, yr000XD);
  display5(hrX0A, hrX0B, hrX0C, hrX0D);
  display5(hr0XA, hr0XB, hr0XC, hr0XD);
  delay(burnTime);

  display6(yrX000A, yrX000B, yrX000C, yrX000D);
  display6(yr0X00A, yr0X00B, yr0X00C, yr0X00D);
  di
  display3(yr0X00A, yr0X00B, yr0X00C, yr0X00D);
  display3(yr00X0A, yr00X0B, yr00X0C, yr00X0D);
  display3(yr000XA, yr000XB, yr000XC, yr000XD);
  display3(hrX0A, hrX0B, hrX0C, hrX0D);
  display3(hr0XA, hr0XB, hr0XC, hr0XD);
  delay(burnTime);

  display4(yrX000A, yrX000B, yrX000C, yrX000D);
  display4(yr0X00A, yr0X00B, yr0X00C, yr0X00D);
  display4(yr00X0A, yr00X0B, yr00X0C, yr00X0D);
  display4(yr000XA, yr000XB, yr000XC, yr000XD);
  display4(hrX0A, hrX0B, hrX0C, hrX0D);
  display4(hr0XA, hr0XB, hr0XC, hr0XD);
  delay(burnTime);

  display5(yrX000A, yrX000B, yrX000C, yrX000D);
  splay6(yr00X0A, yr00X0B, yr00X0C, yr00X0D);
  display6(yr000XA, yr000XB, yr000XC, yr000XD);
  display6(hrX0A, hrX0B, hrX0C, hrX0D);
  display6(hr0XA, hr0XB, hr0XC, hr0XD);
  delay(burnTime);

  display7(yrX000A, yrX000B, yrX000C, yrX000D);
  display7(yr0X00A, yr0X00B, yr0X00C, yr0X00D);
  display7(yr00X0A, yr00X0B, yr00X0C, yr00X0D);
  display7(yr000XA, yr000XB, yr000XC, yr000XD);
  display7(hrX0A, hrX0B, hrX0C, hrX0D);
  display7(hr0XA, hr0XB, hr0XC, hr0XD);
  delay(burnTime);

  display8(yrX000A, yrX000B, yrX000C, yrX000D);
  display8(yr0X00A, yr0X00B, yr0X00C, yr0X00D);
  display8(yr00X0A, yr00X0B, yr00X0C, yr00X0D);
  display8(yr000XA, yr000XB, yr000XC, yr000XD);
  display8(hrX0A, hrX0B, hrX0C, hrX0D);
  display8(hr0XA, hr0XB, hr0XC, hr0XD);
  delay(burnTime);

  display9(yrX000A, yrX000B, yrX000C, yrX000D);
  display9(yr0X00A, yr0X00B, yr0X00C, yr0X00D);
  display9(yr00X0A, yr00X0B, yr00X0C, yr00X0D);
  display9(yr000XA, yr000XB, yr000XC, yr000XD);
  display9(hrX0A, hrX0B, hrX0C, hrX0D);
  display9(hr0XA, hr0XB, hr0XC, hr0XD);
  delay(burnTime);
}

//The following functions send binary output to nixie drivers.

int display0(int inputA, int inputB, int inputC, int inputD) {
  digitalWrite(inputA, LOW);
  digitalWrite(inputB, LOW);
  digitalWrite(inputC, LOW);
  digitalWrite(inputD, LOW);
}

int display1(int inputA, int inputB, int inputC, int inputD) {
  digitalWrite(inputA, HIGH);
  digitalWrite(inputB, LOW);
  digitalWrite(inputC, LOW);
  digitalWrite(inputD, LOW);
}

int display2(int inputA, int inputB, int inputC, int inputD) {
  digitalWrite(inputA, LOW);
  digitalWrite(inputB, HIGH);
  digitalWrite(inputC, LOW);
  digitalWrite(inputD, LOW);
}

int display3(int inputA, int inputB, int inputC, int inputD) {
  digitalWrite(inputA, HIGH);
  digitalWrite(inputB, HIGH);
  digitalWrite(inputC, LOW);
  digitalWrite(inputD, LOW);
}

int display4(int inputA, int inputB, int inputC, int inputD) {
  digitalWrite(inputA, LOW);
  digitalWrite(inputB, LOW);
  digitalWrite(inputC, HIGH);
  digitalWrite(inputD, LOW);
}

int display5(int inputA, int inputB, int inputC, int inputD) {
  digitalWrite(inputA, HIGH);
  digitalWrite(inputB, LOW);
  digitalWrite(inputC, HIGH);
  digitalWrite(inputD, LOW);
}

int display6(int inputA, int inputB, int inputC, int inputD) {
  digitalWrite(inputA, LOW);
  digitalWrite(inputB, HIGH);
  digitalWrite(inputC, HIGH);
  digitalWrite(inputD, LOW);
}

int display7(int inputA, int inputB, int inputC, int inputD) {
  digitalWrite(inputA, HIGH);
  digitalWrite(inputB, HIGH);
  digitalWrite(inputC, HIGH);
  digitalWrite(inputD, LOW);

int display8(int inputA, int inputB, int inputC, int inputD) {
  digitalWrite(inputA, LOW);
  digitalWrite(inputB, LOW);
  digitalWrite(inputC, LOW);
  digitalWrite(inputD, HIGH);
}

int display9(int inputA, int inputB, int inputC, int inputD) {
  digitalWrite(inputA, HIGH);
  digitalWrite(inputB, LOW);
  digitalWrite(inputC, LOW);
  digitalWrite(inputD, HIGH);
}

void timerReset(){
  lastMotion = millis();
}
