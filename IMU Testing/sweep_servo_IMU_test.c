#pragma config(Sensor, S1,     HTGYRO,              sensorAnalogInactive)
#pragma config(Sensor, S2,     HTAC,                sensorI2CCustom)
#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Servo,  srvo_S3_C1_1,    Turret,               tServoStandard)
#pragma config(Servo,  srvo_S3_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_6,    servo6,               tServoNone)

task main()
{
	int servoPosition = 100;
	int now = 0;
	int lastUpdate = 0;
	int servoTimeStamp = 0;
	int servoLastIncrement = 0;

	servo[Turret] = servoPosition;
	wait1Msec(3000);

	while(servoPosition < 200) {

			servo[Turret] = servoPosition;
			servoTimeStamp = nPgmTime;

			if(servoTimeStamp - servoLastIncrement > 100) {
					servoPosition += 1;
					servoLastIncrement = servoTimeStamp;
				}
			}

			wait1Msec(5000);
		}
