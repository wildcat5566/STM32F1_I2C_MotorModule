#include "MotorModule_v1.h"
#define ExtResetPin 22
MotorObject WL;
int wl_count;
bool wl_collide;

void setup() {
  Serial.begin(115200);
  Motor_Init(ExtResetPin);
  WL.setSlaveAddress(0x4F);
  WL.Reverse();
}

void loop() {
  WL.getMotorState(&wl_count, &wl_collide);
  delay(10);
  WL.sendPwmPercent(31);
  delay(10);

  Serial.print("encoder count: ");Serial.print(wl_count); 
  Serial.print(", collision: "); Serial.println(wl_collide);
}

