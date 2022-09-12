#include "Packet.h"

//Packet Class

//Packet Constructor
Packet::Packet(String Packet, unsigned long PlanTimer) {
    _Packet = Packet;
    _PlanTimer = PlanTimer;
    if(CheckPacket()) {
        Split();
        //Split ACK
        Serial.println("gz0002gz");
        //delay After the Pervious Packet is finished
        delay(_Delay * 1000);
        RepeatCommand();
        delay(1000);
        //ACK Packet 
        _PacketACK = "gz0000gz";
    }
    else
        //Non-Ack Packet
        _PacketACK = "gz0001gz";

    //Print ACK
    Serial.println(_PacketACK);
}

//for Initiate Array from this class
Packet::Packet() {}

//Protected
char Packet::HexValue(char Hex) {          //can be short int "Takes 2 bytes"
    if(isdigit(Hex)) return (Hex - 48);
    else if(islower(Hex)) return (Hex - 87);
    else return (Hex - 55);
}

char Packet::CharToHex(char Character) {
    if(Character < 10) return Character + 48;
    return Character + 55;
}

unsigned char Packet::HexToDecimal(unsigned char X,unsigned char Y) {
    return HexValue(_Packet[X]) * 16 + HexValue(_Packet[Y]);
}

String Packet::OneByteHex(short int Character, bool Sign) {
    if(Character == -9999)
        return "00";
    if(Character > 254)
        return "FF";
    if(Sign) {
        if(Character < 0) {
            Character *= -1;
            return "0" + String(CharToHex( (Character / 16) % 16 )) + String(CharToHex( Character % 16 )) ;
        }
        return "1" + String(CharToHex( (Character / 16) % 16 )) + String(CharToHex( Character % 16 )) ;
    }
    return String(CharToHex( (Character / 16) % 16 )) + String(CharToHex( Character % 16 )) ;
}

String Packet::TwoByteHex(unsigned long Character, bool Sign) {
    if(Character == -9999)
        return "00";
    if(Character > 254)
        return "FF";
    if(Sign) {
        if(Character < 0) {
            Character *= -1;
            return "0" + String(CharToHex( (Character / 16*16*16) % 16 )) + String(CharToHex( (Character / 16*16) % 16 )) + String(CharToHex( (Character / 16) % 16 )) + String(CharToHex( Character % 16 )) ;
        }
        return "1" + String(CharToHex( (Character / 16*16*16) % 16 )) + String(CharToHex( (Character / 16*16) % 16 )) + String(CharToHex( (Character / 16) % 16 )) + String(CharToHex( Character % 16 )) ;
    }
    return String(CharToHex( (Character / 16*16*16) % 16 )) + String(CharToHex( (Character / 16*16) % 16 )) + String(CharToHex( (Character / 16) % 16 )) + String(CharToHex( Character % 16 )) ;
}

String Packet::FromPointerData(short int _Para[], char _SubSystem) {
    if(_SubSystem == 0)
        return OneByteHex(_Para[0], true);
    else if(_SubSystem == 1)
        return OneByteHex(_Para[0], true) + OneByteHex(_Para[1], true) + OneByteHex(_Para[2], true);
    return OneByteHex(_Para[0], true);
}

String Packet::ReturnResponsePacket() {
    short int _Para[ Temperature.NumberofReturnValues(_SubSystem) ];
    Temperature.getSensorData(_SubSystem, _Command, _Para);
    String tempString = "gz" + OneByteHex(PacketSize(Temperature.NumberofBytes(_SubSystem)) , false) + OneByteHex(_SubSystem, false) + OneByteHex(_Command, false) + FromPointerData(_Para, _SubSystem) + TwoByteHex( RoundTimer(millis() - _PlanTimer), false ) + "gz";
    //Packet Composed of SysSystem (1 byte) , Command (1 byte) , and Sensor Value (2 bytes);
    return tempString;
}

int Packet::PacketSize(unsigned char SLen) {
    return SLen * 2 + 4 + 2 * 5;
}

unsigned long Packet::RoundTimer(unsigned long timer) {
  if(timer%1000 >= 500 )
    return timer/1000 + 1;
  return timer/1000;
  };

//Public
bool Packet::CheckPacket() {
    //ADD ONE BECAUSE INPUT '\n' IS SEND AND INCREASE STRING SIZE BY ONE.
    return (_Packet[0] == _Packet[10] & _Packet[1] == _Packet[11] & _Packet.length() == 14) ;
}

void Packet::Split() {
    // _Source = HexValue(_Packet[0]) * 16 + HexValue(_Packet[1]);
    // _Destination = HexValue(_Packet[2]) * 16 + HexValue(_Packet[3]);
    _SubSystem = HexToDecimal(2,3);
    _Command = HexToDecimal(4,5);
    _Repeat = HexToDecimal(6,7);
    _Delay = HexToDecimal(8,9);

}

void Packet::RepeatCommand() {
    for(int i = 0; i < _Repeat; i++) {
        Serial.println(ReturnResponsePacket());
        //Delay in Seconds
        delay(1000);
    }
}
