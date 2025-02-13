#include "sw_spi.h"

// FONTS
/*
 const uint8_t fonts[4][32] =
 {
 { 0x00, 0x00, 0xFE, 0x3F, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00,
 0x80, 0x00, 0x80, 0x00, 0xFC, 0x1F, 0x80, 0x00, 0x80,
 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00,
 0xFF, 0x7F, 0x00, 0x00 }, //"王",0
 { 0x40, 0x10, 0x84, 0x08, 0x08, 0x00, 0xE8, 0x3F, 0x00, 0x01,
 0xC0, 0x1F, 0x4F, 0x10, 0xC8, 0x1F, 0x48, 0x10, 0xC8,
 0x1F, 0x48, 0x10, 0xC8, 0x1F, 0x48, 0x10, 0x14, 0x00,
 0xE2, 0x7F, 0x00, 0x00 }, //"道",1
 { 0x10, 0x00, 0x10, 0x00, 0xC8, 0x7F, 0x04, 0x04, 0x12, 0x04,
 0x10, 0x04, 0x88, 0x04, 0x8C, 0x04, 0x8A, 0x3C, 0x89,
 0x04, 0x88, 0x04, 0x88, 0x04, 0x88, 0x04, 0x88, 0x04,
 0xE8, 0x7F, 0x08, 0x00 }, //"征",2
 { 0x00, 0x02, 0x04, 0x05, 0x88, 0x08, 0x48, 0x10, 0xA0, 0x6F,
 0x00, 0x02, 0x0F, 0x02, 0xE8, 0x3F, 0x08, 0x02, 0x48,
 0x12, 0x48, 0x22, 0x28, 0x22, 0x88, 0x02, 0x14, 0x01,
 0xE2, 0x7F, 0x00, 0x00 }, //"途",3
 };
 */
// SPI send
// HSB first
#ifdef SPI_HSB
void spi_HfSendByte(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		SPI_HSB_SCL_RESET;
		if (byte & 0b10000000)
			SPI_HSB_SDA_SET;
		else
			SPI_HSB_SDA_RESET;
		byte = byte << 1;
		SPI_HSB_SCL_SET;
	}
}
#endif
// LSB first
#ifdef SPI_LSB
void spi_LfSendByte(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		SPI_LSB_SCL_RESET;
		if (byte & 0x00000001)
			SPI_LSB_SDA_SET;
		else
			SPI_LSB_SDA_RESET;
		byte = byte >> 1;
		SPI_LSB_SCL_SET;
	}
}
#endif
// ST7302
#ifdef ST7302_ENABLE
// Graphic RAM
uint8_t ST7302_GRAM[4125];
// st7302 send data
void st7302_WriteData(uint8_t byte)
{
	ST7302_DC_SET; //  DC high
	ST7302_CS_RESET;
	spi_HfSendByte(byte);
	ST7302_CS_SET;
}
// st7302 send command
void st7302_WriteCmd(uint8_t byte)
{
	ST7302_DC_RESET; //  DC low
	ST7302_CS_RESET;
	spi_HfSendByte(byte);
	ST7302_CS_SET;
}

