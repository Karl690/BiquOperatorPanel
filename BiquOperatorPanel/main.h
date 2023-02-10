#pragma once
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "configure.h"
#include "global.h"

#include "RevisionHistory.h"
#include "taskmanager.h"
#include "global.h"
#include "GPIO/pins.h"
#include "GPIO/GPIO_Init.h"
#include "GPIO/pinout.h"
	
#include "TouchLCD/lcd.h"
#include "TouchLCD/lcd_touch.h"
#include "SPI/spi.h"
#include "STORAGE/storage.h"
#include "STORAGE/FLASH/w25qxx.h"
#include "SPI/xpt2046.h"

#include "TouchLCD/GUI/PanelMain.designer.h"
#include "Communication/serial.h"
#include "Communication/secsserial.h"
#include "Communication/simpleserial.h"
	
#define VECT_TAB_FLASH 0x08008000UL

typedef enum 
{
	SCREEN_TOUCH_CALIBRATION,
	SCREEN_MAIN
}SCREEN_TYPE;
	
	

	
extern SCREEN_TYPE CurretScreenType;
extern SCREEN_TYPE NewScreenType; //it would be used when transforing screen.

extern uint8_t eraseStorageFlag;
extern uint8_t SoapStringBuffer[SOAPSTRING_BLOCKSIZE];
extern TouchCalibrationInfo touchCalibrationInfo;
extern Numeric* SoapNudsList[30];
void Error_Handler(void);
	extern uint16_t	Refresh;
	extern uint16_t CalibrateScreenFlag;
	

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
