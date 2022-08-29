#ifndef PACKET_H
#define PACKET_H
#include "Arduino.h"
using namespace std;

class Packet {
    private:
        String _Packet;
        unsigned char _To;
        unsigned char _From;

    public:
        Packet(String Packet);
        void Split();
        char HexValue(char Hex);        //can be short int "Takes 2 bytes"

        //Return int BC Arduino keep Converting char as if it is a signed.
        //e.g if char is moer than 128 it give -ve number.
        int getTo() { return _To; }
        int getFrom() { return _From; }
};


#endif