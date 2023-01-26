#pragma once
#ifdef MKS_TFT35_V1_0
// touch screen X, Y channels are swapped for MKS_TFT35_V1_0
// Defined in MKS TFT35 Touch Screen source code: user\others\mks_touch_screen.c CHX=0x90, CHY=0xD0
#define CMD_RDX 0x90
#define CMD_RDY 0xD0
#else
#define CMD_RDX 0xD0
#define CMD_RDY 0x90
#endif

typedef enum
{
	TOUCH_EVENT_NONE,
	TOUCH_EVENT_DOWN,
	TOUCH_EVENT_HOLD,
	TOUCH_EVENT_UP,
}TOUCH_EVENT_TYPE;

typedef struct tagTouchCalibrationInfo
{
	uint8_t IsValid;
	Point LCD_Corner[3];
	Point TP_Points[3];
	uint32_t A, B, C, D, E, F, K;
}TouchCalibrationInfo;

extern TouchCalibrationInfo touchCalibrationInfo;

extern uint8_t touchScreenIsPress;
extern TOUCH_EVENT_TYPE TouchEventStatus;

extern uint8_t* currentCalibrationAddress;
extern uint8_t* currentSoapStringAddress;

extern uint16_t TouchPointX;
extern uint16_t TouchPointY;
void LCD_ProcessTouchEvent();
void lcd_touch_get_coordinates(uint16_t *x, uint16_t *y);
void CheckLCDCalibration();
void lcd_touch_loop_calibration_data();
void save_LCD_Touch_Calibration_Data(void);
uint8_t checkForValidLCDCalibrationData(void);
void saveSoapStringandEraseSector11(void);
void CalibratLcdTouchPanel(void);
void clearcalibrtionData(void);


