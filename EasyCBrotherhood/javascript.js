var IDAttributes = new Array();



function CalculateIDAttributes()
{
	IDAttributes = [];
	for(i = 0; i < $("#motor-config").children(".command").length; i++)
	{
		var Child = $("#motor-id-" + (i + 1));
		var MotorPort = Child.children(".motor-port").value;
		
		alert(Child.children(".motor-port").value);
		var MotorDaisychain = Child.children(".motor-daisychain").value;
		var MotorNumber = Child.children(".motor-number").value;
		IDAttributes.push([MotorPort, MotorDaisychain, MotorNumber]);
	}
}

function Compile()
{
	CalculateIDAttributes();
}

var dragSrcEl = null;

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
  document.getElementById("Program").appendChild(node);

  node.addEventListener('dragstart', handleDragStart, false);
  node.addEventListener('dragover', handleDragOver, false);
  node.addEventListener('dragleave', handleDragLeave, false);
  node.addEventListener('drop', handleDrop, false);
  
  return false;
}

function addDragOver(e) {
  if (e.preventDefault) {
    e.preventDefault(); // Necessary. Allows us to drop.
  }
  e.dataTransfer.dropEffect = 'move'; // See the section on the DataTransfer object. 
  this.classList.add('selected');
  
  return false;
}

function addDragLeave(e) {
  this.classList.remove('selected');
  return false;
}

var TrashElement = document.getElementById("Trash");
var Add = document.getElementById("Add");

TrashElement.addEventListener('dragover', trashDragOver, false);
TrashElement.addEventListener('drop', trashDrop, false);

Add.addEventListener('dragover', addDragOver, false);
Add.addEventListener('drop', addDrop, false);
Add.addEventListener('dragleave', addDragLeave, false);

var cols = document.querySelectorAll('.Command');
[].forEach.call(cols, function(col)
{
  col.addEventListener('dragstart', handleDragStart, false);
  col.addEventListener('dragover', handleDragOver, false);
  col.addEventListener('dragleave', handleDragLeave, false);
  col.addEventListener('drop', handleDrop, false);
});