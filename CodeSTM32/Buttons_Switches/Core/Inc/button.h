/*
 * button.h
 *
 *  Created on: Nov 1, 2023
 *      Author: Vy Nguyen
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "software_timer.h"

#define NORMAL_STATE	SET
#define PRESSED_STATE	RESET

#define NUM_OF_BUTTONS	3

int isButtonPressed(int index);
void subKeyProcess(int index);
void getKeyInput();

#endif /* INC_BUTTON_H_ */
