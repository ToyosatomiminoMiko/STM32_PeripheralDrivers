#include "sw_spi.h"

uint8_t TFT_GRAM[4125];
/*
 const uint8_t fonts[4][32] =
 {
 { 0x00, 0x00, 0xFE, 0x3F, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80,
 0x00, 0xFC, 0x1F, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80,
 0x00, 0x80, 0x00, 0xFF, 0x7F, 0x00, 0x00 },//"王",0
 { 0x40, 0x10, 0x84, 0x08, 0x08, 0x00, 0xE8, 0x3F, 0x00, 0x01, 0xC0, 0x1F, 0x4F,
 0x10, 0xC8, 0x1F, 0x48, 0x10, 0xC8, 0x1F, 0x48, 0x10, 0xC8, 0x1F, 0x48,
 0x10, 0x14, 0x00, 0xE2, 0x7F, 0x00, 0x00 },//"道",1
 { 0x10, 0x00, 0x10, 0x00, 0xC8, 0x7F, 0x04, 0x04, 0x12, 0x04, 0x10, 0x04, 0x88,
 0x04, 0x8C, 0x04, 0x8A, 0x3C, 0x89, 0x04, 0x88, 0x04, 0x88, 0x04, 0x88,
 0x04, 0x88, 0x04, 0xE8, 0x7F, 0x08, 0x00 },//"征",2
 { 0x00, 0x02, 0x04, 0x05, 0x88, 0x08, 0x48, 0x10, 0xA0, 0x6F, 0x00, 0x02, 0x0F,
 0x02, 0xE8, 0x3F, 0x08, 0x02, 0x48, 0x12, 0x48, 0x22, 0x28, 0x22, 0x88,
 0x02, 0x14, 0x01, 0xE2, 0x7F, 0x00, 0x00 }, //"途",3
 };*/

// HSB first
void spi_HfSendByte(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		TFT_SCL_RESET;
		if (byte & 0b10000000)
			TFT_SDA_SET;
		else
			TFT_SDA_RESET;
		byte = byte << 1;
		//HAL_Delay(1);
		TFT_SCL_SET;
		//HAL_Delay(1);
	}
}

// LSB first
void spi_LfSendByte(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		VFD_CLK_RESET;
		if (byte & 0x00000001)
			VFD_DATA_SET;
		else
			VFD_DATA_RESET;
		byte = byte >> 1;
		//HAL_Delay(1);
		VFD_CLK_SET;
		//HAL_Delay(1);
	}
}

// TFT send data
void tft_WriteData(uint8_t byte)
{
	TFT_DC_SET; //  DC high
	TFT_CS_RESET;
	spi_HfSendByte(byte);
	TFT_CS_SET;
}
// TFT send command
void tft_WriteCmd(uint8_t byte)
{
	TFT_DC_RESET; //  DC low
	TFT_CS_RESET;
	spi_HfSendByte(byte);
	TFT_CS_SET;
	TFT_DC_SET;
}

void vfd_SetBrightness(uint16_t brightness)
{
	uint8_t bl, bh;
	bl = brightness % 4;
	bh = brightness / 4;

	VFD_CS_RESET;
	spi_LfSendByte(0x50 | bl);
	spi_LfSendByte(bh);
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
	spi_LfSendByte(0x70);
	VFD_CS_SET;
	// set com1-com16
	HAL_Delay(1);
	VFD_CS_RESET;
	spi_LfSendByte(0x6C);
	VFD_CS_SET;
	// set brightness
	HAL_Delay(1);
	vfd_SetBrightness(brightness * 4);
}