void st7302_Init(void)
{
	ST7302_RES_RESET; // reset
	HAL_Delay(100);
	ST7302_RES_SET;
	HAL_Delay(100);

	HAL_Delay(100);

	HAL_Delay(300); // HAL_Delay 300ms

	st7302_WriteCmd(0x38);
	st7302_WriteCmd(0xEB); // Enable OTP
	st7302_WriteData(0x02);
	st7302_WriteCmd(0xD7); // OTP Load Control
	st7302_WriteData(0x68);
	st7302_WriteCmd(0xD1); // Auto Power Control
	st7302_WriteData(0x01);
	st7302_WriteCmd(0xC0); // Gate Voltage Setting VGH=12V ; VGL=-5V
	st7302_WriteData(0x80);
	st7302_WriteCmd(0xC1);   // VSH Setting
	st7302_WriteData(0x28); //
	st7302_WriteData(0x28);
	st7302_WriteData(0x28);
	st7302_WriteData(0x28);
	st7302_WriteData(0x14);
	st7302_WriteData(0x00);
	st7302_WriteCmd(0xC2); // VSL Setting VSL=0
	st7302_WriteData(0x00);
	st7302_WriteData(0x00);
	st7302_WriteData(0x00);
	st7302_WriteData(0x00);
	st7302_WriteCmd(0xCB);   // VCOMH Setting
	st7302_WriteData(0x14); // 14  0C   7
	st7302_WriteCmd(0xB4);   // Gate EQ Setting HPM EQ LPM EQ
	st7302_WriteData(0xE5);
	st7302_WriteData(0x77);
	st7302_WriteData(0xF1);
	st7302_WriteData(0xFF);
	st7302_WriteData(0xFF);
	st7302_WriteData(0x4F);
	st7302_WriteData(0xF1);
	st7302_WriteData(0xFF);
	st7302_WriteData(0xFF);
	st7302_WriteData(0x4F);
	st7302_WriteCmd(0x11); // Sleep out
	HAL_Delay(100);    // HAL_Delay 100ms
	st7302_WriteCmd(0xC7); // OSC Setting
	st7302_WriteData(0xA6);
	st7302_WriteData(0xE9);
	st7302_WriteCmd(0xB0);   // Duty Setting
	st7302_WriteData(0x64); // 250duty/4=63

	st7302_WriteCmd(0x36); // Memory Data Access Control
	if (ST7302_USE_HORIZONTAL == 0)
		st7302_WriteData(0x00);
	else if (ST7302_USE_HORIZONTAL == 1)
		st7302_WriteData(0x4C);

	st7302_WriteCmd(0x3A); // Data Format Select 4 write for 24 bit
	st7302_WriteData(0x11);
	st7302_WriteCmd(0xB9); // Source Setting
	st7302_WriteData(0x23);
	st7302_WriteCmd(0xB8); // Panel Setting Frame inversion
	st7302_WriteData(0x09);
	st7302_WriteCmd(0x2A); ////Column Address Setting S61~S182
	st7302_WriteData(0x05);
	st7302_WriteData(0x36);
	st7302_WriteCmd(0x2B); ////Row Address Setting G1~G250
	st7302_WriteData(0x00);
	st7302_WriteData(0xC7);
	st7302_WriteCmd(0xD0);
	st7302_WriteData(0x1F);
	st7302_WriteCmd(0x29); // Display on
	st7302_WriteCmd(0xB9); // enable CLR RAM
	st7302_WriteData(0xE3);
	HAL_Delay(100);
	st7302_WriteCmd(0xB9); // enable CLR RAM
	st7302_WriteData(0x23);
	st7302_WriteCmd(0x72);
	st7302_WriteData(0x00); // Destress OFF
	st7302_WriteCmd(0x39);   // LPM
	st7302_WriteCmd(0x2A);   // Column Address Setting
	st7302_WriteData(0x19);
	st7302_WriteData(0x23); // 35
	st7302_WriteCmd(0x2B);   // Row Address Setting
	st7302_WriteData(0);
	st7302_WriteData(0x7C);
	st7302_WriteData(0x2C); // write image data
	HAL_Delay(120);
}

void st7302_Fill(uint8_t data)
{
	uint16_t k = 0;
	for (uint8_t i = 0; i < 33; i++)
	{
		for (uint8_t j = 0; j < 125; j++)
		{
			k = j + i * 125;
			ST7302_GRAM[k] = data;
		}
	}
	st7302_Refresh();
}

