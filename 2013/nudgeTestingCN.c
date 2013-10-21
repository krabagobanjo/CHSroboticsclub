#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     kGyroSensor,    sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     S_lightsensor,  sensorLightActive)
#pragma config(Sensor, S4,     HTIRS2,              sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     M_DriveFL,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     M_DriveBR,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     M_DriveFR,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     M_DriveBL,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     M_Lift,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     M_Unused,      tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    SV_TiltLeft,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    SV_TiltRight,         tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    SV_Swivel,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    SV_LightSensor,       tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

bool  GB_liftTargetSet; //to indicate automatic target for lift
int   GI_liftTarget;    //target value

int expectedGyro;//used to integrate and track rotations
int testScore=-1; //-1,  0,1,2  LMR

#include "JoystickDriver.c"
#include "getJoyValues.c"
#include "constants.c"
#include "CHSGyroDriver.c"
#include "Driving.c"
#include "ServoFns.c"
#include "LiftFns.c"
#include "drivers/hitechnic-irseeker-v2.h"
#include "TrackingRoutines.c"
#include "autoSub.c"


void initializeRobot(){
	//StartTask(GyroDeviceDriver,255);

  servoChangeRate[SV_TiltLeft]        = 10;
  servoChangeRate[SV_TiltRight]       = 10;
  servoChangeRate[SV_Swivel]          = 10;
  servoChangeRate[SV_LightSensor]      = 0;

  nMotorEncoder[M_Lift]    = 0;

  servo[SV_Swivel]=C_SVSWIVELCENTER;
  servo[SV_TiltRight]=C_SVTILTRIGHTUP;
  servo[SV_TiltLeft]=C_SVTILTLEFTUP;
  servo[SV_LightSensor]=C_SVLIGHTSENSORIN;

  wait1Msec(3000);
  servo[SV_TiltRight]=C_SVTILTRIGHTDOWN;
  servo[SV_TiltLeft]=C_SVTILTLEFTDOWN;
  wait1Msec(200);
  servo[SV_TiltRight]=C_SVTILTRIGHTUP;
  servo[SV_TiltLeft]=C_SVTILTLEFTUP;

  fGyroAngle=0; //should be anyway
  expectedGyro=0;

  // the default DSP mode is 1200 Hz.
  //tHTIRS2DSPMode _mode = DSP_1200;
}

