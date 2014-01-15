#include "ServoMovement.c"
float InverseKinematics_ToRadians(float Degree)
{
    return Degree * 0.0174532925;
}

float InverseKinematics_ToDegrees(float Radian)
{
    return Radian / 0.0174532925;
}

void InverseKinematics_SolveTriangle(int a, int b, int c, int *A, int *B, int *C)
{
    *A = InverseKinematics_ToDegrees(Acos((-Pow(a, 2) + Pow(b, 2) + Pow(c, 2)) / (2 * b * c)));
    *B = InverseKinematics_ToDegrees(Acos((Pow(a, 2) - Pow(b, 2) + Pow(c, 2)) / (2 * a * c)));
    *C = InverseKinematics_ToDegrees(Acos((Pow(a, 2) + Pow(b, 2) - Pow(c, 2)) / (2 * a * b)));
}

void InverseKinematics_TwoJoint(float LengthOne, float LengthTwo, float PointX, float PointY, int *DegreeOne, int *DegreeTwo)
{
    float c = Sqrt((PointX * PointX) + (PointY * PointY));
    float ah = InverseKinematics_ToDegrees(Atan(PointX / PointY));
    //b == solve.y
    //c == solve.z
    int A = 0;
    int B = 0;
    int C = 0;

    InverseKinematics_SolveTriangle(LengthOne, LengthTwo, c, &A, &B, &C);

    float AngleOne = (B + ah);
    float AngleTwo = -(180 - C);

    //angle one: Counterclockwise angle starting at a vertical position
    //Angle two: Counterclockwise angle proportional to segment 1
    //return new Vector2(AngleOne, AngleTwo);
    *DegreeOne = AngleOne;
    *DegreeTwo = AngleTwo;
}

bool InverseKinematics_TryMove(float Angle1, float Angle2, float Angle3, int PointX, int PointY, int PointZ)
{
	//calculate target angel of middle joint. This will be pivoted around to derrive two possible positions
  float BottomLength = sqrt(pow(PointX, 2) + pow(PointZ, 2));
  float TargetAngle = InverseKinematics_ToDegrees(atan(PointY / BottomLength));
  TargetAngle -= 90;

  //move the parts
  string MIDDLEJOINT = "Middle Joint";
  string TOPJOINT = "Top Joint";
  string TURRET = "Turret";

	writeDebugStream("%i", Angle1);
	writeDebugStream(", %i", Angle2);
	writeDebugStreamLine(", %i", Angle3);
	writeDebugStream("%i", Angle1);
	writeDebugStream(", %i", TargetAngle + (TargetAngle - Angle2));
	writeDebugStreamLine(", %i", -Angle3);

  if(MovementLibraries_TestRange(MIDDLEJOINT, Angle2) && MovementLibraries_TestRange(TOPJOINT, Angle3))
  {
	  MovementLibraries_MoveTurret(Angle1);
	  MovementLibraries_MoveMiddleJoint(Angle2);
	  MovementLibraries_MoveTopJoint(Angle3);

	  writeDebugStream("%i", Angle1);
	  writeDebugStream(", %i", Angle2);
	  writeDebugStreamLine(", %i", Angle3);
	  return true;
	}
	else if(MovementLibraries_TestRange(MIDDLEJOINT, TargetAngle + (TargetAngle - Angle2)) && MovementLibraries_TestRange(TOPJOINT, -Angle3))
	{
		MovementLibraries_MoveTurret(Angle1);
	  MovementLibraries_MoveMiddleJoint(TargetAngle + (TargetAngle - Angle2));
	  MovementLibraries_MoveTopJoint(-Angle3);

	  writeDebugStream("%i", Angle1);
	  writeDebugStream(", %i", TargetAngle + (TargetAngle - Angle2));
	  writeDebugStreamLine(", %i", -Angle3);
	  return true;
	}
	else
	{
		writeDebugStreamLine("Failed: angle out of range");
		return false;
	}
}

bool InverseKinematics_ThreeJoint(float LengthOne, float LengthTwo, float PointX, float PointY, float PointZ)
{
	//orientation: X is left and right, Y is up and down, Z is forward and backward
	//Angle 1: Bottom swivel
	//Angle 2: Middle joint
  //Angle 3: Top joint

	//makes sure that if the value is negative although squaring is used the answer can be negative
	int Multiplier = 0;
	if (PointZ + PointX >= 0)
	{
	    Multiplier = 1;
	}
	else
	{
	    Multiplier = -1;
	}

	if(PointZ == 0)
	{
		PointZ = .01;
	}

	int KinematicResultX = 0;
	int KinematicResultY = 0;

	InverseKinematics_TwoJoint(LengthOne, LengthTwo, (Multiplier * sqrt(Pow(PointZ, 2) + Pow(PointX, 2))), PointY, &KinematicResultX, &KinematicResultY);
	return InverseKinematics_TryMove(InverseKinematics_ToDegrees(Atan(-PointX / PointZ)), KinematicResultX, KinematicResultY, PointX, PointY, PointZ);

}
