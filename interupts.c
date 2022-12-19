/*
 * interupts.c
 *
 * Created: 2022-12-09 11:56:32
 *  Author: willi
 */ 

#include "main_header.h"

/********************************************************************************
* button_aktivate_interrupt: Aktiverar PCI-avbrott p� angiven tryckknapp s� att
*                          event p� tryckknappens pin medf�r avbrott, b�de p�
*                          stigande och fallande flank. Kontroll av flank m�ste
*                          sk�tas av anv�ndaren, f�rslagsvis via avl�sning i
*                          motsvarande avbrottsrutin.
*
*                          Nedan visas sambandet mellan anv�nd I/O-port samt
*                          avbrottsvektorn f�r motsvarande avbrottsrutin:
*
*                          I/O-port     pin (Arduino Uno)     Avbrottsvektor
*                             B              8 - 13             PCINT0_vect
*                             C             A0 - A5             PCINT1_vect
*                             D              0 - 7              PCINT2_vect
*
*                          - self: Pekare till tryckknappen som PCI-avbrott
*                                  ska aktiveras p�.
********************************************************************************/

void button_aktivate_interupts(struct button* self){
	asm("SEI");
	if (self->io_port_button == IO_PORTB)
	{
		PCMSK0 |= (1 << self->pin);
		PCICR |= (1 << PCIE0);
	}
	else if (self->io_port_button == IO_PORTC)
	{
		PCMSK1 |= (1 << self->pin);
		PCICR |= (1 << PCIE1);
	}
	else if (self->io_port_button == IO_PORTD)
	{
		PCMSK2 |= (1 << self->pin);
		PCICR |= (1 << PCIE2);
	}
	return;
}

/********************************************************************************
 *	ISR(PCINT2_vect) : Vid intryckning av knapparna p� pin 2 och 3 p� port C s�
 *					   aktiveras ett avbrot som togglar om lysdiod 1 och tv� skall vara t�nd.
 *
 *						knapp 1 p� pin 2 t�nder lysdiod 1 p� pin 6.
 *						knapp 2 p� pin 3 t�nder lysdiod 2 p� pin 7.
********************************************************************************/
ISR(PCINT2_vect){
	
	if (button_is_pressed(&b1))
	{
		led_mode[0]=!led_mode[0];
		return;
	}
	else if (button_is_pressed(&b2))
	{
		led_mode[1]=!led_mode[1];
		return;
	}
	return;

}

/********************************************************************************
 *	ISR(PCINT0_vect) : Vid intryckning av knapparna p� pin 11 till 13 p� port B s�
 *					   aktiveras ett avbrot som togglar om lysdiod 3-5 skall vara t�nd.
 *						
 *						knapp 3 p� pin 11 t�nder lysdiod 3 p� pin 8.
 *						knapp 4 p� pin 12 t�nder lysdiod 4 p� pin 9.
 *						knapp 5 p� pin 13 t�nder lysdiod 5 p� pin 10.
********************************************************************************/
ISR(PCINT0_vect){
	if (button_is_pressed(&b3)==1)
	{
		led_mode[2]=!led_mode[2];
		return;
	}
	else if (button_is_pressed(&b4)==1)
	{
		led_mode[3]=!led_mode[3];
		return;
	}
	else if (button_is_pressed(&b5)==1)
	{
		led_mode[4]=!led_mode[4];
		return;
	}
}


