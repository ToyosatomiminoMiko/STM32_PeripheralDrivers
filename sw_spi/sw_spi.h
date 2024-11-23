#ifndef BSP_SOFTWARE_SPI_SW_SPI_H_
#define BSP_SOFTWARE_SPI_SW_SPI_H_
#include "main.h"

// VFD
#define VFD_CS_SET \
	HAL_GPIO_WritePin(VFD_CS_GPIO_Port, VFD_CS_Pin, GPIO_PIN_SET)
#define VFD_CS_RESET \
	HAL_GPIO_WritePin(VFD_CS_GPIO_Port, VFD_CS_Pin, GPIO_PIN_RESET)
#define VFD_RST_SET \
	HAL_GPIO_WritePin(VFD_RST_GPIO_Port, VFD_RST_Pin, GPIO_PIN_SET)
#define VFD_RST_RESET \
	HAL_GPIO_WritePin(VFD_RST_GPIO_Port, VFD_RST_Pin, GPIO_PIN_RESET)
#define VFD_DATA_SET \
	HAL_GPIO_WritePin(VFD_DATA_GPIO_Port, VFD_DATA_Pin, GPIO_PIN_SET)
#define VFD_DATA_RESET \
	HAL_GPIO_WritePin(VFD_DATA_GPIO_Port, VFD_DATA_Pin, GPIO_PIN_RESET)
#define VFD_CLK_SET \
	HAL_GPIO_WritePin(VFD_CLK_GPIO_Port, VFD_CLK_Pin, GPIO_PIN_SET)
#define VFD_CLK_RESET \
	HAL_GPIO_WritePin(VFD_CLK_GPIO_Port, VFD_CLK_Pin, GPIO_PIN_RESET)
// TFT
#define TFT_CS_SET \
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_SET)
#define TFT_CS_RESET \
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET)
#define TFT_SCL_SET \
	HAL_GPIO_WritePin(TFT_SCL_GPIO_Port, TFT_SCL_Pin, GPIO_PIN_SET)
#define TFT_SCL_RESET \
	HAL_GPIO_WritePin(TFT_SCL_GPIO_Port, TFT_SCL_Pin, GPIO_PIN_RESET)
#define TFT_SDA_SET \
	HAL_GPIO_WritePin(TFT_SDA_GPIO_Port, TFT_SDA_Pin, GPIO_PIN_SET)
#define TFT_SDA_RESET \
	HAL_GPIO_WritePin(TFT_SDA_GPIO_Port, TFT_SDA_Pin, GPIO_PIN_RESET)
#define TFT_RES_SET \
	HAL_GPIO_WritePin(TFT_RES_GPIO_Port, TFT_RES_Pin, GPIO_PIN_SET)
#define TFT_RES_RESET \
	HAL_GPIO_WritePin(TFT_RES_GPIO_Port, TFT_RES_Pin, GPIO_PIN_RESET)
#define TFT_DC_SET \
	HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_SET)
#define TFT_DC_RESET \
	HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_RESET)
#define USE_HORIZONTAL 0

void spi_LfSendByte(uint8_t byte);
void spi_HfSendByte(uint8_t byte);
void vfd_SetBrightness(uint16_t brightness);
void vfd_Init(uint8_t brightness);
void tft_Init(void);
void tft_WriteData(uint8_t byte);
void tft_WriteCmd(uint8_t byte);
void vfd_ClearDcram(void);
void vfd_DisplayChar(const unsigned char row, const unsigned char col,
		const unsigned char data);
void vfd_DisplayString(const unsigned char row, const unsigned char col,
		const unsigned char *data, const uint8_t size);
void tft_Fill(uint8_t data);
void tft_Refresh();
uint32_t tft_pow(uint8_t m, uint8_t n);
void tft_DrawPoint(uint16_t x, uint16_t y, uint8_t mode);
void tft_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r);
#endif /* BSP_SOFTWARE_SPI_SW_SPI_H_ */
