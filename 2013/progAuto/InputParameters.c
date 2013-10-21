

int getIntTarget(const string comment,int min=-31000,int max=31000){
	int stepsize=1,nextstepsize=1;
	int value=0;

	ClearTimer(T1);
	nxtDisplayCenteredTextLine(1, comment);
	nxtDisplayCenteredBigTextLine(3, "%d",value);
	while(nNxtButtonPressed == 3){};
	bool done=false;
	//hogCPU();
	eraseDisplay();
  while(!done){
  	if(value<min) value=min;
  	if(value>max) value=max;
      nxtDisplayCenteredTextLine(1, comment);
      nxtDisplayCenteredBigTextLine(3, "%d",value);
      nxtDisplayCenteredTextLine(6, "%d",time100[T1]%10);
      nxtDisplayCenteredTextLine(7, "%d",stepsize);

      ClearTimer(T2);
    	while(time1[T2]<150+50*log10(10*stepsize)){}; // 1/5 seconds per check


    if(nNxtButtonPressed == 1) value+=stepsize;
    if(nNxtButtonPressed == 2) value-=stepsize;
    if(nNxtButtonPressed == 3) done=true;

    if(nNxtButtonPressed == -1) {stepsize=1; ClearTimer(T1); }
    else if((abs(value)/stepsize)%10 == 0){ stepsize*=10; if(stepsize>1000) stepsize=1000; }
    //if(time100[T1]%10 == 8){ stepsize*=10; waitt+=200; if(stepsize>1000) {stepsize=1000; waitt=600;}}

  }
  //releaseCPU();
  return value;
}


float getFloatTarget(const string comment,float min=-3100,float max=3100){
	int stepsize=1,nextstepsize=1;
	int value=0;

	ClearTimer(T1);
	nxtDisplayCenteredTextLine(1, comment);
	nxtDisplayCenteredBigTextLine(3, "%d",value);
	while(nNxtButtonPressed == 3){};
	bool done=false;
	//hogCPU();
	eraseDisplay();
  while(!done){
		if(value>10*max) value=10*max;
		if(value<10*min) value=10*min;
      nxtDisplayCenteredTextLine(1, comment);
      nxtDisplayCenteredBigTextLine(3, "%6.1f",0.1*value);
      nxtDisplayCenteredTextLine(6, "%d",time100[T1]%10);
      nxtDisplayCenteredTextLine(7, "%d",stepsize);

      ClearTimer(T2);
    	while(time1[T2]<150+50*log10(10*stepsize)){}; // 1/5 seconds per check


    if(nNxtButtonPressed == 1) value+=stepsize;
    if(nNxtButtonPressed == 2) value-=stepsize;
    if(nNxtButtonPressed == 3) done=true;

    if(nNxtButtonPressed == -1) {stepsize=1; ClearTimer(T1); }
    else if((abs(value)/stepsize)%10 == 0){ stepsize*=10; if(stepsize>1000) stepsize=1000; }
    //if(time100[T1]%10 == 8){ stepsize*=10; waitt+=200; if(stepsize>1000) {stepsize=1000; waitt=600;}}

  }
  //releaseCPU();
  return (0.1*value);
}







void getInputs(int nParam,string* prompts,float *response){
	for(int prm=0;prm<nParam;prm++){

	}
}
