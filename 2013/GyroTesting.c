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
float GF_SwivelTarget; //for manual control of swivel
float gftmp;

int expectedGyro; //used to integrate and track rotations


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

  wait1Msec(2000);
  servo[SV_TiltRight]=C_SVTILTRIGHTDOWN;
  servo[SV_TiltLeft]=C_SVTILTLEFTDOWN;
  wait1Msec(200);
  servo[SV_TiltRight]=C_SVTILTRIGHTUP;
  servo[SV_TiltLeft]=C_SVTILTLEFTUP;

  fGyroAngle=0; //should be anyway
  expectedGyro=0;

  // the default DSP mode is 1200 Hz.
  tHTIRS2DSPMode _mode = DSP_1200;
}

//102 is the correct light position on the right

task main()
{
	int _dirDC = 0;
  int _dirAC = 0;
	//int dcS1, dcS2, dcS3, dcS4, dcS5 = 0;
	//int acS1, acS2, acS3, acS4, acS5 = 0;

	initializeRobot();

	waitForStart();

	putLiftUpAuto();

	ClearTimer(T4);
	while(time1[T4]<5000){
		nxtDisplayBigTextLine(1,"%d", fGyroAngle);
		nxtDisplayBigTextLine(3,"%d", nMotorEncoder[M_Lift]);
		angleAbortTest();
	}
	scoreRingsAuto();
	wait1Msec(3000);

	putLiftDownAuto();

}