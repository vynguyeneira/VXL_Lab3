/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SELECT_MODE_Pin GPIO_PIN_1
#define SELECT_MODE_GPIO_Port GPIOA
#define MODIFY_MODE_Pin GPIO_PIN_2
#define MODIFY_MODE_GPIO_Port GPIOA
#define SET_VALUE_Pin GPIO_PIN_3
#define SET_VALUE_GPIO_Port GPIOA
#define LED_RED_1h_Pin GPIO_PIN_4
#define LED_RED_1h_GPIO_Port GPIOA
#define LED_YELLOW_1h_Pin GPIO_PIN_5
#define LED_YELLOW_1h_GPIO_Port GPIOA
#define LED_GREEN_1h_Pin GPIO_PIN_6
#define LED_GREEN_1h_GPIO_Port GPIOA
#define LED_RED_2v_Pin GPIO_PIN_7
#define LED_RED_2v_GPIO_Port GPIOA
#define SEG0_Pin GPIO_PIN_0
#define SEG0_GPIO_Port GPIOB
#define SEG1_Pin GPIO_PIN_1
#define SEG1_GPIO_Port GPIOB
#define SEG2_Pin GPIO_PIN_2
#define SEG2_GPIO_Port GPIOB
#define LED_YELLOW_2v_Pin GPIO_PIN_8
#define LED_YELLOW_2v_GPIO_Port GPIOA
#define LED_GREEN_2v_Pin GPIO_PIN_9
#define LED_GREEN_2v_GPIO_Port GPIOA
#define VERTICAL_1_Pin GPIO_PIN_10
#define VERTICAL_1_GPIO_Port GPIOA
#define VERTICAL_2_Pin GPIO_PIN_11
#define VERTICAL_2_GPIO_Port GPIOA
#define HORIZONTAL_1_Pin GPIO_PIN_12
#define HORIZONTAL_1_GPIO_Port GPIOA
#define HORIZONTAL_2_Pin GPIO_PIN_13
#define HORIZONTAL_2_GPIO_Port GPIOA
#define SEG3_Pin GPIO_PIN_3
#define SEG3_GPIO_Port GPIOB
#define SEG4_Pin GPIO_PIN_4
#define SEG4_GPIO_Port GPIOB
#define SEG5_Pin GPIO_PIN_5
#define SEG5_GPIO_Port GPIOB
#define SEG6_Pin GPIO_PIN_6
#define SEG6_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
