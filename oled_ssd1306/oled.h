#ifndef INC_OLED_H_
#define INC_OLED_H_

#include "i2c.h"

#define OLED_I2C hi2c2
#define OLED_ADD 0x78 // 0b01111000

extern uint8_t GRAM[8][128];

HAL_StatusTypeDef oled_WriteCommand(uint8_t i2c_cmd);
HAL_StatusTypeDef oled_WriteData(uint8_t i2c_cmd);
void oled_Init();
void oled_Clear();
void oled_Full();
void oled_Test();
void oled_ShowFrame();
void oled_SoftCirculation();
void oled_SoftRolling();
void oled_NewFrame();
void oled_SetPixel(uint16_t x, uint16_t y);
void oled_SetFrist();
void oled_SetPoint(uint16_t x, uint16_t y);
void oled_ProgressBar(uint8_t count);
void oled_ShowNumber(uint8_t num, uint8_t position, uint8_t line);
void oled_ShowLatin(uint8_t num, uint8_t position, uint8_t line);
void oled_ShowLatinS(uint8_t *chars, uint8_t size, uint8_t position,
		uint8_t line);
void oled_ShowCylil(uint8_t c, uint8_t position, uint8_t line);
void oled_ShowCylilS(uint8_t *chars, uint8_t size, uint8_t position,
		uint8_t line);
void oled_ShowLatinTest();
void oled_ShowLanguageTest();
void oled_ShowNumberTest();
void oled_HW_rolling_stop();
void oled_HW_rolling_start();
void oled_HW_rolling();
void oled_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r);
void oled_ShowImage(uint8_t *image);
void oled_ShowChinese_16x16(uint8_t x0, uint8_t y0, uint8_t *ChineseChar);

#endif /* INC_OLDE_H_ */
