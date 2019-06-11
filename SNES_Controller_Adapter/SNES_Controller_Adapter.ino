 /* SNES Controller Descrete Output Adapter
 * ------------------ 
 * This sketch is designed to decode SNES gamepad
 * signals into descrete outputs for use with arcade 
 * PCBs. 
 * 
 * Appollogies for the sloppy code. It took a lot of trial and error
 * to get everything working properly. There is probably redundant/vestigial
 * code in here left over from the software's original purpose. 
 * 
 * Arthrimus June 10th 2019
 *
 *
 * Based on SNES-controller-Software by Brian Hillman
 *
 *https://github.com/BrianHillman/SNES-controller-Software
*/
 
// Controller buttons
// (based on button-to-clock pulse assignment)
#define SNES_B        32768  // 1000000000000000
#define SNES_Y        16384  // 0100000000000000
#define SNES_SELECT   8192   // 0010000000000000
#define SNES_START    4096   // 0001000000000000
#define SNES_UP       2048   // 0000100000000000
#define SNES_DOWN     1024   // 0000010000000000
#define SNES_LEFT      512   // 0000001000000000
#define SNES_RIGHT     256   // 0000000100000000
#define SNES_A         128   // 0000000010000000
#define SNES_X          64   // 0000000001000000
#define SNES_L          32   // 0000000000100000
#define SNES_R          16   // 0000000000010000
 
// Arduino pins vs. SNES controller pins
// (default is latch 2, clock 3, data 4)
//int LatchPin  = 7; // Latch
//int ClockPin  = 5; // Clock
//int DataPin   = 6; // Serial Data


int LatchPin  = 18; // Latch
int ClockPin  = 15; // Clock
int DataPin   = 19; // Serial Data
int numNs = 0;
int numNs1 = 0;
int UP = 1; // These choose the pins for the button outputs. (Change these-
int DN = 4; // if you wish to remap the buttons.)
int LT = 5;
int RT = 6;
int B = 10;
int A = 13;
int R = 12;
int Y = 7;
int X = 8;
int L = 9;
int SL = 2;
int ST = 11;   
// Current controller data
unsigned int ControllerData = 0;
 
// Setup the controller and serial output
void setup() {
  pinMode(LatchPin,OUTPUT);
  pinMode(ClockPin,OUTPUT);
  pinMode(DataPin,INPUT_PULLUP);
  pinMode(UP, OUTPUT);  // declares buttons as outputs (don't change these)
  pinMode(DN, OUTPUT); 
  pinMode(LT, OUTPUT);
  pinMode(RT, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(Y, OUTPUT);
  pinMode(X, OUTPUT);
  pinMode(L, OUTPUT);
  pinMode(SL, OUTPUT);
  pinMode(ST,OUTPUT);
  digitalWrite(LatchPin,HIGH);
  digitalWrite(ClockPin,HIGH);
  //int LatchPin  = 18; // Latch
//int ClockPin  = 15; // Clock
//int DataPin   = 19; // Serial Data
  
    LatchPin  = 18; // Latch
   ClockPin  = 15; // Clock
   DataPin   = 19; // Serial Data
  
  pinMode(LatchPin,OUTPUT);
  pinMode(ClockPin,OUTPUT);
  pinMode(DataPin,INPUT_PULLUP);
 
  digitalWrite(LatchPin,HIGH);
  digitalWrite(ClockPin,HIGH);

}
 
// Read controller
void controllerRead() {
  // Reset controller states and data
  ControllerData = 0;
  digitalWrite(LatchPin,LOW);
  digitalWrite(ClockPin,HIGH);
 
  // Controller needs to latch the state of all buttons
  digitalWrite(LatchPin,HIGH);
  delayMicroseconds(12);
  digitalWrite(LatchPin,LOW);
  delayMicroseconds(6);
 
  // Read controller data (initial reading)
  ControllerData = digitalRead(DataPin);
 
  // Send 16 clock pulses, one for each button. 
  for (int i = 0; i < 16; i ++) {
    
    digitalWrite(ClockPin,LOW);
    delayMicroseconds(6);
    ControllerData = ControllerData << 1;
    ControllerData = ControllerData + digitalRead(DataPin) ;
    delayMicroseconds(6);
    digitalWrite(ClockPin,HIGH);
  }

  // Do a NOT, so '1' will be pressed buttons and '0' to the rest
 ControllerData = ~ControllerData;

}
 
 




// Program code
void loop() {
  // Read controller data
   LatchPin  = 18; // Latch
   ClockPin  = 15; // Clock
   DataPin   = 19; // Serial Data
   numNs++;

    controllerRead();  
boolean o = ControllerData ==0;
boolean i = ControllerData ==0;
 
  // Write button outputs based on ControllerData
  if (ControllerData != 0) {
    
    numNs= 0;
    if (ControllerData & SNES_B) {
      digitalWrite(B, LOW); // Button output is low
       } else {
      digitalWrite(B, HIGH);   // Button output is High
    }
    if (ControllerData & SNES_Y) {
      digitalWrite(Y, LOW);
      } else {
      digitalWrite(Y, HIGH);
    }
    if (ControllerData & SNES_SELECT) {
      digitalWrite(SL, LOW);
      } else {
      digitalWrite(SL, HIGH);
    }
    if (ControllerData & SNES_START) {
      digitalWrite(ST, LOW);
      } else {
      digitalWrite(ST, HIGH);
    }
    if (ControllerData & SNES_UP) {
      digitalWrite(UP, LOW);
      } else {
      digitalWrite(UP, HIGH);
    }
    if (ControllerData & SNES_DOWN) {
      digitalWrite(DN, LOW);
      } else {
      digitalWrite(DN, HIGH);
    }
    if (ControllerData & SNES_LEFT) {
      digitalWrite(LT, LOW);
      } else {
      digitalWrite(LT, HIGH);
    }
    if (ControllerData & SNES_RIGHT) {
      digitalWrite(RT, LOW);
      } else {
      digitalWrite(RT, HIGH);
    }
    if (ControllerData & SNES_A) {
      digitalWrite(A, LOW);
      } else {
      digitalWrite(A, HIGH);
    }
    if (ControllerData & SNES_X) {
      digitalWrite(X, LOW);
      } else {
      digitalWrite(X, HIGH);
    }
    if (ControllerData & SNES_L) {
      digitalWrite(L, LOW);
      } else {
      digitalWrite(L, HIGH);
    }
    if (ControllerData & SNES_R) {
      digitalWrite(R, LOW);
      } else {
      digitalWrite(R, HIGH);
    }

  }else{

  }
 // Sets all button outputs high if none are pressed. 
 
 if(numNs == 3){
  digitalWrite(R, HIGH);
  digitalWrite(L, HIGH);
  digitalWrite(X, HIGH);
  digitalWrite(A, HIGH);
  digitalWrite(RT, HIGH);
  digitalWrite(LT, HIGH);
  digitalWrite(DN, HIGH);
  digitalWrite(UP, HIGH);
  digitalWrite(ST, HIGH);
  digitalWrite(SL, HIGH);
  digitalWrite(Y, HIGH);
  digitalWrite(B, HIGH);
 }
 
 if(   !i || ControllerData != 0  ){
 }
  delay(10);
}
