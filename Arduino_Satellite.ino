//Need AdaFruit Library
#include "Packet.h"
char StartSession[6];
Plan P;
void(* resetFunc) (void) = 0; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  P.SensorsBegin();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Delay is here to load all the program.
  delay(2000);
  while (Serial.available() == 0) {}

  Serial.readBytes(StartSession, 6);
  P.StartPlan(Serial.readString(), SessionLen(StartSession[2], StartSession[3]) );
  delay(1000);
  resetFunc();
  delay(5000);
}

char HexValue(char Hex) {          //can be short int "Takes 2 bytes"
    if(isdigit(Hex)) return (Hex - 48);
    else if(islower(Hex)) return (Hex - 87);
    else return (Hex - 55);
}

int SessionLen(char Number1, char Number2) {
  return HexValue(Number1) * 16 + HexValue(Number2);
}
//gz03gzgz00000301gzgz01000301gzgz02000301gz

//gz03gzgz01000304gzgz02000304gzgz01010304gz

//    Packet l("C001010A120301C0");
//    Serial.println(l.toHex('~'));
//    delay(1000);

//This before split Code into many File
//Sketch uses 3556 bytes (11%) of program storage space. Maximum is 32256 bytes.
//Global variables use 203 bytes (9%) of dynamic memory, leaving 1845 bytes for local variables. Maximum is 2048 bytes.

//This After Split Code into Class and header File
//Sketch uses 3600 bytes (11%) of program storage space. Maximum is 32256 bytes.
//Global variables use 203 bytes (9%) of dynamic memory, leaving 1845 bytes for local variables. Maximum is 2048 bytes.
