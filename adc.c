/*
 * adc.c
 *
 * Created: 2022-12-19 09:22:15
 *  Author: willi
 */ 

/********************************************************************************
* adc.c: Inneh�ller funktionsdefinitioner f�r implementering av AD-omvandling
*        f�r analoga signaler via strukten adc.
********************************************************************************/

#include "adc.h"

/********************************************************************************
* adc_read: L�ser av en analog insignal och returnerar motsvarande digitala
*           motsvarighet mellan 0 - 1023.
*
*           - self: Pekare till analog pin vars insignal ska AD-omvandlas.
********************************************************************************/
uint16_t adc_read(struct adc_pin* self){
	
	ADMUX = (1 << REFS0) | self->pin;
	ADCSRA = (1 << ADEN) | (1<< ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	while ((ADCSRA & (1 << ADIF)) == 0);
	ADCSRA = (1 << ADIF);
	return ADC;
}

/********************************************************************************
* adc_get_pwm_values: L�ser av en analog insignal och ber�knar on- och off-tid
*                     f�r PWM-generering, avrundat till n�rmaste heltal.
*
*                     - self         : Pekare till analog pin som ska l�sas av.
*                     - pwm_period_us: PWM-perioden (on-tid + off-tid) m�tt i
*                                      mikrosekunder.
********************************************************************************/
void adc_get_pwm_values(struct adc_pin* self, uint16_t pwm_period_us)
{
	const double duty_cycle = adc_read(self) / 1023.0;
	self->pwm_on_us =(uint16_t) (duty_cycle * pwm_period_us+0.5);
	self->pwm_off_us = pwm_period_us - self->pwm_on_us;
	return;
}

/********************************************************************************
* adc_init: Initierar analog pin f�r avl�sning och AD-omvandling av insignaler,
*			Och nollst�ller pwm v�rderna.
*
*           - self: Pekare till analog pin som ska anv�ndas f�r AD-omvandling.
*           - pin : Analog pin som ska l�sas f�r AD-omvandling.
********************************************************************************/
void adc_init(struct adc_pin* self, uint8_t pin)
{
	self->pin = pin;
	self->pwm_off_us = 0;
	self->pwm_on_us = 0;
	(void)adc_read(self);
	return;
}

/********************************************************************************
* adc_delay_on: Aktiverar en f�rdr�jning p� perioden av h�g signal vid pwm styrning
				enligt tidigare avl�st v�rde. 
				F�rdr�jningen blir v�rdet p� pwm_on_us i microsekunder
				
				- self         : Pekare till analog pin som har l�sts av.
********************************************************************************/
void adc_delay_on(struct adc_pin* self){
	delay_us(self->pwm_on_us);
	return;
}

/********************************************************************************
* adc_delay_off: Aktiverar en f�rdr�jning p� perioden av l�g signal vid pwm styrning
				enligt tidigare avl�st v�rde. 
				F�rdr�jningen blir v�rdet p� pwm_off_us i microsekunder
				
				- self         : Pekare till analog pin som har l�sts av.
********************************************************************************/
void adc_delay_off(struct adc_pin* self){
	delay_us(self->pwm_off_us);
	return;
}

