/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
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
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "iic_oled/iic_oled.h"
#include "spi_w25q/spi_w25q.h"
#include "spi_oled/spi_oled.h"
#include "matrix/matrix.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define X 64
#define Y 32
#define S 1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void
SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void Drawline(float x0, float y0, float x1, float y1)
{
	oled_Drawline(x0 * S + X, y0 * S + Y, x1 * S + X, y1 * S + Y);
}
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

	const box b1 =
	{
	{ -1, -1, -1, 1 },
	{ 1, -1, -1, 1 },
	{ 1, -1, 1, 1 },
	{ -1, -1, 1, 1 },
	{ -1, 1, 1, 1 },
	{ -1, 1, -1, 1 },
	{ 1, 1, -1, 1 },
	{ 1, 1, 1, 1 } };
	box b2 =
	{
	{ -1, -1, -1, 1 },
	{ 1, -1, -1, 1 },
	{ 1, -1, 1, 1 },
	{ -1, -1, 1, 1 },
	{ -1, 1, 1, 1 },
	{ -1, 1, -1, 1 },
	{ 1, 1, -1, 1 },
	{ 1, 1, 1, 1 } };
	/* USER CODE END SysInit */
	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_I2C2_Init();
	MX_USART1_UART_Init();
	MX_SPI1_Init();
	MX_SPI2_Init();
	/* USER CODE BEGIN 2 */
	spi_oled_Init();
	spi_oled_ColorTurn(0);
	spi_oled_DisplayTurn(0);
	spi_oled_Full();
	HAL_Delay(100);
	spi_oled_Clear();
	HAL_Delay(100);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	Matrix_4x4 x0, y0, z0, s0;
	float r = 0;
	uint16_t n = 0;
	while (1)
	{
		Matrix_4x4 temp_matrix =
		{
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 } };
		Drawline(b2[0][0], b2[0][1], b2[1][0], b2[1][1]);
		Drawline(b2[1][0], b2[1][1], b2[2][0], b2[2][1]);
		Drawline(b2[2][0], b2[2][1], b2[3][0], b2[3][1]);
		Drawline(b2[3][0], b2[3][1], b2[0][0], b2[0][1]);
		//
		Drawline(b2[3][0], b2[3][1], b2[4][0], b2[4][1]);
		Drawline(b2[0][0], b2[0][1], b2[5][0], b2[5][1]);
		Drawline(b2[1][0], b2[1][1], b2[6][0], b2[6][1]);
		Drawline(b2[2][0], b2[2][1], b2[7][0], b2[7][1]);
		// top
		Drawline(b2[5][0], b2[5][1], b2[6][0], b2[6][1]);
		Drawline(b2[6][0], b2[6][1], b2[7][0], b2[7][1]);
		Drawline(b2[7][0], b2[7][1], b2[4][0], b2[4][1]);
		Drawline(b2[4][0], b2[4][1], b2[5][0], b2[5][1]);
		// show
		spi_oled_DMA_ShowFrame();
		oled_NewFrame();
		if (n == 360)
			n = 0;
		// transformation
		r = (M_PI / 180) * (float) n++;
		rotate_x_3d(x0, r);
		rotate_y_3d(y0, r);
		rotate_z_3d(z0, r);
		scale_3d(s0, 20, 20, 20);
		// matrix multiply
		matrix_multiply_4x4(temp_matrix, z0, temp_matrix);
		matrix_multiply_4x4(temp_matrix, y0, temp_matrix);
		matrix_multiply_4x4(temp_matrix, x0, temp_matrix);
		matrix_multiply_4x4(temp_matrix, s0, temp_matrix);
		// vector multiply
		for (uint8_t i = 0; i < 8; i++)
		{
			Vector_4 temp_vec0 =
			{ b1[i][0], b1[i][1], b1[i][2], 1 };
			matrix_vector_multiply(temp_vec0, temp_matrix, temp_vec0);
			memcpy(b2[i], temp_vec0, sizeof(Vector_4));
		}

		//HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
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
