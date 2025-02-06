#define uint8_t unsigned char

int main(void)
{
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    /*
    320/16=20
    240/16=15
    16*5=80
    320/80=4
    240/80=3
    */
    while (1)
        for (uint8_t u = 0; u < 29; u++)
            for (uint8_t x = 0; x < 3; x++)
                for (uint8_t y = 0; y < 4; y++)
                    for (uint8_t v = 0; v < 16; v++)
                        for (uint8_t w = 0; w < 16; w++)
                            lcd_fill(v * 5 + (x * 80), w * 5 + (y * 80),
                                     v * 5 + 5 + (x * 80),
                                     w * 5 + 5 + (y * 80), frame[u][v][w]);
}
