/*
 * display.h
 *
 *  Created on: Nov 1, 2023
 *      Author: Vy Nguyen
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "main.h"
#include "global.h"

extern int index_led;
extern int counter_led_vertical;
extern int counter_led_horizontal;

void display7SEG(int counter);
void update7SEG(int index);

void updateClockBufferMode1();
void updateClockBufferMode2();
void updateClockBufferMode3();
void updateClockBufferMode4();

#endif /* INC_DISPLAY_H_ */
