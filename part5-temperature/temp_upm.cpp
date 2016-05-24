/**
 * 
 * This is a 'c++' program that demos the usage of the upm library 
 * to interface with the Grove temperature sensor module.
 * The temperature is read and printed onto the console.
 *
 * setup:
 * The Grove temperature sensor is connected to analog port 0. A0
 * 
 * Compilation (on the Intel Galileo/Edison and not on host):
 * g++ temp_upm.cpp -o temp_upm -lupm-grove
 * 
 * Demo:
 * Run the application
 * ./temp_upm
 * 
 * 
 * You can find the tutorial related to this program here:
 * 
 */

#include <stdio.h>  // for printf()

/* Step1: Bring in the upm */
#include <upm/grove.h>


#define TEMP_ADC_PIN    0    // ADC pin is 0

int main(void)
{
	int temperature;
	
	/* Step2: Instantiate an instance of Grove temperature sensor */
	upm::GroveTemp *temp = new upm::GroveTemp(TEMP_ADC_PIN);
	
	/* Step3: Record the temperature and print */
	temperature = temp->value();
	printf ("The temperature is %d degree Celcius\n", temperature);
	
    return 0;
}


   
