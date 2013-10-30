#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S2,     IR,             sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     left_front,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     left_back,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     right_front,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     right_back,    tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "HitecnicInfaredLibrary.h"

/*
	Motor 1 Daisychain 1 on S1 is left front
	Motor 2 Daisychain 1 on S1 is left back
	Motor 1 Daisychain 2 on S1 is right front
	Motor 2 Daisychain 2 on S1 is right back
*/

/*This code is to read the IRSeekerV2 signal and beep when the seeker is pointing directly at the IRBeacon. Currently the code only outputs the y-intercept and slope for the Line of Best Fit (LOBF); read below for more specifics. This code needs to be calibrated before it works: read through the specifics and then consult the bottom of the header.

- Program Specifics
The IRSeekerV2 data is being filtered with a method called "Line of Best Fit" or "Least-Squares Method" which I followed from the following URL: http://hotmath.com/hotmath_help/topics/line-of-best-fit.html.

- Inputs
Each LOBF calculation uses 10 x-inputs and 10 y-inputs. Each X-input is a reading from the IR "acs3" stored in the array "irInput". Assuming the time interval between readings is constant when we constanly call the "HTIRS2readALLACStrencth" function, each corrosponding y-input is an arbirary number 1-10 to remove the equations reliance on actual time.

-Calculation Uses
Isaac, AJ, Dale, and I recognized a nice bell-curve shape when strenght over time from the IR "acs3" signal is graphed. Using the LOBF formula found on the aformentioned URL, we calculate slope. This slope, should approach a value of zero, if not be at zero, only at the top of the bell curve when the IRSeekerV2 is pointing at the IRBeacon. The calculated y-intercept can serve as a threshold for the IR signal however, notice it is dependant on the distance between the IRBeacon and IRSeekerV2


-IMPORTANT Calibrations before use
1) I just realized that I could have mixed up my X and Y variables. I looked at when we solve for the y-intercept and recognized that it would yield un-usable data because I chose my y-variables as arbitrary integers 1-10; shouldn't my y-variable representing time be on the x-axis? Time (or whatever represents it) should always go on the x-axis.
DOUBLE CHECK MY LOGIC PLEASE

2) Run a test to determine the range of the LOBF slope value when the IRSeekerV2 is pointing at the IRBeacon. If no useful data comes up, mess around with the number of readings in each sample (size of "irInput" "y-Input" and length of "For loop") -- if the readings are too close together the slope would be super small and meaningless.

3) Find a good standard strength y-intercept value that we can use as a threshold. If we have not reached a certain strenght, we could just be reading a small flat part on the Bell Curve Graph and not actually be at the top of the curve facing the IRBeacon. Or ditch the y-intercept threshold value altogether because it is dependant on the distance between the IRBeacon and the IRSeekerV2 and instead only read the "acs3" data when both "acs2" and "acs4" have gone to zero.
*/

// number of times we've read IR signals
int readCount = 0;

//X inputs are dependant -> we use integers 0-10 to represent our sample size
int xInput[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}; //changed name from yInput
int sum_x = 210;
int sum_xSquared = 2870;//EQUATION: bottom left half  = 1+4+9+16+25+36+49+64+81+100+All the other #'s squared up to 20^2
float mean_sum_xSquared = (sum_x^2)/20;//EQUATION: bottom right half

//Y inputs
int acS1, acS2, acS3, acS4, acS5 = 0;
int irInput[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float sum_y = 0; //from 55-> 0

float mean_xTimesy = 0;
float sum_xTimesy = 0;
int irInputSum = 0;
float irInputAvg = 0;
float slopeLOBF = 0;
int y_intLOBF = 0;
int slopeTH = 0; //Slope Threshold
int y_intTH = 0; //Y_intercept Threshold
int numLoop = 0;
// Y is our IR input, X is our dependant variable.
task main()
{
	clearDebugStream();

	motor[left_back] = 25;
	motor[left_front] = 25;
	motor[right_back] = -25;
	motor[right_front] = -25;

	while(true)
	{
		sum_y = 0; //from _x->_y
		sum_xTimesy = 0;
		irInputSum = 0;

		for (int i = 0; i<20 ; i++)
			{
			HTIRS2readAllACStrength(IR, acS1, acS2, acS3, acS4, acS5);
			sum_y += acS3; //READINGS: Fill our array with data from the middle node
			//sum_y += irInput[i]; //CALCULATE: The sum of each value in the array. (its easiest this way)
			sum_xTimesy += (xInput[i] * acS3) ;//EQUATION: Top left half
			writeDebugStream("%i,", acS3);
			writeDebugStreamLine("0");
			Sleep(10);
			}//APROOVED
		mean_xTimesy = (sum_x * sum_y)/20; //EQUATION: Top right half
		slopeLOBF = (sum_xTimesy-mean_xTimesy)/(sum_xSquared - mean_sum_xSquared); //CALCULATE: LOBF slope

		// increment the reading count
		readCount++;

		if (slopeLOBF<0)
		{
			writeDebugStream("%i", readCount);
			PlayTone(1000,13);
			// complete stop
			motor[left_back] = 0;
			motor[left_front] = 0;
			motor[right_back] = 0;
			motor[right_front] = 0;
			// rotate 90 degrees
			/*motor[left_back] = -25;
			motor[left_front] = -25;
			motor[right_back] = -25;
			motor[right_front] = -25;*/

			int i = nMotorEncoder[left_back];
			while (nMotorEncoder[left_back] > i-(1440*0.6))
			{
				motor[left_back] = -25;
				motor[left_front] = -25;
				motor[right_back] = -25;
				motor[right_front] = -25;
			}

			while (nMotorEncoder[left_back] < i+(1440*0.09))
			{
				motor[left_back] = 25;
				motor[left_front] = 25;
				motor[right_back] = -25;
				motor[right_front] = -25;
			}
			// complete stop
			motor[left_back] = 0;
			motor[left_front] = 0;
			motor[right_back] = 0;
			motor[right_front] = 0;
		}
		//y_intLOBF = (sum_y/10) - (5.5 * slopeLOBF); //CALCULATE: LOBF y-intercept -> 5.5 = mean_x
		/*
		while (y_intLOBF >= y_intTH) //So long as we are above our y-intercept threshold AKA know we are close to the top of the curve
			{
			if (slopeLOBF <= slopeTH || slopeTH >=) //Wait untill our LOBF slope falls within our calibrated threshold
				{
				//Make beeping noise perhaps turn left because we have determined the IRSeekerV2 to be facing the IRBeacon
				}
			}
			*/
		writeDebugStream("0,");
		writeDebugStreamLine("%f, ", slopeLOBF);
		Sleep(50);
	}
}
