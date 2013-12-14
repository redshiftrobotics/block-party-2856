var dragSrcEl = null;
var headerString = $("#program-header-text").value;

$("#compile").click(function() {
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
  // e.dataTransfer.effectAllowed = 'move';
  // e.dataTransfer.setData('text/html', this.innerHTML);
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

