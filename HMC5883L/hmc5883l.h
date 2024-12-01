#ifndef BSP_HMC5883L_HMC5883L_H_
#define BSP_HMC5883L_HMC5883L_H_
#include "i2c.h"
#include <math.h>

#define CONF_A 00	 // R/W
#define CONF_B 01	 // R/W
#define MODE 02		 // R/W
#define OUT_X_MSB 03 // R
#define OUT_X_LSB 04 // R
#define OUT_Z_MSB 05 // R
#define OUT_Z_LSB 06 // R
#define OUT_Y_MSB 07 // R
#define OUT_Y_LSB 08 // R
#define STATUS 09	 // R
#define IDNENT_A 10	 // R
#define IDNENT_B 11	 // R
#define IDNENT_C 12	 // R
#define HMC5883L 0x3C

void hmc5883l_init();
double hmc5883l_GetAngle();

#endif /* BSP_HMC5883L_HMC5883L_H_ */
