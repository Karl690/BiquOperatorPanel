
#pragma  once
#include <stdint.h>
#include "configure.h"
///#define LCD_DRIVER_IS(n)  ((TFTLCD_DRIVER) == (n))
//#define LCD_DRIVER_HAS(n) (((TFTLCD_DRIVER) & (n)) == (n))

#define BOOL uint8_t;
#define TRUE	(uint8_t)0x1
#define FALSE	(uint8_t)0x0

#define EOT			0x04	//End of Transmission. we use this as the first byte of var pairs 's block
#define FOV			0x0A	//First byte of Var	pair
#define EOV			0x0D	//End byte of var pair
#define FOC			0xFF	//Formatted byte of Charactor

#define ACK		(uint8_t)6
#define NAK		(uint8_t)21
#define ENQ		(uint8_t)5
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