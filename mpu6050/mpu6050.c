#include "mpu6050.h"

// I need a pilot.. flash_dog (uint8_t*)
void mpu6050_Init(void)
{
	// 关闭 AD0
	HAL_GPIO_WritePin(AD0_GPIO_Port, AD0_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	// 电源管理寄存器 清零解除休眠
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADD, 0x6B, 1, 0x80, 1, 0xFF);
	HAL_Delay(100);
	// PLL x
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADD, 0x6B, 1, 0x01, 1, 0xFF);
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADD, 0x6C, 1, 0x00, 1, 0xFF);
	// 陀螺仪初始化 ±2000°/s max 0b11000
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADD, 0x1B, 1, 0x18, 1, 0xFF);
	// 加速度初始化 ±2g max
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADD, 0x1C, 1, 0x00, 1, 0xFF);
	// FIFO 使能 FIFO
	//HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADD, 0x23, 1, 0x08, 1, 0xFF);
	// 陀螺仪采样率 0x32
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADD, 0x19, 1, 0x13, 1, 0xFF);
	// 低通滤波器 0x04
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADD, 0x1A, 1, 0x04, 1, 0xFF);
}

void mpu6050_GetData(float *temperature, double *accel_x, double *accel_y,
		double *accel_z, double *gyro_x, double *gyro_y, double *gyro_z)
{
	uint8_t mpu_data[14] =
	{ };
	uint8_t StartAddress = 0x3B;
	if (HAL_I2C_Mem_Read(&hi2c2, MPU6050_ADD, StartAddress, 1, mpu_data,
			sizeof(mpu_data), 50) != HAL_OK)
	{
		//HAL_UART_Transmit(&huart1, (uint8_t*) "error!!\r\n", 10, 0xFF);
		HAL_Delay(1);
	}
	// 获取温度 拼接
	*temperature = (mpu_data[6] << 8) | mpu_data[7];
	if (*temperature > 32768)
		*temperature -= 65536;
	// 实际温度
	*temperature = (36.53 + *temperature / 340);
	short int accel_x1 = ((mpu_data[0] << 8) | mpu_data[1]);
	short int accel_y1 = ((mpu_data[2] << 8) | mpu_data[3]);
	short int accel_z1 = ((mpu_data[4] << 8) | mpu_data[5]);
	//
	short int gyro_x1 = ((mpu_data[8] << 8) | mpu_data[9]);
	short int gyro_y1 = ((mpu_data[10] << 8) | mpu_data[11]);
	short int gyro_z1 = ((mpu_data[12] << 8) | mpu_data[13]);

	*accel_x = (double) accel_x1 / 16384;
	*accel_y = (double) accel_y1 / 16384;
	*accel_z = (double) accel_z1 / 16384;
	*gyro_x = (double) gyro_x1 / 65.5;
	*gyro_y = (double) gyro_y1 / 65.5;
	*gyro_z = (double) gyro_z1 / 65.5;
}

