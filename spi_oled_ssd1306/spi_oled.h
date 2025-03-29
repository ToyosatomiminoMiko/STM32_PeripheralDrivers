#ifndef BSP_SPI_OLED_SPI_OLED_H_
#define BSP_SPI_OLED_SPI_OLED_H_

#include "main.h"
#include "spi.h"
#include "iic_oled/iic_oled.h"

#define SPI_OLED_CS_SET HAL_GPIO_WritePin(SPI_OLED_CS_GPIO_Port,SPI_OLED_CS_Pin,GPIO_PIN_SET)
#define SPI_OLED_CS_RESET HAL_GPIO_WritePin(SPI_OLED_CS_GPIO_Port,SPI_OLED_CS_Pin,GPIO_PIN_RESET)
#define SPI_OLED_CD_SET HAL_GPIO_WritePin(SPI_OLED_DC_GPIO_Port,SPI_OLED_DC_Pin,GPIO_PIN_SET)
#define SPI_OLED_CD_RESET HAL_GPIO_WritePin(SPI_OLED_DC_GPIO_Port,SPI_OLED_DC_Pin,GPIO_PIN_RESET)

void spi_oled_DMA_WriteCommand(uint8_t spi_cmd);
void spi_oled_DMA_WriteData(uint8_t spi_data);
void spi_oled_WriteCommand(uint8_t spi_cmd);
void spi_oled_WriteData(uint8_t spi_data);
void spi_oled_Clear(void);
void spi_oled_Full(void);
void spi_oled_Init(void);
void spi_oled_ColorTurn(uint8_t i);
void spi_oled_DisplayTurn(uint8_t i);
void spi_oled_address(uint8_t x, uint8_t y);
void spi_oled_Display128x64(uint8_t *image);
void spi_oled_DMA_ShowFrame(void);
void spi_oled_ShowFrame(void);
#endif /* BSP_SPI_OLED_SPI_OLED_H_ */
