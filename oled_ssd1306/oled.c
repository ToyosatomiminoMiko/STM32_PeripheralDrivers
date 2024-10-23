#include "oled.h"

uint8_t GRAM0[128];
uint8_t GRAM1[128];
uint8_t GRAM2[128];
uint8_t GRAM3[128];
uint8_t GRAM4[128];
uint8_t GRAM5[128];
uint8_t GRAM6[128];
uint8_t GRAM7[128];
uint8_t *GRAMz[8] =
{ GRAM0, GRAM1, GRAM2, GRAM3, GRAM4, GRAM5, GRAM6, GRAM7 };

uint8_t numbers_8x8[10][8] =
{
{ 0x00, 0x00, 0x3c, 0x42, 0x42, 0x3c, 0x00, 0x00 }, // 0
		{ 0x00, 0x00, 0x44, 0x42, 0x7e, 0x40, 0x00, 0x00 }, // 1
		{ 0x00, 0x00, 0x64, 0x52, 0x4a, 0x44, 0x00, 0x00 }, // 2
		{ 0x00, 0x00, 0x4a, 0x4a, 0x4a, 0x34, 0x00, 0x00 }, // 3
		{ 0x00, 0x00, 0x38, 0x24, 0x7e, 0x20, 0x00, 0x00 }, // 4
		{ 0x00, 0x00, 0x4e, 0x4a, 0x4a, 0x32, 0x00, 0x00 }, // 5
		{ 0x00, 0x00, 0x3c, 0x4a, 0x4a, 0x32, 0x00, 0x00 }, // 6
		{ 0x00, 0x00, 0x02, 0x62, 0x1a, 0x06, 0x00, 0x00 }, // 7
		{ 0x00, 0x00, 0x34, 0x4a, 0x4a, 0x34, 0x00, 0x00 }, // 8
		{ 0x00, 0x00, 0x4c, 0x52, 0x52, 0x3c, 0x00, 0x00 }, // 9
		};

uint8_t latin_8x8[28][8] =
{
{ 0x00, 0xf8, 0x24, 0x24, 0x24, 0xf8, 0x00, 0x00 }, // 00 A
		{ 0x00, 0xfc, 0x94, 0x94, 0x94, 0x78, 0x00, 0x00 }, // 01 B
		{ 0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x00, 0x00 }, // 02 C
		{ 0x00, 0xfc, 0x84, 0x84, 0x84, 0x78, 0x00, 0x00 }, // 03 D
		{ 0x00, 0xfc, 0x94, 0x94, 0x94, 0x84, 0x00, 0x00 }, // 04 E
		{ 0x00, 0xfc, 0x14, 0x14, 0x14, 0x04, 0x00, 0x00 }, // 05 F
		{ 0x00, 0x78, 0x84, 0x94, 0x94, 0xf4, 0x00, 0x00 }, // 06 G
		{ 0x00, 0xfc, 0x10, 0x10, 0x10, 0xfc, 0x00, 0x00 }, // 07 H
		{ 0x00, 0x84, 0x84, 0xfc, 0x84, 0x84, 0x00, 0x00 }, // 08 I
		{ 0x00, 0x44, 0x84, 0x84, 0x7c, 0x04, 0x00, 0x00 }, // 09 J
		{ 0x00, 0xfc, 0x10, 0x10, 0x28, 0xc4, 0x00, 0x00 }, // 10 K
		{ 0x00, 0xfc, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00 }, // 11 L
		{ 0x00, 0xfc, 0x18, 0x60, 0x18, 0xfc, 0x00, 0x00 }, // 12 M
		{ 0x00, 0xfc, 0x08, 0x30, 0x40, 0xfc, 0x00, 0x00 }, // 13 N
		{ 0x00, 0x78, 0x84, 0x84, 0x84, 0x78, 0x00, 0x00 }, // 14 O
		{ 0x00, 0xfc, 0x24, 0x24, 0x24, 0x18, 0x00, 0x00 }, // 15 P
		{ 0x00, 0x78, 0x84, 0xa4, 0x44, 0xb8, 0x00, 0x00 }, // 16 Q
		{ 0x00, 0xfc, 0x24, 0x64, 0xa4, 0x98, 0x00, 0x00 }, // 17 R
		{ 0x00, 0x48, 0x94, 0x94, 0x94, 0x64, 0x00, 0x00 }, // 18 S
		{ 0x00, 0x04, 0x04, 0xfc, 0x04, 0x04, 0x00, 0x00 }, // 19 T
		{ 0x00, 0x7c, 0x80, 0x80, 0x80, 0x7c, 0x00, 0x00 }, // 20 U
		{ 0x00, 0x1c, 0x60, 0x80, 0x60, 0x1c, 0x00, 0x00 }, // 21 V
		{ 0x00, 0xfc, 0x60, 0x18, 0x60, 0xfc, 0x00, 0x00 }, // 22 W
		{ 0x00, 0x84, 0x48, 0x30, 0x48, 0x84, 0x00, 0x00 }, // 23 X
		{ 0x00, 0x0c, 0x10, 0xe0, 0x10, 0x0c, 0x00, 0x00 }, // 24 Y
		{ 0x00, 0xc4, 0xa4, 0x94, 0x8c, 0x84, 0x00, 0x00 }, // 25 Z
		{ 0x00, 0xf8, 0x04, 0x94, 0x98, 0x60, 0x00, 0x00 }, // 26 ß
		{ 0x00, 0xfc, 0x0a, 0x31, 0x42, 0xfd, 0x00, 0x00 }, // 27 Ñ
		};

