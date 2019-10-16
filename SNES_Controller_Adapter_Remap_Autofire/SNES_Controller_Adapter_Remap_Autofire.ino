
#include <EEPROM.h>
    
//SNES Pins (Arduino)
int DATA_CLOCK    = 15;
int DATA_LATCH    = 18;
int DATA_SERIAL  = 19;
//Buttonpress Status Variables
int UP = 0;                      // Sets up button press variables.
int DN = 0; 
int LT = 0;
int RT = 0;
int A = 0;
int B = 0;
int X = 0;
int Y = 0;
int L = 0;
int R = 0;
int ST = 0;   
int SL = 0;
// General Variables
int val = 0;                     // variable for reading the pin status (should be zero)
int outputb = 0;                 // variable for storing PORTB output values.
int outputd = 0;                 // variable for storing PORTD output values.
int buttonmap = 0;               // variable for storing which buttonmap is used for outputs, 0 = sixbuttonmode.
int remapcount = 0;              // variable for storing the count for the button combo timer
int remapcombo = 0;              // variable for storing the button combo state
int bfcount = 0;
int bfcount1 = 0;
int autofire = 0;
int autofirecombo = 0;
int autofirecount = 0;
int autofiretimer1 = 0;
int autofiretimer2 = 0;
int autofiretimer3 = 0;
int autofiretimer4 = 0;
int autofiretimer5 = 0;
int autofiretimer6 = 0;
int combodelay = 160;             // variable for storing the number of cycles for the combo timer
int combodelay2 = 220;           // variable for storing the number of cycles for combo timer 2
int NB = 0;                      // variable for storing the number of face buttons pressed simultaniously.
int brookfix = 1;
//Buttonmap Values
int YO = 1;                      // Stores the current output map for each input
int XO = 2;
int LO = 3;
int BO = 4;
int AO = 5;
int RO = 6;
//Autofire Values
int XA = 0;                      // Stores the current autofire setting for each input
int YA = 0;
int LA = 0;
int AA = 0;
int BA = 0;
int RA = 0;
// Previous Buttonpress Variables
int XP = 0;                     // Stores the previous state of each button
int YP = 0;
int LP = 0;
int AP = 0;
int BP = 0;
int RP = 0;
int STP = 0;
int SLP = 0;
int UPP = 0;
int DNP = 0;
int LTP = 0;
int RTP = 0;
// Current Buttonpress Variables
int XC = 0;                    // Stores the current state of each button
int YC = 0;
int LC = 0;
int AC = 0;
int BC = 0;
int RC = 0;
int STC = 0;
int SLC = 0;
int UPC = 0;
int DNC = 0;
int LTC = 0;
int RTC = 0;

int buttons[12];

void setup(){
  setupPins();
XO = EEPROM.read(0);
YO = EEPROM.read(1);
LO = EEPROM.read(2);
AO = EEPROM.read(3);
BO = EEPROM.read(4);
RO = EEPROM.read(5);
brookfix = EEPROM.read(6);
XA = EEPROM.read(7);
YA = EEPROM.read(8);
LA = EEPROM.read(9);
AA = EEPROM.read(10);
BA = EEPROM.read(11);
RA = EEPROM.read(12);
}

void loop(){
  scaninputs();
  translatepad(); 
  buttoncombos();
if (brookfix == 1){
    brookfixmode();
  }
if (buttonmap == 1){             // Stores output data for PORTB and PORTD based on sixbutton map.
  autofire = 0;
  buttonmapping();
}else if (autofire == 1){
  autofiremapping();
}else{
  setautofire();
  setoutputs(); 
  }
  DDRB = outputb;                // Sets PORTB and PORTD outputs based on inputs and the chosen buttonmap.
  DDRD = outputd;
}