void st7302_Refresh()
{
	uint16_t k1 = 0;
	if (ST7302_USE_HORIZONTAL == 0)
	{
		st7302_WriteCmd(0x2A);
		st7302_WriteData(0x19);
		st7302_WriteData(0x23);
		st7302_WriteCmd(0x2B);
		st7302_WriteData(0x00);
		st7302_WriteData(0x7C);
		st7302_WriteCmd(0x2C);
	}
	else if (ST7302_USE_HORIZONTAL == 1)
	{
		st7302_WriteCmd(0x2A);
		st7302_WriteData(0x19);
		st7302_WriteData(0x23);
		st7302_WriteCmd(0x2B);
		st7302_WriteData(0x4B);
		st7302_WriteData(0xC7);
		st7302_WriteCmd(0x2C);
	}
	for (uint8_t i = 0; i < 33; i++)
	{
		for (uint8_t j = 0; j < 125; j++)
		{
			st7302_WriteData(ST7302_GRAM[k1]);
			k1++;
		}
	}
}

uint32_t st7302_pow(uint8_t m, uint8_t n)
{
	uint32_t result = 1;
	while (n--)
		result *= m;
	return result;
}

void st7302_DrawPoint(uint16_t x, uint16_t y, uint8_t mode)
{
	uint16_t x1, y1, n, y2;
	x1 = x / 2;
	y1 = y / 4;

	y2 = y - y1 * 4;
	n = st7302_pow(4, (3 - y2));
	if (x - x1 * 2 == 0)
		n *= 2;
	if (mode == 0)
	{
		ST7302_GRAM[x1 * 0x21 + y1] |= n;
	}
	else
	{
		ST7302_GRAM[x1 * 0x21 + y1] |= n;
		ST7302_GRAM[x1 * 0x21 + y1] = ~ST7302_GRAM[x1 * 0x21 + y1];
		ST7302_GRAM[x1 * 0x21 + y1] |= n;
		ST7302_GRAM[x1 * 0x21 + y1] = ~ST7302_GRAM[x1 * 0x21 + y1];
	}
}

