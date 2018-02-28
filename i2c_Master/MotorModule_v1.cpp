#include "MotorModule_v1.h"

void Motor_Init(int ExtReset){
  Wire.begin();
  pinMode(ExtReset, OUTPUT);
  digitalWrite(ExtReset, LOW);
  delay(10);
  digitalWrite(ExtReset, HIGH);
}

MotorObject::MotorObject(){
  rev = false;
}

void MotorObject::getMotorState(int* count, bool* collide){
  Wire.requestFrom(address, 6);
  uint8_t data[6];
  while (Wire.available()) {
    for(int i = 0; i < 6; i ++){
      data[i] = Wire.read();
    }
  }
  *collide = data[0];
  *count = hex2dec(data);
}

void MotorObject::sendPwmPercent(uint8_t pwm){
  //if(pwm <= 100 && pwm >= -100){
    Wire.beginTransmission(address);
    Wire.write(pwm + 100);
    Wire.endTransmission();
  //}
  //else{
  //  Serial.print("PWM value: please set between +100 and -100");
  //}
}
void MotorObject::setSlaveAddress(uint8_t addr){
  address = addr;
}

void MotorObject::Reverse(){
  rev = true;
}

int MotorObject::hex2dec(uint8_t *hex){
  int dec;
  dec = 16777216*hex[2] + 65536*hex[3] + 256*hex[4] + hex[5];
  if(hex[1]!=rev){
    dec = dec*(-1);
  }
  return dec;
}
  
