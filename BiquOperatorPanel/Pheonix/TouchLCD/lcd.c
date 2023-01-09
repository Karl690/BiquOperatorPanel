#include "main.h"
#include "lcd.h"
#include "GUI/gui.h"
void(*pLCD_SetDirection)(uint8_t rotate);
void(*pLCD_SetWindow)(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey);




#ifdef SCREEN_SHOT_TO_SD

uint32_t(*pLCD_ReadPixel_24Bit)(int16_t x, int16_t y);

uint32_t LCD_ReadPixel_24Bit(int16_t x, int16_t y)
{
	return pLCD_ReadPixel_24Bit(x, y);
}
#endif



#ifdef LCD_LED_PIN


void LCD_LED_On()
{
#ifdef LCD_LED_PWM_CHANNEL
	LCD_SET_BRIGHTNESS(100);
#else
	GPIO_SetLevel(LCD_LED_PIN, 1);
#endif
}

void LCD_LED_Off()
{
#ifdef LCD_LED_PWM_CHANNEL
	LCD_SET_BRIGHTNESS(0);
#else
	GPIO_SetLevel(LCD_LED_PIN, 0);
#endif
}

void LCD_LED_Init(void)
{
#ifdef LCD_LED_PWM_CHANNEL
	GPIO_InitSet(LCD_LED_PIN, MGPIO_MODE_AF_PP, LCD_LED_PIN_ALTERNATE);
	TIM_PWM_Init(LCD_LED_PWM_CHANNEL);
#else
	LCD_LED_Off();
	GPIO_InitSet(LCD_LED_PIN, MGPIO_MODE_OUT_PP, 0);
#endif
}

#endif  // LCD_LED_PIN
void Setup_LCD_Driver()
{
	Init_Commands();
	pLCD_SetDirection = SetDirection;
	pLCD_SetWindow = SetWindow;
	
#ifdef LCD_LED_PIN
	LCD_LED_Init();
	LCD_LED_On();
#endif

#ifdef SCREEN_SHOT_TO_SD
	pLCD_ReadPixel_24Bit = ReadPixel_24Bit;
#endif
}

void Init_LCD()
{
	Setup_LCD_Hardware();
	Setup_LCD_Driver();
	
	GUI_Clear(COLOR_BLACK); // I changed this color .. LCD works weelll , now.
	
	
#ifdef STM32_HAS_FSMC
	LCD_DMA_Config(); // spi flash to fsmc lcd DMA channel configuration
#endif
}


void LCD_RefreshDirection(uint8_t rotate)
{
	pLCD_SetDirection(rotate);
}

void LCD_SetWindow(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey)
{
	pLCD_SetWindow(sx, sy, ex, ey);
}
