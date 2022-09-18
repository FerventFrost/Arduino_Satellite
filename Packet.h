#ifndef PACKET_H
#define PACKET_H

#include "Arduino.h"
#include "DHT.h"
#include <Wire.h>
#define DHTPIN 2
#define DHTTYPE DHT11



//class Setup
//Note this class is Declared first becuase it used in Packet Class.
//If I Declare it after packet i will get an error.
class SetupSensors { 
  private:
    static const char MPU = 0x68; 
    static const char trigPin = 9;
    static const char echoPin = 10;
    DHT dht;
    unsigned long StartPlanTimer;
    char _SensorsDefaultBytes[5];
    char _NumberofReturnValue[5];
  public:
    SetupSensors();
    //DHT 11 Sensor
    void DhtBegin();
    int DHT_Sensor(char _CommadId);
    
    //MPU6050 Sensor
    void MpuBegin();
    void MPU_Acc(short int &X, short int &Y, short int &Z);
    void MPU_Gyro(short int &X, short int &Y, short int &Z);
    void MPU_Temp(short int &X, short int &Y, short int &Z);
    void MPU_Sensor(char _CommandId, short int &X, short int &Y, short int &Z);

    //HC-SR04 Sensor
    void HcSrBegin();
    short int HcSr_Sensor(char _CommandId);

    //Class Methods
    void getSensorData(char _SubSystem, char _CommadId, short int _Para[]);
    void InitArray();
    char NumberofBytes(char _SubSystem);
    char NumberofReturnValues(char _SubSytem);
    int RoundReadings(float temp);

};

//Packet Class
class Packet {
    private:
        SetupSensors _Sensors;
        String _Packet;
        String _PacketACK;
        unsigned long _PlanTimer;
        // unsigned char _Source;
        // unsigned char _Destination;
        unsigned char _PacketNumber;
        unsigned char _SubSystem;
        unsigned char _Command;
        unsigned char _Repeat;
        unsigned char _Delay;

    protected:
        char HexValue(char Hex);        //can be short int "Takes 2 bytes"
        char CharToHex(char Character);
        unsigned char HexToDecimal(unsigned char X, unsigned char Y);
        int PacketSize(unsigned char SLen);
        unsigned long RoundTimer(unsigned long timer);
        String OneByteHex(short int Character, bool Sign);
        String TwoByteHex(unsigned long Character, bool Sign);
        String ThreeByteHex(short int Character);
        String FromPointerData(short int _Para[], char _SubSystem);
        String ReturnResponsePacket();

    public:
        Packet(String Packet, unsigned long PlanTimer, unsigned char PacketNumber, SetupSensors &Sesnors);
        Packet();
        
        bool CheckPacket();
        void Split();
        void RepeatCommand();

        //Return int BC Arduino keep Converting char as if it is a signed.
        //e.g if char is moer than 128 it give -ve number.
        // int getSource() { return _Source; }
        // int getDestination() { return _Destination; }
        String getACK() { return _PacketACK; }
        int getSubSystem() { return _SubSystem; }
        int getCommand() { return _Command; }
        int getRepeat() { return _Repeat; }
        int getDelay() { return _Delay; }
};

class Plan {
    private:
        Packet * _Packets;
        SetupSensors _Sensors;
        String _Plan;
        String _PlanAck;
        bool * _PacketSuccessfullySend;
        unsigned long _StartPlanTimer;
        unsigned char _NumberOfPackets;
    public:
        Plan();
        void Split();
        void StartPlan(String Plan, unsigned char NoPackets);
        void SensorsBegin();
        bool CheckPlan();

        Packet getPacketNumber(char No) { return _Packets[No]; }
        String getPlan() { return _Plan; }
        int getNumberofPackets() { return _NumberOfPackets; }  
};

#endif
