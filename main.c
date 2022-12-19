/*
 * prodjekt_3.c
 *
 * Created: 2022-12-06 12:56:01
 * Author : willi
 */ 
/**********************************************************************

	mian_header.h includerar samtliga headers för alla includerade funtioner.
	
**********************************************************************/
#include "main_header.h"

/**********************************************************************

	*mian:
	
**********************************************************************/

int main(void)
{
    setup();
    
    while (1)
    {
	    adc_get_pwm_values(&a1,10000);
	    for (uint8_t i = 0 ; i < v1.size ; i++)
	    {
		    if(led_mode[i] == true) led_on(&v1.leds[i]);
	    }
	    adc_delay_on(&a1);
	    for (uint8_t i = 0 ; i < v1.size ; i++)
	    {
		    led_off(&v1.leds[i]);
	    }
	    adc_delay_off(&a1);
	    
    }
    
    return 0;

}

