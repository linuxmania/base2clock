/***************************
+
+Copyleft [2014] [Daniel Spicer]
+
+Licensed under the Apache License, Version 2.0 (the "License");
+you may not use this file except in compliance with the License.
+You may obtain a copy of the License at
+
+ http://www.apache.org/licenses/LICENSE-2.0
+
+Unless required by applicable law or agreed to in writing, software
+distributed under the License is distributed on an "AS IS" BASIS,
+WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
+See the License for the specific language governing permissions and
+limitations under the License.
+
+****************************/


//adjust fudge factor and offset to tune the arduino.

//slow float fudge_factor = 1.001;
//slightly fast float fudge_factor = 1.0012;
//very slightly fast float fudge_factor = 1.0011;
// became too fast over time float fudge_factor = 1.00107;
// slow float fudge_factor = 1.0006;
// slow float fudge_factor = 1.0008;
float fudge_factor = 1.00095;
int offset = 15;

unsigned long prev_mils,mil,sec,mins,hr,reset_mil = 0;

//initially set hours to zero and minutes to zero.
int hr_init = 0;
int min_init = 0;

//int's representing led's. 1 = on, 0 = off. Initially they will all be off.
int p1,p2,p3,p4,p5,p6,p7,p8 = 0;

//booleans for time setting purposes.
boolean time_set,reset_slow,reset_fast = false;

//call this function if a time set button is pressed.
void reset_init(){
  reset_mil = mil;

  hr_init = 0;
  min_init = 2;
  
  if(time_set){  
    //use current time setting as new initial values.
    if(p1 == 1) hr_init = 4;
    if(p2 == 1) hr_init += 2;
    if(p3 == 1) hr_init += 1;
    if(p4 == 1) min_init += 30;
    if(p5 == 1) min_init += 15;
    if(p6 == 1) min_init += 8;
    if(p7 == 1) min_init += 4;
    if(p8 == 1) min_init += 2;
    
    if(p6 == 1 && p7 == 1 && p8 == 1)
      min_init -= 1;
  }  
  else time_set = true;  
}

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
  pinMode(5, INPUT); digitalWrite(5, HIGH);
  pinMode(4, INPUT); digitalWrite(4, HIGH);
  
} // end setup()

void loop(){
  //reinitialize time setting booleans to false.
  reset_fast = false;
  reset_slow = false;

  //get the time that the program has been running, to calculate time.
  mil = millis();
  
  //add this to determine if mil has counted 50 days and has reset.
  if(prev_mils != 0){
    if(prev_mils > mil){
      time_set = false;
    }  
  }  
  prev_mils = mil;
 
  //see if the time is being set. 
  if(digitalRead(5) == LOW){
    reset_slow = true;
    reset_init();    
  }  else {
    if(digitalRead(4) == LOW){
      reset_fast = true;
      reset_init();    
    }  
  }

  //if the time has not been set since the last power cycle
  //or mil has counted over 50 days and reset, just keep blinking all
  //the lights till the time is set.
  if(!time_set){
    if(p1 == 1){
      digitalWrite(13, LOW);   
      p1=0;   
      digitalWrite(12, LOW);   
      p2=0;   
      digitalWrite(11, LOW);   
      p3=0;   
      digitalWrite(10, LOW);   
      p4=0;   
      digitalWrite(9, LOW);   
      p5=0;   
      digitalWrite(8, LOW);   
      p6=0;   
      digitalWrite(7, LOW);   
      p7=0;   
      digitalWrite(6, LOW);   
      p8=0;   
    }else{
      digitalWrite(13, HIGH);   
      p1=1;   
      digitalWrite(12, HIGH);   
      p2=1;   
      digitalWrite(11, HIGH);   
      p3=1;   
      digitalWrite(10, HIGH);   
      p4=1;   
      digitalWrite(9, HIGH);   
      p5=1;   
      digitalWrite(8, HIGH);   
      p6=1;   
      digitalWrite(7, HIGH);   
      p7=1;   
      digitalWrite(6, HIGH);   
      p8=1;   
    }   
  //else everything is copasetic, display the time
  }else{

    //subtract lapsed time since last occasion that the time was set.    
    mil -= reset_mil;
  
    // TUNE your arduino
    sec = (mil/1000 * fudge_factor) + offset;
  
    //calculate values for hours and minutes.  
    mins = sec/60;
    mins += min_init;
    hr = mins/60;
    mins -= (hr*60);
    hr += hr_init;
    hr = hr%8;

    //figure out which led's to light and unlight.
    if(hr >= 4){
      if(p1 != 1){
        digitalWrite(13, HIGH);   
        p1=1;   
      }  
      hr -= 4;
    } else {
      if(p1 != 0){
        digitalWrite(13, LOW);   
        p1=0;   
      }  
    }	
  
    if(hr >= 2){
      if(p2 != 1){
        digitalWrite(12, HIGH);
        p2=1;   
      }  
      hr -= 2;
    } else {
      if(p2 != 0){
        digitalWrite(12, LOW);   
        p2=0;   
      }  
    }	
  
    if(hr == 1){
      if(p3 != 1){
        digitalWrite(11, HIGH);
        p3=1;   
      }  
    } else {
      if(p3 != 0){
        digitalWrite(11, LOW);   
        p3=0;   
      }  
    }	
  
    if(mins >= 30){
      if(p4 != 1){
        digitalWrite(10, HIGH);
        p4=1;   
      }  
      mins -= 30;
    } else {
      if(p4 != 0){
        digitalWrite(10, LOW);   
        p4=0;   
      }  
    }	
  
    if(mins >= 15){
      if(p5 != 1){
        digitalWrite(9, HIGH);
        p5=1;   
      }  
      mins -= 15;
    } else {
      if(p5 != 0){
        digitalWrite(9, LOW);   
        p5=0;   
      }  
    }	
  
    if(mins >= 8){
      if(p6 != 1){
        digitalWrite(8, HIGH);
        p6=1;   
      }  
      mins -= 8;
    } else {
      if(p6 != 0){
        digitalWrite(8, LOW);   
        p6=0;   
      }  
    }	
  
    if(mins >= 4){
      if(p7 != 1){
        digitalWrite(7, HIGH);
        p7=1;   
      }  
      mins -= 4;
    } else {
      if(p7 != 0){
        digitalWrite(7, LOW);   
        p7=0;   
      }  
    }	
  
    if(mins >= 2){
      if(p8 != 1){
        digitalWrite(6, HIGH);
        p8=1;   
      }  
    } else {
      if(p8 != 0){
        digitalWrite(6, LOW);   
        p8=0;   
      }  
    }		

  }//end else (!time_set)
  
  // wait 5 seconds, 1 second if reset slow button is pressed or time has not been set yet, 
  // 0.1 seconds if reset fast button is pressed.
  if(reset_fast){
    delay(100);
  }else{
    if(reset_slow || !time_set){
      delay(1000);
    }else{
      delay(5000);
    }  
  }    
  
} //end loop()
