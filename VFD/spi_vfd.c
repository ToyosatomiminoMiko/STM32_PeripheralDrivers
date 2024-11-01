#include "spi_vfd.h"

HAL_StatusTypeDef hwspi_SendByte(uint8_t byte)
{
	return HAL_SPI_Transmit(&hspi1, &byte, 1, 0xFF);
}

void vfd_SetBrightness(uint16_t brightness)
{
	uint8_t bl, bh;
	bl = brightness % 4;
	bh = brightness / 4;

	VFD_CS_RESET;
	hwspi_SendByte(0x50 | bl);
	hwspi_SendByte(bh);
	VFD_CS_SET;

	HAL_Delay(1);
}

void vfd_Init(uint8_t brightness)
{
	// reset
	VFD_CS_SET;
	HAL_Delay(100);
	VFD_RST_RESET;
	HAL_Delay(10);
	VFD_RST_SET;
	// normal display
	HAL_Delay(1);
	VFD_CS_RESET;
	hwspi_SendByte(0x70);
	VFD_CS_SET;
	// set com1-com16
	HAL_Delay(1);
	VFD_CS_RESET;
	hwspi_SendByte(0x6C);
	VFD_CS_SET;
	// set brightness
	HAL_Delay(1);
	vfd_SetBrightness(brightness * 4);
}

void vfd_ClearDcram(void)
{
	VFD_CS_RESET;
	hwspi_SendByte(0x90);
	hwspi_SendByte(0x00);
	for (uint8_t i = 0; i < 16; i++)
	{
		hwspi_SendByte(0xFF);
	}
	VFD_CS_SET;
	HAL_Delay(1);

	VFD_CS_RESET;
	hwspi_SendByte(0x10);
	hwspi_SendByte(0x00);
	for (uint8_t i = 0; i < 16; i++)
	{
		hwspi_SendByte(0xFF);
	}
	VFD_CS_SET;
	HAL_Delay(1);
}

void vfd_DisplayChar(const unsigned char row, const unsigned char col,
		const unsigned char data)
{
	VFD_CS_RESET;
	if (row == 0) // low row
	{
		hwspi_SendByte(0x10);
	}
	else if (row == 1) // high row
	{
		hwspi_SendByte(0x90);
	}
	else	// row out range
	{
		VFD_CS_SET;
		HAL_Delay(1);
		return;
	}
	if (col > 15)	// column out range
	{
		VFD_CS_SET;
		HAL_Delay(1);
		return;
	}
	hwspi_SendByte(15 - col);
	hwspi_SendByte(data);
	VFD_CS_SET;
	HAL_Delay(1);
}

void vfd_DisplayString(const unsigned char row, const unsigned char col,
		const unsigned char *data, const uint8_t size)
{
	VFD_CS_RESET;
	if (row == 0) // low row
		hwspi_SendByte(0x10);
	else if (row == 1) // high row
		hwspi_SendByte(0x90);
	else	// row out range
	{
		VFD_CS_SET;
		HAL_Delay(1);
		return;
	}
	if (col > 15)	// column out range
	{
		VFD_CS_SET;
		HAL_Delay(1);
		return;
	}
	hwspi_SendByte(col);
	for (uint8_t i = 0; i < size; i++)
		hwspi_SendByte(data[size - i - 1]);
	VFD_CS_SET;
	HAL_Delay(1);
}