task main()
{
  int _dirAC = 0;
  int loc;

	initializeRobot();

	waitForStart();

	putLiftUpAuto();

	 //need to position servos
  hogCPU();
  servo[SV_TiltRight]=C_SVTILTRIGHTDOWN;
  servo[SV_TiltLeft]=C_SVTILTLEFTDOWN;
  releaseCPU();
  wait1Msec(200);
  servo[SV_Swivel]=C_SVSWIVELLEFT;

		ClearTimer(T3);
	while(time1[T3]<3000){
		ClearTimer(T4);
		while(time1[T4]<50) goHolo(0,30,0);
    allDriveStop();
		wait1Msec(50);
	}
	fGyroAngle=0;

	int lightSTarget;
	  int spower;
  int ioffset;
/*
	lightSTarget=130;
		loc=scanForMax(C_SVLIGHTSENSORIN-60,C_SVLIGHTSENSORMXOUT);
		direction*=-1;
	if(range<C_RANGESAFETY) StopAllTasks();
  setLight(loc+20);
  trackEdge(C_SVLIGHTSENSORMXOUT,C_SVLIGHTSENSORIN,500);

//  while(true){
//  	nxtDisplayBigTextLine(1,"%d",loc);
//  }

  ClearTimer(T3);
	while(time1[T3]<2000){

		trackEdge(C_SVLIGHTSENSORMXOUT,C_SVLIGHTSENSORIN,50);
		allDriveStop();
		trackEdge(C_SVLIGHTSENSORMXOUT,C_SVLIGHTSENSORIN,20);

		ioffset=ServoValue[SV_LightSensor]-lightSTarget;

		spower=abs(6*ioffset);
		if(spower>30) spower=30;

		if(ioffset>0) {
			goGyro(-spower,0);

		}
		if(ioffset<0) {
			goGyro(spower,0);
		}
	}
  allDriveStop();

  setLight(C_SVLIGHTSENSORIN);
  ClearTimer(T3);
  	while(time1[T3]<1000){
		ClearTimer(T4);
		while(time1[T4]<50) goHolo(0,30,0);
    allDriveStop();
		wait1Msec(50);
	}
	fGyroAngle=0;

 //  while(true){
 // 	nxtDisplayBigTextLine(1,"%d",ServoValue[SV_LightSensor]);
//	 }

	*/
		ClearTimer(T3);
	while(time1[T3]<50){
		ClearTimer(T4);
		while(time1[T4]<300) goHolo(0,80,0);
    allDriveStop();
		wait1Msec(50);
	}
		ClearTimer(T4);//fix rotation for some time
	while(time1[T4]<500){
		goMaintainGyro(0,0,0);
	}
	allDriveStop();
	autoDrive(0,4.0);

			ClearTimer(T3);
	while(time1[T3]<1000){
		ClearTimer(T4);
		while(time1[T4]<50) goHolo(0,20,0);
    allDriveStop();
		wait1Msec(50);
	}
	fGyroAngle=0;
		ClearTimer(T3);
	while(time1[T3]<50){
		ClearTimer(T4);
		while(time1[T4]<350) goHolo(0,80,0);
    allDriveStop();
		wait1Msec(50);
	}

    allDriveStop();




	ClearTimer(T4);//fix rotation for some time
	while(time1[T4]<1000){
		goMaintainGyro(0,0,0);
	}
	allDriveStop();


	lightSTarget=70;
		//find and lock on white line and adjust position
	loc=scanForMax(C_SVLIGHTSENSORIN,C_SVLIGHTSENSORMXOUT+60);
	//direction*=-1;
	setLight(loc);
	// while(true){
  //	nxtDisplayBigTextLine(1,"%d",loc);
	// }

	if(range<C_RANGESAFETY) StopAllTasks();

  setLight(loc-20);
  trackEdge(C_SVLIGHTSENSORMXOUT,C_SVLIGHTSENSORIN,1000);
  wait1Msec(100);

  //int spower;
  //int ioffset;
  lightSTarget=220;
  ClearTimer(T3);
	while(time1[T3]<3000){

		trackEdge(C_SVLIGHTSENSORMXOUT,C_SVLIGHTSENSORIN,50);
		allDriveStop();
		trackEdge(C_SVLIGHTSENSORMXOUT,C_SVLIGHTSENSORIN,20);

		ioffset=ServoValue[SV_LightSensor]-lightSTarget;

		spower=abs(3*ioffset);
		if(spower>10) spower=10;

		if(ioffset>0) {
			goGyro(-spower,-spower);

		}
		if(ioffset<0) {
			goGyro(spower,spower);
		}
	}
  allDriveStop();
  setLight(C_SVLIGHTSENSORIN);

  ClearTimer(T4);
  while(time1[T4]<500) goRotRS(-30);
  allDriveStop();


  	//track line in to position scoring
  int signX=-1,signY=1,power=15; //direction 7
  ClearTimer(T4);
  float fGyroTarget=fGyroAngle;
  while(time1[T4]<1000){
  	goMaintainGyro(signX*power,signY*power,fGyroTarget);
  	if(time1[T4]>500) power=5;
  	//trackEdge(C_SVLIGHTSENSORMXOUT,C_SVLIGHTSENSORIN,50);
  }
  allDriveStop();

  	//score rings
  scoreRingsAuto();

	//back out and reset
  autoDrive(3,10.0);

  putLiftDownAuto();

  return;


	loc=scanForMax(C_SVLIGHTSENSORIN,C_SVLIGHTSENSORMXOUT);
	//if(range<C_RANGESAFETY) StopAllTasks();

  setLight(loc);


  wait1Msec(1000);
  //trackEdge(C_SVLIGHTSENSORMXOUT,C_SVLIGHTSENSORIN,5000);
  return;

	ClearTimer(T3);
	while(time1[T3]<5000){
		ClearTimer(T4);
		while(time1[T4]<50) goHolo(0,30,0);
    allDriveStop();
		wait1Msec(50);
	}
	ClearTimer(T3);
	while(time1[T3]<50){
		ClearTimer(T4);
		while(time1[T4]<300) goHolo(0,80,0);
    allDriveStop();
		wait1Msec(50);
	}


}
