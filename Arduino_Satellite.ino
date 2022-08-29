#include "Packet.h"


void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    Packet p(Serial.readString());
    p.Split();
    Serial.println(p.getTo());
    Serial.println(p.getFrom());
    delay(2000);
  }
}



//This before split Code into many File
//Sketch uses 3556 bytes (11%) of program storage space. Maximum is 32256 bytes.
//Global variables use 203 bytes (9%) of dynamic memory, leaving 1845 bytes for local variables. Maximum is 2048 bytes.

//This After Split Code into Class and header File
//Sketch uses 3600 bytes (11%) of program storage space. Maximum is 32256 bytes.
//Global variables use 203 bytes (9%) of dynamic memory, leaving 1845 bytes for local variables. Maximum is 2048 bytes.
