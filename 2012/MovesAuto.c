//*****************************************************************
// Autonomous program
// Distances: 775 for each additional foot
// 1700 Msec for 24 in
// 6350 Msec for 8 ft = 1700 + 775*6
// 10ft would be 6350+2*775 = 7900
//*****************************************************************

//DRIVE ROUTINES
#include "CHSGyroDriver.c"

typedef enum {slow, medium, fast} speedcontrol;

//#include "htirs2-driver.h"
float fOldAngle = -1;
//int _dirDC = 0;
//int _dirAC = 0;
//tHTIRS2DSPMode _mode = DSP_1200;
//int dcS1, dcS2, dcS3, dcS4, dcS5 = 0;
//int acS1, acS2, acS3, acS4, acS5 = 0;


void gyroFlasher(){
  bool bFlasher = false;
  while (!bIsGyroInitialized())
  {
    if (bIsGyroInitialized())
      break;

    //
    // Some flashy graphics.
    //
    if (bFlasher)
    {
      nxtDisplayBigStringAt(0, 23, " Startup ");
      bFlasher = false;
    }
    else
    {
      nxtDisplayBigStringAt(0, 23, "        ");
      bFLasher = true;
    }
    wait1Msec(250);// Wait for the gyro to initialize. This takes a couple of seconds.
  }
}

void autowait1Msec(int duration){
   ClearTimer(T3);
    while(time1[T3]<duration){
      liftReleaseMaintain(0,0);
    }
}
//////////////////////////
//Drive nudging
//positive is forward
void autodriveNudge(int Leftpow,int Rightpow,int duration){
	     motor[LeftSideMotors] = -Leftpow;
       motor[RightSideMotors] = Rightpow;
       autoWait1Msec(duration);
       motor[LeftSideMotors]  = 0;
       motor[RightSideMotors] = 0;
}

void goForward(int time){
  autodriveNudge(100,100,time);
}
void goBack(int time){
  autodriveNudge(-100,-100,time);
}

void goLRBack(int time){
  autodriveNudge(-100,0,time);
}

void goRLBack(int time){
  autodriveNudge(0,-100,time);
}

void distForward(float dist, speedcontrol spd){ //distance in inches
  int power;
  float time, powerfactor;
  switch (spd)
  {
    case medium:
      power = 40;
      time=200 + dist*48.0;
    break;
    case fast:
      power = 100;
      time= 100+ dist*36.5;
    break;
    case slow:
      power = 25;
      time = 250 + dist*67.0;
    break;
 }
 float batvolt = externalBattery;
 if(batvolt==-1) powerfactor=1;
 else
 {
   powerfactor=12200.0/batvolt;
 }
 autodriveNudge(power,power,(int)floor(time*powerfactor));
}

void distBackward(float dist, speedcontrol spd){
  int time, power;
  switch (spd)
  {
    case medium:
      power = 40;
      time=200 + dist*48.0;
    break;
    case fast:
      power = 100;
      time= 100+ dist*36.5;
    break;
    case slow:
      power = 25;
      time = 250 + dist*67.0;
    break;
  }
  autodriveNudge(-power,-power,time);
}

void angleRight(float deg){
  int dur;
  dur=(int)floor(15*deg+60);
  autodriveNudge(100,-100,dur);
}

void angleLeft(float deg){
  int dur;
  dur=(int)floor(15*deg+60);
  autodriveNudge(-100,100,dur);
}


void turnRightTo(float deg, int power){
  while(fGyroAngle >=-deg){
    standardDrive(power,-power);
    liftReleaseMaintain(0,0);
    //nxtDisplayBigStringAt(0, 23, "  %3d   ", (long) fGyroAngle);
    fOldAngle = fGyroAngle;
  }
  standardDrive(0,0);
}

void turnRSideTo(float deg){
  while(fGyroAngle >-deg){
    standardDrive(0,-70);
    liftReleaseMaintain(0,0);
    nxtDisplayBigStringAt(0, 23, "  %3d   ", (long) fGyroAngle);
    fOldAngle = fGyroAngle;
  }
  standardDrive(0,0);
}

void turnLrTo(float deg){
  while(fGyroAngle <-deg){
    standardDrive(-70,20);
    liftReleaseMaintain(0,0);
    //nxtDisplayBigStringAt(0, 23, "  %3d   ", (long) fGyroAngle);
    fOldAngle = fGyroAngle;
  }
  standardDrive(0,0);
}

void turnLeftTo(float deg, int power){
  while(fGyroAngle<=-deg){
    standardDrive(-power,power);
    liftReleaseMaintain(0,0);
    //nxtDisplayBigStringAt(0, 23, "  %3d   ", (long) fGyroAngle);
    fOldAngle = fGyroAngle;
  }
  standardDrive(0,0);
}

void turnLSideTo(float deg){
  while(fGyroAngle<=-deg){
    standardDrive(-70,0);
    liftReleaseMaintain(0,0);
    //nxtDisplayBigStringAt(0, 23, "  %3d   ", (long) fGyroAngle);
    fOldAngle = fGyroAngle;
  }
  standardDrive(0,0);
}

void anglereading(){
  while(fGyroAngle != fOldAngle){
    nxtDisplayBigStringAt(0, 23, "  %3d   ", (long) fGyroAngle);
    fOldAngle = fGyroAngle;
  }
}
/*void IRseeking()
{
  while(true)
  {
   _dirDC = HTIRS2readDCDir(HTIRS2);
      if (_dirDC < 0)
        break; // I2C read error occurred

      // read the current modulated signal direction
      _dirAC = HTIRS2readACDir(HTIRS2);
      if (_dirAC < 0)
        break; // I2C read error occurred

      // Read the individual signal strengths of the internal sensors
      // Do this for both unmodulated (DC) and modulated signals (AC)
      if (!HTIRS2readAllDCStrength(HTIRS2, dcS1, dcS2, dcS3, dcS4, dcS5))
        break; // I2C read error occurred
      if (!HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5 ))
        break; // I2C read error occurred

      switch(_dirAC)
      {
        case 1:
          standardDrive(-100,100);
          break;
        case 2:
          standardDrive(-80,80);
          break;
        case 3:
          standardDrive(-65,65);
          break;
        case 4:
          standardDrive(-50,50);
          break;
        case 5:
          standardDrive(100,100);
          break;
        case 6:
          standardDrive(50,-50);
          break;
        case 7:
          standardDrive(65,-65);
          break;
        case 8:
          standardDrive(80,-80);
          break;
        case 9:
          standardDrive(100,-100);
          break;
      }

    }
    */
