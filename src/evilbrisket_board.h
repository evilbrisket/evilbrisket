/*
Copyright (c) 2017,  Evil Brisket, LLC
All rights reserved.
*/

#include "bcm2835.h"

typedef enum {
	RED = RPI_GPIO_P1_15,
	GREEN = RPI_GPIO_P1_16,
	BLUE =	RPI_GPIO_P1_18	
} eb_led;

typedef enum {
	MAVERICK = 1,
	THERMOWORKS = 2,
	IVATION = 3,
	TAPPEQUE = 4,
	WEBER = 5
} eb_manufacturer;

/* Initialize the Evil Brisket board */
bool init();

/* Specify which probe we're using */
bool init_for_probe(eb_manufacturer manufacturer);

/* Turn on/off the specified LED on the Evil Brisket board */
void led(eb_led led, bool enable);


