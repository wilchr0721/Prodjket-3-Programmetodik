/*
 * interupts.c
 *
 * Created: 2022-12-09 11:56:32
 *  Author: willi
 */ 

#include "main_header.h"

/********************************************************************************
* button_aktivate_interrupt: Aktiverar PCI-avbrott på angiven tryckknapp så att
*                          event på tryckknappens pin medför avbrott, både på
*                          stigande och fallande flank. Kontroll av flank måste
*                          skötas av användaren, förslagsvis via avläsning i
*                          motsvarande avbrottsrutin.
*
*                          Nedan visas sambandet mellan använd I/O-port samt
*                          avbrottsvektorn för motsvarande avbrottsrutin:
*
*                          I/O-port     pin (Arduino Uno)     Avbrottsvektor
*                             B              8 - 13             PCINT0_vect
*                             C             A0 - A5             PCINT1_vect
*                             D              0 - 7              PCINT2_vect
*
*                          - self: Pekare till tryckknappen som PCI-avbrott
*                                  ska aktiveras på.
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
 *	ISR(PCINT2_vect) : Vid intryckning av knapparna på pin 2 och 3 på port C så
 *					   aktiveras ett avbrot som togglar om lysdiod 1 och två skall vara tänd.
 *
 *						knapp 1 på pin 2 tänder lysdiod 1 på pin 6.
 *						knapp 2 på pin 3 tänder lysdiod 2 på pin 7.
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
 *	ISR(PCINT0_vect) : Vid intryckning av knapparna på pin 11 till 13 på port B så
 *					   aktiveras ett avbrot som togglar om lysdiod 3-5 skall vara tänd.
 *						
 *						knapp 3 på pin 11 tänder lysdiod 3 på pin 8.
 *						knapp 4 på pin 12 tänder lysdiod 4 på pin 9.
 *						knapp 5 på pin 13 tänder lysdiod 5 på pin 10.
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


