/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "logger.h"
#include "mqtt_adapter.h"
#include "digital_in_core.h"
#include "buttons.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define GND1_SET HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_HIGH);
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;

LCD_HandleTypeDef hlcd;

UART_HandleTypeDef hlpuart1;
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC_Init(void);
static void MX_LCD_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void show_symbol(uint8_t s, uint8_t s_c);
void gnd_1_set(void);
void gnd_2_set(void);
void gnd_3_set(void);
void gnd_all_set(void);

void show_d80(void);
void show_d81(void);
void show_d82(void);
void show_d83(void);
void show_d84(void);
void show_d85(void);
void show_d86(void);
void show_d87(void);
void show_d88(void);
void show_d89(void);

void show_d0(void);
void show_d1(void);
void show_d2(void);
void show_d3(void);
void show_d4(void);
void show_d5(void);
void show_d6(void);
void show_d7(void);
void show_d8(void);
void show_reset(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t s_c = 0;
uint8_t s_c1 = 0;
uint8_t s_c2 = 0;
uint8_t s_c3 = 0;
uint8_t s_c4 = 0;
uint8_t s_c5 = 0;
uint8_t s_c6 = 0;
uint8_t s_c7 = 0;
uint8_t s_c8 = 0;
uint8_t s_c9 = 0;

uint8_t d8 = 0;

uint8_t d_counter = 1;

uint32_t lcd_data, lcd_data_old = 0;
uint32_t lcd_data_d1 = 0;
uint32_t lcd_data_d1_old = 0;
uint32_t lcd_data_d2, lcd_data_d2_old = 0;
uint32_t lcd_data_d3, lcd_data_d3_old = 0;
uint32_t lcd_data_d4, lcd_data_d4_old = 0;
uint32_t lcd_data_d5, lcd_data_d5_old = 0;
uint32_t lcd_data_d6, lcd_data_d6_old = 0;
uint32_t lcd_data_d7, lcd_data_d7_old = 0;

uint32_t lcd_data0 = 0xFFFFFFFF;
uint32_t lcd_data1 = 0xFFFFFFFF;
uint32_t lcd_data2 = 0xFFFFFFFF;
uint32_t lcd_data0_add = 0xFFFFFFFF;
uint32_t lcd_data1_add = 0xFFFFFFFF;
uint32_t lcd_data2_add = 0xFFFFFFFF;
uint8_t lcd_clear_flag = 0;

uint32_t lcd_data_0[3] = {2 , 5, 7};
uint32_t lcd_data_1[3] = {0 , 4, 4};//{0 , 1, 1};
uint32_t lcd_data_2[3] = {2 , 3, 6};//{2 , 6, 3};
uint32_t lcd_data_3[3] = {2 , 6, 6};//{2 , 3, 3};
uint32_t lcd_data_4[3] = {0 , 6, 5};//{0 , 3, 5};
uint32_t lcd_data_5[3] = {2 , 6, 3};//{2 , 3, 6};
uint32_t lcd_data_6[3] = {2 , 7, 3};//{2 , 7, 6};
uint32_t lcd_data_7[3] = {0 , 4, 6};//{0 , 1, 3};
uint32_t lcd_data_8[3] = {2 , 7, 7};//{2 , 7, 7};
uint32_t lcd_data_9[3] = {2 , 6, 7};//{2 , 3, 7};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
//   MX_DMA_Init();
//   MX_ADC_Init();
//   MX_LCD_Init();
//   MX_LPUART1_UART_Init();
  HAL_Delay(2000);
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	// HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
	
	// HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
	
	// HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  /* Hello from FW */
  extern uint32_t SystemCoreClock;
  logger_dgb_print("\n\n[water-meter] FW started. Core clock = %ld Hz\r\n", SystemCoreClock);

  /* Init SW1, SW2 and its handlers */
  buttons_init();

  /* Enable SIM7080 module, set params for NB-Iot and Yandex MQTT. Real connection will inside polling function */
  mqtt_init();

  while (1)
  {
    mqtt_poll();
	digital_in_poll();

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
			// if(lcd_clear_flag)
			// {
			// 	lcd_clear_flag = 0;
			// 	HAL_LCD_Clear(&hlcd);
			// }
			// 	show_d0();
			// 	show_d1();
			// 	show_d2();
			//   show_d3();
			// 	show_d4();
			// 	show_d5();
			//   show_d6();
			//   show_d7();

			/*
		switch(s_c)
		{
			case 0:
			{
				gnd_1_set();
			}
			break;
			case 1:
			{
				gnd_2_set();
			}
			break;
			case 2:
			{
				gnd_3_set();
			}
			break;
			default : break;
		}
		switch(d_counter)
		{
			case 1:
			{
				//show_symbol(20,8);
				d_counter = 2;
			}
			break;
			case 2:
			{
				//show_symbol(20,8);
				d_counter = 3;
			}
			break;
			case 3:
			{
				//show_symbol(20,8);
				d_counter = 4;
			}
			break;
			case 4:
			{
				//show_symbol(20,8);
				d_counter = 5;
			}
			break;
			case 5:
			{
				//show_symbol(20,8);
				d_counter = 6;
			}
			break;
			case 6:
			{
				//show_symbol(20,8);
				d_counter = 7;
			}
			break;
			case 7:
			{
			//	show_symbol(20,8);
				d_counter = 8;
			}
			break;
			case 8:
			{
				show_symbol(d8,8);
				d_counter = 1;
				//++s_c;
			//	if(s_c > 2)
			//	{
			//		s_c = 0;
			//	}
			}
			break;
			default: break;
		}
		*/
  }
	
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_LPUART1
                              |RCC_PERIPHCLK_RTC;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.OversamplingMode = DISABLE;
  hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.DMAContinuousRequests = ENABLE;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerFrequencyMode = ENABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_2;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_3;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief LCD Initialization Function
  * @param None
  * @retval None
  */
static void MX_LCD_Init(void)
{

  /* USER CODE BEGIN LCD_Init 0 */

  /* USER CODE END LCD_Init 0 */

  /* USER CODE BEGIN LCD_Init 1 */

  /* USER CODE END LCD_Init 1 */
  hlcd.Instance = LCD;
  hlcd.Init.Prescaler = LCD_PRESCALER_1;
  hlcd.Init.Divider = LCD_DIVIDER_16;
  hlcd.Init.Duty = LCD_DUTY_1_3;
  hlcd.Init.Bias = LCD_BIAS_1_2;
  hlcd.Init.VoltageSource = LCD_VOLTAGESOURCE_INTERNAL;
  hlcd.Init.Contrast = LCD_CONTRASTLEVEL_5;
  hlcd.Init.DeadTime = LCD_DEADTIME_0;
  hlcd.Init.PulseOnDuration = LCD_PULSEONDURATION_2;
  hlcd.Init.HighDrive = LCD_HIGHDRIVE_0;
  hlcd.Init.BlinkMode = LCD_BLINKMODE_OFF;
  hlcd.Init.BlinkFrequency = LCD_BLINKFREQUENCY_DIV8;
  hlcd.Init.MuxSegment = LCD_MUXSEGMENT_DISABLE;
  if (HAL_LCD_Init(&hlcd) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LCD_Init 2 */

  /* USER CODE END LCD_Init 2 */

}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 115200;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = (SIM7080_UART_USE_FLOW_CTRL == 1) ? UART_HWCONTROL_RTS_CTS : UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);

  /*Configure GPIO pins : PE4 PE5 PE6 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PC3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_LPTIM1;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PC4 PC5 PC6 PC7
                           PC8 PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PE12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB14 PB3 PB4
                           PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_14|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB11 PB12 */
//   GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
//   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//   GPIO_InitStruct.Pull = GPIO_PULLUP;
//   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PD1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

#if (USE_EXERNAL_SIM7080 == 1)
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
#endif
/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_SYSTICK_Callback(void)
{

	
		/*
	switch(d_counter)
		{
			case 0:
			{
				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER0, 0xFFFFFBFF, lcd_data);
				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER1, 0xFFFFFBFF, lcd_data);
				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER4, 0xFFFFFBFF, lcd_data);
				//show_symbol(0,8);
			//	d_counter = 2;
			}
			break;
			case 1:
			{
				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER0, 0xFFFFFBFF, lcd_data);
				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER1, 0xFFFFFBFF, lcd_data);
				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER4, 0xFFFFFBFF, lcd_data);
				//show_symbol(1,8);
			//	d_counter = 2;
			}
			break;
			case 2:
			{
				//show_symbol(2,8);
				//d_counter = 3;
			}
			break;
			case 3:
			{
				//show_symbol(3,8);
			//	d_counter = 4;
			}
			break;
			case 4:
			{
				//show_symbol(4,8);
				//d_counter = 5;
			}
			break;
			case 5:
			{
				//show_symbol(5,8);
			//	d_counter = 6;
			}
			break;
			case 6:
			{
				//show_symbol(6,8);
			//	d_counter = 7;
			}
			break;
			case 7:
			{
				//show_symbol(7,8);
			//	d_counter = 8;
			}
			break;
			case 8:
			{
				//show_symbol(8,8);
			//	d_counter = 2;
			}
			break;
			case 9:
			{
				//show_symbol(9,8);
			//	d_counter = 1;
				++s_c;
				if(s_c > 2)
				{
					s_c = 0;
				}
			}
			break;
			default: break;
		}
	*/
}
void show_d0(void)
{
	if(lcd_data_old != lcd_data)
				{
					lcd_data_old = lcd_data;
					HAL_LCD_Clear(&hlcd);
				}
				switch(lcd_data)
				{
					case 0:
					{
						lcd_data0 = (lcd_data_0[0] << (uint32_t)(0x1C));
						lcd_data1 = (lcd_data_0[1] << (uint32_t)(0x1C));
						lcd_data2 = (lcd_data_0[2] << (uint32_t)(0x1C));
					}
					break;
					case 1:
					{
						lcd_data0 = (lcd_data_1[0] << (uint32_t)(0x1C));
						lcd_data1 = (lcd_data_1[1] << (uint32_t)(0x1C));
						lcd_data2 = (lcd_data_1[2] << (uint32_t)(0x1C));
					}
					break;
					case 2:
					{
						lcd_data0 = (lcd_data_2[0] << (uint32_t)(0x1C));
						lcd_data1 = (lcd_data_2[1] << (uint32_t)(0x1C));
						lcd_data2 = (lcd_data_2[2] << (uint32_t)(0x1C));
					}
					break;
					case 3:
					{
						lcd_data0 = (lcd_data_3[0] << (uint32_t)(0x1C));
						lcd_data1 = (lcd_data_3[1] << (uint32_t)(0x1C));
						lcd_data2 = (lcd_data_3[2] << (uint32_t)(0x1C));
					}
					break;
					case 4:
					{
						lcd_data0 = (lcd_data_4[0] << (uint32_t)(0x1C));
						lcd_data1 = (lcd_data_4[1] << (uint32_t)(0x1C));
						lcd_data2 = (lcd_data_4[2] << (uint32_t)(0x1C));
					}
					break;
					case 5:
					{
						lcd_data0 = (lcd_data_5[0] << (uint32_t)(0x1C));
						lcd_data1 = (lcd_data_5[1] << (uint32_t)(0x1C));
						lcd_data2 = (lcd_data_5[2] << (uint32_t)(0x1C));
					}
					break;
					case 6:
					{
						lcd_data0 = (lcd_data_6[0] << (uint32_t)(0x1C));
						lcd_data1 = (lcd_data_6[1] << (uint32_t)(0x1C));
						lcd_data2 = (lcd_data_6[2] << (uint32_t)(0x1C));
					}
					break;
					case 7:
					{
						lcd_data0 = (lcd_data_7[0] << (uint32_t)(0x1C));
						lcd_data1 = (lcd_data_7[1] << (uint32_t)(0x1C));
						lcd_data2 = (lcd_data_7[2] << (uint32_t)(0x1C));
					}
					break;
					case 8:
					{
						lcd_data0 = (lcd_data_8[0] << (uint32_t)(0x1C));
						lcd_data1 = (lcd_data_8[1] << (uint32_t)(0x1C));
						lcd_data2 = (lcd_data_8[2] << (uint32_t)(0x1C));
					}
					break;
					case 9:
					{
						lcd_data0 = (lcd_data_9[0] << (uint32_t)(0x1C));
						lcd_data1 = (lcd_data_9[1] << (uint32_t)(0x1C));
						lcd_data2 = (lcd_data_9[2] << (uint32_t)(0x1C));
					}
					break;
					default: break;
				}
				
				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER0, 0xFFFFFFFF, lcd_data0);
				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER2, 0xFFFFFFFF, lcd_data1);
				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER4, 0xFFFFFFFF, lcd_data2);
				
				HAL_LCD_UpdateDisplayRequest(&hlcd);
}
void show_d1(void)
{
	if(lcd_data_d1_old != lcd_data_d1)
				{
					lcd_data_d1_old = lcd_data_d1;
					HAL_LCD_Clear(&hlcd);
				}
				switch(lcd_data_d1)
				{
					case 0:
					{
						lcd_data0 = (lcd_data_0[0] << (uint32_t)(0x0));
						lcd_data1 = (lcd_data_0[1] << (uint32_t)(0x0));
						lcd_data2 = (lcd_data_0[2] << (uint32_t)(0x0));
					}
					break;
					case 1:
					{
						lcd_data0 = (lcd_data_1[0] << (uint32_t)(0x0));
						lcd_data1 = (lcd_data_1[1] << (uint32_t)(0x0));
						lcd_data2 = (lcd_data_1[2] << (uint32_t)(0x0));
					}
					break;
					case 2:
					{
						lcd_data0 = (lcd_data_2[0] << (uint32_t)(0x0));
						lcd_data1 = (lcd_data_2[1] << (uint32_t)(0x0));
						lcd_data2 = (lcd_data_2[2] << (uint32_t)(0x0));
					}
					break;
					case 3:
					{
						lcd_data0 = (lcd_data_3[0] << (uint32_t)(0x0));
						lcd_data1 = (lcd_data_3[1] << (uint32_t)(0x0));
						lcd_data2 = (lcd_data_3[2] << (uint32_t)(0x0));
					}
					break;
					case 4:
					{
						lcd_data0 = (lcd_data_4[0] << (uint32_t)(0x0));
						lcd_data1 = (lcd_data_4[1] << (uint32_t)(0x0));
						lcd_data2 = (lcd_data_4[2] << (uint32_t)(0x0));
					}
					break;
					case 5:
					{
						lcd_data0 = (lcd_data_5[0] << (uint32_t)(0x0));
						lcd_data1 = (lcd_data_5[1] << (uint32_t)(0x0));
						lcd_data2 = (lcd_data_5[2] << (uint32_t)(0x0));
					}
					break;
					case 6:
					{
						lcd_data0 = (lcd_data_6[0] << (uint32_t)(0x0));
						lcd_data1 = (lcd_data_6[1] << (uint32_t)(0x0));
						lcd_data2 = (lcd_data_6[2] << (uint32_t)(0x0));
					}
					break;
					case 7:
					{
						lcd_data0 = (lcd_data_7[0] << (uint32_t)(0x0));
						lcd_data1 = (lcd_data_7[1] << (uint32_t)(0x0));
						lcd_data2 = (lcd_data_7[2] << (uint32_t)(0x0));
					}
					break;
					case 8:
					{
						lcd_data0 = (lcd_data_8[0] << (uint32_t)(0x0));
						lcd_data1 = (lcd_data_8[1] << (uint32_t)(0x0));
						lcd_data2 = (lcd_data_8[2] << (uint32_t)(0x0));
					}
					break;
					case 9:
					{
						lcd_data0 = (lcd_data_9[0] << (uint32_t)(0x0));
						lcd_data1 = (lcd_data_9[1] << (uint32_t)(0x0));
						lcd_data2 = (lcd_data_9[2] << (uint32_t)(0x0));
					}
					break;
					default: break;
				}
				lcd_data0_add = (lcd_data0 & 0x1) << (uint32_t)(0x1F);
				lcd_data0 = (lcd_data0 >> 1);
				lcd_data1_add = (lcd_data1 & 0x1) << (uint32_t)(0x1F);
				lcd_data1 = (lcd_data1 >> 1);
				lcd_data2_add = (lcd_data2 & 0x1) << (uint32_t)(0x1F);
				lcd_data2 = (lcd_data2 >> 1);
				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER0, 0xFFFFFFFF, lcd_data0_add);
				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER1, 0xFFFFFFFF, lcd_data0);
				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER2, 0xFFFFFFFF, lcd_data1_add);
				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER3, 0xFFFFFFFF, lcd_data1);
				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER4, 0xFFFFFFFF, lcd_data2_add);
				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER5, 0xFFFFFFFF, lcd_data2);
						
				HAL_LCD_UpdateDisplayRequest(&hlcd);
}
void show_d2(void)
{
	if(lcd_data_d2_old != lcd_data_d2)
				{
					lcd_data_d2_old = lcd_data_d2;
					HAL_LCD_Clear(&hlcd);
				}
				switch(lcd_data_d2)
				{
					case 0:
					{
						lcd_data0 = (lcd_data_0[0] << (uint32_t)(0x2));
						lcd_data1 = (lcd_data_0[1] << (uint32_t)(0x2));
						lcd_data2 = (lcd_data_0[2] << (uint32_t)(0x2));
					}
					break;
					case 1:
					{
						lcd_data0 = (lcd_data_1[0] << (uint32_t)(0x2));
						lcd_data1 = (lcd_data_1[1] << (uint32_t)(0x2));
						lcd_data2 = (lcd_data_1[2] << (uint32_t)(0x2));
					}
					break;
					case 2:
					{
						lcd_data0 = (lcd_data_2[0] << (uint32_t)(0x2));
						lcd_data1 = (lcd_data_2[1] << (uint32_t)(0x2));
						lcd_data2 = (lcd_data_2[2] << (uint32_t)(0x2));
					}
					break;
					case 3:
					{
						lcd_data0 = (lcd_data_3[0] << (uint32_t)(0x2));
						lcd_data1 = (lcd_data_3[1] << (uint32_t)(0x2));
						lcd_data2 = (lcd_data_3[2] << (uint32_t)(0x2));
					}
					break;
					case 4:
					{
						lcd_data0 = (lcd_data_4[0] << (uint32_t)(0x2));
						lcd_data1 = (lcd_data_4[1] << (uint32_t)(0x2));
						lcd_data2 = (lcd_data_4[2] << (uint32_t)(0x2));
					}
					break;
					case 5:
					{
						lcd_data0 = (lcd_data_5[0] << (uint32_t)(0x2));
						lcd_data1 = (lcd_data_5[1] << (uint32_t)(0x2));
						lcd_data2 = (lcd_data_5[2] << (uint32_t)(0x2));
					}
					break;
					case 6:
					{
						lcd_data0 = (lcd_data_6[0] << (uint32_t)(0x2));
						lcd_data1 = (lcd_data_6[1] << (uint32_t)(0x2));
						lcd_data2 = (lcd_data_6[2] << (uint32_t)(0x2));
					}
					break;
					case 7:
					{
						lcd_data0 = (lcd_data_7[0] << (uint32_t)(0x2));
						lcd_data1 = (lcd_data_7[1] << (uint32_t)(0x2));
						lcd_data2 = (lcd_data_7[2] << (uint32_t)(0x2));
					}
					break;
					case 8:
					{
						lcd_data0 = (lcd_data_8[0] << (uint32_t)(0x2));
						lcd_data1 = (lcd_data_8[1] << (uint32_t)(0x2));
						lcd_data2 = (lcd_data_8[2] << (uint32_t)(0x2));
					}
					break;
					case 9:
					{
						lcd_data0 = (lcd_data_9[0] << (uint32_t)(0x2));
						lcd_data1 = (lcd_data_9[1] << (uint32_t)(0x2));
						lcd_data2 = (lcd_data_9[2] << (uint32_t)(0x2));
					}
					break;
					default: break;
				}


				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER1, 0xFFFFFFFF, lcd_data0);

				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER3, 0xFFFFFFFF, lcd_data1);

				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER5, 0xFFFFFFFF, lcd_data2);
				
				HAL_LCD_UpdateDisplayRequest(&hlcd);
}
void show_d3(void)
{
		if(lcd_data_d3_old != lcd_data_d3)
				{
					lcd_data_d3_old = lcd_data_d3;
					HAL_LCD_Clear(&hlcd);
				}
				switch(lcd_data_d3)
				{
					case 0:
					{
						lcd_data0 = (lcd_data_0[0] << (uint32_t)(0x5));
						lcd_data1 = (lcd_data_0[1] << (uint32_t)(0x5));
						lcd_data2 = (lcd_data_0[2] << (uint32_t)(0x5));
					}
					break;
					case 1:
					{
						lcd_data0 = (lcd_data_1[0] << (uint32_t)(0x5));
						lcd_data1 = (lcd_data_1[1] << (uint32_t)(0x5));
						lcd_data2 = (lcd_data_1[2] << (uint32_t)(0x5));
					}
					break;
					case 2:
					{
						lcd_data0 = (lcd_data_2[0] << (uint32_t)(0x5));
						lcd_data1 = (lcd_data_2[1] << (uint32_t)(0x5));
						lcd_data2 = (lcd_data_2[2] << (uint32_t)(0x5));
					}
					break;
					case 3:
					{
						lcd_data0 = (lcd_data_3[0] << (uint32_t)(0x5));
						lcd_data1 = (lcd_data_3[1] << (uint32_t)(0x5));
						lcd_data2 = (lcd_data_3[2] << (uint32_t)(0x5));
					}
					break;
					case 4:
					{
						lcd_data0 = (lcd_data_4[0] << (uint32_t)(0x5));
						lcd_data1 = (lcd_data_4[1] << (uint32_t)(0x5));
						lcd_data2 = (lcd_data_4[2] << (uint32_t)(0x5));
					}
					break;
					case 5:
					{
						lcd_data0 = (lcd_data_5[0] << (uint32_t)(0x5));
						lcd_data1 = (lcd_data_5[1] << (uint32_t)(0x5));
						lcd_data2 = (lcd_data_5[2] << (uint32_t)(0x5));
					}
					break;
					case 6:
					{
						lcd_data0 = (lcd_data_6[0] << (uint32_t)(0x5));
						lcd_data1 = (lcd_data_6[1] << (uint32_t)(0x5));
						lcd_data2 = (lcd_data_6[2] << (uint32_t)(0x5));
					}
					break;
					case 7:
					{
						lcd_data0 = (lcd_data_7[0] << (uint32_t)(0x5));
						lcd_data1 = (lcd_data_7[1] << (uint32_t)(0x5));
						lcd_data2 = (lcd_data_7[2] << (uint32_t)(0x5));
					}
					break;
					case 8:
					{
						lcd_data0 = (lcd_data_8[0] << (uint32_t)(0x5));
						lcd_data1 = (lcd_data_8[1] << (uint32_t)(0x5));
						lcd_data2 = (lcd_data_8[2] << (uint32_t)(0x5));
					}
					break;
					case 9:
					{
						lcd_data0 = (lcd_data_9[0] << (uint32_t)(0x5));
						lcd_data1 = (lcd_data_9[1] << (uint32_t)(0x5));
						lcd_data2 = (lcd_data_9[2] << (uint32_t)(0x5));
					}
					break;
					default: break;
				}


				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER1, 0xFFFFFFFF, lcd_data0);

				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER3, 0xFFFFFFFF, lcd_data1);

				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER5, 0xFFFFFFFF, lcd_data2);
				
				HAL_LCD_UpdateDisplayRequest(&hlcd);
}
void show_d4(void)
{
	if(lcd_data_d4_old != lcd_data_d4)
				{
					lcd_data_d4_old = lcd_data_d4;
					HAL_LCD_Clear(&hlcd);
				}
				switch(lcd_data_d4)
				{
					case 0:
					{
						lcd_data0 = (lcd_data_0[0] << (uint32_t)(0x8));
						lcd_data1 = (lcd_data_0[1] << (uint32_t)(0x8));
						lcd_data2 = (lcd_data_0[2] << (uint32_t)(0x8));
					}
					break;
					case 1:
					{
						lcd_data0 = (lcd_data_1[0] << (uint32_t)(0x8));
						lcd_data1 = (lcd_data_1[1] << (uint32_t)(0x8));
						lcd_data2 = (lcd_data_1[2] << (uint32_t)(0x8));
					}
					break;
					case 2:
					{
						lcd_data0 = (lcd_data_2[0] << (uint32_t)(0x8));
						lcd_data1 = (lcd_data_2[1] << (uint32_t)(0x8));
						lcd_data2 = (lcd_data_2[2] << (uint32_t)(0x8));
					}
					break;
					case 3:
					{
						lcd_data0 = (lcd_data_3[0] << (uint32_t)(0x8));
						lcd_data1 = (lcd_data_3[1] << (uint32_t)(0x8));
						lcd_data2 = (lcd_data_3[2] << (uint32_t)(0x8));
					}
					break;
					case 4:
					{
						lcd_data0 = (lcd_data_4[0] << (uint32_t)(0x8));
						lcd_data1 = (lcd_data_4[1] << (uint32_t)(0x8));
						lcd_data2 = (lcd_data_4[2] << (uint32_t)(0x8));
					}
					break;
					case 5:
					{
						lcd_data0 = (lcd_data_5[0] << (uint32_t)(0x8));
						lcd_data1 = (lcd_data_5[1] << (uint32_t)(0x8));
						lcd_data2 = (lcd_data_5[2] << (uint32_t)(0x8));
					}
					break;
					case 6:
					{
						lcd_data0 = (lcd_data_6[0] << (uint32_t)(0x8));
						lcd_data1 = (lcd_data_6[1] << (uint32_t)(0x8));
						lcd_data2 = (lcd_data_6[2] << (uint32_t)(0x8));
					}
					break;
					case 7:
					{
						lcd_data0 = (lcd_data_7[0] << (uint32_t)(0x8));
						lcd_data1 = (lcd_data_7[1] << (uint32_t)(0x8));
						lcd_data2 = (lcd_data_7[2] << (uint32_t)(0x8));
					}
					break;
					case 8:
					{
						lcd_data0 = (lcd_data_8[0] << (uint32_t)(0x8));
						lcd_data1 = (lcd_data_8[1] << (uint32_t)(0x8));
						lcd_data2 = (lcd_data_8[2] << (uint32_t)(0x8));
					}
					break;
					case 9:
					{
						lcd_data0 = (lcd_data_9[0] << (uint32_t)(0x8));
						lcd_data1 = (lcd_data_9[1] << (uint32_t)(0x8));
						lcd_data2 = (lcd_data_9[2] << (uint32_t)(0x8));
					}
					break;
					default: break;
				}


				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER1, 0xFFFFFFFF, lcd_data0);

				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER3, 0xFFFFFFFF, lcd_data1);

				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER5, 0xFFFFFFFF, lcd_data2);
				
				HAL_LCD_UpdateDisplayRequest(&hlcd);
}
void show_d5(void)
{
		if(lcd_data_d5_old != lcd_data_d5)
				{
					lcd_data_d5_old = lcd_data_d5;
					HAL_LCD_Clear(&hlcd);
				}
				switch(lcd_data_d5)
				{
					case 0:
					{
						lcd_data0 = (lcd_data_0[0] << (uint32_t)(0xB));
						lcd_data1 = (lcd_data_0[1] << (uint32_t)(0xB));
						lcd_data2 = (lcd_data_0[2] << (uint32_t)(0xB));
					}
					break;
					case 1:
					{
						lcd_data0 = (lcd_data_1[0] << (uint32_t)(0xB));
						lcd_data1 = (lcd_data_1[1] << (uint32_t)(0xB));
						lcd_data2 = (lcd_data_1[2] << (uint32_t)(0xB));
					}
					break;
					case 2:
					{
						lcd_data0 = (lcd_data_2[0] << (uint32_t)(0xB));
						lcd_data1 = (lcd_data_2[1] << (uint32_t)(0xB));
						lcd_data2 = (lcd_data_2[2] << (uint32_t)(0xB));
					}
					break;
					case 3:
					{
						lcd_data0 = (lcd_data_3[0] << (uint32_t)(0xB));
						lcd_data1 = (lcd_data_3[1] << (uint32_t)(0xB));
						lcd_data2 = (lcd_data_3[2] << (uint32_t)(0xB));
					}
					break;
					case 4:
					{
						lcd_data0 = (lcd_data_4[0] << (uint32_t)(0xB));
						lcd_data1 = (lcd_data_4[1] << (uint32_t)(0xB));
						lcd_data2 = (lcd_data_4[2] << (uint32_t)(0xB));
					}
					break;
					case 5:
					{
						lcd_data0 = (lcd_data_5[0] << (uint32_t)(0xB));
						lcd_data1 = (lcd_data_5[1] << (uint32_t)(0xB));
						lcd_data2 = (lcd_data_5[2] << (uint32_t)(0xB));
					}
					break;
					case 6:
					{
						lcd_data0 = (lcd_data_6[0] << (uint32_t)(0xB));
						lcd_data1 = (lcd_data_6[1] << (uint32_t)(0xB));
						lcd_data2 = (lcd_data_6[2] << (uint32_t)(0xB));
					}
					break;
					case 7:
					{
						lcd_data0 = (lcd_data_7[0] << (uint32_t)(0xB));
						lcd_data1 = (lcd_data_7[1] << (uint32_t)(0xB));
						lcd_data2 = (lcd_data_7[2] << (uint32_t)(0xB));
					}
					break;
					case 8:
					{
						lcd_data0 = (lcd_data_8[0] << (uint32_t)(0xB));
						lcd_data1 = (lcd_data_8[1] << (uint32_t)(0xB));
						lcd_data2 = (lcd_data_8[2] << (uint32_t)(0xB));
					}
					break;
					case 9:
					{
						lcd_data0 = (lcd_data_9[0] << (uint32_t)(0xB));
						lcd_data1 = (lcd_data_9[1] << (uint32_t)(0xB));
						lcd_data2 = (lcd_data_9[2] << (uint32_t)(0xB));
					}
					break;
					default: break;
				}


				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER1, 0xFFFFFFFF, lcd_data0);

				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER3, 0xFFFFFFFF, lcd_data1);

				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER5, 0xFFFFFFFF, lcd_data2);
				
				HAL_LCD_UpdateDisplayRequest(&hlcd);
}
void show_d6(void)
{
			if(lcd_data_d6_old != lcd_data_d6)
				{
					lcd_data_d6_old = lcd_data_d6;
					HAL_LCD_Clear(&hlcd);
				}
				switch(lcd_data_d6)
				{
					case 0:
					{
						lcd_data0 = (lcd_data_0[0] << (uint32_t)(0xE));
						lcd_data1 = (lcd_data_0[1] << (uint32_t)(0xE));
						lcd_data2 = (lcd_data_0[2] << (uint32_t)(0xE));
					}
					break;
					case 1:
					{
						lcd_data0 = (lcd_data_1[0] << (uint32_t)(0xE));
						lcd_data1 = (lcd_data_1[1] << (uint32_t)(0xE));
						lcd_data2 = (lcd_data_1[2] << (uint32_t)(0xE));
					}
					break;
					case 2:
					{
						lcd_data0 = (lcd_data_2[0] << (uint32_t)(0xE));
						lcd_data1 = (lcd_data_2[1] << (uint32_t)(0xE));
						lcd_data2 = (lcd_data_2[2] << (uint32_t)(0xE));
					}
					break;
					case 3:
					{
						lcd_data0 = (lcd_data_3[0] << (uint32_t)(0xE));
						lcd_data1 = (lcd_data_3[1] << (uint32_t)(0xE));
						lcd_data2 = (lcd_data_3[2] << (uint32_t)(0xE));
					}
					break;
					case 4:
					{
						lcd_data0 = (lcd_data_4[0] << (uint32_t)(0xE));
						lcd_data1 = (lcd_data_4[1] << (uint32_t)(0xE));
						lcd_data2 = (lcd_data_4[2] << (uint32_t)(0xE));
					}
					break;
					case 5:
					{
						lcd_data0 = (lcd_data_5[0] << (uint32_t)(0xE));
						lcd_data1 = (lcd_data_5[1] << (uint32_t)(0xE));
						lcd_data2 = (lcd_data_5[2] << (uint32_t)(0xE));
					}
					break;
					case 6:
					{
						lcd_data0 = (lcd_data_6[0] << (uint32_t)(0xE));
						lcd_data1 = (lcd_data_6[1] << (uint32_t)(0xE));
						lcd_data2 = (lcd_data_6[2] << (uint32_t)(0xE));
					}
					break;
					case 7:
					{
						lcd_data0 = (lcd_data_7[0] << (uint32_t)(0xE));
						lcd_data1 = (lcd_data_7[1] << (uint32_t)(0xE));
						lcd_data2 = (lcd_data_7[2] << (uint32_t)(0xE));
					}
					break;
					case 8:
					{
						lcd_data0 = (lcd_data_8[0] << (uint32_t)(0xE));
						lcd_data1 = (lcd_data_8[1] << (uint32_t)(0xE));
						lcd_data2 = (lcd_data_8[2] << (uint32_t)(0xE));
					}
					break;
					case 9:
					{
						lcd_data0 = (lcd_data_9[0] << (uint32_t)(0xE));
						lcd_data1 = (lcd_data_9[1] << (uint32_t)(0xE));
						lcd_data2 = (lcd_data_9[2] << (uint32_t)(0xE));
					}
					break;
					default: break;
				}


				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER1, 0xFFFFFFFF, lcd_data0);

				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER3, 0xFFFFFFFF, lcd_data1);

				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER5, 0xFFFFFFFF, lcd_data2);
				//HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER0, 0xFFFFFFFF, 0xFFFFFFFF);
				//HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER1, 0xFFFFFFFF, 0xFFFFFFFF);
				//HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER2, 0xFFFFFFFF, 0xFFFFFFFF);
				//HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER3, 0xFFFFFFFF, 0xFFFFFFFF);
				//HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER4, 0xFFFFFFFF, 0xFFFFFFFF);
				//HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER5, 0xFFFFFFFF, 0xFFFFFFFF);
				HAL_LCD_UpdateDisplayRequest(&hlcd);
}
void show_d7(void)
{
		if(lcd_data_d7_old != lcd_data_d7)
				{
					lcd_data_d7_old = lcd_data_d7;
					HAL_LCD_Clear(&hlcd);
				}
				switch(lcd_data_d7)
				{
					case 0:
					{
						lcd_data0 = (lcd_data_0[0] << (uint32_t)(0x11));
						lcd_data1 = (lcd_data_0[1] << (uint32_t)(0x11));
						lcd_data2 = (lcd_data_0[2] << (uint32_t)(0x11));
					}
					break;
					case 1:
					{
						lcd_data0 = (lcd_data_1[0] << (uint32_t)(0x11));
						lcd_data1 = (lcd_data_1[1] << (uint32_t)(0x11));
						lcd_data2 = (lcd_data_1[2] << (uint32_t)(0x11));
					}
					break;
					case 2:
					{
						lcd_data0 = (lcd_data_2[0] << (uint32_t)(0x11));
						lcd_data1 = (lcd_data_2[1] << (uint32_t)(0x11));
						lcd_data2 = (lcd_data_2[2] << (uint32_t)(0x11));
					}
					break;
					case 3:
					{
						lcd_data0 = (lcd_data_3[0] << (uint32_t)(0x11));
						lcd_data1 = (lcd_data_3[1] << (uint32_t)(0x11));
						lcd_data2 = (lcd_data_3[2] << (uint32_t)(0x11));
					}
					break;
					case 4:
					{
						lcd_data0 = (lcd_data_4[0] << (uint32_t)(0x11));
						lcd_data1 = (lcd_data_4[1] << (uint32_t)(0x11));
						lcd_data2 = (lcd_data_4[2] << (uint32_t)(0x11));
					}
					break;
					case 5:
					{
						lcd_data0 = (lcd_data_5[0] << (uint32_t)(0x11));
						lcd_data1 = (lcd_data_5[1] << (uint32_t)(0x11));
						lcd_data2 = (lcd_data_5[2] << (uint32_t)(0x11));
					}
					break;
					case 6:
					{
						lcd_data0 = (lcd_data_6[0] << (uint32_t)(0x11));
						lcd_data1 = (lcd_data_6[1] << (uint32_t)(0x11));
						lcd_data2 = (lcd_data_6[2] << (uint32_t)(0x11));
					}
					break;
					case 7:
					{
						lcd_data0 = (lcd_data_7[0] << (uint32_t)(0x11));
						lcd_data1 = (lcd_data_7[1] << (uint32_t)(0x11));
						lcd_data2 = (lcd_data_7[2] << (uint32_t)(0x11));
					}
					break;
					case 8:
					{
						lcd_data0 = (lcd_data_8[0] << (uint32_t)(0x11));
						lcd_data1 = (lcd_data_8[1] << (uint32_t)(0x11));
						lcd_data2 = (lcd_data_8[2] << (uint32_t)(0x11));
					}
					break;
					case 9:
					{
						lcd_data0 = (lcd_data_9[0] << (uint32_t)(0x11));
						lcd_data1 = (lcd_data_9[1] << (uint32_t)(0x11));
						lcd_data2 = (lcd_data_9[2] << (uint32_t)(0x11));
					}
					break;
					default: break;
				}


				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER1, 0xFFFFFFFF, lcd_data0);

				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER3, 0xFFFFFFFF, lcd_data1);

				HAL_LCD_Write(&hlcd, LCD_RAM_REGISTER5, 0xFFFFFFFF, lcd_data2);
				
				HAL_LCD_UpdateDisplayRequest(&hlcd);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
