/**
 * 
 * This is a 'c' program that demos the usage of the mraa library 
 * to interface with the Grove temperature sensor module.
 * The temperature is read and printed onto the console.
 *
 * setup:
 * The Grove temperature sensor is connected to analog port 0. A0
 * 
 * Compilation (on the Intel Galileo/Edison and not on host):
 * gcc -o temp temp_mraa.c -lmraa -lm
 * 
 * Demo:
 * Run the application
 * ./temp
 * 
 * 
 * You can find the tutorial related to this program here:
 * 
 */

#include <stdio.h>
#include <mraa.h>
#include <math.h>           // for the log function



const int B  = 4275;         // B value for thermistor
const int R0 = 100;          // R0 is 100k ohms

#define TEMP_ADC_PIN    0    // ADC pin is 0

int main(void)
{
    mraa_aio_context   adcPin;           // used as AIO context
    float              adcValue;         // ADC value read into this variable
    float              R, temperature;   // Used in calculations

    /* Step1: Initialize the mraa */
    mraa_init();

    /* Step2: Initlaize the ADC pin */
    adcPin = mraa_aio_init(TEMP_ADC_PIN);

    /* Step3: Read the ADC value */
    adcValue = mraa_aio_read(adcPin);
    
    /* Step4: Apply the transformation */
    R = 1023.0/((float)adcValue)-1.0;
    R = 100000.0*R;

    temperature = 1.0/(log(R/100000.0)/B+1/298.15)-273.15;

    /* Step5: Print the temperature */
    printf ("The temperature is %0.2f degree Celcius\n", temperature);


    return 0;
}


   