void setautofire(){
autofiretimer1 = (autofiretimer1 + 1);
autofiretimer2 = (autofiretimer2 + 1);
autofiretimer3 = (autofiretimer3 + 1);
autofiretimer4 = (autofiretimer4 + 1);
autofiretimer5 = (autofiretimer5 + 1);
autofiretimer6 = (autofiretimer6 + 1);

if (autofiretimer1 > 1){
  autofiretimer1 = 0; 
}
if (autofiretimer2 > 2){
  autofiretimer2 = 0; 
}
if (autofiretimer3 > 3){
  autofiretimer3 = 0; 
}
if (autofiretimer4 > 5){
  autofiretimer4 = 0; 
}
if (autofiretimer5 > 7){
  autofiretimer5 = 0; 
}
if (autofiretimer6 > 9){
  autofiretimer6 = 0; 
}

if ((XA == 1 && autofiretimer1 < 1) || (XA == 2 && autofiretimer2 < 2) || (XA == 3 && autofiretimer3 < 2) || (XA == 4 && autofiretimer4 < 3) || (XA == 5 && autofiretimer5 < 6) || (XA == 6 && autofiretimer6 < 8)){
    X = 0;     
  }
if ((YA == 1 && autofiretimer1 < 1) || (YA == 2 && autofiretimer2 < 2) || (YA == 3 && autofiretimer3 < 2) || (YA == 4 && autofiretimer4 < 3) || (YA == 5 && autofiretimer5 < 6) || (YA == 6 && autofiretimer6 < 8)){
    Y = 0;     
  }
if ((LA == 1 && autofiretimer1 < 1) || (LA == 2 && autofiretimer2 < 2) || (LA == 3 && autofiretimer3 < 2) || (LA == 4 && autofiretimer4 < 3) || (LA == 5 && autofiretimer5 < 6) || (LA == 6 && autofiretimer6 < 8)){
    L = 0;     
  }  
if ((AA == 1 && autofiretimer1 < 1) || (AA == 2 && autofiretimer2 < 2) || (AA == 3 && autofiretimer3 < 2) || (AA == 4 && autofiretimer4 < 3) || (AA == 5 && autofiretimer5 < 6) || (AA == 6 && autofiretimer6 < 8)){
    A = 0;     
  }
if ((BA == 1 && autofiretimer1 < 1) || (BA == 2 && autofiretimer2 < 2) || (BA == 3 && autofiretimer3 < 2) || (BA == 4 && autofiretimer4 < 3) || (BA == 5 && autofiretimer5 < 6) || (BA == 6 && autofiretimer6 < 8)){
    B = 0;     
  }
if ((RA == 1 && autofiretimer1 < 1) || (RA == 2 && autofiretimer2 < 2) || (RA == 3 && autofiretimer3 < 2) || (RA == 4 && autofiretimer4 < 3) || (RA == 5 && autofiretimer5 < 6) || (RA == 6 && autofiretimer6 < 8)){
    R = 0;     
  }
}


void setupPins(void){
 
  // Set DATA_CLOCK normally HIGH
  pinMode(DATA_CLOCK, OUTPUT);
  digitalWrite(DATA_CLOCK, HIGH);
  
  // Set DATA_LATCH normally LOW
  pinMode(DATA_LATCH, OUTPUT);
  digitalWrite(DATA_LATCH, LOW);

  pinMode(DATA_SERIAL, INPUT_PULLUP);  
}

void scaninputs(void){
    // Latch for 12us
    delay(15);
    delayMicroseconds(450);
    digitalWrite(DATA_LATCH, HIGH);
    delayMicroseconds(11);
    digitalWrite(DATA_LATCH, LOW);
    delayMicroseconds(6);
    
    // Retrieve button presses from shift register by pulling the clock high for 6us
    for(int i = 0; i < 16; i++){
        digitalWrite(DATA_CLOCK, LOW);
        delayMicroseconds(6);
        if(i <= 11){
            buttons[i] = digitalRead(DATA_SERIAL);
        }
        digitalWrite(DATA_CLOCK, HIGH);
            delayMicroseconds(6);
    }
}

