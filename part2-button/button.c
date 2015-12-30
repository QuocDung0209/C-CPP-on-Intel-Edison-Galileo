/**
 * 
 * This is a 'c' program that demos the usage of the mraa library 
 * to interface with the button on Intel Edison/Galileo.
 * The LED is toggled whenever the button is clicked.
 * 
 * setup:
 * Button is connected to port D6 and the LED is connected to port D5
 * 
 * Compilation (on the Intel Galileo/Edison and not on host):
 * gcc -o button button.c -lmraa
 * 
 * Demo:
 * Run the application
 * ./button
 * Now click the button to see the LED toggle
 * 
 * You can exit this demo by hitting ctrl+c
 * 
 * You can find the tutorial related to this program here:
 * 
 * 
 */

#include <mraa.h>
#include <inttypes.h>

#define LED_PIN      5        /**< The pin where the LED is connected */
#define BTN_PIN      6        /**< Button is connected to this pin */


int main(void)
{
    mraa_gpio_context      ledPin;  /* Will be used to represnt the LED pin */
    mraa_gpio_context      btnPin;  /* Will be used to represnt the button pin */
    
    uint32_t               toggle;   /* Used to toggle the LED */
    uint32_t               btnState; /* Used to capture the state of the button */
    
    
    
    /* Step1: Init the mraa subsystem */
    mraa_init();
    
    /* Step2: Set the ledPin as port D5 and btnPin as port D6*/
    ledPin = mraa_gpio_init(LED_PIN);
    btnPin = mraa_gpio_init(BTN_PIN);
     
    /* Step3: Set the 'ledPin(D5)' pin as output */
    mraa_gpio_dir(ledPin, MRAA_GPIO_OUT);
    
    /* LED is turned off to start with */
    toggle = 0;                     
    mraa_gpio_write(ledPin, toggle);
    
    /* 
     * Step4: Set the 'btnPin(D6)' pin as input, will be used to read
     * the button state
     */
    mraa_gpio_dir(btnPin, MRAA_GPIO_IN);
    
    while(1)
    {
      /* Step5: Wait until there is some activty on the button pin */
      while (mraa_gpio_read(btnPin) != 0)
      { }
      /* 
       * Step6: Button state has changed, wait for signal to settle, and 
       * then read the pin again to get the 'stable' signal, this is 
       * simplest form of debouncing.
       */
       usleep(10);  /* man usleep */
       if (mraa_gpio_read(btnPin) == 1)
       {
           /* Step7: Control the LED state based on the button toggle */
           if (toggle == 0)
           {
               toggle = 1;  /* If the LED is off, trun it on */
               
           }
           else
           {
               toggle = 0;  /* Turn off the LED */
           }
           mraa_gpio_write(ledPin, toggle);
       }
       // else: false click, ignore it
    }
    
    return 0;
}

