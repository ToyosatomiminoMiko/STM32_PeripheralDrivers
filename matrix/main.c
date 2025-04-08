#include <stdio.h>
#include "iic_oled/iic_oled.h"
#include "spi_w25q/spi_w25q.h"
#include "spi_oled/spi_oled.h"
#include "matrix/matrix.h"
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

	HAL_Init();
	SystemClock_Config();
	/* USER CODE BEGIN SysInit */
	Matrix_4x4 temp_matrix =
	{
	{ } };
	box b2 =
	{
	{ 0, 0, 0, 1 },
	{ 1, 0, 0, 1 },
	{ 1, 0, 1, 1 },
	{ 0, 0, 1, 1 },
	{ 0, 1, 1, 1 },
	{ 0, 1, 0, 1 },
	{ 1, 1, 0, 1 },
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
	Matrix_4x4 x0 =
	{
	{ 1, 0, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 1 } };
	Matrix_4x4 y0 =
	{
	{ 1, 0, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 1 } };
	Matrix_4x4 z0 =
	{
	{ 1, 0, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 1 } };
	while (1)
	{
		// Draw -> OLED
		// button
		oled_Drawline(b2[0][0] * 40 + 48, b2[0][2] * 40 + 12,
				b2[1][0] * 40 + 48, b2[1][2] * 40 + 12);
		oled_Drawline(b2[1][0] * 40 + 48, b2[1][2] * 40 + 12,
				b2[2][0] * 40 + 48, b2[2][2] * 40 + 12);
		oled_Drawline(b2[2][0] * 40 + 48, b2[2][2] * 40 + 12,
				b2[3][0] * 40 + 48, b2[3][2] * 40 + 12);
		oled_Drawline(b2[3][0] * 40 + 48, b2[3][2] * 40 + 12,
				b2[0][0] * 40 + 48, b2[0][2] * 40 + 12);
		//
		oled_Drawline(b2[3][0] * 40 + 48, b2[3][2] * 40 + 12,
				b2[4][0] * 40 + 48, b2[4][2] * 40 + 12);
		oled_Drawline(b2[0][0] * 40 + 48, b2[0][2] * 40 + 12,
				b2[5][0] * 40 + 48, b2[5][2] * 40 + 12);
		oled_Drawline(b2[1][0] * 40 + 48, b2[1][2] * 40 + 12,
				b2[6][0] * 40 + 48, b2[6][2] * 40 + 12);
		oled_Drawline(b2[2][0] * 40 + 48, b2[2][2] * 40 + 12,
				b2[7][0] * 40 + 48, b2[7][2] * 40 + 12);
		// top
		oled_Drawline(b2[5][0] * 40 + 48, b2[5][2] * 40 + 12,
				b2[6][0] * 40 + 48, b2[6][2] * 40 + 12);
		oled_Drawline(b2[6][0] * 40 + 48, b2[6][2] * 40 + 12,
				b2[7][0] * 40 + 48, b2[7][2] * 40 + 12);
		oled_Drawline(b2[7][0] * 40 + 48, b2[7][2] * 40 + 12,
				b2[4][0] * 40 + 48, b2[4][2] * 40 + 12);
		oled_Drawline(b2[4][0] * 40 + 48, b2[4][2] * 40 + 12,
				b2[5][0] * 40 + 48, b2[5][2] * 40 + 12);

		spi_oled_DMA_ShowFrame();
		oled_NewFrame();
		// transformation
		rotate_x_3d(x0, (M_PI / 180));
		rotate_y_3d(y0, (M_PI / 180));
		rotate_z_3d(z0, (M_PI / 180));
		matrix_multiply_4x4(temp_matrix, x0, y0);
		matrix_multiply_4x4(temp_matrix, temp_matrix, z0);
		// matrix multiply
		for (uint8_t i = 0; i < 8; i++)
		{
			Vector_4 temp_vec0 =
			{ b2[i][0], b2[i][1], b2[i][2], b2[i][3] };
			matrix_vector_multiply(temp_vec0, temp_matrix, temp_vec0);
			b2[i][0] = temp_vec0[0];
			b2[i][1] = temp_vec0[1];
			b2[i][2] = temp_vec0[2];
			b2[i][3] = temp_vec0[3];
		}
		//HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}