uint8_t cylil_8x8[][8] =
{
{ 0x00, 0xf8, 0x24, 0x24, 0x24, 0xf8, 0x00, 0x00 }, // 0 А
		{ 0x00, 0xfc, 0x94, 0x94, 0x94, 0x64, 0x00, 0x00 }, // 1 Б
		{ 0x00, 0xfc, 0x94, 0x94, 0x94, 0x78, 0x00, 0x00 }, // 2 В
		{ 0x00, 0x0c, 0xb0, 0xc0, 0x30, 0x1c, 0x00, 0x00 }, // 3 У
		{ 0x00, 0xfc, 0x40, 0x30, 0x08, 0xfc, 0x00, 0x00 }, // 4 И
		{ 0x00, 0xfc, 0x41, 0x32, 0x09, 0xfc, 0x00, 0x00 }, // 5 Й
		{ 0x00, 0xfc, 0x24, 0x24, 0x24, 0x18, 0x00, 0x00 }, // 6 Р
		{ 0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x00, 0x00 }, // 7 С
		{ 0x00, 0xfc, 0x10, 0x10, 0x28, 0xc4, 0x00, 0x00 }, // 8 К
		};

HAL_StatusTypeDef oled_Write_Command(uint8_t i2c_cmd)
{
	uint8_t *cmd = &i2c_cmd;
	return HAL_I2C_Mem_Write(&OLED_I2C, OLED_ADD, 0x00, I2C_MEMADD_SIZE_8BIT,
			cmd, 1, 0xFF);
}

HAL_StatusTypeDef oled_Write_Data(uint8_t i2c_cmd)
{
	uint8_t *cmd = &i2c_cmd;
	return HAL_I2C_Mem_Write(&OLED_I2C, OLED_ADD, 0x40, I2C_MEMADD_SIZE_8BIT,
			cmd, 1, 0xFF);
}

void oled_NewFrame()
{
	uint8_t m, n;
	const uint8_t zero = 0;
	for (m = 0; m < 8; m++)
	{
		for (n = 0; n < 128; n++)
		{
			GRAMz[m][n] = zero;
		}
	}
}

void oled_ShowFrame()
{
	uint8_t m, n;
	for (m = 0; m < 8; m++)
	{
		oled_Write_Command(0xb0 + m);
		oled_Write_Command(0x00);
		oled_Write_Command(0x10);
		for (n = 0; n < 128; n++)
		{
			oled_Write_Data(GRAMz[m][n]);
		}
	}
}

void oled_Clear()
{
	uint8_t m, n;
	for (m = 0; m < 8; m++)
	{
		oled_Write_Command(0xb0 + m); // set page address(0~7)
		oled_Write_Command(0x00); // set display column low address
		oled_Write_Command(0x10); // set display column low address
		for (n = 0; n < 128; n++)
			oled_Write_Data(0);
	} // update
}

void oled_Full()
{
	uint8_t m, n;
	for (m = 0; m < 8; m++)
	{
		oled_Write_Command(0xb0 + m); // set page address(0~7)
		oled_Write_Command(0x00); // set display column low address
		oled_Write_Command(0x10); // set display column high address
		for (n = 0; n < 128; n++)
			oled_Write_Data(0b11111111);
	} // update
}

void oled_Test()
{
	uint8_t m, n;
	for (m = 0; m < 8; m++)
	{
		oled_Write_Command(0xb0 + m); // set page address(0~7)
		oled_Write_Command(0x00); // set display column low address
		oled_Write_Command(0x10); // set display column high address
		for (n = 0; n < 128; n++)
			oled_Write_Data(0xAA);
	} // update
}

void oled_SoftRolling()
{
	uint8_t m, n;
	for (m = 0; m < 8; m++)
	{
		for (n = 0; n < 128; n++)
		{
			GRAMz[m][n] = GRAMz[m][n + 1];
		}
	}
}

