#include <FlexiTimer2.h>  // Contains FlexiTimer2 Library

//======================================CONSTANTS++++++++++++++++++++++++++++++++++++++++++

const byte numTable[] =
{
  B11111100,  //numeral 0
  B01100000,  //numeral 1
  B11011010,  //numeral 2
  B11110010,  //numeral 3
  B01100110,  //numeral 4
  B10110110,  //numeral 5
  B10111110,  //numeral 6
  B11100000,  //numeral 7
  B11111110,  //numeral 8
  B11110110   //numeral 9
};

const byte numTableDP[] =
{
  B11111101,  //numeral 0
  B01100001,  //numeral 1
  B11011011,  //numeral 2
  B11110011,  //numeral 3
  B01100111,  //numeral 4
  B10110111,  //numeral 5
  B10111111,  //numeral 6
  B11100001,  //numeral 7
  B11111111,  //numeral 8
  B11110111   //numeral 9
};

const int _7segCLK = 13;           //Connected to TPIC pin 13: SRCLK (aka Clock)
const int _7segLATCH = 10;          //Connected to TPIC pin 12: RCLK (aka Latch/load/CS/SS...)
const int _7segOE = 9;          //Connected to TPIC pin 9: OE (Output Enable)
const int _7segDOUT = 11;          //Connected to TPIC pin 3: SER (aka MOSI)

int doorPin = 3;            // pin for monitoring room door being closed
int second = 2701;          // Define variable for starting time in seconds

int mins= 0;                // variable for holding minutes
int secs = 0;               // variable for holding seconds
int splitmins1 = 0;         // variable for holding first digits of minutes
int splitmins2 = 0;         // variable for holding second digits of minutes
int splitsecs1 = 0;         // variable for holding first digits of seconds
int splitsecs2 = 0;         // variable for holding second digits of seconds

//======================================VARIABLES++++++++++++++++++++++++++++++

int x, y, z, q = 0;


void setup(){
  pinMode(doorPin, INPUT);
  pinMode(_7segCLK,OUTPUT);
  pinMode(_7segLATCH,OUTPUT);
  pinMode(_7segDOUT, OUTPUT);
  pinMode(_7segOE, OUTPUT);
  clear_7segA();  
  digitalWrite(doorPin, HIGH);       // set door lock monitor pin to high
  //FlexiTimer2::set(1000, timerInt);  // configure the timer and interrupt function
  //FlexiTimer2::start();              // start timer
  Serial.begin(9600);
}


//======================================
void loop(){

  if(digitalRead(doorPin)==LOW){  // while the switch at pin 3 is closed, this will run
    second--;                     // second minus 1
  if (second==0) {              // handling the time out issue
    second = 2701;
  }
  mins = int(second/60);        // minutes as 45, 44, 43...
  secs = int(second % 60);      // seconds of every minute
  splitmins1 = int(mins / 10);  // first digit of minutes
  splitmins2 = int(mins % 10);  // second digit of minutes
  splitsecs1 = int(secs / 10);  // first digit of seconds
  splitsecs2 = int(secs % 10);  // second digit of seconds
  x = splitmins1; // get first digit hexcode from num array
  y = splitmins2; // get second digit hexcode from num array
  z = splitsecs1; // get third digit hexcode from num array
  q = splitsecs2; // get fourth digit hexcode from num array
  }
  else {                          // switch opens, the clock shows the time left at opening
    delay(10);
  }
  send7segs();
  delay(1000);
  }

//======================================


void send7segs(){ 

      digitalWrite(_7segLATCH,LOW);    //Open shift registers for data
      shiftOut(_7segDOUT,_7segCLK,LSBFIRST,numTable[q]);   //send fourth digit
      shiftOut(_7segDOUT,_7segCLK,LSBFIRST,numTable[z]);   //send third digit
      shiftOut(_7segDOUT,_7segCLK,LSBFIRST,numTableDP[y]); //send second digit with dp
      shiftOut(_7segDOUT,_7segCLK,LSBFIRST,numTable[x]);   //send first digit
      digitalWrite(_7segLATCH,HIGH); 
 
  }
  

//========================================

void clear_7segA(){
  //clears the display
  digitalWrite(_7segOE,LOW);        
  digitalWrite(_7segLATCH,LOW);    
  shiftOut(_7segDOUT,_7segCLK,LSBFIRST,0); 
  shiftOut(_7segDOUT,_7segCLK,LSBFIRST,0);
  shiftOut(_7segDOUT,_7segCLK,LSBFIRST,0);
  shiftOut(_7segDOUT,_7segCLK,LSBFIRST,0);
  digitalWrite(_7segLATCH,HIGH);     
 

}
//========================================
