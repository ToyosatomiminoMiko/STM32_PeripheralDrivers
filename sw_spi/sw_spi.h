#ifndef BSP_SOFTWARE_SPI_SW_SPI_H_
#define BSP_SOFTWARE_SPI_SW_SPI_H_
#include "main.h"

// VFD
#ifdef VFD_ENABLE
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
// SPI
#define SPI_LSB
#define SPI_LSB_SCL_SET VFD_CLK_SET
#define SPI_LSB_SCL_RESET VFD_CLK_RESET
#define SPI_LSB_SDA_SET VFD_DATA_SET
#define SPI_LSB_SDA_RESET VFD_DATA_RESET
#endif

// ST7302
#ifdef ST7302_ENABLE
#define ST7302_CS_SET \
	HAL_GPIO_WritePin(ST7302_CS_GPIO_Port, ST7302_CS_Pin, GPIO_PIN_SET)
#define ST7302_CS_RESET \
	HAL_GPIO_WritePin(ST7302_CS_GPIO_Port, ST7302_CS_Pin, GPIO_PIN_RESET)
#define ST7302_SCL_SET \
	HAL_GPIO_WritePin(ST7302_SCL_GPIO_Port, ST7302_SCL_Pin, GPIO_PIN_SET)
#define ST7302_SCL_RESET \
	HAL_GPIO_WritePin(ST7302_SCL_GPIO_Port, ST7302_SCL_Pin, GPIO_PIN_RESET)
#define ST7302_SDA_SET \
	HAL_GPIO_WritePin(ST7302_SDA_GPIO_Port, ST7302_SDA_Pin, GPIO_PIN_SET)
#define ST7302_SDA_RESET \
	HAL_GPIO_WritePin(ST7302_SDA_GPIO_Port, ST7302_SDA_Pin, GPIO_PIN_RESET)
#define ST7302_RES_SET \
	HAL_GPIO_WritePin(ST7302_RES_GPIO_Port, ST7302_RES_Pin, GPIO_PIN_SET)
#define ST7302_RES_RESET \
	HAL_GPIO_WritePin(ST7302_RES_GPIO_Port, ST7302_RES_Pin, GPIO_PIN_RESET)
#define ST7302_DC_SET \
	HAL_GPIO_WritePin(ST7302_DC_GPIO_Port, ST7302_DC_Pin, GPIO_PIN_SET)
#define ST7302_DC_RESET \
	HAL_GPIO_WritePin(ST7302_DC_GPIO_Port, ST7302_DC_Pin, GPIO_PIN_RESET)
// SPI
#define SPI_HSB
#define SPI_HSB_SCL_SET ST7302_SCL_SET
#define SPI_HSB_SCL_RESET ST7302_SCL_RESET
#define SPI_HSB_SDA_SET ST7302_SDA_SET
#define SPI_HSB_SDA_RESET ST7302_SDA_RESET
// other
#define USE_HORIZONTAL 0
#endif
// GC9A01
#ifdef GC9A01_ENABLE
#define GC9A01_CS_SET \
	HAL_GPIO_WritePin(GC9A01_CS_GPIO_Port, GC9A01_CS_Pin, GPIO_PIN_SET)
#define GC9A01_CS_RESET \
	HAL_GPIO_WritePin(GC9A01_CS_GPIO_Port, GC9A01_CS_Pin, GPIO_PIN_RESET)
#define GC9A01_SCL_SET \
	HAL_GPIO_WritePin(GC9A01_SCL_GPIO_Port, GC9A01_SCL_Pin, GPIO_PIN_SET)
#define GC9A01_SCL_RESET \
	HAL_GPIO_WritePin(GC9A01_SCL_GPIO_Port, GC9A01_SCL_Pin, GPIO_PIN_RESET)
#define GC9A01_SDA_SET \
	HAL_GPIO_WritePin(GC9A01_SDA_GPIO_Port, GC9A01_SDA_Pin, GPIO_PIN_SET)
#define GC9A01_SDA_RESET \
	HAL_GPIO_WritePin(GC9A01_SDA_GPIO_Port, GC9A01_SDA_Pin, GPIO_PIN_RESET)
#define GC9A01_RES_SET \
	HAL_GPIO_WritePin(GC9A01_RES_GPIO_Port, GC9A01_RES_Pin, GPIO_PIN_SET)
#define GC9A01_RES_RESET \
	HAL_GPIO_WritePin(GC9A01_RES_GPIO_Port, GC9A01_RES_Pin, GPIO_PIN_RESET)
#define GC9A01_DC_SET \
	HAL_GPIO_WritePin(GC9A01_DC_GPIO_Port, GC9A01_DC_Pin, GPIO_PIN_SET)
#define GC9A01_DC_RESET \
	HAL_GPIO_WritePin(GC9A01_DC_GPIO_Port, GC9A01_DC_Pin, GPIO_PIN_RESET)
#define GC9A01_BL_SET \
	HAL_GPIO_WritePin(GC9A01_BL_GPIO_Port, GC9A01_BL_Pin, GPIO_PIN_SET)
#define GC9A01_BL_RESET \
	HAL_GPIO_WritePin(GC9A01_BL_GPIO_Port, GC9A01_BL_Pin, GPIO_PIN_RESET)
// SPI
#define SPI_HSB
#define SPI_HSB_SCL_SET GC9A01_SCL_SET
#define SPI_HSB_SCL_RESET GC9A01_SCL_RESET
#define SPI_HSB_SDA_SET GC9A01_SDA_SET
#define SPI_HSB_SDA_RESET GC9A01_SDA_RESET
// OTHER
#define USE_HORIZONTAL 0
#endif

void spi_LfSendByte(uint8_t byte);
void spi_HfSendByte(uint8_t byte);
void vfd_SetBrightness(uint16_t brightness);
void vfd_Init(uint8_t brightness);
void st7302_Init(void);
void st7302_WriteData(uint8_t byte);
void st7302_WriteCmd(uint8_t byte);
void vfd_ClearDcram(void);
void vfd_DisplayChar(const unsigned char row, const unsigned char col,
		const unsigned char data);
void vfd_DisplayString(const unsigned char row, const unsigned char col,
		const unsigned char *data, const uint8_t size);
void st7302_Fill(uint8_t data);
void st7302_Refresh();
uint32_t st7302_pow(uint8_t m, uint8_t n);
void st7302_DrawPoint(uint16_t x, uint16_t y, uint8_t mode);
void st7302_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r);
void st7302_GramSet(uint16_t address, uint8_t data);
void gc9a01_WriteData8(uint8_t byte);
void gc9a01_WriteData16(uint16_t byte);
void gc9a01_WriteCmd(uint8_t byte);
void gc9a01_Init();
void gc9a01_AddressSet(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void gc9a01_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend,
		uint16_t color);
void gc9a01_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void gc9a01_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);
void gc9a01_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
		uint16_t color);
#endif /* BSP_SOFTWARE_SPI_SW_SPI_H_ */
