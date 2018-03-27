#include "MotorModule_v1.h"
#include <PID_v1.h>

#define RelayPin 22
#define ExtResetPin 23
MotorObject FR, FL, RR, RL, WR, WL;
int fr_count, fl_count, rr_count, rl_count, wr_count, wl_count;
bool fr_collide, fl_collide, rr_collide, rl_collide;
int pwm = 0; //-1000 < pwm < 1000

//******PID Settings******//
double Timer3_HZ = 100.0;
int PWMmax = 500;
int W_PWMmax = 100;
//Angular Velocity Control Gains = (4, 12, 0);
//Position Angle Control Gains = (2, 4, 0);
float P_Kp = 0.2, P_Ki = 0.2, P_Kd = 0;
//Feed & Set Settings
float FL_Setpoint_Tick = 0, FR_Setpoint_Tick = 0, RL_Setpoint_Tick = 0, RR_Setpoint_Tick = 0;
double FL_Feed = 0, FR_Feed = 0, RL_Feed = 0, RR_Feed = 0, WL_Feed = 0, WR_Feed = 0;
double FL_Set = 0, FR_Set = 0, RL_Set = 0, RR_Set = 0, WL_Set = 0, WR_Set = 0;
//Computed PWM requirement
double FL_PWMvalue = 0, FR_PWMvalue = 0, RL_PWMvalue = 0, RR_PWMvalue = 0, WL_PWMvalue = 0, WR_PWMvalue = 0;
//Control Variables
float FL_Angular_V_Tar = 0, FR_Angular_V_Tar = 0, RL_Angular_V_Tar = 0, RR_Angular_V_Tar = 0;
float Angular_V_Tar = 0;
float Angular_V_Add = 0.1;
//PID Objects Velocity(4, 12, 0); Position(2, 4, 0);
PID FL_PID(&FL_Feed, &FL_PWMvalue, &FL_Set, 0, 0, 0, DIRECT);
PID FR_PID(&FR_Feed, &FR_PWMvalue, &FR_Set, 0, 0, 0, DIRECT);
PID RL_PID(&RL_Feed, &RL_PWMvalue, &RL_Set, 0, 0, 0, DIRECT);
PID RR_PID(&RR_Feed, &RR_PWMvalue, &RR_Set, 0, 0, 0, DIRECT);
PID WR_PID(&WR_Feed, &WR_PWMvalue, &WR_Set, 20, 0, 0, DIRECT);
PID WL_PID(&WL_Feed, &WL_PWMvalue, &WL_Set, 20, 0, 0, DIRECT);

void setup() {
  Serial.begin(115200);
  Motor_Init(ExtResetPin);
  WL.setSlaveAddress(0x4A); // Waist Left
  FL.setSlaveAddress(0x4B); // Front left
  WR.setSlaveAddress(0x4C);  // Waist Right
  FR.setSlaveAddress(0x4D);  // Front Right
  RR.setSlaveAddress(0x4E); // Rear Right
  RL.setSlaveAddress(0x4F);  // Rear Left
  FR.Reverse(); WR.Reverse();
  
  pinMode(RelayPin, OUTPUT);
  digitalWrite(RelayPin, HIGH);

  PID_init();
  PWMmax = 100;
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

  RL_Feed = rl_count;
  RR_Feed = rr_count;

  RL_Set += 100;
  RR_Set += 100;

  RL_PID.SetTunings(P_Kp, P_Ki, P_Kd);
  RR_PID.SetTunings(P_Kp, P_Ki, P_Kd);

  RL_PID.Compute();
  RR_PID.Compute();
    
  FR.sendPwm(i);
  FL.sendPwm(i);
  RR.sendPwm(RR_PWMvalue);
  RL.sendPwm(RL_PWMvalue);
  WR.sendPwm(i);
  WL.sendPwm(i);
  
  Serial.print("rl_count: \t ");Serial.print(rl_count);
  Serial.print("  rr_count: \t ");Serial.print(rr_count);
  Serial.print("  rl_set: \t ");Serial.print(RL_Set);
  Serial.print("  rr_set: \t ");Serial.print(RR_Set);
  Serial.print("  rl_PWM: \t ");Serial.print(RL_PWMvalue);
  Serial.print("  rr_PWM: \t ");Serial.println(RR_PWMvalue);  
/*  Serial.print("  rear_left: \t ");Serial.print(rl_count);
  Serial.print("  rear_right: \t ");Serial.print(rr_count);
  Serial.print("  waist_left: \t ");Serial.print(wl_count);
  Serial.print("  waist_right: \t ");Serial.println(wr_count);*/

  /*Serial.print("\t ");Serial.print(fl_collide);
Serial.print("\t ");Serial.print(fr_collide);
Serial.print("\t ");Serial.print(rl_collide);
Serial.print("\t ");Serial.println(rr_collide);*/

}
