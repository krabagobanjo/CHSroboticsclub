#pragma config(Sensor, S2,     HTAC,                sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-accelerometer-test1.c 109 2012-09-25 17:10:26Z xander $
 */

/**
 * hitechnic-accelerometer.h provides an API for the HiTechnic Acceleration Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Make use of new API calls
 * - 0.3: Better comments
 * - 0.4: Fixed display line (thanks Dave)
 * - 0.5: Removed single axis functions, they're no longer in the driver\n
 *        Removed common.h from includes
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.51 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * 20 February 2011
 * version 0.5
 */

#include "drivers/hitechnic-accelerometer.h"

task main () {
  int _x_axis = 0;
  int _y_axis = 0;
  int _z_axis = 0;

  string _tmp;

  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "Accel");
  nxtDisplayCenteredTextLine(3, "Test 1");
  nxtDisplayCenteredTextLine(5, "Connect sensor");
  nxtDisplayCenteredTextLine(6, "to S1");
  wait1Msec(2000);

  PlaySound(soundBeepBeep);
  while(bSoundActive) EndTimeSlice();

  while (true) {
    eraseDisplay();

    // Read all of the axes at once
    if (!HTACreadAllAxes(HTAC, _x_axis, _y_axis, _z_axis)) {
      nxtDisplayTextLine(4, "ERROR!!");
      wait1Msec(2000);
      StopAllTasks();
    }

    nxtDisplayTextLine(0,"HTAC Test 1");

    // We can't provide more than 2 parameters to nxtDisplayTextLine(),
    // so we'll do in two steps using StringFormat()
    nxtDisplayTextLine(2, "   X    Y    Z");
    StringFormat(_tmp, "%4d %4d", _x_axis, _y_axis);
    nxtDisplayTextLine(3, "%s %4d", _tmp, _z_axis);

    wait1Msec(100);
  }
}

/*
 * $Id: hitechnic-accelerometer-test1.c 109 2012-09-25 17:10:26Z xander $
 */