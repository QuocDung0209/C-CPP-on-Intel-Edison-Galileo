/**
 * 
 * This is a 'c' program that demos the usage of the mraa library 
 * to blink an LED connected to port D5 on Intel Edison/Galileo
 * 
 * setup:
 * The LED is connected to port D5
 * 
 * Compilation (on the Intel Galileo/Edison and not on host):
 * gcc -o blinky blinky.c -lmraa
 * 
 * Demo:
 * Run the application
 * ./blinky
 * You should see the LED blink 
 * 
 * You can exit this demo by hitting ctrl+c
 * 
 * You can find the tutorial related to this program here:
 * https://navinbhaskar.wordpress.com/2015/11/13/c-on-intel-edisongalileo-part1/
 * 
 */

#include <mraa.h>

#define LED_PIN      5        /**< The pin where the LED is connected */


int main(void)
{
    mraa_gpio_context      ledPin;
    
    /* Step1: Init the mraa subsystem */
    mraa_init();
    
    /* Step2: Set the ledPin as port D5 */
    ledPin = mraa_gpio_init(LED_PIN);
     
    /* Step3: Set the said pin as output */
    mraa_gpio_dir(ledPin, MRAA_GPIO_OUT);
    
    while(1)
    {
        /* Step4: Set the desired voltage level at the pin */
        mraa_gpio_write(ledPin, 1);
        sleep(1);
        mraa_gpio_write(ledPin, 0);
        sleep(1);
    }
    
    return 0;
}