void st7302_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r)
{
	int32_t a, b;
	int32_t di;
	a = 0;
	b = r;
	di = 3 - (r << 1); /* 判断下个点位置的标志 */

	while (a <= b)
	{
		st7302_DrawPoint(x0 + a, y0 - b, 0); /* 5 */
		st7302_DrawPoint(x0 + b, y0 - a, 0); /* 0 */
		st7302_DrawPoint(x0 + b, y0 + a, 0); /* 4 */
		st7302_DrawPoint(x0 + a, y0 + b, 0); /* 6 */
		st7302_DrawPoint(x0 - a, y0 + b, 0); /* 1 */
		st7302_DrawPoint(x0 - b, y0 + a, 0);
		st7302_DrawPoint(x0 - a, y0 - b, 0); /* 2 */
		st7302_DrawPoint(x0 - b, y0 - a, 0); /* 7 */
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

void st7302_GramSet(uint16_t address, uint8_t data)
{
	if (address > 4125)
		return;
	ST7302_GRAM[address] = data;
}
#endif

#ifdef VFD_ENABLE
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
#endif

// GC9A01
#ifdef GC9A01_ENABLE
// ga9a01 send data
void gc9a01_WriteData8(uint8_t byte)
{
	GC9A01_DC_SET; //  DC high
	GC9A01_CS_RESET;
	spi_HfSendByte(byte);
	GC9A01_CS_SET;
}
void gc9a01_WriteData16(uint16_t byte)
{
	GC9A01_DC_SET; //  DC high
	GC9A01_CS_RESET;
	spi_HfSendByte(byte >> 8);
	GC9A01_CS_SET;
	GC9A01_CS_RESET;
	spi_HfSendByte(byte);
	GC9A01_CS_SET;
}

// ga9a01 send command
void gc9a01_WriteCmd(uint8_t byte)
{
	GC9A01_DC_RESET; //  DC low
	GC9A01_CS_RESET;
	spi_HfSendByte(byte);
	GC9A01_CS_SET;
}

void gc9a01_Init()
{
	GC9A01_RES_RESET; // 复位
	HAL_Delay(100);
	GC9A01_RES_SET;
	HAL_Delay(100);

	GC9A01_BL_SET; // 打开背光
	HAL_Delay(100);

	gc9a01_WriteCmd(0xEF);
	gc9a01_WriteCmd(0xEB);
	gc9a01_WriteData8(0x14);

	gc9a01_WriteCmd(0xFE);
	gc9a01_WriteCmd(0xEF);

	gc9a01_WriteCmd(0xEB);
	gc9a01_WriteData8(0x14);

	gc9a01_WriteCmd(0x84);
	gc9a01_WriteData8(0x40);

	gc9a01_WriteCmd(0x85);
	gc9a01_WriteData8(0xFF);

	gc9a01_WriteCmd(0x86);
	gc9a01_WriteData8(0xFF);

	gc9a01_WriteCmd(0x87);
	gc9a01_WriteData8(0xFF);

	gc9a01_WriteCmd(0x88);
	gc9a01_WriteData8(0x0A);

	gc9a01_WriteCmd(0x89);
	gc9a01_WriteData8(0x21);

	gc9a01_WriteCmd(0x8A);
	gc9a01_WriteData8(0x00);

	gc9a01_WriteCmd(0x8B);
	gc9a01_WriteData8(0x80);

	gc9a01_WriteCmd(0x8C);
	gc9a01_WriteData8(0x01);

	gc9a01_WriteCmd(0x8D);
	gc9a01_WriteData8(0x01);

	gc9a01_WriteCmd(0x8E);
	gc9a01_WriteData8(0xFF);

	gc9a01_WriteCmd(0x8F);
	gc9a01_WriteData8(0xFF);

	gc9a01_WriteCmd(0xB6);
	gc9a01_WriteData8(0x00);
	gc9a01_WriteData8(0x20);

	gc9a01_WriteCmd(0x36);
	if (GC9A01_USE_HORIZONTAL == 0)
		gc9a01_WriteData8(0x08);
	else if (GC9A01_USE_HORIZONTAL == 1)
		gc9a01_WriteData8(0xC8);
	else if (GC9A01_USE_HORIZONTAL == 2)
		gc9a01_WriteData8(0x68);
	else
		gc9a01_WriteData8(0xA8);

	gc9a01_WriteCmd(0x3A);
	gc9a01_WriteData8(0x05);

	gc9a01_WriteCmd(0x90);
	gc9a01_WriteData8(0x08);
	gc9a01_WriteData8(0x08);
	gc9a01_WriteData8(0x08);
	gc9a01_WriteData8(0x08);

	gc9a01_WriteCmd(0xBD);
	gc9a01_WriteData8(0x06);

	gc9a01_WriteCmd(0xBC);
	gc9a01_WriteData8(0x00);

	gc9a01_WriteCmd(0xFF);
	gc9a01_WriteData8(0x60);
	gc9a01_WriteData8(0x01);
	gc9a01_WriteData8(0x04);

	gc9a01_WriteCmd(0xC3);
	gc9a01_WriteData8(0x13);
	gc9a01_WriteCmd(0xC4);
	gc9a01_WriteData8(0x13);

	gc9a01_WriteCmd(0xC9);
	gc9a01_WriteData8(0x22);

	gc9a01_WriteCmd(0xBE);
	gc9a01_WriteData8(0x11);

	gc9a01_WriteCmd(0xE1);
	gc9a01_WriteData8(0x10);
	gc9a01_WriteData8(0x0E);

	gc9a01_WriteCmd(0xDF);
	gc9a01_WriteData8(0x21);
	gc9a01_WriteData8(0x0c);
	gc9a01_WriteData8(0x02);

	gc9a01_WriteCmd(0xF0);
	gc9a01_WriteData8(0x45);
	gc9a01_WriteData8(0x09);
	gc9a01_WriteData8(0x08);
	gc9a01_WriteData8(0x08);
	gc9a01_WriteData8(0x26);
	gc9a01_WriteData8(0x2A);

	gc9a01_WriteCmd(0xF1);
	gc9a01_WriteData8(0x43);
	gc9a01_WriteData8(0x70);
	gc9a01_WriteData8(0x72);
	gc9a01_WriteData8(0x36);
	gc9a01_WriteData8(0x37);
	gc9a01_WriteData8(0x6F);

	gc9a01_WriteCmd(0xF2);
	gc9a01_WriteData8(0x45);
	gc9a01_WriteData8(0x09);
	gc9a01_WriteData8(0x08);
	gc9a01_WriteData8(0x08);
	gc9a01_WriteData8(0x26);
	gc9a01_WriteData8(0x2A);

	gc9a01_WriteCmd(0xF3);
	gc9a01_WriteData8(0x43);
	gc9a01_WriteData8(0x70);
	gc9a01_WriteData8(0x72);
	gc9a01_WriteData8(0x36);
	gc9a01_WriteData8(0x37);
	gc9a01_WriteData8(0x6F);

	gc9a01_WriteCmd(0xED);
	gc9a01_WriteData8(0x1B);
	gc9a01_WriteData8(0x0B);

	gc9a01_WriteCmd(0xAE);
	gc9a01_WriteData8(0x77);

	gc9a01_WriteCmd(0xCD);
	gc9a01_WriteData8(0x63);

	gc9a01_WriteCmd(0x70);
	gc9a01_WriteData8(0x07);
	gc9a01_WriteData8(0x07);
	gc9a01_WriteData8(0x04);
	gc9a01_WriteData8(0x0E);
	gc9a01_WriteData8(0x0F);
	gc9a01_WriteData8(0x09);
	gc9a01_WriteData8(0x07);
	gc9a01_WriteData8(0x08);
	gc9a01_WriteData8(0x03);

	gc9a01_WriteCmd(0xE8);
	gc9a01_WriteData8(0x34);

	gc9a01_WriteCmd(0x62);
	gc9a01_WriteData8(0x18);
	gc9a01_WriteData8(0x0D);
	gc9a01_WriteData8(0x71);
	gc9a01_WriteData8(0xED);
	gc9a01_WriteData8(0x70);
	gc9a01_WriteData8(0x70);
	gc9a01_WriteData8(0x18);
	gc9a01_WriteData8(0x0F);
	gc9a01_WriteData8(0x71);
	gc9a01_WriteData8(0xEF);
	gc9a01_WriteData8(0x70);
	gc9a01_WriteData8(0x70);

	gc9a01_WriteCmd(0x63);
	gc9a01_WriteData8(0x18);
	gc9a01_WriteData8(0x11);
	gc9a01_WriteData8(0x71);
	gc9a01_WriteData8(0xF1);
	gc9a01_WriteData8(0x70);
	gc9a01_WriteData8(0x70);
	gc9a01_WriteData8(0x18);
	gc9a01_WriteData8(0x13);
	gc9a01_WriteData8(0x71);
	gc9a01_WriteData8(0xF3);
	gc9a01_WriteData8(0x70);
	gc9a01_WriteData8(0x70);

	gc9a01_WriteCmd(0x64);
	gc9a01_WriteData8(0x28);
	gc9a01_WriteData8(0x29);
	gc9a01_WriteData8(0xF1);
	gc9a01_WriteData8(0x01);
	gc9a01_WriteData8(0xF1);
	gc9a01_WriteData8(0x00);
	gc9a01_WriteData8(0x07);

	gc9a01_WriteCmd(0x66);
	gc9a01_WriteData8(0x3C);
	gc9a01_WriteData8(0x00);
	gc9a01_WriteData8(0xCD);
	gc9a01_WriteData8(0x67);
	gc9a01_WriteData8(0x45);
	gc9a01_WriteData8(0x45);
	gc9a01_WriteData8(0x10);
	gc9a01_WriteData8(0x00);
	gc9a01_WriteData8(0x00);
	gc9a01_WriteData8(0x00);

	gc9a01_WriteCmd(0x67);
	gc9a01_WriteData8(0x00);
	gc9a01_WriteData8(0x3C);
	gc9a01_WriteData8(0x00);
	gc9a01_WriteData8(0x00);
	gc9a01_WriteData8(0x00);
	gc9a01_WriteData8(0x01);
	gc9a01_WriteData8(0x54);
	gc9a01_WriteData8(0x10);
	gc9a01_WriteData8(0x32);
	gc9a01_WriteData8(0x98);

	gc9a01_WriteCmd(0x74);
	gc9a01_WriteData8(0x10);
	gc9a01_WriteData8(0x85);
	gc9a01_WriteData8(0x80);
	gc9a01_WriteData8(0x00);
	gc9a01_WriteData8(0x00);
	gc9a01_WriteData8(0x4E);
	gc9a01_WriteData8(0x00);

	gc9a01_WriteCmd(0x98);
	gc9a01_WriteData8(0x3e);
	gc9a01_WriteData8(0x07);

	gc9a01_WriteCmd(0x35);
	gc9a01_WriteCmd(0x21);

	gc9a01_WriteCmd(0x11);
	HAL_Delay(120);
	gc9a01_WriteCmd(0x29);
	HAL_Delay(20);
}
void gc9a01_AddressSet(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	gc9a01_WriteCmd(0x2a); // 列地址设置
	gc9a01_WriteData16(x1);
	gc9a01_WriteData16(x2);
	gc9a01_WriteCmd(0x2b); // 行地址设置
	gc9a01_WriteData16(y1);
	gc9a01_WriteData16(y2);
	gc9a01_WriteCmd(0x2c); // 储存器写
}
void gc9a01_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend,
		uint16_t color)
{
	uint16_t i, j;
	gc9a01_AddressSet(xsta, ysta, xend - 1, yend - 1); // 设置显示范围
	for (i = ysta; i < yend; i++)
		for (j = xsta; j < xend; j++)
			gc9a01_WriteData16(color);
}
void gc9a01_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
	gc9a01_AddressSet(x, y, x, y); // 设置光标位置
	gc9a01_WriteData16(color);
}
void gc9a01_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color)
{
	int32_t a, b;
	a = 0;
	b = r;
	while (a <= b)
	{
		gc9a01_DrawPoint(x0 - b, y0 - a, color); // 3
		gc9a01_DrawPoint(x0 + b, y0 - a, color); // 0
		gc9a01_DrawPoint(x0 - a, y0 + b, color); // 1
		gc9a01_DrawPoint(x0 - a, y0 - b, color); // 2
		gc9a01_DrawPoint(x0 + b, y0 + a, color); // 4
		gc9a01_DrawPoint(x0 + a, y0 - b, color); // 5
		gc9a01_DrawPoint(x0 + a, y0 + b, color); // 6
		gc9a01_DrawPoint(x0 - b, y0 + a, color); // 7
		a++;
		if ((a * a + b * b) > (r * r)) // 判断要画的点是否过远
		{
			b--;
		}
	}
}
void gc9a01_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
		uint16_t color)
{
	uint16_t t;
	int32_t xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int32_t incx, incy, uRow, uCol;
	delta_x = x2 - x1; // 计算坐标增量
	delta_y = y2 - y1;
	uRow = x1; // 画线起点坐标
	uCol = y1;
	if (delta_x > 0)
		incx = 1; // 设置单步方向
	else if (delta_x == 0)
		incx = 0; // 垂直线
	else
	{
		incx = -1;
		delta_x = -delta_x;
	}
	if (delta_y > 0)
		incy = 1;
	else if (delta_y == 0)
		incy = 0; // 水平线
	else
	{
		incy = -1;
		delta_y = -delta_y;
	}
	if (delta_x > delta_y)
		distance = delta_x; // 选取基本增量坐标轴
	else
		distance = delta_y;
	for (t = 0; t < distance + 1; t++)
	{
		gc9a01_DrawPoint(uRow, uCol, color); // 画点
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance)
		{
			xerr -= distance;
			uRow += incx;
		}
		if (yerr > distance)
		{
			yerr -= distance;
			uCol += incy;
		}
	}
}
#endif
// NV3023B
#ifdef NV3023B_ENABLE

