/***************************
*
* base 2 clock code for arduino
* Copyleft (C) 2015 Daniel K. Spicer
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
****************************/

// 12 seconds/day  / millisecond
#define INTERVAL_TIME 7494

//seconds to blink on power up prior to time being set. 
//useful to change to ensure new program has been downloaded.
#define BLINK_DELAY 1

//int's representing led's. 1 = on, 0 = off. Initially they will all be off.
int p1,p2,p3,p4,p5,p6,p7,p8 = 0;

// count for timeSetFast n.b. make local
//int count = 0;

// count in 7.5 second increments
int iterations = 0;

boolean time_set = false;

// for timeSetSlow n.b. make local
//unsigned long mils, prev_mils = 0;

// function prototypes
void setTimeSlow();
void setTimeFast();
void resetTimeSetFlags();
void doIncrement();
void lightLights();

void setup(){
  
  //8 led's as outputs.
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  
  //time set 
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);

  attachInterrupt(0, setTimeSlow , LOW); // pin 2
  attachInterrupt(1, setTimeFast , LOW); // pin 3

//  prev_mils = millis();
    
} // end setup()

void loop(){
  if(time_set){ //time has been set, so increment as instructed.
    iterations++;
    if(iterations == 15){ // 2 base2 minutes = 15*7.5 = 112.5 seconds; 1/16 shy of 2 minutes (7.5 seconds)
      iterations = 0;
      doIncrement(); 
    }  
    delay(INTERVAL_TIME);
 } else { // time has never been set so just blink the lights.
    if(p8 == 0)
      p8 = p7 = p6 = p5 = p4 = p3 = p2 = p1 = 1;
    else	
      p8 = p7 = p6 = p5 = p4 = p3 = p2 = p1 = 0;

    lightLights();
    delay(1000 * BLINK_DELAY);
 }
} // end loop()

void setTimeSlow(){
  unsigned long mils, prev_mils;  
  
  resetTimeSetFlags();
  mils = millis();
  if(mils - prev_mils > 50)
    doIncrement();
  prev_mils = mils; 
}

void setTimeFast(){
  int count;
  
  resetTimeSetFlags(); 
  count++;
  if(count > 5000){
    count = 0;
    doIncrement();
  } 
}

void resetTimeSetFlags(){
  time_set = true;
  iterations = 0;
}

void doIncrement(){

  if(p8 == 0){
    p8 = 1;
  } 
  else if (p7 == 0){
    p7 = 1;
    p8 = 0;
  } 
  else if (p6 == 0){
    p6 = 1;
    p8 = p7 = 0;
  } 
  else if (p5 == 0){
    p5 = 1;
    p8 = p7 = p6 = 0;
  } 
  else if (p4 == 0){
    p4 = 1;
    p8 = p7 = p6 = p5 = 0;
  } 
  else if (p3 == 0){
    p3 = 1;
    p8 = p7 = p6 = p5 = p4 = 0;
  } 
  else if (p2 == 0){
    p2 = 1;
    p8 = p7 = p6 = p5 = p4 = p3 = 0;
  } 
  else if (p1 == 0){
    p1 = 1;
    p8 = p7 = p6 = p5 = p4 = p3 = p2 = 0;
  } 
  else { // all lights were lit, so this increment resets them to all off
    p8 = p7 = p6 = p5 = p4 = p3 = p2 = p1 = 0;
  }

  lightLights();
} // end doIncrement()


void lightLights() {
    if(p1 == 1)
      digitalWrite(13, HIGH);
    else	
      digitalWrite(13, LOW);
    if(p2 == 1)
      digitalWrite(12, HIGH);
    else	
      digitalWrite(12, LOW);
    if(p3 == 1)
      digitalWrite(11, HIGH);
    else	
      digitalWrite(11, LOW);
    if(p4 == 1)
      digitalWrite(10, HIGH);
    else	
      digitalWrite(10, LOW);
    if(p5 == 1)
      digitalWrite(9, HIGH);
    else	
      digitalWrite(9, LOW);
    if(p6 == 1)
      digitalWrite(8, HIGH);
    else	
      digitalWrite(8, LOW);
    if(p7 == 1)
      digitalWrite(7, HIGH);
    else	
      digitalWrite(7, LOW);
    if(p8 == 1)
      digitalWrite(6, HIGH);
    else	
      digitalWrite(6, LOW);

} // end lightLights()