// Prints which buttons are pressed
void translatepad(void){
  // New Previous State 
XP = XC;                      // new previous state variables = old current state variables
YP = YC;
RP = RC;
AP = AC;
BP = BC;
LP = LC;
STP = STC;
SLP = SLC;
UPP = UPC;
DNP = DNC;
LTP = LTC;
RTP = RTC;
// Reset All Variables
outputb = 0;                   // Resets Port Maniplulation Variables
outputd = 0;
UP = 0;                        // Resets all button state variables
DN = 0;
LT = 0;
RT = 0;
SL = 0;
ST = 0;
NB = 0;
STC = 0;
SLC = 0;
UPC = 0;
DNC = 0;
LTC = 0;
RTC = 0;
XC = 0;
YC = 0;
LC = 0;
AC = 0;
BC = 0;
RC = 0;
X = 0;
Y = 0;
L = 0;
A = 0;
B = 0;
R = 0;

    if(buttons[0] == 0){
  B = BO;                        // Stores the B button as pressed.
  BC = 1;                     
  }
    if(buttons[1] == 0){
  Y = YO;                       
  YC = 1;                     
  }
    if(buttons[2] == 0){
  SL = 1;     
  SLC = 1;                                       
  }
    if(buttons[3] == 0){                       
  ST = 1;    
  STC = 1;                 
  }
    if(buttons[4] == 0){
  UP = 1; 
  UPC = 1;                    
  }
    if(buttons[5] == 0){
  DN = 1; 
  DNC = 1;                    
  }
    if(buttons[6] == 0){
  LT = 1; 
  LTC = 1;                    
  }
    if(buttons[7] == 0){
  RT = 1; 
  RTC = 1;                    
  }
    if(buttons[8] == 0){
  A = AO;                       
  AC = 1;                     
    }
    if(buttons[9] == 0){
  X = XO;                       
  XC = 1;                     
  }
    if(buttons[10] == 0){
  L = LO;                       
  LC = 1;                     
  }
    if(buttons[11] == 0){
  R = RO;                       
  RC = 1;                     
  }
  NB = (XC + YC + LC + AC + BC + RC);
}

void setoutputs(){           // Translates demuxpad data into the sixbutton output map.

if (Y == 2 || X == 2 || L == 2 || A == 2 || B == 2 || R == 2) 
  outputb |= 1;                    
if (L == 3 || Y == 3 || X == 3 || A == 3 || B == 3 || R == 3)
  outputb |= 2; 
if (A == 4 || Y == 4 || X == 4 || L == 4 || B == 4 || R == 4)
  outputb |= 4;    
if (ST == 1) 
  outputb |= 8;
if (R == 6 || Y == 6 || X == 6 || L == 6 || A == 6 || B == 6)
  outputb |= 16;
if (B == 5 || Y == 5 || X == 5 || L == 5 || A == 5 || R == 5) 
  outputb |= 32;    
if (UP == 1)
  outputd |= 2;                    
if (SL == 1)
  outputd |= 4;
if (DN == 1)
  outputd |= 16;           
if (LT == 1)   
  outputd |= 32;
if (RT == 1)
  outputd |= 64;
if (X == 1 || Y == 1 || L == 1 || A == 1 || B == 1 || R == 1) 
  outputd |= 128;    
}

void buttoncombos(){
if (ST == 1 && (NB == 2 && (STP == 1))){        // Checks if Start and 2 buttons are pressed. 
  remapcount = (remapcount + 1);
}else{ 
  remapcount = 0;
}

if (remapcount >= combodelay){
remapcount = 0;
buttonmap = 1;                // Sets buttonmap mode to 1 
 }

if (ST == 1 && (NB == 1 && (STP == 1))){        // Checks if Start and 2 buttons are pressed. 
  autofirecount = (autofirecount + 1);
}else{ 
  autofirecount = 0;
}

if (autofirecount >= combodelay){
autofirecount = 0;
autofire = 1;                // Sets autofire mode to 1 
 }
if (ST == 1 && (NB == 6 && (STP == 1))){
  bfcount = (bfcount + 1);
}else{ bfcount = 0;
}
if (ST == 1 && (NB == 5 && (STP == 1))){
  bfcount1 = (bfcount1 + 1);
}else{ bfcount1 = 0;
}

if (bfcount >= combodelay){
  bfcount = 0;
  brookfix = 0;
  EEPROM.write(6,brookfix);
  }
if (bfcount1 >= combodelay){
  bfcount1 = 0;
  brookfix = 1; 
  EEPROM.write(6,brookfix);
  
  }
}


