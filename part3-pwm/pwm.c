/**
 * 
 * This is a 'c' program that demos the usage of the mraa library 
 * to set up and use PWM Intel Edison/Galileo.
 * The intensity with which the LED connected to port D5 glows is 
 * controlled
 * 
 * setup:
 * The LED is connected to port D5
 * 
 * Compilation (on the Intel Galileo/Edison and not on host):
 * gcc -o pwm pwm.c -lmraa
 * 
 * Demo:
 * Run the application
 * ./pwm
 * 
 * You can exit this demo by hitting ctrl+c
 * 
 * You can find the tutorial related to this program here:
 * 
 */

#include <mraa.h>

#define PWM_PIN      5        /**< The pin where the LED is connected */


int main(void)
{
    mraa_pwm_context       pwmPin;   /* The PWM pin context */
    float                  duty;     /* Will hold the duty cycle */
    float                  delta;    /* holds the ammount by which the duty cycle is to vary */
    
    /* Step1: Intialize the mraa system */
    mraa_init();
    
    /* Step2: Initialize D5 for PWM operation */
    pwmPin = mraa_pwm_init(PWM_PIN);
    
    /*
     * Control the period with "mraa_pwm_period_us"
     *
     *       +----------------+                +----------------+                |
     *       |                |                |                |                |
     *       |                |                |                |                |
     *       |                |                |                |                |
     *       |                |                |                |                |
     *       |                |                |                |                |
     *       |                |                |                |                |
     *       |                |                |                |                |
     *       |                |                |                |                |
     *       +                +----------------+                +----------------+
     *       ^                                 ^
     *       |                                 |
     *       |<---------- Period ------------->|
     *       |               ^                 |
     *       |               |                 |
     *                       | 
     *      mraa_pwm_period_us(5000)
     */
    
    /* Step3: Set the period on the PWM pin */
    mraa_pwm_period_us(pwmPin, 5000);      // Set the period as 5000 us or 5ms
    
    /* Step4: Enable the PWM pulse on the pin */
    mraa_pwm_enable(pwmPin, 1);
    
    delta = 0.05;   /* Variation on the duty cycle */
    duty = 0;       /* 0% duty cycle */
    
    while (1)
    {
        if (duty >= 1)
        {
            duty = 1;          // Intensity of LED at highest 
            delta = -0.05;     // Need to decrease the duty cycle
        }
        else if (duty <= 0)
        {
            duty = 0;          // Intensity of LED at the lowest
            delta = +0.05;     // Need to increase the duty cycle 
        }
       /*
        *  Control the duty cycle with "write"
        *    +------+                            +------+                            
        *    |      |                            |      |                           
        *    |      |                            |      |                           
        *    |      |                            |      |                           
        *    |      |                            |      |                           
        *    |      |                            |      |                           
        *    |      |                            |      |                           
        *    |      |                            |      |                           
        *    |      |                            |      |                           
        *    +      +----------------------------+      +---------------------------+
        *    ^      ^
        *    |      |
        *    |<---->|
        *        ^
        *        |-----------------
        *                          |
        *  mraa_pwm_write(pwmPin, 0.2)
        * 
        */
        
        /* Step5: Use the function 'mraa_pwm_write' to set the duty cycle */
        mraa_pwm_write(pwmPin, duty);
        /* Wait for some time */
        usleep(50000);
        
        duty = duty + delta;
    }
        
    return 0;
}