void tft_Init(void)
{
	//tft_GPIO_Init(); // init GPIO

	TFT_RES_RESET; // reset
	HAL_Delay(100);
	TFT_RES_SET;
	HAL_Delay(100);

	HAL_Delay(100);

	HAL_Delay(300); // HAL_Delay 300ms

	tft_WriteCmd(0x38);
	tft_WriteCmd(0xEB); // Enable OTP
	tft_WriteData(0x02);
	tft_WriteCmd(0xD7); // OTP Load Control
	tft_WriteData(0x68);
	tft_WriteCmd(0xD1); // Auto Power Control
	tft_WriteData(0x01);
	tft_WriteCmd(0xC0); // Gate Voltage Setting VGH=12V ; VGL=-5V
	tft_WriteData(0x80);
	tft_WriteCmd(0xC1);   // VSH Setting
	tft_WriteData(0x28); //
	tft_WriteData(0x28);
	tft_WriteData(0x28);
	tft_WriteData(0x28);
	tft_WriteData(0x14);
	tft_WriteData(0x00);
	tft_WriteCmd(0xC2); // VSL Setting VSL=0
	tft_WriteData(0x00);
	tft_WriteData(0x00);
	tft_WriteData(0x00);
	tft_WriteData(0x00);
	tft_WriteCmd(0xCB);   // VCOMH Setting
	tft_WriteData(0x14); // 14  0C   7
	tft_WriteCmd(0xB4);   // Gate EQ Setting HPM EQ LPM EQ
	tft_WriteData(0xE5);
	tft_WriteData(0x77);
	tft_WriteData(0xF1);
	tft_WriteData(0xFF);
	tft_WriteData(0xFF);
	tft_WriteData(0x4F);
	tft_WriteData(0xF1);
	tft_WriteData(0xFF);
	tft_WriteData(0xFF);
	tft_WriteData(0x4F);
	tft_WriteCmd(0x11); // Sleep out
	HAL_Delay(100);    // HAL_Delay 100ms
	tft_WriteCmd(0xC7); // OSC Setting
	tft_WriteData(0xA6);
	tft_WriteData(0xE9);
	tft_WriteCmd(0xB0);   // Duty Setting
	tft_WriteData(0x64); // 250duty/4=63

	tft_WriteCmd(0x36); // Memory Data Access Control
	if (USE_HORIZONTAL == 0)
		tft_WriteData(0x00);
	else if (USE_HORIZONTAL == 1)
		tft_WriteData(0x4C);

	tft_WriteCmd(0x3A); // Data Format Select 4 write for 24 bit
	tft_WriteData(0x11);
	tft_WriteCmd(0xB9); // Source Setting
	tft_WriteData(0x23);
	tft_WriteCmd(0xB8); // Panel Setting Frame inversion
	tft_WriteData(0x09);
	tft_WriteCmd(0x2A); ////Column Address Setting S61~S182
	tft_WriteData(0x05);
	tft_WriteData(0x36);
	tft_WriteCmd(0x2B); ////Row Address Setting G1~G250
	tft_WriteData(0x00);
	tft_WriteData(0xC7);
	tft_WriteCmd(0xD0);
	tft_WriteData(0x1F);
	tft_WriteCmd(0x29); // Display on
	tft_WriteCmd(0xB9); // enable CLR RAM
	tft_WriteData(0xE3);
	HAL_Delay(100);
	tft_WriteCmd(0xB9); // enable CLR RAM
	tft_WriteData(0x23);
	tft_WriteCmd(0x72);
	tft_WriteData(0x00); // Destress OFF
	tft_WriteCmd(0x39);   // LPM
	tft_WriteCmd(0x2A);   // Column Address Setting
	tft_WriteData(0x19);
	tft_WriteData(0x23); // 35
	tft_WriteCmd(0x2B);   // Row Address Setting
	tft_WriteData(0);
	tft_WriteData(0x7C);
	tft_WriteData(0x2C); // write image data
	HAL_Delay(120);
}

