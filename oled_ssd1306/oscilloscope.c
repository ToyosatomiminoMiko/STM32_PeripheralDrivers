/*
!WARNING!
本文件代码不完整,不可直接运行
仅展示示波器模式的示例代码
*/
uint32_t adc_v;
oled_NewFrame();
while (1)
{
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 0xFF) == HAL_OK)
    {
        adc_v = HAL_ADC_GetValue(&hadc1) * (3.3 / 64);
    }
    oled_SetPoint(127, adc_v);
    oled_SetFrist();
    oled_SoftRolling();
    oled_ShowFrame();
}
