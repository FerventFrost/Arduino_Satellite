#include "Packet.h"

//Plan cLass

Plan::Plan(String Plan, unsigned char NoPackets) {
    _StartPlanTimer = millis();
    _Plan = Plan;
    _NumberOfPackets = NoPackets;
    if(CheckPlan()) {
        _Packets = new Packet [_NumberOfPackets];
        _PacketSuccessfullySend = new bool [_NumberOfPackets];
        Split();
        //Plan Ack
        _PlanAck = "gz0100gz";
    }
    else
        //Plan Non-ACK
        _PlanAck = "gz0101gz";

    //Print ACK
    Serial.println(_PlanAck);
}

void Plan::Split() {
    for(int i = 0; i < _NumberOfPackets; i++) {
        _Packets[i] = Packet(_Plan.substring(0 + (i * 12) , 12 + (i * 12)) +"\n", _StartPlanTimer); //gz0100030Agz

        if(_Packets[i].CheckPacket()) 
            _PacketSuccessfullySend[i] = true;
        else
            _PacketSuccessfullySend[i] = false;

        delay(1000);
    }
}

bool Plan::CheckPlan() {
    return _Plan.length() == (12 * _NumberOfPackets + 1);   //ADD ONE BECAUSE INPUT '\n' IS SEND AND INCREASE STRING SIZE BY ONE.
  }
