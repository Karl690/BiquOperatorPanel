
#pragma  once
#include <stdint.h>
#include "configure.h"
///#define LCD_DRIVER_IS(n)  ((TFTLCD_DRIVER) == (n))
//#define LCD_DRIVER_HAS(n) (((TFTLCD_DRIVER) & (n)) == (n))

#define BOOL uint8_t;
#define TRUE	(uint8_t)0x1
#define FALSE	(uint8_t)0x0
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