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

typedef struct tagTouchCalibrationInfo
{
	uint8_t IsValid;
	Point LCD_Corner[3];
	Point TP_Points[3];
	uint32_t A, B, C, D, E, F, K;
}TouchCalibrationInfo;

extern TouchCalibrationInfo touchCalibrationInfo;

extern uint8_t touchScreenIsPress;

extern uint16_t TouchPointX;
extern uint16_t TouchPointY;
void LCD_ProcessTouchEvent();
void lcd_touch_get_coordinates(uint16_t *x, uint16_t *y);
void lcd_touch_calibration_screen(uint8_t);
void lcd_touch_loop_calibration_data(uint8_t);
void lcd_touch_store_calibration(void);
uint8_t lcd_touch_read_calibration(void);

