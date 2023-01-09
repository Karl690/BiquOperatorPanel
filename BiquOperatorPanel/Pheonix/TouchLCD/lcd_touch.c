#include "main.h"
#include "lcd.h"
#include "GUI/gui.h"
//#include "GUI/FontArial.h"
#include "../SPI/xpt2046.h"

#include "lcd_touch.h"

TouchCalibrationInfo touchCalibrationInfo = { 0 };
//{
//	.LCD_Corner = { { 0x28, 0x28 }, { 0x218, 0x28 }, { 0x218, 0x1b8 } },
//	.TP_Points = { { 0x7e, 0x13e }, { 0x778, 0x116 }, { 0x773, 0x6dd } },
//	.A = 0x103fb0,
//	.B = 0x0e10,
//	.C = 0xfe3b4db0,
//	.D = 0x00003e80,
//	.E = 0x000ae6a0,
//	.F = 0xf8a2e070,
//	.K = 0x00284d8e 
//};
//	


#define XL1 touchCalibrationInfo.LCD_Corner[0].x
#define XL2 touchCalibrationInfo.LCD_Corner[1].x
#define XL3 touchCalibrationInfo.LCD_Corner[2].x

#define YL1 touchCalibrationInfo.LCD_Corner[0].y
#define YL2 touchCalibrationInfo.LCD_Corner[1].y
#define YL3 touchCalibrationInfo.LCD_Corner[2].y

#define X1 touchCalibrationInfo.TP_Points[0].x
#define X2 touchCalibrationInfo.TP_Points[1].x
#define X3 touchCalibrationInfo.TP_Points[2].x

#define Y1 touchCalibrationInfo.TP_Points[0].y
#define Y2 touchCalibrationInfo.TP_Points[1].y
#define Y3 touchCalibrationInfo.TP_Points[2].y


#define A touchCalibrationInfo.A
#define B touchCalibrationInfo.B
#define C touchCalibrationInfo.C
#define D touchCalibrationInfo.D
#define E touchCalibrationInfo.E
#define F touchCalibrationInfo.F
#define K touchCalibrationInfo.K


uint8_t touchScreenIsPress = 0;

uint8_t touchCalibrationCounter = 0;
int32_t TSC_Para[7];
uint16_t TouchPointX = 0;
uint16_t TouchPointY = 0;
static uint8_t touch;
void LCD_ProcessTouchEvent()
{
	
	if (!XPT2046_Read_Pen())
	{
		if (touch >= 10)  // 20ms
		{
			touchScreenIsPress = 1;
			lcd_touch_get_coordinates(&TouchPointX, &TouchPointY);
			//GUI_FillRect(TouchPointX, TouchPointY, TouchPointX + 4, TouchPointY + 4, COLOR_YELLOW);
		}
		else
		{
			touch++;
		}
	}
	else
	{
		touchScreenIsPress = 0;
		touch = 0;
	}
}

void lcd_touch_get_coordinates(uint16_t *x, uint16_t *y)
{
	uint16_t tp_x = XPT2046_Repeated_Compare_AD(CMD_RDX);
	uint16_t tp_y = XPT2046_Repeated_Compare_AD(CMD_RDY);

	*x = (A * tp_x + B * tp_y + C) / K;
	*y = (D * tp_x + E * tp_y + F) / K;
}


void lcd_touch_store_calibration(void)
{
	erase_memory();
	write_memory(0, (uint8_t*)&touchCalibrationInfo, sizeof(TouchCalibrationInfo));
}
uint8_t lcd_touch_read_calibration(void)
{
	read_memory(0, (uint8_t*)&touchCalibrationInfo, sizeof(TouchCalibrationInfo));
	if (touchCalibrationInfo.IsValid != 0x80) return 0;
	return 1;
}
void lcd_touch_calibration_screen(uint8_t isForce)
{
	if (!isForce && lcd_touch_read_calibration()) return;
	
	touchCalibrationInfo.LCD_Corner[0].x = 40;
	touchCalibrationInfo.LCD_Corner[1].x = LCD_WIDTH - 40;
	touchCalibrationInfo.LCD_Corner[2].x = LCD_WIDTH - 40;
	
	touchCalibrationInfo.LCD_Corner[0].y = 40;
	touchCalibrationInfo.LCD_Corner[1].y = 40;
	touchCalibrationInfo.LCD_Corner[2].y = LCD_HEIGHT - 40;
	
	uint16_t TP_X[3], TP_Y[3];
	uint32_t tp_num = 0;
	int i;
	GUI_Clear(COLOR_WHITE);				
	//GUI_DrawString(LCD_WIDTH / 2, 5, "Touch Screen Calibration", &Font20, COLOR_BLACK);
	for (tp_num = 0; tp_num < 3; tp_num++)
	{	
		GUI_HLine(touchCalibrationInfo.LCD_Corner[tp_num].x - 10, touchCalibrationInfo.LCD_Corner[tp_num].y, touchCalibrationInfo.LCD_Corner[tp_num].x + 10, COLOR_RED);
		GUI_VLine(touchCalibrationInfo.LCD_Corner[tp_num].x, touchCalibrationInfo.LCD_Corner[tp_num].y-10, touchCalibrationInfo.LCD_Corner[tp_num].y + 10, COLOR_RED);
	}
	lcd_touch_loop_calibration_data(isForce);
}

void lcd_touch_loop_calibration_data(uint8_t isForce)
{	
	touchCalibrationCounter = 0;
	while (touchCalibrationCounter < 3)
	{
		if (!touchScreenIsPress) continue;
		touchCalibrationInfo.TP_Points[touchCalibrationCounter].x = XPT2046_Repeated_Compare_AD(CMD_RDX);
		touchCalibrationInfo.TP_Points[touchCalibrationCounter].y = XPT2046_Repeated_Compare_AD(CMD_RDY);
		GUI_FillRect(touchCalibrationInfo.LCD_Corner[touchCalibrationCounter].x - 20, 
			touchCalibrationInfo.LCD_Corner[touchCalibrationCounter].y - 20,
			touchCalibrationInfo.LCD_Corner[touchCalibrationCounter].x + 20,
			touchCalibrationInfo.LCD_Corner[touchCalibrationCounter].y + 20,
			COLOR_RED);
		touchCalibrationCounter++;
		touchScreenIsPress = FALSE;		
		touch = 0;
		HAL_Delay(200);
	}
	touchCalibrationCounter = 100;
	
	K = (X1 - X3) * (Y2 - Y3) - (X2 - X3) * (Y1 - Y3);
	A = ((XL1 - XL3) * (Y2 - Y3) - (XL2 - XL3) * (Y1 - Y3));
	B = ((X1 - X3) * (XL2 - XL3) - (XL1 - XL3) * (X2 - X3));
	C = (Y1 * (X3 * XL2 - X2 * XL3) + Y2 * (X1 * XL3 - X3 * XL1) + Y3 * (X2 * XL1 - X1 * XL2));
	D = ((YL1 - YL3) * (Y2 - Y3) - (YL2 - YL3) * (Y1 - Y3));
	E = ((X1 - X3) * (YL2 - YL3) - (YL1 - YL3) * (X2 - X3));
	F = (Y1 * (X3 * YL2 - X2 * YL3) + Y2 * (X1 * YL3 - X3 * YL1) + Y3 * (X2 * YL1 - X1 * YL2));
	
	touchCalibrationInfo.IsValid = 0x80;
	lcd_touch_store_calibration();
}
