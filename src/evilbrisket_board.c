/*

Copyright (c) 2017,  Evil Brisket, LLC
All rights reserved.

*/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <bcm2835.h>

#include "evilbrisket_board.h"
#include "LTC2983_configuration_constants.h"
#include "LTC2983_support_functions.h"
#include "LTC2983_table_coeffs.h"

bool init() {
 
    if (!bcm2835_init() || !bcm2835_spi_begin()) {
	   printf("*** ERROR: Unable to initialize bcm2835 ***\n");
       return 0;
    }
	   
	// LTC2983 SPI
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);  
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);  
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_512);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                  
 	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);     

	// Red LED
	bcm2835_gpio_fsel(RPI_GPIO_P1_15, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(RPI_GPIO_P1_15, LOW);
	
	// Blue LED
	bcm2835_gpio_fsel(RPI_GPIO_P1_18, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(RPI_GPIO_P1_18, LOW);
	
	// Green LED
	bcm2835_gpio_fsel(RPI_GPIO_P1_16, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(RPI_GPIO_P1_16, LOW);

	// LTC2983 status
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_38, BCM2835_GPIO_FSEL_INPT);

	// LTC2983 Reset
	bcm2835_gpio_fsel(RPI_BPLUS_GPIO_J8_40, BCM2835_GPIO_FSEL_OUTP);
	
	return init_for_probe(THERMOWORKS);
}

bool init_for_probe(eb_manufacturer manufacturer) {
	
	// GPIO 21 (physical pin 40) is reset. 
	// While this pin is LOW, the device is forced into the reset state. 
	//Once this pin is returned HIGH, the device initiates its start-up sequence. 	
	
	bcm2835_gpio_write(RPI_BPLUS_GPIO_J8_40, LOW);
	
	// Enter initialization state on LTC2983
	bcm2835_gpio_write(RPI_BPLUS_GPIO_J8_40, HIGH);
	
	// Wait for LTC2983 ready state
	while (0 == bcm2835_gpio_lev(RPI_V2_GPIO_P1_38));
	      
	// Initialize the LTC2983 with Evil Brisket board config
	configure_channels();			
	configure_memory_table(manufacturer);
	configure_global_parameters();
		
	printf("*** LTC2983 is ready ***\n");
			
	return 0;
}

void led(eb_led led, bool enable) {
	bcm2835_gpio_write(led, enable);
}