void buttonmapping(){
if (ST == 1 && (NB == 2)){                        // Checks if the buttonmap combo is still held. 
 XO = 0;                                          // Resets all buttonmap values to 0
 YO = 0;
 LO = 0;
 AO = 0;
 BO = 0;
 RO = 0;
}else{                                                       // If buttonmap combo is no longer pressed, continue to button mapping mode
if (XC == 1 && (XP == 0 && (NB == 1))){            // If X is currently pressed, if X was previously not pressed, if only one button (X) is pressed and if XO is less than 6
  XO = (XO + 1);                                             // If all of the above conditions are met, XO is iterated +1
}
if (XO > 6){                                       // If XO is greater than 6, XO is reset to 0
  XO = 0;
}
if (YC == 1 && (YP == 0 && (NB == 1))){
  YO = (YO + 1);
}
if (YO > 6){
  YO = 0;
}
if (LC == 1 && (LP == 0 && (NB == 1))){
  LO = (LO + 1);
}
if (LO > 6){
  LO = 0;
}
if (AC == 1 && (AP == 0 && (NB == 1))){
  AO = (AO + 1);
}
if (AO > 6){
  AO = 0;
}
if (BC == 1 && (BP == 0 && (NB == 1))){
  BO = (BO + 1);
}
if (BO > 6){
  BO = 0;
}
if (RC == 1 && (RP == 0 && (NB == 1))){
  RO = (RO + 1);
}
if (RO > 6){
  RO = 0;
  }
if (ST == 1 && (STP == 0)){
    buttonmap = 0;
    EEPROM.write(0,XO);
    EEPROM.write(1,YO);
    EEPROM.write(2,LO);
    EEPROM.write(3,AO);
    EEPROM.write(4,BO);
    EEPROM.write(5,RO);
    
  } 
 }
}

void autofiremapping(){
if (ST == 1 && (NB == 1)){                        // Checks if the buttonmap combo is still held. 
 XA = 0;                                          // Resets all buttonmap values to 0
 YA = 0;
 LA = 0;
 AA = 0;
 BA = 0;
 RA = 0;
}else{                                                       // If buttonmap combo is no longer pressed, continue to button mapping mode
if (XC == 1 && (XP == 0 && (NB == 1))){            // If X is currently pressed, if X was previously not pressed, if only one button (X) is pressed and if XO is less than 6
  XA = (XA + 1);                                             // If all of the above conditions are met, XO is iterated +1
}
if (XA > 6){                                       // If XO is greater than 6, XO is reset to 0
  XA = 0;
}
if (YC == 1 && (YP == 0 && (NB == 1))){
  YA = (YA + 1);
}
if (YA > 6){
  YA = 0;
}
if (LC == 1 && (LP == 0 && (NB == 1))){
  LA = (LA + 1);
}
if (LA > 6){
  LA = 0;
}
if (AC == 1 && (AP == 0 && (NB == 1))){
  AA = (AA + 1);
}
if (AA > 6){
  AA = 0;
}
if (BC == 1 && (BP == 0 && (NB == 1))){
  BA = (BA + 1);
}
if (BA > 6){
  BA = 0;
}
if (RC == 1 && (RP == 0 && (NB == 1))){
  RA = (RA + 1);
}
if (RA > 6){
  RA = 0;
  }
if (ST == 1 && (STP == 0)){
    autofire = 0;
    EEPROM.write(7,XA);
    EEPROM.write(8,YA);
    EEPROM.write(9,LA);
    EEPROM.write(10,AA);
    EEPROM.write(11,BA);
    EEPROM.write(12,RA);
    
  } 
 }
}

void brookfixmode(){
  if (BC == 0 && BP == 1){
    B = BO;
  }
    if (AC == 0 && AP == 1){
    A = AO;
  }
    if (XC == 0 && XP == 1){
    X = XO;
  }
    if (YC == 0 && YP == 1){
    Y = YO;
  }
    if (LC == 0 && LP == 1){
    L = LO;
  }
    if (RC == 0 && RP == 1){
    R = RO;
  }
    if (STC == 0 && STP == 1){
    ST = STP;
  }
    if (SLC == 0 && SLP == 1){
    SL = SLP;
  }
      if (UPC == 0 && UPP == 1){
    UP = UPP;
  }
      if (DNC == 0 && DNP == 1){
    DN = DNP;
  }
      if (LTC == 0 && LTP == 1){
    LT = LTP;
  }
      if (RTC == 0 && RTP == 1){
    RT = RTP;
  }
}
