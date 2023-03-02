#include "pinout.h"
#include "GPIO_Init.h"
void Init_GPIO_OLD()
{
	GPIO_InitSet(LCD_ENCA_PIN, MGPIO_MODE_IPU, 0);
	GPIO_InitSet(LCD_ENCB_PIN, MGPIO_MODE_IPU, 0);
	GPIO_InitSet(LCD_BTN_PIN, MGPIO_MODE_IPU, 0);
}