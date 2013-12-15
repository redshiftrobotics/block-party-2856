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

$("#compile").click(function() {
  getMotorConfig();
  parseProgram();
})

function getMotorValues(id) {
  for (var i=0; i<motors.length;i++) {
    if (motors[i].motorId === id) {
      if (isNaN(motors[i].port) || isNaN(motors[i].daisy) || isNaN(motors[i].number)) {
        alert("Motor "+id+" is used, but is not configured correctly!");
        return null;
      } 
      return motors[i];
    }
  }
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
    if (isNaN(values.sleep) || values.sleep < 0) {
      console.log(element[0]);
      alert("Command: "+element+" has an invalid sleep time (positive floats allowed)");
      return false;
    }
  }
  if (values.motorId) {
    var motorValid = false;
    for (var i=0; i<window.motors.length;i++) {
      if (window.motors[i].motorId === values.motorId) {
        motorValid = true;
      }
    }
    if (!motorValid) {
      alert("Command: "+element+" has an invalid motorId");
      return false;
    }
  }
  if (values.speed) {
    if (isNaN(values.speed) || values.speed < -100 || values.speed > 100) {
      alert("Command: "+element+" has an invalid speed value (-100 through 100 integer allowed)");
      return false;
    }
  }
  if (values.rotations) {
    if (isNaN(values.rotations)) {
      alert("Command: "+element+" has an invalid rotation number (positive or negative floats allowed)");
      return false;
    }
  }
  if (values.position) {
    if (isNaN(values.position) || values.position < 0 || values.position > 256) {
      alert("Command: "+element+" has an invalid position number (0-256 integers allowed)")
    }
  }
  return true;
}

function parseProgram() {
  programString = $("#program-header-text").text();
  
  var elementList = $("#workbench").children();
  elementList.each(function() {
    var command = $(this);
    switch (command.attr("command-type")) {
      case "sleep":
        var sleepTime = parseFloat(command.children(".sleep-value")[0].value);
        var values = {
          sleep: sleepTime
        };
        if (validateValues(command,values)) {
          addSleep(sleepTime);
        }
      break;

      case "motor-speed":
        var motorId = parseInt(command.children(".motor-id")[0].value);
        var speed = parseInt(command.children(".speed-value")[0].value);
        var values = {
          motorId: motorId,
          speed: speed
        };
        if (validateValues(command,values)) {
          addMotorSpeed(motorId, speed);
        }
      break;

      case "motor-rotation":
        var motorId = parseInt(command.children(".motor-id")[0].value);
        var speed = parseInt(command.children(".speed-value")[0].value);
        var rotations = parseFloat(command.children(".rotation-value")[0].value);
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
        var motorId = parseInt(command.children(".motor-id")[0].value);
        var position = parseInt(command.children(".position-value")[0].value);
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
  console.log(programString);
  $("#program").text(programString);
  $("body, html").animate({scrollTop: $(".program-window").offset().top-45});
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
  
  if(this == document.getElementById("Trash"))
  {
    dragSrcEl.remove();
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
  $(".panel-right").appendChild(node);

  node.on('dragstart', handleDragStart, false);
  node.on('dragover', handleDragOver, false);
  node.on('dragleave', handleDragLeave, false);
  node.on('drop', handleDrop, false);
  
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

trashElement.on('dragover', trashDragOver, false);
trashElement.on('drop', trashDrop, false);

add.on('dragover', addDragOver, false);
add.on('drop', addDrop, false);
add.on('dragleave', addDragLeave, false);

var commands = $('.command');
for(var i=0;i<commands.length;i++) {
  $(commands[i]).on('dragstart', handleDragStart);
  $(commands[i]).on('dragover', handleDragOver);
  $(commands[i]).on('dragleave', handleDragLeave);
  $(commands[i]).on('dragend', handleDrop);
};

