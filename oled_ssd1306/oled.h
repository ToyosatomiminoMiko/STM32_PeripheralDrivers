#ifndef INC_OLED_H_
#define INC_OLED_H_

#include "i2c.h"

#define OLED_I2C hi2c2
#define OLED_ADD 0x78 // 0b01111000

extern uint8_t GRAM0[128];
extern uint8_t GRAM1[128];
extern uint8_t GRAM2[128];
extern uint8_t GRAM3[128];
extern uint8_t GRAM4[128];
extern uint8_t GRAM5[128];
extern uint8_t GRAM6[128];
extern uint8_t GRAM7[128];
extern uint8_t *GRAMz[8];

HAL_StatusTypeDef oled_Write_Command(uint8_t i2c_cmd);
void oled_Init();
void oled_Clear();
void oled_Full();
void oled_Test();
void oled_ShowFrame();
void oled_NewFrame();
void oled_SetPixel(uint8_t x, uint8_t y);
void oled_ProgressBar(uint8_t count);
void oled_ShowNumber(uint8_t num, uint8_t position, uint8_t line);
void oled_ShowLatin(uint8_t num, uint8_t position, uint8_t line);
void oled_ShowLatinS(uint8_t *chars, uint8_t size, uint8_t position,
		uint8_t line);
void oled_ShowCylil(uint8_t c, uint8_t position, uint8_t line);
void oled_ShowCylilS(uint8_t *chars, uint8_t size, uint8_t position,
		uint8_t line);
void oled_ShowLatinTest();
void oled_ShowNumberTest();
void oled_SoftRolling();
void oled_ShowImage(const uint8_t *image, uint8_t size_x, uint8_t size_y);
#endif /* INC_OLDE_H_ */
