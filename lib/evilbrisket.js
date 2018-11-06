/*
	Copyright (c) 2017,  Evil Brisket, LLC
	All rights reserved.
*/

var binding = require('bindings')('evilbrisket');
var util = require("util");
var EventEmitter = require("events").EventEmitter;

util.inherits(Evilbrisket, EventEmitter);

function Evilbrisket() {
	EventEmitter.call(this);
}

Evilbrisket.prototype.LED = {
	RED : 0,
	BLUE : 1,
	GREEN : 2
};

Evilbrisket.prototype.PROBE = {
	THERMISTOR_1 : 4,
	THERMISTOR_2 : 6,
	THERMISTOR_3 : 8,
	THERMISTOR_4 : 10,
	THERMISTOR_5 : 12,
	THERMISTOR_6 : 14,
	THERMISTOR_7 : 18,
	THERMOCOUPLE_2 : 15, 
	THERMOCOUPLE_1 : 16, 
	DIODE : 20
};

Evilbrisket.prototype.PROBE_MANUFACTURER = {
	MAVERICK : 1,
	THERMOWORKS : 2,
	IVATION : 3,
	TAPPEQUE : 4,
	WEBER : 5
};

Evilbrisket.prototype.init = function() {
	binding.init()
};

Evilbrisket.prototype.use_probe = function (manufacturer) {
	binding.use_probe(manufacturer);
};

Evilbrisket.prototype.measure_temperature_cb = function(channel, cb) {
	return binding.measure_temperature_cb(channel, cb)
};

Evilbrisket.prototype.measure_temperature = function(channel) {
	return binding.measure_temperature(channel)
};

Evilbrisket.prototype.led = function(l, enabled) {
	return binding.led(l, enabled)
};

var temperatures = null;

Evilbrisket.prototype.lastRead = function() {
	return temperatures;
};

Evilbrisket.prototype.readAllProbes = function() {
	var probes = [
			Evilbrisket.prototype.PROBE.THERMISTOR_1,
			Evilbrisket.prototype.PROBE.THERMISTOR_2,
			Evilbrisket.prototype.PROBE.THERMISTOR_3,
			Evilbrisket.prototype.PROBE.THERMISTOR_4,
			Evilbrisket.prototype.PROBE.THERMISTOR_5,
			Evilbrisket.prototype.PROBE.THERMISTOR_6,
			Evilbrisket.prototype.PROBE.THERMISTOR_7,
			Evilbrisket.prototype.PROBE.THERMOCOUPLE_1,
			Evilbrisket.prototype.PROBE.THERMOCOUPLE_2,
		/*Evilbrisket.prototype.PROBE.DIODE*/];

	 var temps = [];

	Evilbrisket.prototype.led.call(this, Evilbrisket.prototype.LED.RED, 1);

	probes.forEach(function(probe, index) {
		temps.push(Evilbrisket.prototype.measure_temperature.call(this, probe));
	});

	Evilbrisket.prototype.led.call(this, Evilbrisket.prototype.LED.GREED, 0);

	temperatures = temps;
	
	return temps;
};

module.exports = Evilbrisket;
