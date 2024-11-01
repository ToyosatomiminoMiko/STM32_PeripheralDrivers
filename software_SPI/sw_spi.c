#include "sw_spi.h"

void swspi_SendByte(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		VFD_CLK_RESET;
		if (byte & 0x01)
		{
			VFD_DATA_SET;
		}
		else
		{
			VFD_DATA_RESET;
		}
		byte = byte >> 1;
		HAL_Delay(1);
		VFD_CLK_SET;
		HAL_Delay(1);
	}
}
