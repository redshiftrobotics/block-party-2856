var CurrentBlock;
var ReturnCode = new Array();
var CodeAddition = $("#LibrariesText").text();
var BlocksAdded = 0;
var Context;
var Canvas;


function RefreshPage()
{
	document.getElementById("TextArea").value = "";
	location.reload();
}

function Initialize()
{
	Canvas = document.getElementById('canvas');
	Context = Canvas.getContext('2d');
	Context.fillStyle = "Black";
	Context.fillRect(0, 0, Canvas.width, Canvas.height);
	Sleep();
}

function Add()
{
	var AddedBlock = false;
	
	if(CurrentBlock == "ServoPosition" && document.getElementById("ServoPositionPosition").value != "" && document.getElementById("ServoPositionPort").value != "" && document.getElementById("ServoPositionDaisyChain").value != "" && document.getElementById("ServoPositionMotorNumber").value != "")
	{
		ReturnCode[ReturnCode.length] = "Servos_SetPosition(S" + document.getElementById("ServoPositionPort").value + ", " + document.getElementById("ServoPositionDaisyChain").value + ", " + document.getElementById("ServoPositionMotorNumber").value + ", " + document.getElementById("ServoPositionPosition").value + ");\n";
		
		Context.fillStyle = "Pink";
		Context.fillRect(5, 5 + BlocksAdded * 55, 300, 50);
		Context.fillStyle = "Black";
		Context.fillText("Servo position " + document.getElementById("ServoPositionPosition").value + ", port S" + document.getElementById("ServoPositionPort").value + ", daisy chain level " + document.getElementById("ServoPositionDaisyChain").value + ", servo " + document.getElementById("ServoPositionMotorNumber").value, 10, 25 + BlocksAdded * 55);
		
		AddedBlock = true;
	}
	else if(CurrentBlock == "Sleep" && document.getElementById("SleepSeconds").value != "")
	{
		ReturnCode[ReturnCode.length] = "Sleep(" + document.getElementById("SleepSeconds").value * 1000 + ");\n";
		
		Context.fillStyle = "Blue";
		Context.fillRect(5, 5 + BlocksAdded * 55, 300, 50);
		Context.fillStyle = "Black";
		Context.fillText("Sleep for " + document.getElementById("SleepSeconds").value + " seconds.", 10, 25 + BlocksAdded * 55);
		
		AddedBlock = true;
	}
	else if(CurrentBlock == "TurnRotations" && document.getElementById("TurnRotationsDaisyChain").value != "" && document.getElementById("TurnRotationsMotor").value != "" && document.getElementById("TurnRotationsPort").value != "" && document.getElementById("TurnRotationsNumber").value != "" && document.getElementById("TurnRotationsSpeed").value != "")
	{
		var Encoder = "(I2C_GetEncoderPosition(S" + document.getElementById("TurnRotationsPort").value + ", " +  document.getElementById("TurnRotationsDaisyChain").value + ", " + document.getElementById("TurnRotationsMotor").value + ")";
		var AmountToAdd =  document.getElementById("TurnRotationsNumber").value * 1440 + "" + ")";
		ReturnCode[ReturnCode.length] = "Motors_SetPosition(S" + document.getElementById("TurnRotationsPort").value + ", " + document.getElementById("TurnRotationsDaisyChain").value + ", " + document.getElementById("TurnRotationsMotor").value + ", "  + Encoder + " + " + AmountToAdd + ", " + document.getElementById("TurnRotationsSpeed").value + ");\n"; 
	
				
		Context.fillStyle = "Brown";
		Context.fillRect(5, 5 + BlocksAdded * 55, 300, 50);
		Context.fillStyle = "Black";
		Context.fillText("Turn for " + document.getElementById("TurnRotationsNumber").value + " rotations on port " + document.getElementById("TurnRotationsPort").value + ", daisy chain level " + document.getElementById("TurnRotationsDaisyChain").value + ", motor " + document.getElementById("TurnRotationsMotor").value + ".", 10, 25 + BlocksAdded * 55);
		AddedBlock = true;
	}	
	else if(CurrentBlock == "MoveSpeed" && document.getElementById("MoveSpeedSpeed").value != "" && document.getElementById("MoveSpeedPort").value != "" && document.getElementById("MoveSpeedMotor").value != "" && document.getElementById("MoveDaisyChain").value != "")
	{
		ReturnCode[ReturnCode.length] = "Motors_SetSpeed(S"  + document.getElementById("MoveSpeedPort").value + ", " + document.getElementById("MoveDaisyChain").value + ", " + document.getElementById("MoveSpeedMotor").value + ", " + document.getElementById("MoveSpeedSpeed").value + ");\n";
	
		Context.fillStyle = "Green";
		Context.fillRect(5, 5 + BlocksAdded * 55, 300, 50);
		Context.fillStyle = "Black";
		Context.fillText("Move port " + document.getElementById("MoveSpeedPort").value + ", daisy chain level " + document.getElementById("MoveDaisyChain").value + ", motor " + document.getElementById("MoveSpeedMotor").value + " at " + document.getElementById("MoveSpeedSpeed").value + " percent speed.", 10, 25 + BlocksAdded * 55);
		AddedBlock = true;
	}
	else
	{
		alert("Not all text boxes filled out");
	}
	
	if(AddedBlock)
	{
		BlocksAdded++;
		
		var TextAreaValue = "";
		
		for(i = 0; i < ReturnCode.length; i++)
		{
			TextAreaValue += ReturnCode[i];
		}
		document.getElementById("TextArea").value = CodeAddition;
		document.getElementById("TextArea").value += "task main() {\n";
		document.getElementById("TextArea").value += TextAreaValue;
		document.getElementById("TextArea").value += "}\n";
		
		
		ResetTextBoxes();
	}
}

function ResetTextBoxes()
{
	document.getElementById("ServoPositionPosition").value = "";
	document.getElementById("ServoPositionPort").value = "";
	document.getElementById("ServoPositionDaisyChain").value = "";
	document.getElementById("ServoPositionMotorNumber").value = "";
	
	document.getElementById("SleepSeconds").value = "";
	document.getElementById("TurnRotationsMotor").value = "";
	document.getElementById("TurnRotationsPort").value = "";
	document.getElementById("TurnRotationsNumber").value = "";
	document.getElementById("MoveSpeedSpeed").value = "";
	document.getElementById("MoveSpeedPort").value = "";
	document.getElementById("MoveDaisyChain").value = "";
	document.getElementById("MoveSpeedMotor").value = "";
	document.getElementById("TurnRotationsSpeed").value = "";
	document.getElementById("TurnRotationsDaisyChain").value = "";
}

function Sleep()
{
	ShowElement("Sleep");
}

function ServoPosition()
{
	ShowElement("ServoPosition");
}

function TurnRotations()
{
	ShowElement("TurnRotations");
}

function MoveSpeed()
{
	ShowElement("MoveSpeed");
}

function ShowElement(ID)
{
	$("#Sleep").hide();
	$("#TurnRotations").hide();
	$("#MoveSpeed").hide();
	$("#ServoPosition").hide();
	$("#" + ID).show();
	CurrentBlock = ID;
}




