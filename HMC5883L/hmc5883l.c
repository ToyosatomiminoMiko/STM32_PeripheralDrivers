#include "hmc5883l.h"

void hmc5883l_init()
{
	uint8_t config = 0x70;
	HAL_I2C_Mem_Write(&hi2c2, HMC5883L, CONF_A, 1, &config, 1, 0xFF);
	config = 0x20;
	HAL_I2C_Mem_Write(&hi2c2, HMC5883L, CONF_B, 1, &config, 1, 0xFF);
	config = 0x00;
	HAL_I2C_Mem_Write(&hi2c2, HMC5883L, MODE, 1, &config, 1, 0xFF);
}

double hmc5883l_GetAngle()
{
	uint8_t data[6];
	int16_t dx, dy;
	float X, Y;
	double angle;
	// read data
	HAL_I2C_Mem_Read(&hi2c2, HMC5883L, OUT_X_MSB, 1, data, 6, 0xFF);
	dx = data[0] << 8 | data[1];
	dy = data[4] << 8 | data[5];
	X = (float) dx / 1090;
	Y = (float) dy / 1090;
	// resolve
	if ((X > 0) && (Y > 0))
		angle = atan(Y / X) * 57;
	else if ((X > 0) && (Y < 0))
		angle = 360 + atan(Y / X) * 57;
	else if ((X == 0) && (Y > 0))
		angle = 90;
	else if ((X == 0) && (Y < 0))
		angle = 270;
	else if (X < 0)
		angle = 180 + atan(Y / X) * 57;
	// output
	//sprintf(s, "X=%03f;Y=%03f\r\n", X, Y);
	//HAL_UART_Transmit(&huart1, (uint8_t*) s, sizeof(s), 0xFF);
	//sprintf(s, "angle=%03.03f\r\n\0", angle);
	//HAL_UART_Transmit(&huart1, (uint8_t*) s, sizeof(s), 0xFF);
	return angle;
}