void nv3023b_WriteData(uint8_t byte)
{
	NV3023B_DC_SET; //  DC high
	NV3023B_CS_RESET;
	spi_HfSendByte(byte);
	NV3023B_CS_SET;
}
void nv3023b_WriteData2(uint16_t dat)
{
	NV3023B_DC_SET;
	spi_HfSendByte(dat >> 8);
	spi_HfSendByte(dat & 0xFF);
	NV3023B_DC_SET;
}
void nv3023b_WriteCmd(uint8_t byte)
{
	NV3023B_DC_RESET; //  DC low
	NV3023B_CS_RESET;
	spi_HfSendByte(byte);
	NV3023B_CS_SET;
}
void nv3023b_AddressSet(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
	nv3023b_WriteCmd(0x2a); // 列地址设置
	nv3023b_WriteData2(xs);
	nv3023b_WriteData2(xe);
	nv3023b_WriteCmd(0x2b); // 行地址设置
	nv3023b_WriteData2(ys);
	nv3023b_WriteData2(ye);
	nv3023b_WriteCmd(0x2c); // 储存器写
}
void nv3023b_Fill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye,
		uint16_t color)
{
	uint16_t i, j;
	nv3023b_AddressSet(xs, ys, xe - 1, ye - 1);
	for (j = ys; j < ye; j++)
	{
		for (i = xs; i < xe; i++)
		{
			nv3023b_WriteData2(color);
		}
	}
}
void nv3023b_Init(void)
{
	NV3023B_RES_SET;
	HAL_Delay(20);
	NV3023B_RES_RESET;
	HAL_Delay(200);
	NV3023B_RES_SET;
	HAL_Delay(120);
	NV3023B_BL_SET;
	//----------------Star Initial Sequence-------//
	nv3023b_WriteCmd(0xff);
	nv3023b_WriteData(0xa5); //
	nv3023b_WriteCmd(0x3E);
	nv3023b_WriteData(0x08); //
	nv3023b_WriteCmd(0x3A);
	nv3023b_WriteData(0x55);
	nv3023b_WriteCmd(0x82);
	nv3023b_WriteData(0x00);
	nv3023b_WriteCmd(0x98);
	nv3023b_WriteData(0x00);
	nv3023b_WriteCmd(0x63);
	nv3023b_WriteData(0x10);
	nv3023b_WriteCmd(0x64);
	nv3023b_WriteData(0x10);
	nv3023b_WriteCmd(0xB4);
	nv3023b_WriteData(0x34); // 34 55
	nv3023b_WriteCmd(0xB5);
	nv3023b_WriteData(0x30);
	nv3023b_WriteCmd(0x83);
	nv3023b_WriteData(0x03);
	nv3023b_WriteCmd(0x86); //
	nv3023b_WriteData(0x00);
	nv3023b_WriteCmd(0x87);
	nv3023b_WriteData(0x16);
	nv3023b_WriteCmd(0x88); // VCOM
	nv3023b_WriteData(0x09);
	nv3023b_WriteCmd(0x89); //
	nv3023b_WriteData(0x2f);
	nv3023b_WriteCmd(0x93); //
	nv3023b_WriteData(0x63);
	nv3023b_WriteCmd(0x96);
	nv3023b_WriteData(0x81);
	nv3023b_WriteCmd(0xC3);
	nv3023b_WriteData(0x01); //
	nv3023b_WriteCmd(0xE6);
	nv3023b_WriteData(0x00);
	nv3023b_WriteCmd(0x99);
	nv3023b_WriteData(0x01);
	////////////////////////gamma_set//////////////////////////////////////
	nv3023b_WriteCmd(0x70);
	nv3023b_WriteData(0x07); // VRP 0
	nv3023b_WriteCmd(0x71);
	nv3023b_WriteData(0x1b); // VRP 1
	nv3023b_WriteCmd(0x72);
	nv3023b_WriteData(0x08); // VRP 2
	nv3023b_WriteCmd(0x73);
	nv3023b_WriteData(0x0f); // VRP 3
	nv3023b_WriteCmd(0x74);
	nv3023b_WriteData(0x16); // VRP 6
	nv3023b_WriteCmd(0x75);
	nv3023b_WriteData(0x1A); // VRP 8
	nv3023b_WriteCmd(0x76);
	nv3023b_WriteData(0x3c); // VRP 10
	nv3023b_WriteCmd(0x77);
	nv3023b_WriteData(0x0a); // VRP 14
	nv3023b_WriteCmd(0x78);
	nv3023b_WriteData(0x05); // VRP 17
	nv3023b_WriteCmd(0x79);
	nv3023b_WriteData(0x3a); // VRP 21
	nv3023b_WriteCmd(0x7a);
	nv3023b_WriteData(0x06); // VRP 23
	nv3023b_WriteCmd(0x7b);
	nv3023b_WriteData(0x0b); // VRP 25
	nv3023b_WriteCmd(0x7c);
	nv3023b_WriteData(0x12); // VRP 28
	nv3023b_WriteCmd(0x7d);
	nv3023b_WriteData(0x0b); // VRP 29
	nv3023b_WriteCmd(0x7e);
	nv3023b_WriteData(0x0a); // VRP 30
	nv3023b_WriteCmd(0x7f);
	nv3023b_WriteData(0x08); // VRP 31
	nv3023b_WriteCmd(0xa0);
	nv3023b_WriteData(0x0b); // VRN 0
	nv3023b_WriteCmd(0xa1);
	nv3023b_WriteData(0x36); // VRN 1
	nv3023b_WriteCmd(0xa2);
	nv3023b_WriteData(0x0b); // VRN 2
	nv3023b_WriteCmd(0xa3);
	nv3023b_WriteData(0x0c); // VRN 3
	nv3023b_WriteCmd(0xa4);
	nv3023b_WriteData(0x08); // VRN 6
	nv3023b_WriteCmd(0xa5);
	nv3023b_WriteData(0x22); // VRN 8
	nv3023b_WriteCmd(0xa6);
	nv3023b_WriteData(0x43); // VRN 10
	nv3023b_WriteCmd(0xa7);
	nv3023b_WriteData(0x04); // VRN 14
	nv3023b_WriteCmd(0xa8);
	nv3023b_WriteData(0x05); // VRN 17
	nv3023b_WriteCmd(0xa9);
	nv3023b_WriteData(0x3F); // VRN 21
	nv3023b_WriteCmd(0xaa);
	nv3023b_WriteData(0x0A); // VRN 23
	nv3023b_WriteCmd(0xab);
	nv3023b_WriteData(0x11); // VRN 25
	nv3023b_WriteCmd(0xac);
	nv3023b_WriteData(0x0d); // VRN 28
	nv3023b_WriteCmd(0xad);
	nv3023b_WriteData(0x06); // VRN 29
	nv3023b_WriteCmd(0xae);
	nv3023b_WriteData(0x3b); // VRN 30
	nv3023b_WriteCmd(0xaf);
	nv3023b_WriteData(0x07); // VRN 31
	//////////////////////////////////////////////////////////////////
	nv3023b_WriteCmd(0xff);
	nv3023b_WriteData(0x00);
	nv3023b_WriteCmd(0x11);
	HAL_Delay(120);
	nv3023b_WriteCmd(0x36); // MX, MY, RGB mode
	if (NV3023B_USE_HORIZONTAL == 0)
		nv3023b_WriteData(0x48);
	else if (NV3023B_USE_HORIZONTAL == 1)
		nv3023b_WriteData(0x88);
	else if (NV3023B_USE_HORIZONTAL == 2)
		nv3023b_WriteData(0xF8);
	else
		nv3023b_WriteData(0x28);
	nv3023b_WriteCmd(0x35);
	nv3023b_WriteData(0x00);
	nv3023b_WriteCmd(0x29);
	HAL_Delay(100);
}

#endif

