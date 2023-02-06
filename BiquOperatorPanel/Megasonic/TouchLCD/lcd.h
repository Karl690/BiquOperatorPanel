#include "global.h"

#pragma once

#ifdef SSD1963 //LCD_DRIVER_HAS(SSD1963)
#include "TouchLCD/Drivers/SSD1963.h"
#endif
#ifdef STM32_HAS_FSMC

#else
//#error "don't support LCD-GPIO yet"
#endif
#include "TouchLCD/4xx/TouchLCD_4xx.h"
#if LCD_DATA_16BIT == 1
#define LCD_WR_16BITS_DATA(c) do{ LCD_WR_DATA(c); }while(0)
#else
#define LCD_WR_16BITS_DATA(c) do{ LCD_WR_DATA(((c)>>8)&0xFF); LCD_WR_DATA((c)&0xFF); }while(0)
#endif

#ifdef LCD_LED_PWM_CHANNEL
#define LCD_SET_BRIGHTNESS(percentage) TIM_PWM_SetDutyCycle(LCD_LED_PWM_CHANNEL, percentage)
#else
#define LCD_SET_BRIGHTNESS(percentage)
#endif

#ifdef SCREEN_SHOT_TO_SD
uint32_t LCD_ReadPixel_24Bit(int16_t x, int16_t y);
#endif

void Setup_LCD_Driver();
void Init_LCD();
void LCD_RefreshDirection(uint8_t rotate);
void LCD_SetWindow(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey);

void LCD_ProcessTouchEvent();
