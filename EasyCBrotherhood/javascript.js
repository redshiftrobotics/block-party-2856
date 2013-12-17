function getMotorConfig()
{
	motors = [];
  var motorConfigs = $("#motor-config").children(".command");
	for(i = 0; i < motorConfigs.length; i++)
	{
    var current = $(motorConfigs[i]);
    var motorId = i+1;
		var motorPort = parseInt(current.children(".motor-port")[0].value);
		var motorDaisychain = parseInt(current.children(".motor-daisychain")[0].value);
		var motorNumber = parseInt(current.children(".motor-number")[0].value);
		motors.push({
      motorId: motorId,
      port: motorPort,
      daisy: motorDaisychain,
      number: motorNumber
    });
	}
}

var dragSrcEl = null;
var headerString = $("#program-header-text").value;

$("#compile").click(function() {
  getMotorConfig();
  parseProgram();
})

function getMotorValues(motorId) {
  window.motors.forEach(function(motor,index,motorList) {
    if (motor.motorId === motorId) {
      return motor;
    }
  })
}

function addSleep(time) {
  programString += "Sleep("+time*1000+");";
}

function addMotorSpeed(motorId, speed) {
  var motor = getMotorValues(motorId);
  programString += "Motors_MoveSpeed(S"+motor.port+", "+motor.daisy+", "+motor.number+", "+speed+");";
}

function addMotorRotation(motorId, rotations, speed) {
  var motor = getMotorValues(motorId);
  programString += "Motors_MoveRotations(S"+motor.port+", "+motor.daisy+", "+motor.number+", "+rotations+", "+speed+");";
}

function addMoveServo(motorId, position) {
  var motor = getMotorValues(motorId);
  programString += "Servos_SetPosition(S"+motor.port+", "+motor.daisy+", "+motor.number+", "+position+");";
}

function validateValues(element, values) {
  if (values.sleep) {
    if (!typeof values.sleep === "number" || values.sleep < 0) {
      alert("Command: "+element+"has an invalid parameter");
      return false;
    }
  }
  if (values.motorId) {
    var motorValid = false;
    for (var i=0; i<window.motors.length;i++) {
      if (window.motors[i].motorId === values.motorId) {
        motorValid = true;
      }
      if (!motorValid) {
        return false;
      }
    }
  }
  //TODO: Add more validation cases for the rest of the values
  return true;
}

function parseProgram() {
  var programString = "";
  
  var elementList = $(".panel-right").children(); 
  elementList.forEach(function(command, index, list) {
    switch (command.attr("command-type")) {
      case "sleep":
        var sleepTime = command.children(".sleep-value").first().value;
        var values = {
          sleep: sleepTime
        };
        if (validateValues(command,values)) {
          addSleep(sleepTime);
        }
      break;

      case "motor-speed":
        var motorId = command.children(".motor-id").first().value;
        var speed = command.children(".speed-value").first().value;
        var values = {
          motorId: motorId,
          speed: speed
        };
        if (validateValues(command,values)) {
          addMotorSpeed(motorId, speed);
        }
      break;

      case "motor-rotation":
        var motorId = command.children(".motor-id").first().value;
        var speed = command.children(".speed-value").first().value;
        var rotations = command.children(".rotation-value").first().value;
        var values = {
          motorId: motorId,
          speed: speed,
          rotations: rotations
        };
        if (validateValues(command, values)) {
          addMotorRotation(motorId, rotations, speed);
        }
      break;

      case "move-servo":
        var motorId = command.children(".motor-id").first().value;
        var position = command.children(".position-value").first().value;
        var values = {
          motorId: motorId,
          position: position
        }
        if (validateValues(command, values)) {
          addMoveServo(motorId, position);
        }
      break;

      default:
      break;
    }
  });
  $("#program").value = programString;
}

function handleDragStart(e) {
	// Target (this) element is the source node.
	dragSrcEl = this;
	e.dataTransfer.effectAllowed = 'move';
	e.dataTransfer.setData('text/html', this.innerHTML);
}

function handleDrop(e) {
  this.classList.remove('selected');
  if (e.stopPropagation) {
    e.stopPropagation(); // Stops some browsers from redirecting.
  }
  
  if(dragSrcEl == document.getElementById("trash"))
  {
	alert("Trashing me");
    this.remove();
  }
  else if (dragSrcEl != this && dragSrcEl.parentNode.getAttribute('id') == "Program")
  {
    dragSrcEl.innerHTML = this.innerHTML;
    this.innerHTML = e.dataTransfer.getData('text/html');
  }
  return false;
}

function handleDragOver(e) {
  if (e.preventDefault) {
    e.preventDefault(); // Necessary. Allows us to drop.
  }
  e.dataTransfer.dropEffect = 'move'; // See the section on the DataTransfer object. 
  if(this != dragSrcEl && dragSrcEl.parentNode.getAttribute('id') == "Program")
  {
    this.classList.add('selected');
  }
  return false;
}
  
function handleDragLeave(e) {
  if(dragSrcEl.parentNode.getAttribute('id') == "Program")
  {
    this.classList.remove('selected');
  }
  return false;
}

function trashDrop(e) {
  if (e.stopPropagation) {
    e.stopPropagation(); // Stops some browsers from redirecting.
  }
  if(dragSrcEl.parentNode.getAttribute('id') == "Program")
  {
    dragSrcEl.remove();
  }
  return false;
}

function trashDragOver(e) {
  if (e.preventDefault) {
    e.preventDefault(); // Necessary. Allows us to drop.
  }
  e.dataTransfer.dropEffect = 'move'; // See the section on the DataTransfer object. 
  return false;
}

function addDrop(e) {
  this.classList.remove('selected');
  if (e.stopPropagation) {
    e.stopPropagation(); // Stops some browsers from redirecting.
  }
  
  var node = dragSrcEl.cloneNode(true);
  $(".panel-right")[0].appendChild(node);

  node.on('dragstart', handleDragStart);
  node.on('dragover', handleDragOver);
  node.on('dragleave', handleDragLeave);
  node.on('drop', handleDrop);
  
  return false;
}

function addDragOver(e) {
  if (e.preventDefault) {
    e.preventDefault(); // Necessary. Allows us to drop.
  }
  e.dataTransfer.dropEffect = 'move'; // See the section on the DataTransfer object. 
  $(this).addClass("selected");
  
  return false;
}

function addDragLeave(e) {
  $(this).removeClass('selected');
  return false;
}

var trashElement = $("#trash");
var add = $(".panel-right");

trashElement.bind('dragover', trashDragOver);
trashElement.bind('drop', trashDrop);

add.bind('dragover', addDragOver);
add.bind('drop', addDrop);
add.bind('dragleave', addDragLeave);

var commandblocks = $('.command');
for(var i=0;i<commandblocks.length;i++) {
  $(commandblocks[i]).on('dragstart', handleDragStart);
  $(commandblocks[i]).on('dragover', handleDragOver);
  $(commandblocks[i]).on('dragleave', handleDragLeave);
  $(commandblocks[i]).on('dragend', handleDrop);
};

