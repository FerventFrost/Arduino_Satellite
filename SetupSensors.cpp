#include "Packet.h"


SetupSensors::SetupSensors():dht(DHTPIN ,DHTTYPE) {
  DhtBegin();
  MpuBegin();
  InitArray();
}
//DHT 11 Sensor
void SetupSensors::DhtBegin() {
  dht.begin();
}

int SetupSensors::DHT_Sensor(char _CommadId) { 
  if(_CommadId == 0)
    return RoundReadings(dht.readTemperature());
  return RoundReadings(dht.readHumidity());
}

//MPU 6050 Sensor
void SetupSensors::MpuBegin() {
    Wire.begin();                      // Initialize comunication
    Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
    Wire.write(0x6B);                  // Talk to the register 6B
    Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
    Wire.endTransmission(true);        //end the transmission
    // calculate_IMU_error();          //uncomment it to get the error values in horizontal postion
    delay(20);
}

void SetupSensors::MPU_Sensor(char _CommandId, short int &X, short int &Y, short int &Z) {
    if(_CommandId == 0)
      MPU_Acc(X,Y,Z);
    else if(_CommandId == 1)
      MPU_Gyro(X,Y,Z);
    else
      MPU_Temp(X,Y,Z);
      
    delay(1000);
    if(!Wire.available() != 0)
      MpuBegin();
}

void SetupSensors::MPU_Acc(short int &X, short int &Y, short int &Z) {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true); 

    if(Wire.available() != 0) {
      delay(20);
      X = RoundReadings( (Wire.read() << 8 | Wire.read()) / 2048.0 ); // X-axis value
      Y = RoundReadings( (Wire.read() << 8 | Wire.read()) / 2048.0 ); // Y-axis value
      Z = RoundReadings( (Wire.read() << 8 | Wire.read()) / 2048.0 ); // Z-axis value
    }
    else {
      X = -9999;
      Y = -9999;
      Z = -9999;
    }
}

void SetupSensors::MPU_Gyro(short int &X, short int &Y, short int &Z) {
    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    if(Wire.available() != 0) {
      X = RoundReadings( (Wire.read() << 8 | Wire.read()) / 65.5 );
      Y = RoundReadings( (Wire.read() << 8 | Wire.read()) / 65.5 );
      Z = RoundReadings( (Wire.read() << 8 | Wire.read()) / 65.5 );
    }
    else {
      X = -9999;
      Y = -9999;
      Z = -9999;
    }
}

void SetupSensors::MPU_Temp(short int &X, short int &Y, short int &Z) {
    Wire.beginTransmission(MPU);
    Wire.write(0x41);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 2, true);
    if(Wire.available() != 0) {
      X = RoundReadings( (Wire.read() << 8 | Wire.read()) / 340 + 36.53 );
      Y = 0;
      Z = 0;
    }
    else {
      X = -9999;
      Y = -9999;
      Z = -9999;
    }
}

//HC-SR04 Sensor
void SetupSensors::HcSrBegin() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

short int SetupSensors::HcSr_Sensor(char _CommandId) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  // Calculating the distance
  short int Distance =  pulseIn(echoPin, HIGH) * 0.034 / 2;
  return Distance;
  delay(1000);
}

//Class Methods
int SetupSensors::RoundReadings(float temp) {
  if( int(temp * 10) % 10 >= 5 )
    return temp + 1;
  return temp;
};

void SetupSensors::getSensorData(char _SubSystem, char _CommandId, short int _Para[]) { 
  if(_SubSystem == 0)
    _Para[0] =  DHT_Sensor(_CommandId);
  else if(_SubSystem == 1)
    MPU_Sensor(_CommandId, _Para[0], _Para[1], _Para[2]);
  else if(_SubSystem == 2)
    _Para[0] = HcSr_Sensor(_CommandId);
  else
    _Para[0] = -9999;
}

void SetupSensors::InitArray() {
  _SensorsDefaultBytes[0] = 1;
  _SensorsDefaultBytes[1] = 3;
  _SensorsDefaultBytes[2] = 1;
  _NumberofReturnValue[0] = 1;
  _NumberofReturnValue[1] = 3;
  _NumberofReturnValue[2] = 1;
}

char SetupSensors::NumberofBytes(char _SubSystem) { return _SensorsDefaultBytes[_SubSystem]; }

char SetupSensors::NumberofReturnValues(char _SubSystem) { return _NumberofReturnValue[_SubSystem]; }
// float SetupSensors::DhtTempFloat() { return dht.readTemperature(); }
// void SetupSensors::PrintTemp() { Serial.println((SensorsArray[0][0](false,false))); }