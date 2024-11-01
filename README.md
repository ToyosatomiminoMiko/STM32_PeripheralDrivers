# STM32: Peripheral Drivers
1. 本存储库是 `STM32F103ZET6` 的外设驱动
2. 开发板使用的*正点原子/精英版STM32F103*(**这不是广告**)
3. 作者能力有限,这些代码和文档难免会有错误和不足,请谅解或提交**Issue**
4. 本存储库的许可证不适用于**正点原子团队(ALIENTEK)的代码**copyright归原作者所有,在此仅用于学习

## § 0x00 感谢名单 Bilibili
他们的代码给了我重要的参考,放在这里以表示感谢
- [大明狐(B站主页)](https://space.bilibili.com/3162360)<br>
    提供的 OLED 0.96 教程和大量的踩坑
- [keysking(B站主页)](https://space.bilibili.com/6100925)<br>
    [keysking(站内主页)](https://github.com/keysking)<br>
    提供的最精致的 STM32 系列教程
- [一直在入门啊(B站主页)](https://space.bilibili.com/2044983862)<br>
    提供的没有废话清晰明了的 STM32 系列教程<br>
    [一直在入门啊(gitee教程代码)](https://gitee.com/siyu233/Stm32Code_1)<br>
    教程的代码也采用了*GPL-3.0*


## § 0x01 OLED(0.96) SSD1306
OLED 显示器(0.96 寸)
### SSD1306 i2c address: `0x78`
|   7   |   6   |   5   |   4   |   3   |   2   |   1   |  R/W  |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|   0   |   1   |   1   |   1   |   1   |   0   |   0   |  1/0  |
### 分辨率: 128 * 64 (共`1024 Byte`)
### 实现功能
1. 显存操作
2. 屏幕滚动
3. 显示数字
4. 拉丁字母
5. 西里尔字母
6. 进度条
### 图形调试器
- `oled_debugger.html`用于验证绘图算法, 纯前端实现


## § 0x02 EEPROM 24C02
24C02 带电可擦可编程只读存储器
### 24C02 i2c address: `0xA0` (当`A0`,`A1`,`A2`接地时`GND`)
|   7   |   6   |   5   |   4   |  A2   |  A1   |  A0   |  R/W  |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|   1   |   0   |   1   |   0   |   0   |   0   |   0   |  1/0  |
### 容量: `256 Byte`
### 实现功能
1. 检测该设备是否存在
2. 按位读取函数
3. 按位写入函数


## RotaryEncoder
旋转编码器


## DigitalTube
数码管


## FSMC_TFT-LCD
- *Thin film transistor liquid crystal display*
- **薄膜晶体管液晶显示器**
- ***代码来自正点原子***
- 型号: `ST7789`

## VFD
- *Vacuum Fluorescent Display*
- **真空荧光显示器**
- 型号: `CIG25-1605N`
