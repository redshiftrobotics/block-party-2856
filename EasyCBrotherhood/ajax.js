var libraryRequests = ["drivers/common", "I2C", "Motors", "Servos"];
var libraryText = ["drivers/common", "I2C", "Motors", "Servos"];
var numberOfLoadedLibraries = 0;
var programheader;

// TODO: don't use rawgithub.com
// we have to use rawgithub.com instead of raw.github.com because GitHub sends a MIME of text/plain and XMLHttpRequest only accepts text/html, text/xml, etc.
var library_base_url = "https://rawgithub.com/saasrobotics/Robotics2013-14/master/libraries/";

var pragmaConfig = "#pragma config(Sensor, S1,     ,               sensorI2CCustom)\n#pragma config(Sensor, S2,     ,               sensorI2CCustom)\n#pragma config(Sensor, S3,     ,               sensorI2CCustom)\n#pragma config(Sensor, S4,     ,               sensorI2CCustom)\n";

function requestLibrary(name)
{
	console.log("requesting " + name);
	libraryRequests[name] = new XMLHttpRequest();
	libraryRequests[name].onload = function(){recieveLibrary(name);};
	libraryRequests[name].open("get", library_base_url + name + ".h", true);
	libraryRequests[name].send();
}

function recieveLibrary(name)
{
	console.log("received " + name);
	
	// filter out #include directives
	var array = libraryRequests[name].responseText.split("\n");
	array = $.grep(array, function(string) {
		return (string.indexOf("#include") !== -1 && string.indexOf("firmwareVersion.h") == -1);			
	}, true);
 	libraryText[name] = array.join("\n");

	numberOfLoadedLibraries++;

	if (numberOfLoadedLibraries == 4) {
		// everything's done loading
		console.log("loaded all libraries");
		
		// instantiate the data into JavaScript
		programheader = pragmaConfig + libraryText["drivers/common"] + libraryText["I2C"] + libraryText["Motors"] + libraryText["Servos"];
		
		// get rid of the infobar and enable the app
		$("#loadingAlert").remove();
		$("#addButton").removeAttr("disabled");
	}
}
