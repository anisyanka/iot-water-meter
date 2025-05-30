/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#if (USE_EXERNAL_SIM7080 == 1)
# define GSM_PWRKEY_PORT GPIOD
# define GSM_PWRKEY_PIN  GPIO_PIN_2
#else
# define GSM_PWRKEY_PORT GPIOB
# define GSM_PWRKEY_PIN  GPIO_PIN_14
#endif

#define SW1_BTN_ID        0
#define SW1_BTN_PORT      GPIOB
#define SW1_BTN_PIN       GPIO_PIN_11
#define SW1_PORT_CLK_EN() __HAL_RCC_GPIOB_CLK_ENABLE()

#define SW2_BTN_ID        1
#define SW2_BTN_PORT      GPIOB
#define SW2_BTN_PIN       GPIO_PIN_12
#define SW2_PORT_CLK_EN() __HAL_RCC_GPIOB_CLK_ENABLE()

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
