/*
 * setup.c
 *
 * Created: 2022-12-19 09:24:57
 *  Author: willi
 */ 

/********************************************************************************
* setup.c: Innehåller funktionalitet för initiering av det inbyggda systemet.
********************************************************************************/

#include "main_header.h"
#include "setup.h"

/********************************************************************************
* setup: initeierar det inbyggda systemet
*
********************************************************************************/
struct led l1,l2,l3,l4,l5;
struct button b1,b2,b3,b4,b5;
struct led_vect v1;
struct adc_pin a1;
bool led_mode[5];

void setup(void)
{
	led_init(&l1,6);
	led_init(&l2,7);
	led_init(&l3,8);
	led_init(&l4,9);
	led_init(&l5,10);
	
	button_init(&b1,2);
	button_init(&b2,3);
	button_init(&b3,11);
	button_init(&b4,12);
	button_init(&b5,13);
	
	led_vect_init(&v1);
	
	led_vect_push(&v1,&l1);
	led_vect_push(&v1,&l2);
	led_vect_push(&v1,&l3);
	led_vect_push(&v1,&l4);
	led_vect_push(&v1,&l5);
	
	adc_init(&a1,PO1);
	
	button_aktivate_interupts(&b1);
	button_aktivate_interupts(&b2);
	button_aktivate_interupts(&b3);
	button_aktivate_interupts(&b4);
	button_aktivate_interupts(&b5);
	
	
	for (uint8_t i = 0; i < 5; i++) led_mode[i] = false;

	return;
}
