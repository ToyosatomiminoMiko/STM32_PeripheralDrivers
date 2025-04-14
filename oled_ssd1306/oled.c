#include "iic_oled.h"

uint8_t GRAM[8][128];

const uint8_t bitmap[] =
    {};

const uint8_t numbers_3x5[10][3] =
    {
        {0b01111100, 0b01000100, 0b01111100},
        {0b01000100, 0b01111100, 0b01000000},
        {0b01110100, 0b01010100, 0b01011100},
        {0b01010100, 0b01010100, 0b01111100},
        {0b00011100, 0b00010000, 0b01111100},
        {0b01011100, 0b01010100, 0b01110100},
        {0b01111100, 0b01010100, 0b01110100},
        {0b00000100, 0b00000100, 0b01111100},
        {0b01111100, 0b01010100, 0b01111100},
        {0b01011100, 0b01010100, 0b01111100}};

const uint8_t latin_8x8[28][8] =
    {
        {0x00, 0xf8, 0x24, 0x24, 0x24, 0xf8, 0x00, 0x00}, // 00 A
        {0x00, 0xfc, 0x94, 0x94, 0x94, 0x78, 0x00, 0x00}, // 01 B
        {0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x00, 0x00}, // 02 C
        {0x00, 0xfc, 0x84, 0x84, 0x84, 0x78, 0x00, 0x00}, // 03 D
        {0x00, 0xfc, 0x94, 0x94, 0x94, 0x84, 0x00, 0x00}, // 04 E
        {0x00, 0xfc, 0x14, 0x14, 0x14, 0x04, 0x00, 0x00}, // 05 F
        {0x00, 0x78, 0x84, 0x94, 0x94, 0xf4, 0x00, 0x00}, // 06 G
        {0x00, 0xfc, 0x10, 0x10, 0x10, 0xfc, 0x00, 0x00}, // 07 H
        {0x00, 0x84, 0x84, 0xfc, 0x84, 0x84, 0x00, 0x00}, // 08 I
        {0x00, 0x44, 0x84, 0x84, 0x7c, 0x04, 0x00, 0x00}, // 09 J
        {0x00, 0xfc, 0x10, 0x10, 0x28, 0xc4, 0x00, 0x00}, // 10 K
        {0x00, 0xfc, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00}, // 11 L
        {0x00, 0xfc, 0x18, 0x60, 0x18, 0xfc, 0x00, 0x00}, // 12 M
        {0x00, 0xfc, 0x08, 0x30, 0x40, 0xfc, 0x00, 0x00}, // 13 N
        {0x00, 0x78, 0x84, 0x84, 0x84, 0x78, 0x00, 0x00}, // 14 O
        {0x00, 0xfc, 0x24, 0x24, 0x24, 0x18, 0x00, 0x00}, // 15 P
        {0x00, 0x78, 0x84, 0xa4, 0x44, 0xb8, 0x00, 0x00}, // 16 Q
        {0x00, 0xfc, 0x24, 0x64, 0xa4, 0x98, 0x00, 0x00}, // 17 R
        {0x00, 0x48, 0x94, 0x94, 0x94, 0x64, 0x00, 0x00}, // 18 S
        {0x00, 0x04, 0x04, 0xfc, 0x04, 0x04, 0x00, 0x00}, // 19 T
        {0x00, 0x7c, 0x80, 0x80, 0x80, 0x7c, 0x00, 0x00}, // 20 U
        {0x00, 0x1c, 0x60, 0x80, 0x60, 0x1c, 0x00, 0x00}, // 21 V
        {0x00, 0xfc, 0x60, 0x18, 0x60, 0xfc, 0x00, 0x00}, // 22 W
        {0x00, 0x84, 0x48, 0x30, 0x48, 0x84, 0x00, 0x00}, // 23 X
        {0x00, 0x0c, 0x10, 0xe0, 0x10, 0x0c, 0x00, 0x00}, // 24 Y
        {0x00, 0xc4, 0xa4, 0x94, 0x8c, 0x84, 0x00, 0x00}, // 25 Z
        {0x00, 0xf8, 0x04, 0x94, 0x98, 0x60, 0x00, 0x00}, // 26 ß
        {0x00, 0xfc, 0x0a, 0x31, 0x42, 0xfd, 0x00, 0x00}, // 27 Ñ
};

