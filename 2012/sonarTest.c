#pragma config(Sensor, S2,     snrL,                sensorSONAR)
#pragma config(Sensor, S3,     snrR,                sensorSONAR)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
  int sonarsenseL=0;
  int sonarsenseR=0;
  while(true){

    sonarsenseL=SensorValue(snrL);
    sonarsenseR=SensorValue(snrR);
    //nxtDisplayCenteredTextLine(4,"HI %d",sense);
    nxtDisplayBigTextLine(2,"Lft %d",sonarsenseL);
    nxtDisplayBigTextLine(4,"Rgt %d",sonarsenseR);
  }
}
