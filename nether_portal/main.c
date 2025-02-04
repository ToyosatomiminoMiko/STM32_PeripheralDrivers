int main(){
  // display 320*240
while (1)
	{
		for (uint8_t u = 0; u < 29; u++)
		{
			for (uint8_t x = 0; x < 2; x++)
			{
				for (uint8_t y = 0; y < 3; y++)
				{
					for (uint8_t v = 0; v < 16; v++)
					{
						for (uint8_t w = 0; w < 16; w++)
						{
							//lcd_draw_point(v, w, frame_1[v][w]);
							lcd_fill(v * 7.5 + (x * 120), w * 7.5 + (y * 120),
									v * 7.5 + 7 + (x * 120),
									w * 7.5 + 7 + (y * 120), frame[u][v][w]);
						}
					}
				}
			}
		}

	}
}
