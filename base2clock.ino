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

// adjust this value to tune the clock. 10,000 should be close, lower if clock runs slow, higher if fast.
// #define INTERVAL_TIME 9991 slightly slow
// #define INTERVAL_TIME 9990 very slightly slow

#define INTERVAL_TIME 9995

// fine tune here after establishing an INTERVAL_TIME which is slighly slow and if you decrease by one it
// will be fast. The higher this number the faster. If 99 is still too slow, drop INTERVAL_TIME by one. 

// #define PERCENT_FASTER 10

//seconds to blink on power up prior
//to time being set. useful to ensure
//new program has been downloaded.
#define BLINK_DELAY 1

//int's representing led's. 1 = on, 0 = off. Initially they will all be off.
int p1,p2,p3,p4,p5,p6,p7,p8 = 0;
int iterations, count, time_count = 0;
// int interval_time = INTERVAL_TIME;
boolean time_set, increment_flg = false;
unsigned long mils, prev_mils = 0;
// boolean hasP1changed, hasP2changed, hasP3changed ,  hasP4changed, hasP5changed, hasP6changed, hasP7changed, hasP8changed =  false;

// function prototypes
void setTimeSlow();
void setTimeFast();
void resetTimeSetFlags();
boolean setIncrementFlag();
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
  
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);

  attachInterrupt(0, setTimeSlow , LOW); // pin 2
  attachInterrupt(1, setTimeFast , LOW); // pin 3

  prev_mils = millis();
    
} // end setup()

void loop(){
  if(time_set){ //time has been set, so increment as instructed.
/*
    time_count++;
    if(time_count == 1000 - (10*PERCENT_FASTER)){
     if(interval_time == INTERVAL_TIME)
       interval_time -= 1;
    }
    if(time_count >= 1000){
     time_count = 0;
     interval_time = INTERVAL_TIME;
    }
*/
    iterations++;
    if(iterations == 6){
      iterations = 0;
      if(!setIncrementFlag()) 
        doIncrement(); 
    }
    delay(INTERVAL_TIME);
 } else { // time has never been set so just blink the lights.
    if(p8 == 0)
      p8 = p7 = p6 = p5 = p4 = p3 = p2 = p1 = 1;
    else	
      p8 = p7 = p6 = p5 = p4 = p3 = p2 = p1 = 0;

 //   hasP1changed = hasP2changed = hasP3changed  =  hasP4changed = hasP5changed = hasP6changed = hasP7changed = hasP8changed =  true;
    lightLights();
    delay(1000 * BLINK_DELAY);
 }
} // end loop()

void setTimeSlow(){
  resetTimeSetFlags();
  mils = millis();
  if(mils - prev_mils > 50)
    doIncrement();
  prev_mils = mils; 
}

void setTimeFast(){
  resetTimeSetFlags(); 
  count++;
  if(count > 5000){
    count = 0;
    doIncrement();
  } 
}

void resetTimeSetFlags(){
  time_set = true;
  time_count = 0;
  iterations = 0;
  increment_flg = false;
}

boolean setIncrementFlag(){
  if(increment_flg == false && (p8 == 0 || p7 == 0 || p6 == 0)){
    increment_flg = true;
    return true;
  }
  return false;
}

void doIncrement(){
  increment_flg = false;

  if(p8 == 0){
    p8 = 1;
//    hasP8changed =  true;
  } 
  else if (p7 == 0){
    p7 = 1;
    p8 = 0;
//    hasP7changed = hasP8changed =  true;
  } 
  else if (p6 == 0){
    p6 = 1;
    p8 = p7 = 0;
//    hasP6changed = hasP7changed = hasP8changed =  true;
  } 
  else if (p5 == 0){
    p5 = 1;
    p8 = p7 = p6 = 0;
//    hasP5changed = hasP6changed = hasP7changed = hasP8changed =  true;
  } 
  else if (p4 == 0){
    p4 = 1;
    p8 = p7 = p6 = p5 = 0;
//    hasP4changed = hasP5changed = hasP6changed = hasP7changed = hasP8changed =  true;
  } 
  else if (p3 == 0){
    p3 = 1;
    p8 = p7 = p6 = p5 = p4 = 0;
//    hasP3changed  =  hasP4changed = hasP5changed = hasP6changed = hasP7changed = hasP8changed =  true;
  } 
  else if (p2 == 0){
    p2 = 1;
    p8 = p7 = p6 = p5 = p4 = p3 = 0;
//    hasP2changed = hasP3changed  =  hasP4changed = hasP5changed = hasP6changed = hasP7changed = hasP8changed =  true;
  } 
  else if (p1 == 0){
    p1 = 1;
    p8 = p7 = p6 = p5 = p4 = p3 = p2 = 0;
//    hasP1changed = hasP2changed = hasP3changed  =  hasP4changed = hasP5changed = hasP6changed = hasP7changed = hasP8changed =  true;
  } 
  else { // all lights were lit, so this increment resets them to all off
    p8 = p7 = p6 = p5 = p4 = p3 = p2 = p1 = 0;
//    hasP1changed = hasP2changed = hasP3changed  =  hasP4changed = hasP5changed = hasP6changed = hasP7changed = hasP8changed =  true;
  }

  lightLights();
} // end doIncrement()


void lightLights() {
//  if(hasP1changed){
    if(p1 == 1)
      digitalWrite(13, HIGH);
    else	
      digitalWrite(13, LOW);
//  }  
//  if(hasP2changed){
    if(p2 == 1)
      digitalWrite(12, HIGH);
    else	
      digitalWrite(12, LOW);
//  }
//  if(hasP3changed){
    if(p3 == 1)
      digitalWrite(11, HIGH);
    else	
      digitalWrite(11, LOW);
//  }
//  if(hasP4changed){
    if(p4 == 1)
      digitalWrite(10, HIGH);
    else	
      digitalWrite(10, LOW);
//  }
//  if(hasP5changed){
    if(p5 == 1)
      digitalWrite(9, HIGH);
    else	
      digitalWrite(9, LOW);
//  }
//  if(hasP6changed){
    if(p6 == 1)
      digitalWrite(8, HIGH);
    else	
      digitalWrite(8, LOW);
//  }
//  if(hasP7changed){
    if(p7 == 1)
      digitalWrite(7, HIGH);
    else	
      digitalWrite(7, LOW);
//  }
//  if(hasP8changed){
    if(p8 == 1)
      digitalWrite(6, HIGH);
    else	
      digitalWrite(6, LOW);
//  }  

//  hasP1changed = hasP2changed = hasP3changed  =  hasP4changed = hasP5changed = hasP6changed = hasP7changed = hasP8changed =  false;
} // end lightLights()
