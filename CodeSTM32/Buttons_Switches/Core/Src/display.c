/*
 * display.c
 *
 *  Created on: Nov 1, 2023
 *      Author: Vy Nguyen
 */

#include "display.h"

void display7SEG(int counter)
{
	/* Declare an array includes bit values to display numbers from 0 to 9 */
	unsigned char disp_arr[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
	/* Declare a variable stores bit values 7-SEG of "counter" to display number */
	unsigned char bit_var, varr = disp_arr[counter];

	bit_var = varr & 0x01;
	HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, bit_var);

	bit_var = (varr>>1) & 0x01;
	HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, bit_var);

	bit_var = (varr>>2) & 0x01;
	HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, bit_var);

	bit_var = (varr>>3) & 0x01;
	HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, bit_var);

	bit_var = (varr>>4) & 0x01;
	HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, bit_var);

	bit_var = (varr>>5) & 0x01;
	HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, bit_var);

	bit_var = (varr>>6) & 0x01;
	HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, bit_var);
}

//---------------//

const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1, 2, 3, 4};

void update7SEG(int index)
{
	display7SEG(led_buffer[index]);
	switch (index)
	{
		case 0:
			//Display the first 7SEG with led_buffer[0]
			index_led = 1;
			HAL_GPIO_WritePin(VERTICAL_1_GPIO_Port, VERTICAL_1_Pin, RESET);
			HAL_GPIO_WritePin(VERTICAL_2_GPIO_Port, VERTICAL_2_Pin, SET);
			HAL_GPIO_WritePin(HORIZONTAL_1_GPIO_Port, HORIZONTAL_1_Pin, SET);
			HAL_GPIO_WritePin(HORIZONTAL_2_GPIO_Port, HORIZONTAL_2_Pin, SET);
			break;

		case 1:
			//Display the first 7SEG with led_buffer[1]
			index_led = 2;
			HAL_GPIO_WritePin(VERTICAL_1_GPIO_Port, VERTICAL_1_Pin, SET);
			HAL_GPIO_WritePin(VERTICAL_2_GPIO_Port, VERTICAL_2_Pin, RESET);
			HAL_GPIO_WritePin(HORIZONTAL_1_GPIO_Port, HORIZONTAL_1_Pin, SET);
			HAL_GPIO_WritePin(HORIZONTAL_2_GPIO_Port, HORIZONTAL_2_Pin, SET);
			break;
		case 2:
			//Display the first 7SEG with led_buffer[2]
			index_led = 3;
			HAL_GPIO_WritePin(VERTICAL_1_GPIO_Port, VERTICAL_1_Pin, SET);
			HAL_GPIO_WritePin(VERTICAL_2_GPIO_Port, VERTICAL_2_Pin, SET);
			HAL_GPIO_WritePin(HORIZONTAL_1_GPIO_Port, HORIZONTAL_1_Pin, RESET);
			HAL_GPIO_WritePin(HORIZONTAL_2_GPIO_Port, HORIZONTAL_2_Pin, SET);
			break;
		case 3:
			//Display the first 7SEG with led_buffer[3]
			index_led = 0;
			HAL_GPIO_WritePin(VERTICAL_1_GPIO_Port, VERTICAL_1_Pin, SET);
			HAL_GPIO_WritePin(VERTICAL_2_GPIO_Port, VERTICAL_2_Pin, SET);
			HAL_GPIO_WritePin(HORIZONTAL_1_GPIO_Port, HORIZONTAL_1_Pin, SET);
			HAL_GPIO_WritePin(HORIZONTAL_2_GPIO_Port, HORIZONTAL_2_Pin, RESET);
			break;
		default:
			break;
	}
}

//------------------//

int counter_led_vertical = 1;
int counter_led_horizontal = 1;

