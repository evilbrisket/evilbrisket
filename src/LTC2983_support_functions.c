/*!

LTC2983_support_functions.cpp:
This file contains all the support functions used in the main program.

http://www.linear.com/product/LTC2983

http://www.linear.com/product/LTC2983#demoboards

$Revision: 1.3.4 $
$Date: October 5, 2016 $
Copyright (c) 2014, Linear Technology Corp.(LTC)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of Linear Technology Corp.

The Linear Technology Linduino is not affiliated with the official Arduino team.
However, the Linduino is only possible because of the Arduino team's commitment
to the open-source community.  Please, visit http://www.arduino.cc and
http://store.arduino.cc , and consider a purchase that will help fund their
ongoing work.

12/15/2017 - Rob Derstadt <rob@evilbrisket.com> 
Modified to work on RaspberryPi using bcm2835 library and Evil Brisket temperature board. The LTC2983 
configuration in this file is specific to the Evil Brisket Board.

*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <bcm2835.h>
#include "LTC2983_configuration_constants.h"
#include "LTC2983_table_coeffs.h"
#include "LTC2983_support_functions.h"

void configure_channels()
{
  uint8_t channel_number;
  uint32_t channel_assignment_data;

  // ----- Channel 2: Assign Sense Resistor -----
  channel_assignment_data = 
    SENSOR_TYPE__SENSE_RESISTOR |
    (uint32_t) 0x61A8000 << SENSE_RESISTOR_VALUE_LSB;		// sense resistor - value: 100000.
  assign_channel(2, channel_assignment_data);
  
  // ----- Channel 4: Assign Thermistor Custom Steinhart-Hart -----
  channel_assignment_data =
    SENSOR_TYPE__THERMISTOR_CUSTOM_STEINHART_HART |
    THERMISTOR_RSENSE_CHANNEL__2 |
    THERMISTOR_DIFFERENTIAL |
    THERMISTOR_EXCITATION_MODE__SHARING_ROTATION |
    THERMISTOR_EXCITATION_CURRENT__500NA |
    (uint32_t) 0x0 << THERMISTOR_CUSTOM_ADDRESS_LSB;	// thermistor - custom address: 0.
  assign_channel(4, channel_assignment_data);
  
  // ----- Channel 6: Assign Thermistor Custom Steinhart-Hart -----
  channel_assignment_data = 
    SENSOR_TYPE__THERMISTOR_CUSTOM_STEINHART_HART |
    THERMISTOR_RSENSE_CHANNEL__2 |
    THERMISTOR_DIFFERENTIAL |
    THERMISTOR_EXCITATION_MODE__SHARING_ROTATION |
    THERMISTOR_EXCITATION_CURRENT__500NA |
    ((uint32_t) 0xA << THERMISTOR_CUSTOM_ADDRESS_LSB);		// thermistor - custom address: 10.
  assign_channel(6, channel_assignment_data);
  // ----- Channel 8: Assign Thermistor Custom Steinhart-Hart -----
  channel_assignment_data = 
    SENSOR_TYPE__THERMISTOR_CUSTOM_STEINHART_HART |
    THERMISTOR_RSENSE_CHANNEL__2 |
    THERMISTOR_DIFFERENTIAL |
    THERMISTOR_EXCITATION_MODE__SHARING_ROTATION |
    THERMISTOR_EXCITATION_CURRENT__500NA |
    (uint32_t) 0x14 << THERMISTOR_CUSTOM_ADDRESS_LSB;		// thermistor - custom address: 20.
  assign_channel(8, channel_assignment_data);
  // ----- Channel 10: Assign Thermistor Custom Steinhart-Hart -----
  channel_assignment_data = 
    SENSOR_TYPE__THERMISTOR_CUSTOM_STEINHART_HART |
    THERMISTOR_RSENSE_CHANNEL__2 |
    THERMISTOR_DIFFERENTIAL |
    THERMISTOR_EXCITATION_MODE__SHARING_ROTATION |
    THERMISTOR_EXCITATION_CURRENT__500NA |
    (uint32_t) 0x1E << THERMISTOR_CUSTOM_ADDRESS_LSB;		// thermistor - custom address: 30.
  assign_channel(10, channel_assignment_data);
  // ----- Channel 12: Assign Thermistor Custom Steinhart-Hart -----
  channel_assignment_data = 
    SENSOR_TYPE__THERMISTOR_CUSTOM_STEINHART_HART |
    THERMISTOR_RSENSE_CHANNEL__2 |
    THERMISTOR_DIFFERENTIAL |
    THERMISTOR_EXCITATION_MODE__SHARING_ROTATION |
    THERMISTOR_EXCITATION_CURRENT__500NA |
    (uint32_t) 0x28 << THERMISTOR_CUSTOM_ADDRESS_LSB;		// thermistor - custom address: 40.
  assign_channel(12, channel_assignment_data);
  // ----- Channel 14: Assign Thermistor Custom Steinhart-Hart -----
  channel_assignment_data = 
    SENSOR_TYPE__THERMISTOR_CUSTOM_STEINHART_HART |
    THERMISTOR_RSENSE_CHANNEL__2 |
    THERMISTOR_DIFFERENTIAL |
    THERMISTOR_EXCITATION_MODE__SHARING_ROTATION |
    THERMISTOR_EXCITATION_CURRENT__500NA |
    (uint32_t) 0x32 << THERMISTOR_CUSTOM_ADDRESS_LSB;		// thermistor - custom address: 50.
  assign_channel(14, channel_assignment_data);
  
  channel_assignment_data =
    SENSOR_TYPE__THERMISTOR_CUSTOM_STEINHART_HART |
    THERMISTOR_RSENSE_CHANNEL__2 |
    THERMISTOR_DIFFERENTIAL |
    THERMISTOR_EXCITATION_MODE__SHARING_ROTATION |
    THERMISTOR_EXCITATION_CURRENT__500NA |
    (uint32_t) 0x3C << THERMISTOR_CUSTOM_ADDRESS_LSB;		// thermistor - custom address: 60.
  assign_channel(18, channel_assignment_data);

  
  // ----- Channel 15: Assign Type K Thermocouple -----
  channel_assignment_data = 
    SENSOR_TYPE__TYPE_K_THERMOCOUPLE |
    TC_COLD_JUNCTION_CH__20 |
    TC_SINGLE_ENDED |
    TC_OPEN_CKT_DETECT__YES |
    TC_OPEN_CKT_DETECT_CURRENT__10UA;
  assign_channel(15, channel_assignment_data);
  
  // ----- Channel 16: Assign Type K Thermocouple -----
  channel_assignment_data = 
    SENSOR_TYPE__TYPE_K_THERMOCOUPLE |
    TC_COLD_JUNCTION_CH__20 |
    TC_SINGLE_ENDED |
    TC_OPEN_CKT_DETECT__YES |
    TC_OPEN_CKT_DETECT_CURRENT__10UA;
  assign_channel(16, channel_assignment_data);
  
  
  
  // ----- Channel 20: Assign Off-Chip Diode -----
  channel_assignment_data = 
    SENSOR_TYPE__OFF_CHIP_DIODE |
    DIODE_SINGLE_ENDED |
    DIODE_NUM_READINGS__3 |
    DIODE_AVERAGING_OFF |
    DIODE_CURRENT__20UA_80UA_160UA |
    (uint32_t) 0x100C49 << DIODE_IDEALITY_FACTOR_LSB;		// diode - ideality factor(eta): 1.00299930572509765625
  assign_channel(20, channel_assignment_data);

}

void configure_memory_table(int manufacturer) 
{
  uint16_t start_address;
  uint16_t table_length;
  
  //   TX-1003X-AP: (R25 ~100kΩ – meas. 95.5kΩ)
  float thermoworks_tx_1003x_ap[] = {
	  1.677413579215600e-03,
	  -2.814005003707225e-05,
	  1.970224605090087e-05,
	  -3.918267008816783e-07,
	  0.0,
	  0.0
  };
  
  // Tappecue: (R25 ~250kΩ – meas. 255kΩ)
  float tappecue[] = {
	  6.004357398031257e-04,
	  2.404048860932369e-04,
	  -5.002240575386761e-06,
	  2.931109523732953e-07,
	  0.0,
	  0.0
  };
  
  // Ivation: (R25 ~1MΩ)
  float ivation[] = {
	  3.223158617721970e-03,
	  -4.005965478566934e-04,
	  4.245835194606874e-05,
	  -9.255044738108043e-07,
	  0.0,
	  0.0
  };
  
  // Maverick (R25 ~1MΩ)
  float maverick[] = {
	  8.543458557451216e-04,
	  1.509483714989171e-04,
	  6.045758867833531e-07,
	  1.147214965618761e-07,
	  0.0,
	  0.0
  };
  
  float* coeffs;
  
  switch(manufacturer) {
	  case MAVERICK:
	  	coeffs = maverick;
		break;
	  case THERMOWORKS:
	  	coeffs = thermoworks_tx_1003x_ap;
		break;
	  case IVATION:
	  	coeffs = ivation;
		break;
	 case TAPPEQUE:
	 	coeffs = tappecue;
		break;
	 default:
	  	coeffs = thermoworks_tx_1003x_ap;
  }
  
  start_address = 592;	// Real address = 6*0 + 0x250 = 592
  write_custom_steinhart_hart(coeffs, start_address);

  start_address = 652;	// Real address = 6*10 + 0x250 = 652
  write_custom_steinhart_hart(coeffs, start_address);

  start_address = 712;	// Real address = 6*20 + 0x250 = 712
  write_custom_steinhart_hart(coeffs, start_address);

  start_address = 772;	// Real address = 6*30 + 0x250 = 772
  write_custom_steinhart_hart(coeffs, start_address);

  start_address = 832;	// Real address = 6*40 + 0x250 = 832
  write_custom_steinhart_hart(coeffs, start_address);

  start_address = 892;	// Real address = 6*50 + 0x250 = 892
  write_custom_steinhart_hart(coeffs, start_address);
  
   start_address = 952;	// Real address = 6*60 + 0x250 = 892
   write_custom_steinhart_hart(coeffs, start_address);

}

void configure_global_parameters() 
{
  // -- Set global parameters
  transfer_byte( WRITE_TO_RAM, 0xF0, TEMP_UNIT__F | REJECTION__50_60_HZ);
  // -- Set any extra delay between conversions (in this case, 0*100us)
  transfer_byte( WRITE_TO_RAM, 0xFF, 0);
}

// *****************
// Return temperature reading and fault byte
// *****************
float measure_temperature(uint8_t channel_number, uint8_t* fault) {
	 
     uint32_t raw_data;
     uint8_t fault_data;
     uint16_t start_address = get_start_address(CONVERSION_RESULT_MEMORY_BASE, channel_number);
     uint32_t raw_conversion_result;
	 
	 convert_channel(channel_number);
	  
     raw_data = transfer_four_bytes(READ_FROM_RAM, start_address, 0);
  
     // 24 LSB's are conversion result
     int32_t signed_data = raw_data & 0xFFFFFF;
  
     // Convert the 24 LSB's into a signed 32-bit integer
      if(signed_data & 0x800000)
  		 signed_data = signed_data | 0xFF000000;
   
      // 8 MSB's show the fault data
      *fault = raw_data >> 24;
   
      return ((float) signed_data) / 1024.0;
}

// ***********************
// Program the part
// ***********************
void assign_channel(uint8_t channel_number, uint32_t channel_assignment_data)
{
  uint16_t start_address = get_start_address(CH_ADDRESS_BASE, channel_number);
  transfer_four_bytes(WRITE_TO_RAM, start_address, channel_assignment_data);
}


void write_custom_steinhart_hart(float steinhart_hart_coeffs[6], uint16_t start_address)
{
 
 CustomTableValue coefficient;
 
 uint8_t tx[27];
 int i;
 
 tx[0] = WRITE_TO_RAM;
 tx[1] = (uint8_t) (start_address>>8);
 tx[2] = (uint8_t) start_address;
 
 for(i=0; i<6; i++) {
 	 coefficient.value = steinhart_hart_coeffs[i];
 	 int offset = (i * 4);
 	 tx[3 + offset] = coefficient.buffer[3];
 	 tx[4 + offset] = coefficient.buffer[2];
 	 tx[5 + offset] = coefficient.buffer[1];
 	 tx[6 + offset] = coefficient.buffer[0];
 }

  bcm2835_spi_transfern(tx, 27);

}

// *****************
// Measure channel
// *****************
void measure_channel(uint8_t channel_number, uint8_t channel_output)
{
    convert_channel(channel_number);
	get_result(channel_number, channel_output);
}


void convert_channel(uint8_t channel_number)
{
  transfer_byte(WRITE_TO_RAM, COMMAND_STATUS_REGISTER, CONVERSION_CONTROL_BYTE | channel_number);
  wait_for_process_to_finish();
}


void wait_for_process_to_finish()
{
  uint8_t process_finished = 0;
  uint8_t data;
  while (process_finished == 0)
  {
    data = transfer_byte(READ_FROM_RAM, COMMAND_STATUS_REGISTER, 0);
    process_finished  = data & 0x40;
  }
}


// *********************************
// Get results
// *********************************
void get_result(uint8_t channel_number, uint8_t channel_output)
{
  uint32_t raw_data;
  uint8_t fault_data;
  uint16_t start_address = get_start_address(CONVERSION_RESULT_MEMORY_BASE, channel_number);
  uint32_t raw_conversion_result;

  raw_data = transfer_four_bytes(READ_FROM_RAM, start_address, 0);
  
  // 24 LSB's are conversion result
  raw_conversion_result = raw_data & 0xFFFFFF;
  
  print_conversion_result(raw_conversion_result, channel_output);

  // If you're interested in the raw voltage or resistance, use the following
  //if (channel_output != VOLTAGE)
  //{
   // read_voltage_or_resistance_results(chip_select, channel_number);
  //}

  // 8 MSB's show the fault data
  fault_data = raw_data >> 24;
  print_fault_data(fault_data);
}


void print_conversion_result(uint32_t raw_conversion_result, uint8_t channel_output)
{
	
	
  int32_t signed_data = raw_conversion_result;
  float scaled_result;

  // Convert the 24 LSB's into a signed 32-bit integer
   if(signed_data & 0x800000)
    signed_data = signed_data | 0xFF000000;

  // Translate and print result
  if (channel_output == TEMPERATURE)
  {
    scaled_result = ((float) signed_data) / 1024.0;
    printf(" Temperature = ");
    printf("%f\n", scaled_result);
  }
  else if (channel_output == VOLTAGE)
  {
    scaled_result = ((float) signed_data) / 2097152;
    printf("  Direct ADC reading in V = ");
    printf("%f\n", scaled_result);
  }
  
}


void read_voltage_or_resistance_results(uint8_t channel_number)
{
  int32_t raw_data;
  float voltage_or_resistance_result;
  uint16_t start_address = get_start_address(VOUT_CH_BASE, channel_number);

  raw_data = transfer_four_bytes(READ_FROM_RAM, start_address, 0);
  voltage_or_resistance_result = (float)raw_data/1024;
  printf("  Voltage or resistance = ");
  printf("%f\n", voltage_or_resistance_result);
}


// Translate the fault byte into usable fault data and print it out
void print_fault_data(uint8_t fault_byte)
{
  //
  //printf("  FAULT DATA = ");
  //printf("%d\n", fault_byte);

  if (fault_byte & SENSOR_HARD_FAILURE)
    printf("  - SENSOR HARD FALURE");
  if (fault_byte & ADC_HARD_FAILURE)
    printf("  - ADC_HARD_FAILURE");
  if (fault_byte & CJ_HARD_FAILURE)
    printf("  - CJ_HARD_FAILURE");
  if (fault_byte & CJ_SOFT_FAILURE)
    printf("  - CJ_SOFT_FAILURE");
  if (fault_byte & SENSOR_ABOVE)
    printf("  - SENSOR_ABOVE");
  if (fault_byte & SENSOR_BELOW)
    printf("  - SENSOR_BELOW");
  if (fault_byte & ADC_RANGE_ERROR)
    printf("  - ADC_RANGE_ERROR");
  if (!(fault_byte & VALID))
    printf("INVALID READING !!!!!!");
  if (fault_byte == 0b11111111)
    printf("CONFIGURATION ERROR !!!!!!");
  
  printf("\n");
}

// *********************
// SPI RAM data transfer
// *********************
// To write to the RAM, set ram_read_or_write = WRITE_TO_RAM.
// To read from the RAM, set ram_read_or_write = READ_FROM_RAM.
// input_data is the data to send into the RAM. If you are reading from the part, set input_data = 0.
uint32_t transfer_four_bytes(uint8_t ram_read_or_write, uint16_t start_address, uint32_t input_data)
{
  uint32_t output_data;
  uint8_t tx[7], rx[7];
  
  tx[0] = ram_read_or_write;
  tx[1] = (uint8_t)(start_address >> 8);
  tx[2] = (uint8_t)start_address;
  tx[3] = (uint8_t)(input_data >> 24);
  tx[4] = (uint8_t)(input_data >> 16);
  tx[5] = (uint8_t)(input_data >> 8);
  tx[6] = (uint8_t) input_data;
  
  bcm2835_spi_transfernb(tx, rx, 7);

  output_data = (uint32_t) (rx[3] << 24) |
                (uint32_t) (rx[4] << 16) |
                (uint32_t) (rx[5] << 8 ) |
                (uint32_t) rx[6];

  return output_data;
}


uint8_t transfer_byte(uint8_t ram_read_or_write, uint16_t start_address, uint8_t input_data)
{
  uint8_t tx[4];
  
	 tx[0] = ram_read_or_write;
     tx[1] = (uint8_t)(start_address >> 8);
     tx[2] = (uint8_t)start_address;
	 tx[3] = input_data; 
	 
  bcm2835_spi_transfern(tx, 4);
  
  //printf("%2X %2X %2X %2X\n", tx[0], tx[1], tx[2], tx[3]);
  
  return tx[3];
}


// ******************************
// Misc support functions
// ******************************
uint16_t get_start_address(uint16_t base_address, uint8_t channel_number)
{
  return base_address + 4 * (channel_number-1);
}











