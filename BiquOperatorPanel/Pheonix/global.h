#pragma  once
#define LCD_DRIVER_IS(n)  ((TFTLCD_DRIVER) == (n))
#define LCD_DRIVER_HAS(n) (((TFTLCD_DRIVER) & (n)) == (n))

typedef union
{
	uint16_t color;
	struct
	{
		uint16_t b : 5;
		uint16_t g : 6;
		uint16_t r : 5;
	} RGB;
} GUI_COLOR;