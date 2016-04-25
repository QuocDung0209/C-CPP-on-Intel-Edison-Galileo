/**
 * 
 * This is a 'c' program that demos the usage of the mraa library 
 * to set up and use PWM Intel Edison/Galileo.
 * The intensity with which the LED connected at port D5 glows is 
 * controlled by the position of rotary angle sensor connected to analog
 * port A0
 * 
 * setup:
 * Rotary angle sensor is connected to analog port A0 and 
 * the LED is connected to port D5
 * 
 * Compilation (on the Intel Galileo/Edison and not on host):
 * gcc -o adc adc.c -lmraa
 * 
 * Demo:
 * Run the application
 * ./adc
 * 
 * You can exit this demo by hitting ctrl+c
 * 
 * You can find the tutorial related to this program here:
 * https://navinbhaskar.wordpress.com/2016/04/25/cc-on-intel-edisongalileo-part4adc/ 
 *
 */

#include <mraa.h>
#include <signal.h>


#define PWM_PIN      5        /**< The pin where the LED is connected */
#define ADC_PIN      0        /**< The ADC pin */
#define ADC_MAX   (1024.0)    /**< Maximum value output by a 10-bit ADC */

volatile int keepRunning;

/** Signal handler used to stop this application cleanly */
void handler(int arg)
{
    (arg);
    keepRunning = 0;
}


int main(void)
{
    mraa_pwm_context       pwmPin;   /* The PWM pin context */
    mraa_aio_context       adcPin;   /* ADC pin context */
    
    float                  intensity; /* Intensity with which LED is to glow */
    float                  adcValue;  /* Read ADC value */
    
    /* Step1: Intialize the mraa system */
    mraa_init();
    
    /* Step2: Initalize analog port 0 for ADC operation */
    adcPin = mraa_aio_init(ADC_PIN);
    
    /* Step3: Initialize D5 for PWM operation */
    pwmPin = mraa_pwm_init(PWM_PIN);
    
    /* Step4: Set the period on the PWM pin */
    mraa_pwm_period_us(pwmPin, 5000);      // Set the period as 5000 us or 5ms
    
    /* Step5: Enable the PWM pulse on the pin */
    mraa_pwm_enable(pwmPin, 1);
   
    keepRunning = 1;
    
    /* 
     * Associate ctrl+c with our handler that clears the 'keepRunning'
     * flag that allows us to stop the PWM and ADC when exiting 
     */
    signal(SIGINT, handler);
    
    while (keepRunning)
    {
        /* Step6: Read the ADC value using the function 'mraa_aio_read()' */
        adcValue = mraa_aio_read(adcPin);
        intensity = adcValue/ADC_MAX;
        /* Step7: Set the intensity of the LED at port D5 using PWM */
        mraa_pwm_write(pwmPin, intensity);
        usleep(500);
    }
    
    /* Step8: Stop the PWM and ADC when not required */
    mraa_pwm_enable(pwmPin, 0);
    mraa_aio_close(adcPin);
        
    return 0;
}

