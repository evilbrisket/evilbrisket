/*
	Copyright (c) 2017,  Evil Brisket, LLC
	All rights reserved.
*/

#include <node.h>
#include <nan.h>

extern "C" {
	#include "evilbrisket_board.h"
	#include "LTC2983_support_functions.h"
	#include "LTC2983_configuration_constants.h"
}

using namespace Nan;

NAN_METHOD(init)
{
	init();
};

NAN_METHOD(use_probe)
{
	if (info.Length() != 1) {
		return ThrowTypeError("Incorrect number of arguments.");
	}
	
	if (!info[0]->IsNumber()) {
		return ThrowTypeError("Incorrect argument type for probe manufacturer.");
	}
	
	init_for_probe(eb_manufacturer((int)info[0]->NumberValue()));
	
};

NAN_METHOD(measure_temperature)
{
	int channel = -1;
	uint8_t fault = VALID;
	
	if (info.Length() != 1) {
		return ThrowTypeError("Incorrect number of arguments.");
	}
	
	if (info[0]->IsNumber()) {
		channel = info[0]->NumberValue();
	}  else {
		return ThrowTypeError("Incorrect argument type for channel.");
	}

	float t = measure_temperature(channel, &fault);

	info.GetReturnValue().Set(t);
};

NAN_METHOD(measure_temperature_cb)
{
	int channel = -1;
	uint8_t fault = VALID;
	
	if (info.Length() != 2) {
		return ThrowTypeError("Incorrect number of arguments.");
	}
	
	if (info[0]->IsNumber()) {
		channel = info[0]->NumberValue();
	}  else {
		return ThrowTypeError("Incorrect argument type for channel.");
	}

	float t = measure_temperature(channel, &fault);
	
	Callback *callback = new Callback(To<v8::Function>(info[1]).ToLocalChecked());
	
	v8::Local<v8::Value> results[] = {
			New<v8::Number>(channel), 
	        New<v8::Number>(t), 
			New<v8::Number>(fault)
	};
	
	callback->Call(3, results);

};

NAN_METHOD(led)
{
	if (info.Length() != 2) {
		return ThrowTypeError("Incorrect number of arguments.");
	}
	
	if (!info[0]->IsNumber() && !info[1]->IsNumber()) {
		return ThrowTypeError("Incorrect argument type for channel.");
	}
	
	// Map LED 0,1,2 to red, green, blue
	eb_led l;
	
	switch((int)info[0]->NumberValue()) {
	case 0:
		l = RED;
		break;
	case 1:
		l = BLUE;
		break;
	case 2:
		l = GREEN;
		break;
	default:
		return ThrowTypeError("Invalid LED specified.");
	}
	
	bool enabled = info[1]->NumberValue();
	
	led(l, enabled);
};

NAN_MODULE_INIT(setup)
{
	NAN_EXPORT(target, init);
	NAN_EXPORT(target, use_probe);
	NAN_EXPORT(target, measure_temperature);
	NAN_EXPORT(target, measure_temperature_cb);
	NAN_EXPORT(target, led);
};

NODE_MODULE(evilbrisket, setup)