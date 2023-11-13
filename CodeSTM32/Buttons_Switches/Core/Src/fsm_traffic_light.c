/*
 * fsm_traffic_light.c
 *
 *  Created on: Nov 1, 2023
 *      Author: Vy Nguyen
 */


#include "fsm_traffic_light.h"

void fsm_traffic_light()
{
	switch (status)
	{

	//------------MODE INIT ----------------//
	case INIT:
		status = MODE_1;
		break;

	//-----------MODE 1 -------------------//
	case MODE_1:
		status = RED1_GREEN2;

		HAL_GPIO_WritePin(LED_RED_1h_GPIO_Port, LED_RED_1h_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW_1h_GPIO_Port, LED_YELLOW_1h_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_1h_GPIO_Port, LED_GREEN_1h_Pin, SET);

		HAL_GPIO_WritePin(LED_RED_2v_GPIO_Port, LED_RED_2v_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2v_GPIO_Port, LED_YELLOW_2v_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_2v_GPIO_Port, LED_GREEN_2v_Pin, RESET);


		counter_led_horizontal = 1;
		counter_led_vertical = 1;
		index_led = 0;
		updateClockBufferMode1();
		update7SEG(index_led);

		setTimer(0, PERIOD_GREEN * 1000); //timer for case RED1_GREEN2
		setTimer(1, 1000);	// timer updateClockBufferMode1
		setTimer(2, 250);	// timer scanning LED 7-SEG
		clearTimer(3);
		break;

	case RED1_GREEN2:
		HAL_GPIO_WritePin(LED_RED_1h_GPIO_Port, LED_RED_1h_Pin, RESET);
		HAL_GPIO_WritePin(LED_GREEN_1h_GPIO_Port, LED_GREEN_1h_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_2v_GPIO_Port, LED_RED_2v_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_2v_GPIO_Port, LED_GREEN_2v_Pin, RESET);

		if(timer_flag[0] == 1)
		{
			status = RED1_YELLOW2;
			setTimer(0, PERIOD_YELLOW * 1000);
		}

		if(timer_flag[1] == 1)
		{
			updateClockBufferMode1();
			setTimer(1, 1000);
		}

		if(timer_flag[2] == 1)
		{
			update7SEG(index_led);
			setTimer(2, 250);
		}

		if (isButtonPressed(0) == 1) //Button SELECT MODE is pressed
		{
			status = MODE_2;
		}
		break;

	case RED1_YELLOW2:
		HAL_GPIO_WritePin(LED_GREEN_2v_GPIO_Port, LED_GREEN_2v_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2v_GPIO_Port, LED_YELLOW_2v_Pin, RESET);

		if(timer_flag[0] == 1)
		{
			status = GREEN1_RED2;
			setTimer(0, PERIOD_GREEN * 1000);
		}

		if(timer_flag[1] == 1)
		{
			updateClockBufferMode1();
			setTimer(1, 1000);
		}

		if(timer_flag[2] == 1)
		{
			update7SEG(index_led);
			setTimer(2, 250);
		}

		if (isButtonPressed(0) == 1) //Button SELECT MODE is pressed
		{
			status = MODE_2;
		}
		break;

	case GREEN1_RED2:
		 HAL_GPIO_WritePin(LED_RED_1h_GPIO_Port, LED_RED_1h_Pin, SET);
		 HAL_GPIO_WritePin(LED_GREEN_1h_GPIO_Port, LED_GREEN_1h_Pin, RESET);
		 HAL_GPIO_WritePin(LED_RED_2v_GPIO_Port, LED_RED_2v_Pin, RESET);
		 HAL_GPIO_WritePin(LED_YELLOW_2v_GPIO_Port, LED_YELLOW_2v_Pin, SET);

		if(timer_flag[0] == 1)
		{
			status = YELLOW1_RED2;
			setTimer(0, PERIOD_YELLOW * 1000);
		}

		if(timer_flag[1] == 1)
		{
			updateClockBufferMode1();
			setTimer(1, 1000);
		}

		if(timer_flag[2] == 1)
		{
			update7SEG(index_led);
			setTimer(2, 250);
		}

		if (isButtonPressed(0) == 1) //Button SELECT MODE is pressed
		{
			status = MODE_2;
		}
		break;

	case YELLOW1_RED2:
		 HAL_GPIO_WritePin(LED_GREEN_1h_GPIO_Port, LED_GREEN_1h_Pin, SET);
		 HAL_GPIO_WritePin(LED_YELLOW_1h_GPIO_Port, LED_YELLOW_1h_Pin, RESET);

		if(timer_flag[0] == 1)
		{
			status = RED1_GREEN2;
			setTimer(0, PERIOD_GREEN * 1000);
		}

		if(timer_flag[1] == 1)
		{
			updateClockBufferMode1();
			setTimer(1, 1000);
		}

		if(timer_flag[2] == 1)
		{
			update7SEG(index_led);
			setTimer(2, 250);
		}

		if (isButtonPressed(0) == 1) //Button SELECT MODE is pressed
		{
			status = MODE_2;
		}
		break;

		//-----------MODE 2 -------------------//
	case MODE_2:
		HAL_GPIO_WritePin(LED_RED_1h_GPIO_Port, LED_RED_1h_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW_1h_GPIO_Port, LED_YELLOW_1h_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_1h_GPIO_Port, LED_GREEN_1h_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_2v_GPIO_Port, LED_RED_2v_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW_2v_GPIO_Port, LED_YELLOW_2v_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_2v_GPIO_Port, LED_GREEN_2v_Pin, SET);

		index_led = 0;
		updateClockBufferMode2();
		update7SEG(index_led);

		setTimer(2, 250);	// timer scanning LED 7-SEG
							// and updateClockBufferMode2
		setTimer(3, 500);	// timer blinking LED_RED
		clearTimer(0);
		clearTimer(1);

		status = AUTO_RED;
		break;

	case AUTO_RED:
		//Toggle all led RED and set timer.
		if (timer_flag[3] == 1)
		{
			setTimer(3, 500);
			HAL_GPIO_TogglePin(LED_RED_1h_GPIO_Port, LED_RED_1h_Pin);
			HAL_GPIO_TogglePin(LED_RED_2v_GPIO_Port, LED_RED_2v_Pin);
		}

		//Scanning LED 7-SEG
		if (timer_flag[2] == 1)
		{
			setTimer(2, 250);
			updateClockBufferMode2();
			update7SEG(index_led);
		}

		if (isButtonPressed(0) == 1)  //Button SELECT MODE is pressed
		{
			status = MODE_3;
		}

		if(isButtonPressed(1) == 1)  //Button MODIFY MODE is pressed
		{
			status = INC_RED;
			if(PERIOD_RED >= 99) PERIOD_RED = PERIOD_YELLOW + 1;
			else PERIOD_RED++;
		}
		break;

	case INC_RED:
		if (timer_flag[3] == 1)
		{
			setTimer(3, 500);
			HAL_GPIO_TogglePin(LED_RED_1h_GPIO_Port, LED_RED_1h_Pin);
			HAL_GPIO_TogglePin(LED_RED_2v_GPIO_Port, LED_RED_2v_Pin);
		}

		//Scanning LED 7-SEG
		if (timer_flag[2] == 1)
		{
			setTimer(2, 250);
			updateClockBufferMode2();
			update7SEG(index_led);
		}

		if (isButtonPressed(1) == 1)  //Button MODIFY MODE is pressed
		{
			if(PERIOD_RED >= 99) PERIOD_RED = PERIOD_YELLOW + 1;
			else PERIOD_RED++;
		}

		if(isButtonPressed(2) == 1)  //Button SELECT VALUE is pressed
		{
			status = AUTO_RED;
			PERIOD_GREEN = PERIOD_RED - PERIOD_YELLOW;
		}
		break;

		//-----------MODE 3 -------------------//
	case MODE_3:
		HAL_GPIO_WritePin(LED_RED_1h_GPIO_Port, LED_RED_1h_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_1h_GPIO_Port, LED_YELLOW_1h_Pin, RESET);
		HAL_GPIO_WritePin(LED_GREEN_1h_GPIO_Port, LED_GREEN_1h_Pin, SET);
		HAL_GPIO_WritePin(LED_RED_2v_GPIO_Port, LED_RED_2v_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2v_GPIO_Port, LED_YELLOW_2v_Pin, RESET);
		HAL_GPIO_WritePin(LED_GREEN_2v_GPIO_Port, LED_GREEN_2v_Pin, SET);

		index_led = 0;
		updateClockBufferMode2();
		update7SEG(index_led);

		setTimer(2, 250);	// timer scanning LED 7-SEG
							// and updateClockBufferMode2
		setTimer(3, 500);	// timer blinking LED_YELLOW
		clearTimer(0);
		clearTimer(1);

		status = AUTO_YELLOW;
		break;

	case AUTO_YELLOW:
		//Toggle all led RED and set timer.
		if (timer_flag[3] == 1)
		{
			setTimer(3, 500);
			HAL_GPIO_TogglePin(LED_YELLOW_1h_GPIO_Port, LED_YELLOW_1h_Pin);
			HAL_GPIO_TogglePin(LED_YELLOW_2v_GPIO_Port, LED_YELLOW_2v_Pin);
		}

		//Scanning LED 7-SEG
		if (timer_flag[2] == 1)
		{
			setTimer(2, 250);
			updateClockBufferMode3();
			update7SEG(index_led);
		}

		if (isButtonPressed(0) == 1)  //Button SELECT MODE is pressed
		{
			status = MODE_4;
		}

		if(isButtonPressed(1) == 1)  //Button MODIFY MODE is pressed
		{
			status = INC_YELLOW;
			if(PERIOD_YELLOW >= 5) PERIOD_YELLOW = 1;
			else PERIOD_YELLOW++;
		}
		break;

	case INC_YELLOW:
		if (timer_flag[3] == 1)
		{
			setTimer(3, 500);
			HAL_GPIO_TogglePin(LED_YELLOW_1h_GPIO_Port, LED_YELLOW_1h_Pin);
			HAL_GPIO_TogglePin(LED_YELLOW_2v_GPIO_Port, LED_YELLOW_2v_Pin);
		}

		//Scanning LED 7-SEG
		if (timer_flag[2] == 1)
		{
			setTimer(2, 250);
			updateClockBufferMode3();
			update7SEG(index_led);
		}

		if (isButtonPressed(1) == 1)  //Button MODIFY MODE is pressed
		{
			if(PERIOD_YELLOW >= 5) PERIOD_YELLOW = 1;
			else PERIOD_YELLOW++;
		}

		if(isButtonPressed(2) == 1)  //Button SELECT VALUE is pressed
		{
			status = AUTO_YELLOW;
			if(PERIOD_RED <= PERIOD_YELLOW) PERIOD_RED = PERIOD_YELLOW + 1;
			PERIOD_GREEN = PERIOD_RED - PERIOD_YELLOW;
		}
		break;

		//-----------MODE 4 -------------------//
	case MODE_4:
		HAL_GPIO_WritePin(LED_RED_1h_GPIO_Port, LED_RED_1h_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_1h_GPIO_Port, LED_YELLOW_1h_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_1h_GPIO_Port, LED_GREEN_1h_Pin, RESET);
		HAL_GPIO_WritePin(LED_RED_2v_GPIO_Port, LED_RED_2v_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW_2v_GPIO_Port, LED_YELLOW_2v_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN_2v_GPIO_Port, LED_GREEN_2v_Pin, RESET);

		index_led = 0;
		updateClockBufferMode2();
		update7SEG(index_led);

		setTimer(2, 250);	// timer scanning LED 7-SEG
							// and updateClockBufferMode2
		setTimer(3, 500);	// timer blinking LED_YELLOW
		clearTimer(0);
		clearTimer(1);

		status = AUTO_GREEN;
		break;

	case AUTO_GREEN:
		//Toggle all led RED and set timer.
		if (timer_flag[3] == 1)
		{
			setTimer(3, 500);
			HAL_GPIO_TogglePin(LED_GREEN_1h_GPIO_Port, LED_GREEN_1h_Pin);
			HAL_GPIO_TogglePin(LED_GREEN_2v_GPIO_Port, LED_GREEN_2v_Pin);
		}

		//Scanning LED 7-SEG
		if (timer_flag[2] == 1)
		{
			setTimer(2, 250);
			updateClockBufferMode4();
			update7SEG(index_led);
		}

		if (isButtonPressed(0) == 1)  //Button SELECT MODE is pressed
		{
			status = MODE_1;
		}

		if(isButtonPressed(1) == 1)  //Button MODIFY MODE is pressed
		{
			status = INC_GREEN;
			if(PERIOD_GREEN >= 99) PERIOD_GREEN = 1;
			else PERIOD_GREEN++;
		}
		break;

	case INC_GREEN:
		if (timer_flag[3] == 1)
		{
			setTimer(3, 500);
			HAL_GPIO_TogglePin(LED_GREEN_1h_GPIO_Port, LED_GREEN_1h_Pin);
			HAL_GPIO_TogglePin(LED_GREEN_2v_GPIO_Port, LED_GREEN_2v_Pin);
		}

		//Scanning LED 7-SEG
		if (timer_flag[2] == 1)
		{
			setTimer(2, 250);
			updateClockBufferMode4();
			update7SEG(index_led);
		}

		if (isButtonPressed(1) == 1)  //Button MODIFY MODE is pressed
		{
			if(PERIOD_GREEN >= 99) PERIOD_GREEN = 1;
			else PERIOD_GREEN++;
		}

		if(isButtonPressed(2) == 1)  //Button SELECT VALUE is pressed
		{
			status = AUTO_GREEN;
			PERIOD_RED = PERIOD_GREEN + PERIOD_YELLOW;
		}
		break;

		//---------------------------//

	default:
		break;
}











}
