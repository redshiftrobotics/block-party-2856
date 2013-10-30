#pragma config(Sensor, S1,     IR,             sensorI2CCustom)
#include "HitecnicInfaredLibrary.h"

int acS1, acS2, acS3, acS4, acS5 = 0;

long sY = 0; //We are squaring summations -> KEEP THESE AS LONGS
long sX = 0;
long spX2p = 0;
long psXp2 = 0;
float mpsXp2 = 0;
long sXsY = 0;
float msXsY = 0;
long spXYp = 0;

float LOBF_slope = 0;

float slopeLOBF (int n, bool debug) //"n" is your sample size and WILL INCREASE THE TIME YOU ENCONTER SLEEP FUNCTIONS
{
	if (debug == true) {clearDebugStream();}

	sY = 0;
	sX = 0;
	spXYp = 0;
	spX2p = 0;
	for (int X = 1; X<n+1 ; X++)
	{
		HTIRS2readAllACStrength(IR, acS1, acS2, acS3, acS4, acS5);
		sY += acS3;
		sX += X;
		spX2p += X*X;
		spXYp += (X * acS3) ;
		if (debug == true)
		{
			writeDebugStream("%i,", acS3);
			writeDebugStreamLine("0");
		}
		Sleep(10);
	}
	psXp2 = (sX*sX);
	mpsXp2 = psXp2/n;
	sXsY = (sX*sY);
	msXsY = (sXsY)/n;
	LOBF_slope = (spXYp - msXsY)/(spX2p - mpsXp2);
	return LOBF_slope;

	if (debug == true)
	{
		writeDebugStream("0, ");
		writeDebugStream("slope:%f, ", LOBF_slope);
		writeDebugStream("sY:%i, ", sY);
		writeDebugStream("psXp2:%i, ", psXp2);
		writeDebugStream("mpsXp2:%f, ", mpsXp2);
		writeDebugStream("sXsY:%i, ", sXsY);
		writeDebugStream("msXsY:%f, ", msXsY);
		writeDebugStreamLine("spXYp:%i", spXYp);
	}
	Sleep(50);
}
