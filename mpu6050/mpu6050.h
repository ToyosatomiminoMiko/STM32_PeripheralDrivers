#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_
#include "i2c.h"
#include "usart.h"
#include <stdio.h>

#define MPU6050_ADD 0xD0
void mpu6050_Init(void);
void mpu6050_GetData(float *T, double *Ax, double *Ay, double *Az, double *Gx,
		double *Gy, double *Gz);

#endif /* INC_MPU6050_H_ */
