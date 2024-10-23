#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_
#include "i2c.h"
#include "main.h"

#define EEPROM_ADD 0b10100000U
#define EEPROM_wADD 0b10100000U
#define EEPROM_rADD 0b10100001U

#define EEPROM_hi2c hi2c1

HAL_StatusTypeDef eeprom_is_ready();
HAL_StatusTypeDef eeprom_write_byte(uint16_t memadd, uint8_t *data);
HAL_StatusTypeDef eeprom_read_byte(uint16_t memadd, uint8_t *data);


#endif /* INC_EEPROM_H_ */