const uint8_t cylil_8x8[][8] =
    {
        {0x00, 0xf8, 0x24, 0x24, 0x24, 0xf8, 0x00, 0x00}, // 0 А
        {0x00, 0xfc, 0x94, 0x94, 0x94, 0x64, 0x00, 0x00}, // 1 Б
        {0x00, 0xfc, 0x94, 0x94, 0x94, 0x78, 0x00, 0x00}, // 2 В
        {0x00, 0x0c, 0xb0, 0xc0, 0x30, 0x1c, 0x00, 0x00}, // 3 У
        {0x00, 0xfc, 0x40, 0x30, 0x08, 0xfc, 0x00, 0x00}, // 4 И
        {0x00, 0xfc, 0x41, 0x32, 0x09, 0xfc, 0x00, 0x00}, // 5 Й
        {0x00, 0xfc, 0x24, 0x24, 0x24, 0x18, 0x00, 0x00}, // 6 Р
        {0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x00, 0x00}, // 7 С
        {0x00, 0xfc, 0x10, 0x10, 0x28, 0xc4, 0x00, 0x00}, // 8 К
};

HAL_StatusTypeDef oled_WriteCommand(uint8_t i2c_cmd)
{
    uint8_t *cmd = &i2c_cmd;
    return HAL_I2C_Mem_Write(&OLED_I2C, OLED_ADD, 0x00,
                             I2C_MEMADD_SIZE_8BIT, cmd, 1, 0xFF);
}

HAL_StatusTypeDef oled_WriteData(uint8_t i2c_cmd)
{
    uint8_t *cmd = &i2c_cmd;
    return HAL_I2C_Mem_Write(&OLED_I2C, OLED_ADD, 0x40,
                             I2C_MEMADD_SIZE_8BIT, cmd, 1, 0xFF);
}

void oled_NewFrame()
{
    const uint8_t zero = 0;
    for (uint8_t m = 0; m < 8; m++) {
        for (uint8_t n = 0; n < 128; n++) {
            GRAM[m][n] = zero;
        }
    }
}

// 循环滚动
void oled_SoftCirculation()
{
    uint8_t temp;
    for (uint8_t m = 0; m < 8; m++) {
        temp = GRAM[m][0];
        for (uint8_t n = 0; n < 127; n++) {
            GRAM[m][n] = GRAM[m][n + 1];
        }
        GRAM[m][127] = temp;
    }
}

// 不循环滚动
void oled_SoftRolling()
{
    for (uint8_t m = 0; m < 8; m++)
        for (uint8_t n = 0; n < 128; n++)
            GRAM[m][n] = GRAM[m][n + 1];
}

void oled_ShowFrame()
{
    for (uint8_t m = 0; m < 8; m++) {
        oled_WriteCommand(0xb0 + m);
        oled_WriteCommand(0x00);
        oled_WriteCommand(0x10);
        for (uint8_t n = 0; n < 128; n++)
            oled_WriteData(GRAM[m][n]);
    }
}

void oled_Clear()
{
    for (uint8_t m = 0; m < 8; m++) {
        oled_WriteCommand(0xb0 + m); // set page address(0~7)
        oled_WriteCommand(0x00);     // set display column low address
        oled_WriteCommand(0x10);     // set display column low address
        for (uint8_t n = 0; n < 128; n++)
            oled_WriteData(0);
    } // update
}

void oled_Full()
{
    for (uint8_t m = 0; m < 8; m++) {
        oled_WriteCommand(0xb0 + m); // set page address(0~7)
        oled_WriteCommand(0x00);     // set display column low address
        oled_WriteCommand(0x10);     // set display column high address
        for (uint8_t n = 0; n < 128; n++)
            oled_WriteData(0b11111111);
    } // update
}

void oled_Test()
{
    for (uint8_t m = 0; m < 8; m++) {
        oled_WriteCommand(0xb0 + m); // set page address(0~7)
        oled_WriteCommand(0x00);     // set display column low address
        oled_WriteCommand(0x10);     // set display column high address
        for (uint8_t n = 0; n < 128; n++)
            oled_WriteData(0xAA);
    } // update
}

