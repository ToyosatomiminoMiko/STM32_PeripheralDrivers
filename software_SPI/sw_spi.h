#ifndef BSP_SOFTWARE_SPI_SW_SPI_H_
#define BSP_SOFTWARE_SPI_SW_SPI_H_
#include "main.h"

#define VFD_CS_SET \
	HAL_GPIO_WritePin(VFD_CS_GPIO_Port, VFD_CS_Pin, GPIO_PIN_SET)
#define VFD_CS_RESET \
	HAL_GPIO_WritePin(VFD_CS_GPIO_Port, VFD_CS_Pin, GPIO_PIN_RESET)
#define VFD_RST_SET \
	HAL_GPIO_WritePin(VFS_RST_GPIO_Port, VFS_RST_Pin, GPIO_PIN_SET)
#define VFD_RST_RESET \
	HAL_GPIO_WritePin(VFS_RST_GPIO_Port, VFS_RST_Pin, GPIO_PIN_RESET)
#define VFD_DATA_SET \
	HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_SET)
#define VFD_DATA_RESET \
	HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_RESET)
#define VFD_CLK_SET \
	HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET)
#define VFD_CLK_RESET \
	HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET)

void swspi_SendByte(uint8_t byte);
#endif /* BSP_SOFTWARE_SPI_SW_SPI_H_ */

