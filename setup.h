/*
 * setup.h
 *
 * Created: 2022-12-19 09:25:15
 *  Author: willi
 */ 

/********************************************************************************
*  setup.h:	Innehåller funktionalitet för initiering av det inbyggda systemet.
*			Innehåler eventuella globala variabeldefinitioner eller
*			Definitioner av globala struktar.
*
********************************************************************************/

#ifndef SETUP_H_
#define SETUP_H_

#include "main_header.h"

void setup(void);

extern struct led l1,l2,l3,l4,l5;
extern struct button b1,b2,b3,b4,b5;
extern struct led_vect v1;
extern struct adc_pin a1;

extern bool led_mode[5];

#endif /* SETUP_H_ */