void oled_SetFrist()
{
    for (uint8_t i = 0; i < 8; i++)
        GRAM[i][0] = 0x00;
}

void oled_SetPoint(uint8_t x, uint8_t y)
{
    if (x >= 128)
        x = 127;
    if (x < 0)
        x = 0;
    if (y >= 64)
        y = 63;
    if (y < 0)
        y = 0;
    GRAM[y / 8][x] |= 0b1 << (y % 8);
}

void oled_ShowImage(uint8_t *image)
{
    uint16_t i = 0;
    for (uint8_t y = 0; y < 8; y++)
        for (uint8_t x = 0; x < 128; x++) {
            GRAM[y][x] = image[i];
            i++;
        }
}

void oled_ShowChinese_16x16(uint8_t x0, uint8_t y0, uint8_t *ChineseChar)
{
    uint16_t i = 0;
    for (uint8_t y = y0; y < y0 + 2; y++)
        for (uint8_t x = x0; x < x0 + 16; x++)
            GRAM[y][x] = ChineseChar[i++];
}

void oled_ProgressBar(uint8_t count)
{
    uint8_t length = count / 2;
    for (uint8_t n = 0; n < length; n++) {
        GRAM[1][n] = 0b11111111;
    }
}

void oled_ShowNumber(uint8_t num, uint8_t position, uint8_t line)
{
    if (num < 0 || num >= 10 || position > 120 || position < 0 || line < 0 || line > 8)
        return;
    for (uint8_t n = position; n < (position + 3); n++) {
        GRAM[line][n] = numbers_3x5[num][n - position];
    }
}

void oled_ShowLatin(uint8_t c, uint8_t position, uint8_t line)
{
    if (c < 0 || c > sizeof(latin_8x8) || position > 120 || position < 0 || line < 0 || line > 8)
        return;
    uint8_t n;
    for (n = 0; n < 8; n++) {
        GRAM[line][n + position] = latin_8x8[c][n];
    }
}

void oled_ShowCylil(uint8_t c, uint8_t position, uint8_t line)
{
    if (c < 0 || c > sizeof(cylil_8x8) || position > 120 || position < 0 || line < 0 || line > 8)
        return;
    uint8_t n;
    for (n = 0; n < 8; n++) {
        GRAM[line][n + position] = cylil_8x8[c][n];
    }
}

void oled_ShowLatinS(uint8_t *chars, uint8_t size, uint8_t position,
                     uint8_t line)
{
    if ((position + size) > 128)
        return;
    for (uint8_t n = position; n < (position + size); n += 1) {
        oled_ShowLatin(chars[n - position], n * 8, line);
    }
}

void oled_ShowCylilS(uint8_t *chars, uint8_t size, uint8_t position,
                     uint8_t line)
{
    if ((position + size) > 128)
        return;
    for (uint8_t n = position; n < (position + size); n += 1) {
        oled_ShowCylil(chars[n - position], n * 8, line);
    }
}

void oled_ShowLatinTest()
{
    uint8_t n;
    for (n = 0; n < 14; n++) {
        oled_ShowLatin(n, n * 8, 3);
    }
    for (n = 14; n < 26; n++) {
        oled_ShowLatin(n, (n - 14) * 8, 4);
    }
}

void oled_ShowLanguageTest()
{
    const char english[] =
        {4, 13, 6, 11, 8, 18, 7};
    const char espanol[] =
        {4, 18, 15, 0, 27, 14, 11};
    const char russkij[] =
        {6, 3, 7, 7, 8, 4, 5};
    const char deutsch[] =
        {3, 4, 20, 19, 18, 2, 7};
    oled_ShowLatinS((uint8_t *)espanol, sizeof(espanol), 0, 4);
    oled_ShowLatinS((uint8_t *)english, sizeof(english), 0, 5);
    oled_ShowLatinS((uint8_t *)deutsch, sizeof(deutsch), 0, 6);
    oled_ShowCylilS((uint8_t *)russkij, sizeof(russkij), 0, 7);
}

