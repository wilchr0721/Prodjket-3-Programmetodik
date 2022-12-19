/*
 * adc.h
 *
 * Created: 2022-12-19 09:21:47
 *  Author: willi
 */ 

/********************************************************************************
* adc.h: Inneh�ller funktionalitet f�r enkel implementering av AD-omvandling
*        f�r analoga signaler via strukten adc. AD-omvandling sker via inl�sning
*        av signaler fr�n analoga pinnar A0 - A5 p� Arduino Uno, vilket
*        motsvarar PORTC0 - PORTC5 p� ATmega328P.
*
*		 AD-omvanlingen kan till exemel anv�ndas f�r att l�sa av en.
*		 Potensiometer som kan variera sp�nningen fr�n 0 - 5 V som blir 
*		 en digital signal fr�n 0 - 1023. 
*		
*		 Signalen kan till exemepl anv�ndas f�r att sjukstera ljusstyrka med
*        en duty_cycle som ber�knas med: 
*
*			duty_cycle = ADC_Value/Max_Value
*		
********************************************************************************/

#ifndef ADC_H_
#define ADC_H_

/* Inkluderingsderektiv:*/
#include "misc.h"
#include "setup.h"

#define PO1 0 /* Potensiometer kopplad till ing�ng A0 p� aruduinot.*/
#define PO2 1 /* Potensiometer kopplad till ing�ng A1 p� aruduinot.*/

/********************************************************************************
* adc: Strukt f�r implementering av AD-omvandlare, som m�jligg�r avl�sning
*      av insignaler fr�n analoga pinnar samt ber�kning av on- och off-tid f�r
*      PWM-generering 
********************************************************************************/
struct adc_pin{
	uint8_t pin;			/* pin: anger vilken pin p� arduinot som l�ses av.*/
	uint16_t pwm_on_us;		/* pwm_on_us: Anger hur l�nge en signal skall vara h�g vid PWM styrning.*/
	uint16_t pwm_off_us;	/* pwm_off_us: Anger hur l�nge en signal skall vara l�g vid PWM styrning.*/
};

/********************************************************************************
* adc_init: Initierar analog pin f�r avl�sning och AD-omvandling av insignaler,
*			Och nollst�ller pwm v�rderna.
*
*           - self: Pekare till analog pin som ska anv�ndas f�r AD-omvandling.
*           - pin : Analog pin som ska l�sas f�r AD-omvandling.
********************************************************************************/
void adc_init(struct adc_pin* self, uint8_t pin);

/********************************************************************************
* adc_read: L�ser av en analog insignal och returnerar motsvarande digitala
*           motsvarighet mellan 0 - 1023.
*
*           - self: Pekare till analog pin vars insignal ska AD-omvandlas.
********************************************************************************/
uint16_t adc_read(struct adc_pin* self);

/********************************************************************************
* adc_get_pwm_values: L�ser av en analog insignal och ber�knar on- och off-tid
*                     f�r PWM-generering, avrundat till n�rmaste heltal.
*
*                     - self         : Pekare till analog pin som ska l�sas av.
*                     - pwm_period_us: PWM-perioden (on-tid + off-tid) m�tt i
*                                      mikrosekunder.
********************************************************************************/
void adc_get_pwm_values(struct adc_pin* self, uint16_t pwm_period_us);

/********************************************************************************
* adc_delay_on: Aktiverar en f�rdr�jning p� perioden av h�g signal vid pwm styrning
				enligt tidigare avl�st v�rde. 
				F�rdr�jningen blir v�rdet p� pwm_on_us i microsekunder
				
				- self         : Pekare till analog pin som har l�sts av.
********************************************************************************/
void adc_delay_on(struct adc_pin* self);

/********************************************************************************
* adc_delay_off: Aktiverar en f�rdr�jning p� perioden av l�g signal vid pwm styrning
				enligt tidigare avl�st v�rde. 
				F�rdr�jningen blir v�rdet p� pwm_off_us i microsekunder
				
				- self         : Pekare till analog pin som har l�sts av.
********************************************************************************/
void adc_delay_off(struct adc_pin* self);

#endif /* ADC_H_ */