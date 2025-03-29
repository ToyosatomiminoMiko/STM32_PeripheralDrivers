#include "spi_oled.h"

void spi_oled_DMA_WriteCommand(uint8_t spi_cmd)
{
	SPI_OLED_CD_RESET;
	SPI_OLED_CS_RESET;
	uint8_t *cmd = &spi_cmd;
	HAL_SPI_Transmit_DMA(&hspi1, cmd, 1);
	SPI_OLED_CD_SET;
	SPI_OLED_CS_SET;
}

void spi_oled_DMA_WriteData(uint8_t spi_data)
{
	SPI_OLED_CD_SET;
	SPI_OLED_CS_RESET;
	uint8_t *data = &spi_data;
	HAL_SPI_Transmit_DMA(&hspi1, data, 1);
	SPI_OLED_CS_SET;
}

void spi_oled_WriteCommand(uint8_t spi_cmd)
{
	SPI_OLED_CD_RESET;
	SPI_OLED_CS_RESET;
	uint8_t *cmd = &spi_cmd;
	HAL_SPI_Transmit(&hspi1, cmd, 1, 0xFF);
	SPI_OLED_CD_SET;
	SPI_OLED_CS_SET;
}

void spi_oled_WriteData(uint8_t spi_data)
{
	SPI_OLED_CD_SET;
	SPI_OLED_CS_RESET;
	uint8_t *data = &spi_data;
	HAL_SPI_Transmit(&hspi1, data, 1, 0xFF);
	SPI_OLED_CS_SET;
}

void spi_oled_Clear(void)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		spi_oled_WriteCommand(0xb0 + i); // 设置页地址
		spi_oled_WriteCommand(0x10);     // 设置列地址的高4位
		spi_oled_WriteCommand(0x00);     // 设置列地址的低4位
		for (uint8_t n = 0; n < 128; n++)
		{
			spi_oled_WriteData(0x00); // 清除所有数据
		}
	}
}

void spi_oled_Full(void)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		spi_oled_WriteCommand(0xb0 + i);
		spi_oled_WriteCommand(0x10);
		spi_oled_WriteCommand(0x00);
		for (uint8_t n = 0; n < 128; n++)
		{
			spi_oled_WriteData(0xFF);
		}
	}
}

void spi_oled_Init(void)
{
	spi_oled_WriteCommand(0xAE); //--turn off oled panel
	spi_oled_WriteCommand(0x00); //---set low column address
	spi_oled_WriteCommand(0x10); //---set high column address
	spi_oled_WriteCommand(0x40); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	spi_oled_WriteCommand(0x81); //--set contrast control register
	spi_oled_WriteCommand(0xCF); // Set SEG Output Current Brightness
	spi_oled_WriteCommand(0xA1); //--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	spi_oled_WriteCommand(0xC8); // Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	spi_oled_WriteCommand(0xA6); //--set normal display
	spi_oled_WriteCommand(0xA8); //--set multiplex ratio(1 to 64)
	spi_oled_WriteCommand(0x3f); //--1/64 duty
	spi_oled_WriteCommand(0xD3); //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	spi_oled_WriteCommand(0x00); //-not offset
	spi_oled_WriteCommand(0xd5); //--set display clock divide ratio/oscillator frequency
	spi_oled_WriteCommand(0x80); //--set divide ratio, Set Clock as 100 Frames/Sec
	spi_oled_WriteCommand(0xD9); //--set pre-charge period
	spi_oled_WriteCommand(0xF1); // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	spi_oled_WriteCommand(0xDA); //--set com pins hardware configuration
	spi_oled_WriteCommand(0x12);
	spi_oled_WriteCommand(0xDB); //--set vcomh
	spi_oled_WriteCommand(0x40); // Set VCOM Deselect Level
	spi_oled_WriteCommand(0x20); //-Set Page Addressing Mode (0x00/0x01/0x02)
	spi_oled_WriteCommand(0x02); //
	spi_oled_WriteCommand(0x8D); //--set Charge Pump enable/disable
	spi_oled_WriteCommand(0x14); //--set(0x10) disable
	spi_oled_WriteCommand(0xA4); // Disable Entire Display On (0xa4/0xa5)
	spi_oled_WriteCommand(0xA6); // Disable Inverse Display On (0xa6/a7)
	spi_oled_Clear();
	spi_oled_WriteCommand(0xAF); // display ON
}

void spi_oled_ColorTurn(uint8_t i)
{
	if (i)
		spi_oled_WriteCommand(0xA7); // 反色显示
	else
		spi_oled_WriteCommand(0xA6); // 正常显示
}

void spi_oled_DisplayTurn(uint8_t i)
{
	if (i)
	{
		spi_oled_WriteCommand(0xC0); // 反转显示
		spi_oled_WriteCommand(0xA0);
	}
	else
	{
		spi_oled_WriteCommand(0xC8); // 正常显示
		spi_oled_WriteCommand(0xA1);
	}
}

void spi_oled_address(uint8_t x, uint8_t y)
{
	spi_oled_WriteCommand(0xb0 + y);                 // 设置页地址
	spi_oled_WriteCommand(((x & 0xf0) >> 4) | 0x10); // 设置列地址的高4位
	spi_oled_WriteCommand((x & 0x0f));               // 设置列地址的低4位
}

void spi_oled_Display128x64(uint8_t *image)
{
	for (uint8_t m = 0; m < 8; m++)
	{
		spi_oled_address(0, m);
		for (uint8_t n = 0; n < 128; n++)
		{
			spi_oled_WriteData(*image); // 写数据到OLED,每写完一个8位的数据后列地址自动加1
			image++;
		}
	}
}

void spi_oled_DMA_ShowFrame(void)
{
	for (uint8_t m = 0; m < 8; m++)
	{
		spi_oled_DMA_WriteCommand(0xb0 + m);
		spi_oled_DMA_WriteCommand(0x10);
		spi_oled_DMA_WriteCommand(0x00);
		for (uint8_t n = 0; n < 128; n++)
		{
			spi_oled_DMA_WriteData(GRAM[m][n]);
		}
	}
}

void spi_oled_ShowFrame(void)
{
	for (uint8_t m = 0; m < 8; m++)
	{
		spi_oled_WriteCommand(0xb0 + m);
		spi_oled_WriteCommand(0x10);
		spi_oled_WriteCommand(0x00);
		for (uint8_t n = 0; n < 128; n++)
		{
			spi_oled_WriteData(GRAM[m][n]);
		}
	}
}