void updateClockBufferMode1()
{
	/*
	For 2 horizontally aligned 7-segment LEDs
	- The led RED horizontally lights up counting down
	from PERIOD_RED - 1 to 0.
	- The red GREEN horizontally lights up counting down
	from PERIOD_GREEN - 1 to 0.
	- The led YELLOW horizontally lights up counting down
	from PERIOD_YELLOW - 1 to 0.
	- If the time for the LED YELLOW ends, return to
	setting up the time for the LED RED to light up again.
	*/

	if(counter_led_horizontal <= PERIOD_RED)
	{
		led_buffer[0] = (PERIOD_RED - counter_led_horizontal) / 10;
		led_buffer[1] = (PERIOD_RED - counter_led_horizontal) % 10;
	}

	else if(counter_led_horizontal <= PERIOD_RED + PERIOD_GREEN)
	{
		led_buffer[0] = (PERIOD_RED + PERIOD_GREEN - counter_led_horizontal) / 10;
		led_buffer[1] = (PERIOD_RED + PERIOD_GREEN - counter_led_horizontal) % 10;
	}

	else
	{
		led_buffer[0] = (PERIOD_RED + PERIOD_GREEN + PERIOD_YELLOW - counter_led_horizontal) / 10;
		led_buffer[1] = (PERIOD_RED + PERIOD_GREEN + PERIOD_YELLOW - counter_led_horizontal) % 10;
	}
	counter_led_horizontal++;

	if (counter_led_horizontal > PERIOD_RED + PERIOD_YELLOW + PERIOD_GREEN)
		counter_led_horizontal = 1;


	/*
	For 2 vertically aligned 7-segment LEDs
	- The red GREEN vertically lights up counting down
	from PERIOD_GREEN - 1 to 0.
	- The led YELLOW vertically lights up counting down
	from PERIOD_YELLOW - 1 to 0.
	- The led RED vertically lights up counting down
	from PERIOD_RED - 1 to 0.
	- If the time for the LED YELLOW ends, return to
	setting up the time for the LED RED to light up again.
	*/

	if(counter_led_vertical <= PERIOD_GREEN)
	{
		led_buffer[2] = (PERIOD_GREEN - counter_led_vertical) / 10;
		led_buffer[3] = (PERIOD_GREEN - counter_led_vertical) % 10;
	}

	else if(counter_led_vertical <= PERIOD_GREEN + PERIOD_YELLOW)
	{
		led_buffer[2] = (PERIOD_GREEN + PERIOD_YELLOW - counter_led_vertical) / 10;
		led_buffer[3] = (PERIOD_GREEN + PERIOD_YELLOW - counter_led_vertical) % 10;
	}

	else
	{
		led_buffer[2] = (PERIOD_RED + PERIOD_GREEN + PERIOD_YELLOW - counter_led_vertical) / 10;
		led_buffer[3] = (PERIOD_RED + PERIOD_GREEN + PERIOD_YELLOW - counter_led_vertical) % 10;
	}
	counter_led_vertical++;

	if (counter_led_vertical > PERIOD_RED + PERIOD_YELLOW + PERIOD_GREEN)
		counter_led_vertical = 1;
}

//------------------//

void updateClockBufferMode2()
{
	// Display the mode.
	led_buffer[0] = 0;
	led_buffer[1] = 2;

	//Display the value of led RED;
	led_buffer[2] = PERIOD_RED / 10;
	led_buffer[3] = PERIOD_RED % 10;
}

//------------------//

void updateClockBufferMode3()
{
	// Display the mode.
	led_buffer[0] = 0;
	led_buffer[1] = 3;

	//Display the value of led YELLOW;
	led_buffer[2] = PERIOD_YELLOW / 10;
	led_buffer[3] = PERIOD_YELLOW % 10;
}

//------------------//

void updateClockBufferMode4()
{
	// Display the mode.
	led_buffer[0] = 0;
	led_buffer[1] = 4;

	//Display the value of led GREEN;
	led_buffer[2] = PERIOD_GREEN / 10;
	led_buffer[3] = PERIOD_GREEN % 10;
}