void oled_ShowNumberTest()
{
    oled_ShowNumber(0, 0, 0);
    oled_ShowNumber(1, 5, 0);
    oled_ShowNumber(2, 10, 0);
    oled_ShowNumber(3, 15, 0);
    oled_ShowNumber(4, 20, 0);
    oled_ShowNumber(5, 25, 0);
    oled_ShowNumber(6, 30, 0);
    oled_ShowNumber(7, 35, 0);
    oled_ShowNumber(8, 40, 0);
    oled_ShowNumber(9, 45, 0);
}

void oled_HW_rolling_stop()
{
    oled_WriteCommand(0x2E); // rolling stop
}

void oled_HW_rolling_start()
{
    oled_WriteCommand(0x2F); // rolling start
}

void oled_HW_rolling()
{
    oled_WriteCommand(0x27); // left
    oled_WriteCommand(0x00); // none
    oled_WriteCommand(0x00); // line start
    oled_WriteCommand(0x00); // speed
    oled_WriteCommand(0x07); // line stop
    oled_WriteCommand(0x00); // row start
    oled_WriteCommand(0x7F); // row stop
}

void oled_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r)
{
    int a, b;
    int di;
    a  = 0;
    b  = r;
    di = 3 - (r << 1); /* 判断下个点位置的标志 */
    while (a <= b) {
        oled_SetPoint(x0 + a, y0 - b); /* 5 */
        oled_SetPoint(x0 + b, y0 - a); /* 0 */
        oled_SetPoint(x0 + b, y0 + a); /* 4 */
        oled_SetPoint(x0 + a, y0 + b); /* 6 */
        oled_SetPoint(x0 - a, y0 + b); /* 1 */
        oled_SetPoint(x0 - b, y0 + a);
        oled_SetPoint(x0 - a, y0 - b); /* 2 */
        oled_SetPoint(x0 - b, y0 - a); /* 7 */
        a++;
        /* 使用Bresenham算法画圆 */
        if (di < 0) {
            di += 4 * a + 6;
        } else {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}

void oled_Init()
{
    oled_WriteCommand(0xAE); // display off
    oled_WriteCommand(0x00); //---set low column address
    oled_WriteCommand(0x10); //---set high column address
    oled_WriteCommand(0x40); //--set start line address
    oled_WriteCommand(0xB0); //--set page address
    oled_WriteCommand(0x81); // contract control
    oled_WriteCommand(0xFF); //--128
    oled_WriteCommand(0xA1); // set segment remap
    oled_WriteCommand(0xA6); // [invert]normal / reverse display
    oled_WriteCommand(0xA8); //--set multiplex ratio(1 to 64)
    oled_WriteCommand(0x3F); //--1/32 duty
    oled_WriteCommand(0xC8); // Com scan direction
    oled_WriteCommand(0xD3); //-set display offset
    oled_WriteCommand(0x00); //

    oled_WriteCommand(0xD5); // set osc division
    oled_WriteCommand(0x80); //

    oled_WriteCommand(0xD8); // set area color mode off
    oled_WriteCommand(0x05); //

    oled_WriteCommand(0xD9); // Set Pre-Charge Period
    oled_WriteCommand(0xF1); //

    oled_WriteCommand(0xDA); // set com pin configuartion
    oled_WriteCommand(0x12); //

    oled_WriteCommand(0xDB); // set Vcomh
    oled_WriteCommand(0x30); //

    oled_WriteCommand(0x8D); // set charge pump enable
    oled_WriteCommand(0x14); //

    oled_WriteCommand(0xAF); // display on
}

void oled_Drawline(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    uint16_t t;
    int16_t xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int16_t incx, incy, row, col;
    // 计算坐标增量
    delta_x = x2 - x1;
    delta_y = y2 - y1;
    row     = x1;
    col     = y1;
    if (delta_x > 0)
        incx = 1; // 设置单步方向
    else if (delta_x == 0)
        incx = 0; // 垂直线
    else {
        incx    = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; // 水平线
    else {
        incy    = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
        distance = delta_x; // 选取基本增量坐标轴
    else
        distance = delta_y;
    // 画线输出
    for (t = 0; t <= distance + 1; t++) {
        oled_SetPoint(row, col);
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance) {
            xerr -= distance;
            row += incx;
        }
        if (yerr > distance) {
            yerr -= distance;
            col += incy;
        }
    }
}