void oled_SetPixel(uint8_t x, uint8_t y)
{
	if (x >= 128 || y >= 64)
		return;
	GRAMz[y / 8][x] |= 0b1 << (y % 8);
}

void oled_ShowImage(const uint8_t *image, uint8_t size_x, uint8_t size_y)
{
	uint16_t i = 0;
	for (uint8_t x = 0; x < size_x; x++)
	{
		for (uint8_t y = 0; y < (size_y / 8); y++)
		{
			GRAMz[y][x] = image[i];
			i++;
		}
	}
}

void oled_ProgressBar(uint8_t count)
{
	uint8_t length = count / 2;
	for (uint8_t n = 0; n < length; n++)
	{
		GRAMz[1][n] = 0b11111111;
	}
}

void oled_ShowNumber(uint8_t num, uint8_t position, uint8_t line)
{
	if (num < 0 || num >= 10 || position > 120 || position < 0 || line < 0
			|| line > 8)
		return;
	uint8_t n;
	for (n = position; n < (position + 8); n++)
	{
		GRAMz[line][n] = numbers_8x8[num][n - position];
	}
}

void oled_ShowLatin(uint8_t c, uint8_t position, uint8_t line)
{
	if (c < 0 || c > sizeof(latin_8x8) || position > 120 || position < 0
			|| line < 0 || line > 8)
		return;
	uint8_t n;
	for (n = position; n < (position + 8); n++)
	{
		GRAMz[line][n] = latin_8x8[c][n - position];
	}
}

void oled_ShowCylil(uint8_t c, uint8_t position, uint8_t line)
{
	if (c < 0 || c > sizeof(latin_8x8) || position > 120 || position < 0
			|| line < 0 || line > 8)
		return;
	uint8_t n;
	for (n = position; n < (position + 8); n++)
	{
		GRAMz[line][n] = cylil_8x8[c][n - position];
	}
}

void oled_ShowLatinS(uint8_t *chars, uint8_t size, uint8_t position,
		uint8_t line)
{
	if ((position + size) > 128)
		return;
	for (uint8_t n = position; n < (position + size); n += 1)
	{
		oled_ShowLatin(chars[n - position], n * 8, line);
	}
}

void oled_ShowCylilS(uint8_t *chars, uint8_t size, uint8_t position,
		uint8_t line)
{
	if ((position + size) > 128)
		return;
	for (uint8_t n = position; n < (position + size); n += 1)
	{
		oled_ShowCylil(chars[n - position], n * 8, line);
	}
}

void oled_ShowLatinTest()
{
	uint8_t n;
	for (n = 0; n < 14; n++)
	{
		oled_ShowLatin(n, n * 8, 3);
	}
	for (n = 14; n < 26; n++)
	{
		oled_ShowLatin(n, (n - 14) * 8, 4);
	}
}

void oled_ShowNumberTest()
{
	oled_ShowNumber(0, 0, 0);
	oled_ShowNumber(1, 8, 0);
	oled_ShowNumber(2, 16, 0);
	oled_ShowNumber(3, 24, 0);
	oled_ShowNumber(4, 32, 0);
	oled_ShowNumber(5, 40, 0);
	oled_ShowNumber(6, 48, 0);
	oled_ShowNumber(7, 56, 0);
	oled_ShowNumber(8, 64, 0);
	oled_ShowNumber(9, 72, 0);
}

void oled_Init()
{
	oled_Write_Command(0xAE); // display off
	oled_Write_Command(0x00); //---set low column address
	oled_Write_Command(0x10); //---set high column address
	oled_Write_Command(0x40); //--set start line address
	oled_Write_Command(0xB0); //--set page address
	oled_Write_Command(0x81); // contract control
	oled_Write_Command(0xFF); //--128
	oled_Write_Command(0xA1); //set segment remap
	oled_Write_Command(0xA6); // [invert]normal / reverse display
	oled_Write_Command(0xA8); //--set multiplex ratio(1 to 64)
	oled_Write_Command(0x3F); //--1/32 duty
	oled_Write_Command(0xC8); //Com scan direction
	oled_Write_Command(0xD3); //-set display offset
	oled_Write_Command(0x00); //

	oled_Write_Command(0xD5); //set osc division
	oled_Write_Command(0x80); //

	oled_Write_Command(0xD8); //set area color mode off
	oled_Write_Command(0x05); //

	oled_Write_Command(0xD9); //Set Pre-Charge Period
	oled_Write_Command(0xF1); //

	oled_Write_Command(0xDA); //set com pin configuartion
	oled_Write_Command(0x12); //

	oled_Write_Command(0xDB); //set Vcomh
	oled_Write_Command(0x30); //

	oled_Write_Command(0x8D); //set charge pump enable
	oled_Write_Command(0x14); //

	oled_Write_Command(0xAF); // display on
}