void vfd_ClearDcram(void)
{
	VFD_CS_RESET;
	spi_LfSendByte(0x90);
	spi_LfSendByte(0x00);
	for (uint8_t i = 0; i < 16; i++)
	{
		spi_LfSendByte(0xFF);
	}
	VFD_CS_SET;
	HAL_Delay(1);

	VFD_CS_RESET;
	spi_LfSendByte(0x10);
	spi_LfSendByte(0x00);
	for (uint8_t i = 0; i < 16; i++)
	{
		spi_LfSendByte(0xFF);
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
		spi_LfSendByte(0x10);
	}
	else if (row == 1) // high row
	{
		spi_LfSendByte(0x90);
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
	spi_LfSendByte(15 - col);
	spi_LfSendByte(data);
	VFD_CS_SET;
	HAL_Delay(1);
}

void vfd_DisplayString(const unsigned char row, const unsigned char col,
		const unsigned char *data, const uint8_t size)
{
	VFD_CS_RESET;
	if (row == 0) // low row
		spi_LfSendByte(0x10);
	else if (row == 1) // high row
		spi_LfSendByte(0x90);
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
	spi_LfSendByte(col);
	for (uint8_t i = 0; i < size; i++)
		spi_LfSendByte(data[size - i - 1]);
	VFD_CS_SET;
	HAL_Delay(1);
}

void tft_Fill(uint8_t data)
{
	uint16_t k = 0;
	for (uint8_t i = 0; i < 33; i++)
	{
		for (uint8_t j = 0; j < 125; j++)
		{
			k = j + i * 125;
			TFT_GRAM[k] = data;
		}
	}
	tft_Refresh();
}

void tft_Refresh()
{
	uint16_t k1 = 0;
	if (USE_HORIZONTAL == 0)
	{
		tft_WriteCmd(0x2A);
		tft_WriteData(0x19);
		tft_WriteData(0x23);
		tft_WriteCmd(0x2B);
		tft_WriteData(0x00);
		tft_WriteData(0x7C);
		tft_WriteCmd(0x2C);
	}
	else if (USE_HORIZONTAL == 1)
	{
		tft_WriteCmd(0x2A);
		tft_WriteData(0x19);
		tft_WriteData(0x23);
		tft_WriteCmd(0x2B);
		tft_WriteData(0x4B);
		tft_WriteData(0xC7);
		tft_WriteCmd(0x2C);
	}
	for (uint8_t i = 0; i < 33; i++)
	{
		for (uint8_t j = 0; j < 125; j++)
		{
			tft_WriteData(TFT_GRAM[k1]);
			k1++;
		}
	}
}

uint32_t tft_pow(uint8_t m, uint8_t n)
{
	uint32_t result = 1;
	while (n--)
		result *= m;
	return result;
}

void tft_DrawPoint(uint16_t x, uint16_t y, uint8_t mode)
{
	uint16_t x1, y1, n, y2;
	x1 = x / 2;
	y1 = y / 4;

	y2 = y - y1 * 4;
	n = tft_pow(4, (3 - y2));
	if (x - x1 * 2 == 0)
		n *= 2;
	if (mode == 0)
	{
		TFT_GRAM[x1 * 0x21 + y1] |= n;
	}
	else
	{
		TFT_GRAM[x1 * 0x21 + y1] |= n;
		TFT_GRAM[x1 * 0x21 + y1] = ~TFT_GRAM[x1 * 0x21 + y1];
		TFT_GRAM[x1 * 0x21 + y1] |= n;
		TFT_GRAM[x1 * 0x21 + y1] = ~TFT_GRAM[x1 * 0x21 + y1];
	}
}

void tft_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r)
{
	int a, b;
	int di;
	a = 0;
	b = r;
	di = 3 - (r << 1); /* 判断下个点位置的标志 */

	while (a <= b)
	{
		tft_DrawPoint(x0 + a, y0 - b, 0); /* 5 */
		tft_DrawPoint(x0 + b, y0 - a, 0); /* 0 */
		tft_DrawPoint(x0 + b, y0 + a, 0); /* 4 */
		tft_DrawPoint(x0 + a, y0 + b, 0); /* 6 */
		tft_DrawPoint(x0 - a, y0 + b, 0); /* 1 */
		tft_DrawPoint(x0 - b, y0 + a, 0);
		tft_DrawPoint(x0 - a, y0 - b, 0); /* 2 */
		tft_DrawPoint(x0 - b, y0 - a, 0); /* 7 */
		a++;
		// Bresenham
		if (di < 0)
		{
			di += 4 * a + 6;
		}
		else
		{
			di += 10 + 4 * (a - b);
			b--;
		}
	}
}
