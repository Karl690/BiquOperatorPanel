#pragma once
#include "stm32f4xx_hal.h"
#include "STORAGE/FLASH/flash_4xx.h"
#define USE_FLASH

// LCD interface
// Supported LCD drivers: [ST7789, SSD1963, RM68042, NT35310, ILI9488, ILI9341, ILI9325, HX8558]
#define SSD1963
#ifndef TFTLCD_DRIVER
	#define TFTLCD_DRIVER       SSD1963
	#define TFTLCD_DRIVER_SPEED 0x10     // SSD1963 needs slower speed
#endif

#define LCD_HARDWARE_WIDTH 800
#define LCD_HARDWARE_HEIGHT 480

#define LCD_WIDTH  800
#define LCD_HEIGHT 480
// Only for TFTLCD_DRIVER SSD1963
#ifndef SSD1963_LCD_PARA
	#define SSD1963_LCD_PARA
	#define SSD_DCLK_FREQUENCY  30   // 30Mhz

	#define SSD_HOR_PULSE_WIDTH 1
	#define SSD_HOR_BACK_PORCH  46
	#define SSD_HOR_FRONT_PORCH 210

	#define SSD_VER_PULSE_WIDTH 3
	#define SSD_VER_BACK_PORCH  33
	#define SSD_VER_FRONT_PORCH 22
#endif

// FSMC 8080 interface (high speed) or normal IO interface (low speed)
#ifndef STM32_HAS_FSMC
	#define STM32_HAS_FSMC
#endif

// LCD data 16bit or 8bit
#ifndef LCD_DATA_16BIT
#define LCD_DATA_16BIT 1
#endif

// LCD Backlight pins (adjust brightness with LED PWM)
#ifndef LCD_LED_PIN
	#define LCD_LED_PIN           PD12
	//#define LCD_LED_PIN_ALTERNATE GPIO_AF_TIM4
//#define LCD_LED_PWM_CHANNEL   _TIM4_CH1
#endif

// LCD Encoder pins
#ifndef LCD_ENCA_PIN
	#define LCD_ENCA_PIN   PA8
	#define LCD_ENCB_PIN   PC9
	#define LCD_BTN_PIN    PC8
	#define LCD_ENC_EN_PIN PC6
#endif