/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/

#define BUTTON1_PORT 	GPIOA
#define BUTTON1_PIN		GPIO_PIN_1

#define BUTTON2_PORT	GPIOA
#define BUTTON2_PIN		GPIO_PIN_2

#define LED1_PORT		GPIOB
#define LED1_PIN		GPIO_PIN_0

#define LED2_PORT		GPIOB
#define LED2_PIN		GPIO_PIN_1

#define LED3_PORT		GPIOB
#define LED3_PIN		GPIO_PIN_2

/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

	/* USER CODE BEGIN 1 */
	/* defining a variable to store the current led state */
	unsigned char button1_counter =0;
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
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */


	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		if (HAL_GPIO_ReadPin (BUTTON1_PORT, BUTTON1_PIN))
		{
			/* to avoid de-bouncing */
			HAL_Delay(30);

			if (HAL_GPIO_ReadPin (BUTTON1_PORT, BUTTON1_PIN))
			{
				switch (button1_counter)
				{
				case 0:
					HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET);
					HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(LED3_PORT, LED3_PIN, GPIO_PIN_RESET);
					button1_counter++;
					break;
				case 1:
					HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_SET);
					HAL_GPIO_WritePin(LED3_PORT, LED3_PIN, GPIO_PIN_RESET);
					button1_counter++;
					break;
				case 2:
					HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(LED3_PORT, LED3_PIN, GPIO_PIN_SET);
					button1_counter=0;
					break;
				}
			}
		}

		if (HAL_GPIO_ReadPin (BUTTON2_PORT, BUTTON2_PIN))
		{
			/* to avoid de-bouncing */
			HAL_Delay(30);
			if (HAL_GPIO_ReadPin (BUTTON2_PORT, BUTTON2_PIN))
			{
				HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN);
				HAL_GPIO_TogglePin(LED2_PORT, LED2_PIN);
				HAL_GPIO_TogglePin(LED3_PORT, LED3_PIN);
			}
		}

		/* to avoid incrementing two state with only one small push on the button
		 * but in the same time, in case of long push the states will increment*/
		HAL_Delay(50);
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

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}

	/** Enables the Clock Security System
	 */
	HAL_RCC_EnableCSS();
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);

	/*Configure GPIO pins : PA1 PA2 */
	GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB0 PB1 PB2 */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
