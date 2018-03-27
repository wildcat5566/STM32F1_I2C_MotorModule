void PID_init(){
  //MANUAL: PID off; AUTOMATIC: PID on;
  FL_PID.SetSampleTime(1000 / Timer3_HZ);
  FL_PID.SetOutputLimits(0, PWMmax);
  FL_PID.SetMode(MANUAL);
  FR_PID.SetSampleTime(1000 / Timer3_HZ);
  FR_PID.SetOutputLimits(0, PWMmax);
  FR_PID.SetMode(MANUAL);
  RL_PID.SetSampleTime(1000 / Timer3_HZ);
  RL_PID.SetOutputLimits(0, PWMmax);
  RL_PID.SetMode(MANUAL);
  RR_PID.SetSampleTime(1000 / Timer3_HZ);
  RR_PID.SetOutputLimits(0, PWMmax);
  RR_PID.SetMode(MANUAL);
  
  WL_PID.SetSampleTime(1000 / Timer3_HZ);
  WL_PID.SetOutputLimits(-W_PWMmax, W_PWMmax);
  WL_PID.SetMode(MANUAL);
  WR_PID.SetSampleTime(1000 / Timer3_HZ);
  WR_PID.SetOutputLimits(-W_PWMmax, W_PWMmax);
  WR_PID.SetMode(MANUAL);

  FL_PID.SetMode(MANUAL);
  FR_PID.SetMode(MANUAL);
  RL_PID.SetMode(MANUAL);
  RR_PID.SetMode(MANUAL);  
  WL_PID.SetMode(MANUAL);
  WR_PID.SetMode(MANUAL);

  FL_PID.SetMode(AUTOMATIC);
  FR_PID.SetMode(AUTOMATIC);
  RL_PID.SetMode(AUTOMATIC);
  RR_PID.SetMode(AUTOMATIC);
  WL_PID.SetMode(AUTOMATIC);
  WR_PID.SetMode(AUTOMATIC);
} //PID_init()
