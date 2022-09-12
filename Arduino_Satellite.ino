#include "Packet.h"
String ss;
void setup() {
  // put your setup code here, to run once:
   Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Delay is here to load all the program.
  delay(2000);
  if(Serial.available() > 0) {
    ss = Serial.readString();
    Plan P(ss, 2);
    delay(1000);
  }
}
//gz01020502gz
//gz01010c030401gz
// C00102010A0301C0
//    p.getPacketNumber(0).RepeatCommand();

//    Packet l("C001010A120301C0");
//    Serial.println(l.toHex('~'));
//    delay(1000);


//gz1A01000000040003gz






//C001020419A0FFC0C00101030D20A0C0
//C0010103120301C0C00101030D20A0C0

//This before split Code into many File
//Sketch uses 3556 bytes (11%) of program storage space. Maximum is 32256 bytes.
//Global variables use 203 bytes (9%) of dynamic memory, leaving 1845 bytes for local variables. Maximum is 2048 bytes.

//This After Split Code into Class and header File
//Sketch uses 3600 bytes (11%) of program storage space. Maximum is 32256 bytes.
//Global variables use 203 bytes (9%) of dynamic memory, leaving 1845 bytes for local variables. Maximum is 2048 bytes.

//X: 2 Y: -2 Z: 2

//gz0C0100 020.02 0028gz
