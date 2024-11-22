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
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fsmc_tftlcd/lcd.h"
#include <math.h>
#include "S42/s42.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define PI 3.1415926f
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
	MX_FSMC_Init();
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */
	lcd_init();
	lcd_clear(BLACK);
	g_back_color = BLACK;
	s42_Init();
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	uint8_t receive_buffer[36];
	//char *temp_data;
	int length = 0; // Receive data
	char s[5] = "";
	//char s0[7] = "";
	uint8_t d = 0; // angle
	// O-point
	const uint8_t Ox = 110, Oy = 132;
	// target point
	int8_t point_x = 0, point_y = 0;
	int8_t line_x = 0, line_y = 0;
	lcd_draw_circle(Ox, Oy, 102, GREEN);
	lcd_show_string(0, 0, 180, 16, 16, "RADAR SCANNING...", GREEN);
	lcd_show_string(Ox - 108, Oy - 6, 20, 12, 12, "0", GREEN);
	lcd_show_string(Ox + 104, Oy - 6, 20, 12, 12, "180", GREEN);
	lcd_show_string(Ox - 10, Oy + 104, 20, 12, 12, "90", GREEN);
	lcd_show_string(Ox - 10, Oy - 116, 20, 12, 12, "270", GREEN);
	while (1)
	{
		if (d <= 0)
			d = 200;
		line_y = sin((d - 1) * 1.8 * PI / 180) * (double) 101;
		line_x = cos((d - 1) * 1.8 * PI / 180) * (double) 101;
		lcd_draw_line(Ox, Oy, Ox - line_x, Oy - line_y, WHITE);
		HAL_UART_Receive(&huart2, receive_buffer, sizeof(receive_buffer), 0xFF);
		for (uint8_t i = 0; i < sizeof(receive_buffer); i++)
		{
			if (receive_buffer[i] == 'd' && receive_buffer[i + 1] == ':')
			{
				sprintf(s, "%c%c%c%c", receive_buffer[i + 2],
						receive_buffer[i + 3], receive_buffer[i + 4],
						receive_buffer[i + 5]);
				length = atoi(s);
				if (length > 2000)
					length = 2000;
				length = length / 20;
				point_y = sin(d * 1.8 * PI / 180) * (double) length;
				point_x = cos(d * 1.8 * PI / 180) * (double) length;
				lcd_draw_point(Ox - point_x, Oy - point_y, GREEN);
				d--;
				s42_pul();
				lcd_draw_line(Ox, Oy, Ox - line_x, Oy - line_y, BLACK);
				//sprintf(s0, "%d\r\n", length);
				//HAL_UART_Transmit(&huart1, (uint8_t*) s0, sizeof(s0), 0xFF);

			}
		}
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct =
	{ 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct =
	{ 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
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
