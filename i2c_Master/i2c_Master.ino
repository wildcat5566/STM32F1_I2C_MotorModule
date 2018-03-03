#include "MotorModule_v1.h"
#define ExtResetPin 22
MotorObject FR, FL, RR, RL, WR, WL;
int fr_count, fl_count, rr_count, rl_count, wr_count, wl_count;
bool fr_collide, fl_collide, rr_collide, rl_collide;
int pwm = 0; //-1000 < pwm < 1000

void setup() {
  Serial.begin(115200);
  Motor_Init(ExtResetPin);
  FR.setSlaveAddress(0x4A);
  FL.setSlaveAddress(0x4B);
  RR.setSlaveAddress(0x4C);
  RL.setSlaveAddress(0x4D);
  WR.setSlaveAddress(0x4E);
  WL.setSlaveAddress(0x4F);
  //WL.Reverse();
}
int i = 0;
void loop() {
  if(i<500){
    i++;
  }
  FR.getMotorState(&fr_count, &fr_collide);
  FL.getMotorState(&fl_count, &fl_collide);
  RR.getMotorState(&rr_count, &rr_collide);
  RL.getMotorState(&rl_count, &rl_collide);
  WR.getMotorState(&wr_count);
  WL.getMotorState(&wl_count);
    
  FR.sendPwm(i);
  FL.sendPwm(i);
  RR.sendPwm(i);
  RL.sendPwm(i);
  WR.sendPwm(i);
  WL.sendPwm(i);
  Serial.print("encoder count: ");Serial.print(fr_count);
  Serial.print(", collision: "); Serial.println(fl_count);
}
