#ifndef BSP_SOFTWARE_SPI_SW_SPI_H_
#define BSP_SOFTWARE_SPI_SW_SPI_H_
#include "main.h"
#include "spi.h"

#define VFD_CS_SET \
	HAL_GPIO_WritePin(VFD_CS_GPIO_Port, VFD_CS_Pin, GPIO_PIN_SET)
#define VFD_CS_RESET \
	HAL_GPIO_WritePin(VFD_CS_GPIO_Port, VFD_CS_Pin, GPIO_PIN_RESET)
#define VFD_RST_SET \
	HAL_GPIO_WritePin(VFD_RST_GPIO_Port, VFD_RST_Pin, GPIO_PIN_SET)
#define VFD_RST_RESET \
	HAL_GPIO_WritePin(VFD_RST_GPIO_Port, VFD_RST_Pin, GPIO_PIN_RESET)

HAL_StatusTypeDef hwspi_SendByte(uint8_t byte);
void vfd_SetBrightness(uint16_t brightness);
void vfd_Init(uint8_t brightness);
void vfd_ClearDcram(void);
void vfd_DisplayChar(const unsigned char row, const unsigned char col,
		const unsigned char data);
void vfd_DisplayString(const unsigned char row, const unsigned char col,
		const unsigned char *data, const uint8_t size);

#endif /* BSP_SOFTWARE_SPI_SW_SPI_H_ */
