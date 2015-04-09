/***************************
 * 
 * 	base 2 clock code for arduino
 * 	Copyleft (C) 2015  Daniel K. Spicer
 * 
 * 	This program is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 * 
 * 	This program is distributed in the hope that it will be useful,
 * 	but WITHOUT ANY WARRANTY; without even the implied warranty of
 * 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * 	GNU General Public License for more details.
 * 
 * 	You should have received a copy of the GNU General Public License
 * 	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 ****************************/

// adjust this value to tune the clock. 5000 should be close, lower if clock runs slow, higher if fast.
#define INTERVAL_TIME 4900

//int's representing led's. 1 = on, 0 = off. Initially they will all be off.
int p1,p2,p3,p4,p5,p6,p7,p8,p9 = 0;

int iterations = 0;
boolean increment, reset_fast, reset_slow, time_set = false;

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

  //2 time set buttons as inputs.
  pinMode(5, INPUT); 
  digitalWrite(5, HIGH);
  pinMode(4, INPUT); 
  digitalWrite(4, HIGH);
} // end setup()

void loop(){

  //reinitialize time setting booleans to false.
  reset_fast = false;
  reset_slow = false;

  //see if the time is being set. 
  if(digitalRead(5) == LOW){
    reset_slow = true;
    increment = true;
    time_set = true;
  } else if(digitalRead(4) == LOW){
      reset_fast = true;
      increment = true;
      time_set = true;
    }  

  if(!time_set){ // time has never been set so just blink the lights.
    if(p8 == 1)
      p8 = p7 = p6 = p5 = p4 = p3 = p2 = p1 = 0;
    else	
      p8 = p7 = p6 = p5 = p4 = p3 = p2 = p1 = 1;
  } else { //time has been set, so increment as instructed.
    iterations += 1;
    if(iterations == 12){
      iterations = 0;
      increment = true;
    }
    if(increment) doIncrement();
  } //end time_set is true

  //light the appropriate lights
  lightLights();

  // figure out the loop delay, typically 5 seconds, 1 second if the time has never been set
  // and we are blinking the lights, 0.07 seconds if we are coarse setting the time and 0.7 seconds
  // if we are fine setting the time.
  if(reset_fast){
    delay(70);
    iterations = 0;
  } else if(reset_slow){
      delay(700);
      iterations = 0;
    } else if(!time_set) {
        delay(1000);
      } else delay(INTERVAL_TIME);
} // end loop()

void doIncrement(){
  increment = false;
  if(p9 == 0){
    if(p8 == 1 && p7 == 1 && p6 == 1){
      p8 = p7 = p6 = 0;
      
      // p8, p7, and p6 were all 1, so now see if any lights are zero and set them to 1,
      // otherwise, set all lights to zero.
      switch(1) {
        case 1:
          if(p5 == 0){
            p5 = 1;
            break;
          } 
        case 2:
          if(p4 == 0){
            p4 = 1;
            p5 = 0;
            break;
          } 
        case 3:
          if(p3 == 0){
            p3 = 1;
            p4 = p5 = 0;
            break;
          } 
        case 4:
          if(p2 == 0){
            p2 = 1;
            p3 = p4 = p5 = 0;
            break;
          } 
        case 5:
          if(p1 == 0) {
            p1 = 1;
            p2 = p3 = p4 = p5 = 0;
            break;
          } 
        default: // all lights were lit, so this increment resets them to all off  
          p1 = p2 = p3 = p4 = p5 = 0;
      } // end switch
      
    } else { // p9 is zero, and so is either p8, p7, or p6, so set p9 to 1.
      p9 = 1;
    }  
  } else { // p9 equals 1, so either p8, p7, or p6 must be zero.
    p9 = 0;
    if(p8 == 0){
      p8 = 1;
    } else if(p7 == 0){
        p7 = 1;
        p8 = 0;
      } else { // p6 must be zero
        p6 = 1;
        p7 = p8 = 0;
      }  
  } // end p9 equals 1  		
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
