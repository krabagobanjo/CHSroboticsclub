#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     DriveFL,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     DriveBR,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     DriveFR,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     DriveBL,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     Mtr_ParaLift,  tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     Mtr_RingSlider, tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    PullSliderServo,      tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    RotServo,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "getJoyValues.c"
#include "constants.c"
#include "Driving.c"
#include "ParallelLifter.c"
#include "RingSlider.c"

void globalAbort(){
	motor[DriveFL]=0;
	motor[DriveBL]=0;
	motor[DriveFR]=0;
	motor[DriveBR]=0;
	motor[Mtr_ParaLift]=0;
	motor[Mtr_RingSlider]=0;
	B_liftTargetSet=false;
}


void initializeRobot(){

  servoChangeRate[RotServo]        = 10;
  servoChangeRate[PullSliderServo] = 10;

  //for actual competition this is avoided
  //if(false){
  if(true){
    servo[RotServo]        =  C_ROTSERVOHOLD;
    servo[PullSliderServo] =  C_PULLSLIDERIN;
  }

  //reset encoders -- assumes arm in set position
  //if not driver should execute armButton5 and reposition flapper verically
  nMotorEncoder[Mtr_ParaLift]    = 0;

  B_liftTargetSet=false;
}

task main()
{
	initializeRobot();
	waitForStart();
	ClearTimer(T1);
  ClearTimer(T2);

}
