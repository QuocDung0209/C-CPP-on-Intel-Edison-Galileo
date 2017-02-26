/**
 * 
 * This is a 'cpp' program that demos the usage of the upm library 
 * to set up and use Grove light sensor on Intel Edison/Galileo.
 * The intensity with which the LED connected at port D5 glows is 
 * controlled by the intensity of light falling onto the light
 * sensor
 * 
 * setup:
 * Light sensor is connected to analog port A0 and the LED is connected 
 * to port D5
 * 
 * Compilation (on the Intel Galileo/Edison and not on host):
 * g++ light_sensor.cpp -o light_sensor -lupm-grove -lmraa
 * 
 * Demo:
 * Run the application
 * ./light_sensor
 * 
 * You can exit this demo by hitting ctrl+c
 * 
 * You can find the tutorial related to this program here:
 * 
 *
 */

#include <mraa.h>
#include <signal.h>
#include <upm/grove.h>

#define LED_PWM_PIN            5        /**< The pin where the LED is connected */
#define LIGHT_SENSOR_PIN       0        /**< Analog pin to which light sensor is connected */
#define MAX_LIGHT             50        /**< Value to which we want to normalize the lux */

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
    upm::GroveLight *light = NULL;   /* Will hold pointer to light sensor object */
    

    int               ambientLight;
    float                 pwmValue;
    int                  tempLight;
    
    /* Step1: Intialize the mraa system */
    mraa_init();
    
    /* Step2: Initialize D5 for PWM operation */
    pwmPin = mraa_pwm_init(LED_PWM_PIN);
    
    /* Step3: Initilaize the pin for light sensor and create the upm object */
    light = new upm::GroveLight(LIGHT_SENSOR_PIN);
    
    /* Step4: Set the period on the PWM pin */
    mraa_pwm_period_us(pwmPin, 5000);      // Set the period as 5000 us or 5ms
    
    /* Step5: Enable the PWM pulse on the pin */
    mraa_pwm_enable(pwmPin, 1);
   
    keepRunning = 1;
    
    /* 
     * Associate ctrl+c with our handler that clears the 'keepRunning'
     * flag that allows us to stop the PWM when exiting 
     */
    signal(SIGINT, handler);
    printf ("\n");
    while (keepRunning)
    {
        printf ("Light sensor: ");
        /* Step6: Read the light sensor value in lux using method 'value()' */
        ambientLight = light->value();
        
        /* Step7: Normalize the light value for PWM control */
        tempLight = ambientLight;
        if (tempLight > MAX_LIGHT)
        {
            tempLight = MAX_LIGHT;
        }
        
        pwmValue = (MAX_LIGHT - tempLight)/(float)(MAX_LIGHT);
                           
        /* Step8: Set the intensity of the LED at port D5 using PWM */
        mraa_pwm_write(pwmPin, pwmValue);

        /* step9: Output the bar display on the console */
        printf("%02d [", tempLight);

        for (int i=0; i<MAX_LIGHT; i++)
        {
            if (ambientLight > i)
            {
                printf("=");
            }
            else if (ambientLight == i)
            {
                printf ("|");
            }
            else
            {
                printf (" ");
            }
        }

        printf ("]\r");
        usleep(5000);
    }
    
    /* Step10: Stop all the periphrals and exit */
    printf ("\nDone....\n");
    mraa_pwm_enable(pwmPin, 0);
    delete light;
        
    return 0;
}
