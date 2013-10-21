//////////////////////////////////////////////////
//standard Drive Control
void standardDrive(int nLMotorPower,int nRMotorPower){

   motor[LeftSideMotors]  = nLMotorPower;
   motor[RightSideMotors] = -nRMotorPower;

}

//LIFT MAINTENANCE
void liftReleaseMaintain(int releasetargetB,int releasetargetC){
  int readB,readC;
  readB=nMotorEncoder[catchR];
  readC=nMotorEncoder[catchL];
  if(readB>releasetargetB || readC>releasetargetC) {
    motor[catchR]=-95;
    motor[catchL]=-95;
  }
  else {
    motor[catchR]=0;
    motor[catchL]=0;
  }
}

//////////////////////////
//Drive nudging
//positive is forward
void driveNudge(int Leftpow,int Rightpow,int duration){
	     motor[LeftSideMotors] = Leftpow;
       motor[RightSideMotors] = -Rightpow;
       wait1Msec(duration);
       motor[LeftSideMotors] = 0;
       motor[RightSideMotors] = 0;
}
