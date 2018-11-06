/*
Copyright (c) 2017,  Evil Brisket, LLC
All rights reserved.
*/

var evilbrisket = require('../lib/evilbrisket');

evilbrisket.init()

evilbrisket.led(evilbrisket.LED.RED, true);
evilbrisket.led(evilbrisket.LED.GREEN, true);
evilbrisket.led(evilbrisket.LED.BLUE, true);



// Read each channel
var probes = [
	evilbrisket.PROBE.THERMISTOR_1,
	evilbrisket.PROBE.THERMISTOR_2,
	evilbrisket.PROBE.THERMISTOR_3,
	evilbrisket.PROBE.THERMISTOR_4,
	evilbrisket.PROBE.THERMISTOR_5,
	evilbrisket.PROBE.THERMISTOR_6,
	evilbrisket.PROBE.THERMOCOUPLE_1, 
	evilbrisket.PROBE.THERMOCOUPLE_2, 
	evilbrisket.PROBE.DIODE];


probes.forEach(function(probe, index) {

console.log("Measuring...");

	evilbrisket.measure_temperature_cb(probe, function(ch, temp, err) {

		if (err == 1) {
			console.log("Temperature on channel " + ch + " is " + temp);
		} else {
				console.log("Error on channel " + ch + " is " + err);
		}
	});
})


evilbrisket.led(evilbrisket.LED.RED, false);
evilbrisket.led(evilbrisket.LED.GREEN, false);
evilbrisket.led(evilbrisket.LED.BLUE, false);