#include "eeprom.h"

HAL_StatusTypeDef eeprom_is_ready()
{
	uint32_t t = 10;
	return HAL_I2C_IsDeviceReady(&EEPROM_hi2c, EEPROM_rADD, t, 0xFF);
}

HAL_StatusTypeDef eeprom_write_byte(uint16_t memadd, uint8_t *data)
{
	return HAL_I2C_Mem_Write(&EEPROM_hi2c, EEPROM_wADD, memadd,
	I2C_MEMADD_SIZE_8BIT, data, 1, 0xFF);
}
HAL_StatusTypeDef eeprom_read_byte(uint16_t memadd, uint8_t *data)
{
	return HAL_I2C_Mem_Read(&hi2c1, EEPROM_rADD, memadd,
	I2C_MEMADD_SIZE_8BIT, data, 1, 0xFF);
}

