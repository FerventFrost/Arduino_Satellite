#include "Packet.h"

Packet::Packet(String Packet) {
    _Packet = Packet;
}

char Packet::HexValue(char Hex) {          //can be short int "Takes 2 bytes"
    if(isdigit(Hex)) return (Hex - 48);
    else if(islower(Hex)) return (Hex - 87);
    else return (Hex - 55);
}

void Packet::Split() {
    _To = HexValue(_Packet[0]) * 16 + HexValue(_Packet[1]);
    _From = HexValue(_Packet[2]) * 16 + HexValue(_Packet[3]);
}