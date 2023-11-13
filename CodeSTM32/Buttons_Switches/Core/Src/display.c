/*
 * display.c
 *
 *  Created on: Nov 1, 2023
 *      Author: Vy Nguyen
 */

#include "display.h"

void display7SEG(int num)
{
	if (num == 0)
	{
		HAL_GPIO_WritePin (GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin (GPIOB, SEG6_Pin, GPIO_PIN_SET);
	}
	else if (num == 1)
	{
		HAL_GPIO_WritePin (GPIOB, SEG1_Pin|SEG2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin (GPIOB, SEG0_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_SET);
	}
	else if (num == 2)
	{
		HAL_GPIO_WritePin (GPIOB, SEG0_Pin|SEG1_Pin|SEG3_Pin|SEG4_Pin|SEG6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin (GPIOB, SEG2_Pin|SEG5_Pin, GPIO_PIN_SET);
	}
	else if (num == 3)
	{
		HAL_GPIO_WritePin (GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin (GPIOB, SEG4_Pin|SEG5_Pin, GPIO_PIN_SET);
	}
	else if (num == 4)
	{
		HAL_GPIO_WritePin (GPIOB, SEG1_Pin|SEG2_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin (GPIOB, SEG0_Pin|SEG3_Pin|SEG4_Pin, GPIO_PIN_SET);
	}
	else if (num == 5)
	{
		HAL_GPIO_WritePin (GPIOB, SEG0_Pin|SEG2_Pin|SEG3_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin (GPIOB, SEG1_Pin|SEG4_Pin, GPIO_PIN_SET);
	}
	else if (num == 6)
	{
		HAL_GPIO_WritePin (GPIOB, SEG0_Pin|SEG2_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin (GPIOB, SEG1_Pin, GPIO_PIN_SET);
	}
	else if (num == 7)
	{
		HAL_GPIO_WritePin (GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin (GPIOB, SEG3_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_SET);
	}
	else if (num == 8)
	{
		HAL_GPIO_WritePin (GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin (GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin (GPIOB, SEG4_Pin, GPIO_PIN_SET);
	}
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
	counter_led_horizontal++;

	if (counter_led_horizontal > PERIOD_RED + PERIOD_YELLOW + PERIOD_GREEN)
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
