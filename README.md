# STM32:Peripheral Drivers
本库存储`STM32F103ZET6`的外设驱动

开发板使用**正点原子/精英版STM32F103**

本存储库按照**GPL-2.0**自由软件许可证开放

所有涉及到`i2c`通信的外设都会以表格形式将每一位地址展示出来


## OLED(0.96) SSD1306
OLED 显示器(0.96 寸)
### SSD1306 i2c address: `0x78`
|   7   |   6   |   5   |   4   |   3   |   2   |   1   |  R/W  |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|   0   |   1   |   1   |   1   |   1   |   0   |   0   |  1/0  |
### SIZE 分辨率: 128 * 64 (共`1024 Byte`)
### 实现功能
1. 模拟显存操作,将显存发送到屏幕上
2. 屏幕滚动操作
3. 显示数字
4. 显示拉丁字母
5. 显示西里尔字母
6. 显示进度条


## EEPROM 24C02
24C02 带电可擦可编程只读存储器
### 24C02 i2c address: `0xA0` (当`A0`,`A1`,`A2`接地时`GND`)
|   7   |   6   |   5   |   4   |  A2   |  A1   |  A0   |  R/W  |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|   1   |   0   |   1   |   0   |   0   |   0   |   0   |  1/0  |
### SIZE 容量: `256 Byte`
### 实现功能
1. 检测该设备是否存在
2. 按位读取函数
3. 按位写入函数


## RotaryEncoder
旋转编码器


## DigitalTube
数码管

