#pragma config(Sensor, S1,     DIMU,                sensorI2CCustomFastSkipStates)

#include "drivers/dexterind-imu.h"
#include "drivers/hitechnic-gyro.h"
#include "drivers/hitechnic-accelerometer.h"

// System constants
const float gyroMeasError = 3.14159265358979 * (5.0 / 180.0); // gyroscope measurement error in rad/s (shown as 5 deg/s)
const float beta = sqrt(3.0 / 4.0) * gyroMeasError; // compute beta

// Global system variables
float deltaT;
float a_x, a_y, a_z; // accelerometer measurements
float w_x, w_y, w_z; // gyroscope measurements in rad/s
float SEq_1 = 1.0;
float SEq_2 = 0.0;
float SEq_3 = 0.0;
float SEq_4 = 0.0; // estimated orientation quaternion elements with initial conditions
float q0, q1, q2, q3;

void filterUpdate(float w_x, float w_y, float w_z, float a_x, float a_y, float a_z)
{
// Local system variables
float norm; // vector norm
float SEqDot_omega_1, SEqDot_omega_2, SEqDot_omega_3, SEqDot_omega_4; // quaternion derrivative from gyroscopes elements
float f_1, f_2, f_3; // objective function elements
float J_11or24, J_12or23, J_13or22, J_14or21, J_32, J_33; // objective function Jacobian elements
float SEqHatDot_1, SEqHatDot_2, SEqHatDot_3, SEqHatDot_4; // estimated direction of the gyroscope error
// Axulirary variables to avoid reapeated calcualtions
float halfSEq_1 = 0.5 * SEq_1;
float halfSEq_2 = 0.5 * SEq_2;
float halfSEq_3 = 0.5 * SEq_3;
float halfSEq_4 = 0.5 * SEq_4;
float twoSEq_1 = 2.0 * SEq_1;
float twoSEq_2 = 2.0 * SEq_2;
float twoSEq_3 = 2.0 * SEq_3;

// Normalise the accelerometer measurement
norm = sqrt(a_x * a_x + a_y * a_y + a_z * a_z);
a_x /= norm;
a_y /= norm;
a_z /= norm;
// Compute the objective function and Jacobian
f_1 = twoSEq_2 * SEq_4 - twoSEq_1 * SEq_3 - a_x;
f_2 = twoSEq_1 * SEq_2 + twoSEq_3 * SEq_4 - a_y;
f_3 = 1.0 - twoSEq_2 * SEq_2 - twoSEq_3 * SEq_3 - a_z;
J_11or24 = twoSEq_3; // J_11 negated in matrix multiplication
J_12or23 = 2.0 * SEq_4;
J_13or22 = twoSEq_1; // J_12 negated in matrix multiplication
J_14or21 = twoSEq_2;
J_32 = 2.0 * J_14or21; // negated in matrix multiplication
J_33 = 2.0 * J_11or24; // negated in matrix multiplication
// Compute the gradient (matrix multiplication)
SEqHatDot_1 = J_14or21 * f_2 - J_11or24 * f_1;
SEqHatDot_2 = J_12or23 * f_1 + J_13or22 * f_2 - J_32 * f_3;
SEqHatDot_3 = J_12or23 * f_2 - J_33 * f_3 - J_13or22 * f_1;
SEqHatDot_4 = J_14or21 * f_1 + J_11or24 * f_2;
// Normalise the gradient
norm = sqrt(SEqHatDot_1 * SEqHatDot_1 + SEqHatDot_2 * SEqHatDot_2 + SEqHatDot_3 * SEqHatDot_3 + SEqHatDot_4 * SEqHatDot_4);
SEqHatDot_1 /= norm;
SEqHatDot_2 /= norm;
SEqHatDot_3 /= norm;
SEqHatDot_4 /= norm;
// Compute the quaternion derrivative measured by gyroscopes
SEqDot_omega_1 = -halfSEq_2 * w_x - halfSEq_3 * w_y - halfSEq_4 * w_z;
SEqDot_omega_2 = halfSEq_1 * w_x + halfSEq_3 * w_z - halfSEq_4 * w_y;
SEqDot_omega_3 = halfSEq_1 * w_y - halfSEq_2 * w_z + halfSEq_4 * w_x;
SEqDot_omega_4 = halfSEq_1 * w_z + halfSEq_2 * w_y - halfSEq_3 * w_x;
// Compute then integrate the estimated quaternion derrivative
SEq_1 += (SEqDot_omega_1 - (beta * SEqHatDot_1)) * deltaT;
SEq_2 += (SEqDot_omega_2 - (beta * SEqHatDot_2)) * deltaT;
SEq_3 += (SEqDot_omega_3 - (beta * SEqHatDot_3)) * deltaT;
SEq_4 += (SEqDot_omega_4 - (beta * SEqHatDot_4)) * deltaT;
// Normalise quaternion
norm = sqrt(SEq_1 * SEq_1 + SEq_2 * SEq_2 + SEq_3 * SEq_3 + SEq_4 * SEq_4);
SEq_1 /= norm;
SEq_2 /= norm;
SEq_3 /= norm;
SEq_4 /= norm;
}

task main()
{
	int now = 0;
	int lastUpdate = 0;
	float euler[3];

	if (!DIMUconfigAccel(DIMU, DIMU_ACC_RANGE_2G))		//startup accelerometer
    PlaySound(soundException);

  if(!DIMUconfigGyro(DIMU, DIMU_GYRO_RANGE_500))	 //startup gyro
    PlaySound(soundException);

	while(true) {
 			// read accelerometer, 10 bits
 			DIMUreadAccelAxes10Bit(DIMU, a_x, a_y, a_z);

 			// read gyro, degrees per second
 			DIMUreadGyroAxes(DIMU, w_x, w_y, w_z);

 			//convert to rad/s
 			w_x *= PI/180;
 			w_y *= PI/180;
 			w_z *= PI/180;

			now = nPgmTime;
 			deltaT = (now - lastUpdate) / 1000.0; // in seconds
 			lastUpdate = now;

 			//call function to find quaternion
 			filterUpdate(w_x, w_y, w_z, a_x, a_y, a_z);

 			q0 = SEq_1;
  		q1 = SEq_2;
  		q2 = SEq_3;
  		q3 = SEq_4;

 			//compute euler angles
	 	 	euler[0] = atan2(2 * q1 * q2 - 2 * q0 * q3, 2 * q0*q0 + 2 * q1 * q1 - 1); // psi
  		euler[1] = -asin(2 * q1 * q3 + 2 * q0 * q2); // theta
  		euler[2] = atan2(2 * q2 * q3 - 2 * q0 * q1, 2 * q0 * q0 + 2 * q3 * q3 - 1); // phi

  		writeDebugStreamLine("q0, %f", q0);
 			writeDebugStream("  q1, %f", q1);
 			writeDebugStream("  q2, %f", q2);
 			writeDebugStream("  q3, %f", q3);
 			writeDebugStream("  Psi, %f", euler[0]);
 			writeDebugStream("  Theta, %f", euler[1]);
 			writeDebugStream("  Phi, %f", euler[2]);
 			writeDebugStream("  Hz, %f", deltaT);

 			eraseDisplay();
 			nxtDisplayString(0, "%f", euler[0]);
 			nxtDisplayString(1, "%f", euler[1]);
 			nxtDisplayString(2, "%f", euler[2]);

 			wait1Msec(10);

	}
}
