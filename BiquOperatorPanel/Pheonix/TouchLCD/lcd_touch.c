#include "main.h"
#include "lcd.h"
#include "GUI/gui.h"
//#include "GUI/FontArial.h"
#include "../SPI/xpt2046.h"

#include "lcd_touch.h"


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

Point LCD_Corner[3] = { 0 };

#define XL1 LCD_Corner[0].x
#define XL2 LCD_Corner[1].x
#define XL3 LCD_Corner[2].x

#define YL1 LCD_Corner[0].y
#define YL2 LCD_Corner[1].y
#define YL3 LCD_Corner[2].y

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

uint16_t calibrationPointX = 0;
uint16_t CalibrationPointY = 0;
static uint8_t touch;
TOUCH_EVENT_TYPE TouchEventStatus;
void LCD_ProcessTouchEvent()
{
	if (!XPT2046_Read_Pen())//0=touch event detected, 1= no touch detected
	{
		if (touch >= 5)  // 20ms
		{
			if (TouchEventStatus == TOUCH_EVENT_NONE) TouchEventStatus = TOUCH_EVENT_DOWN;		//if the previous status is NONE, it would be the down event.
			else if (TouchEventStatus == TOUCH_EVENT_DOWN) TouchEventStatus = TOUCH_EVENT_HOLD; // if the previous status is DOWN, it would be the hold event
			else TouchEventStatus = TOUCH_EVENT_HOLD;											//otherwise the it

			touch++;
			if (CalibrateScreenFlag)
			{
				//this means we are calibrating the screen at this time
				//if(calibrationPointX<1)
				uint16_t tp_x = XPT2046_Repeated_Compare_AD(CMD_RDX);
				uint16_t tp_y = XPT2046_Repeated_Compare_AD(CMD_RDY);
				
				if (touch > 5)
				{
					switch (CalibrateScreenFlag)
					{						
					case 2: touchCalibrationInfo.TP_Points[0].x = tp_x;
						touchCalibrationInfo.TP_Points[0].y = tp_y;
						CalibrateScreenFlag++; break; //waiting for press
					case 4: touchCalibrationInfo.TP_Points[1].x = tp_x;
						touchCalibrationInfo.TP_Points[1].y = tp_y;
						CalibrateScreenFlag++; break; //waiting for press
					case 6: touchCalibrationInfo.TP_Points[2].x = tp_x;
						touchCalibrationInfo.TP_Points[2].y = tp_y;
						CalibrateScreenFlag++; break; //waiting for press
					}
					return;
				}
			}
			else 
				lcd_touch_get_coordinates(&TouchPointX, &TouchPointY);
			touchScreenIsPress = 1;
		}
		else
		{
			touch++;
		}
	}
	else //
	{
		if (TouchEventStatus == TOUCH_EVENT_DOWN || TouchEventStatus == TOUCH_EVENT_HOLD) 
		{
			TouchEventStatus = TOUCH_EVENT_UP;
			touch++;
		}
		else if (TouchEventStatus == TOUCH_EVENT_UP)
		{
			if (touch >= 5)
			{
				TouchEventStatus = TOUCH_EVENT_NONE; // Touch Up event keep for a while.
				touch = 0;
			}
			else
			{
				touch++;
			}
		}
		else
		{
			TouchEventStatus = TOUCH_EVENT_NONE;
			touchScreenIsPress = 0;
			touch = 0;	
		}
		
	}
}

void lcd_touch_get_coordinates(uint16_t *x, uint16_t *y)
{
	uint16_t tp_x = XPT2046_Repeated_Compare_AD(CMD_RDX);//read the data from the 2046 registers
	uint16_t tp_y = XPT2046_Repeated_Compare_AD(CMD_RDY);

	*x = (A * tp_x + B * tp_y + C) / K;
	*y = (D * tp_x + E * tp_y + F) / K;
}

/*
 *uint8_t checkForValidLCDCalibrationData();   returns 1 if good and 0 if false, loads data from storage to working structure
 *getValidlcdDataStorageAddress();   sets variable currentCalibrationAddress to current storage pointer
 *
 *saveSoapStringandEraseSector11();   makes copy of soapstring to ram, then erased sector, then moves back
 *to first soapstring block  sector11+4k
 *
 *
 *
 *
 **/



void InitializeCalibrationParameters()
{//sets the 3 points for screen touch panel calibration in pixels
	LCD_Corner[0].x = 40;
	LCD_Corner[1].x = LCD_WIDTH - 40;
	LCD_Corner[2].x = LCD_WIDTH - 40;
	
	LCD_Corner[0].y = 40;
	LCD_Corner[1].y = 40;
	LCD_Corner[2].y = LCD_HEIGHT - 40;
}
void drawCalibrationCrossHairs(int16_t Index,Color16 CrosshairColor)
{//draws cross hair over current calibration point.
	GUI_HLine(LCD_Corner[Index].x - 10, LCD_Corner[Index].y, LCD_Corner[Index].x + 10, CrosshairColor);
	GUI_VLine(LCD_Corner[Index].x, LCD_Corner[Index].y - 10, LCD_Corner[Index].y + 10, CrosshairColor);	
}
void CalibratLcdTouchPanel()
{//starts the screen calibration	
	switch (CalibrateScreenFlag)
	{
	case 0: break;//not active just leave
	case 1: if (touch)break;
			GUI_Clear(COLOR_BLACK);
			drawCalibrationCrossHairs(0, COLOR_RED); CalibrateScreenFlag++; break;//draw first crosshair
	case 2: break;//just waiting for interrupt to process the press event
	case 3: if (touch)break;
		drawCalibrationCrossHairs(0, COLOR_BLACK); //erase previous cross hair
		drawCalibrationCrossHairs(1, COLOR_RED); CalibrateScreenFlag++; break; //draw first crosshair
	case 4: break;//just waiting for interrupt to process the press event
	case 5: if (touch)break;
		drawCalibrationCrossHairs(1, COLOR_BLACK); //erase previous cross hair
		drawCalibrationCrossHairs(2, COLOR_RED); CalibrateScreenFlag++; break; //draw first crosshair
	case 6: break;//do nothing, we are waiting for the last press event to fire and process}
	case 7://set up the points for transformation		
		K = (X1 - X3) * (Y2 - Y3) - (X2 - X3) * (Y1 - Y3);
		A = ((XL1 - XL3) * (Y2 - Y3) - (XL2 - XL3) * (Y1 - Y3));
		B = ((X1 - X3) * (XL2 - XL3) - (XL1 - XL3) * (X2 - X3));
		C = (Y1 * (X3 * XL2 - X2 * XL3) + Y2 * (X1 * XL3 - X3 * XL1) + Y3 * (X2 * XL1 - X1 * XL2));
		D = ((YL1 - YL3) * (Y2 - Y3) - (YL2 - YL3) * (Y1 - Y3));
		E = ((X1 - X3) * (YL2 - YL3) - (YL1 - YL3) * (X2 - X3));
		F = (Y1 * (X3 * YL2 - X2 * YL3) + Y2 * (X1 * YL3 - X3 * YL1) + Y3 * (X2 * YL1 - X1 * YL2));
//
		touchCalibrationInfo.IsValid = 0x80;//update in structure that it is now valid data
		save_LCD_Touch_Calibration_Data();//save to storage
		CalibrateScreenFlag = 0;
		Root_Panel.RedrawMe = 1;
		Refresh = 1;
		break;
	}
}
//	uint16_t TP_X[3], TP_Y[3];
//	uint32_t tp_num = 0;
//	int i;
//	GUI_Clear(COLOR_BLACK);				
//	//GUI_DrawString(LCD_WIDTH / 2, 5, "Touch Screen Calibration", &Font20, COLOR_BLACK);
//
//	
//	touchCalibrationCounter = 0;
//	while (touchCalibrationCounter < 3)
//	{//we loop until 3 points are pressed
//		if (TouchEventStatus != TOUCH_EVENT_DOWN) continue;
//		touchCalibrationInfo.TP_Points[touchCalibrationCounter].x = XPT2046_Repeated_Compare_AD(CMD_RDX);
//		touchCalibrationInfo.TP_Points[touchCalibrationCounter].y = XPT2046_Repeated_Compare_AD(CMD_RDY);
//		//Draw the rectangle at the selected point
//		GUI_FillRect(touchCalibrationInfo.LCD_Corner[touchCalibrationCounter].x - 20, 
//			touchCalibrationInfo.LCD_Corner[touchCalibrationCounter].y - 20,
//			touchCalibrationInfo.LCD_Corner[touchCalibrationCounter].x + 20,
//			touchCalibrationInfo.LCD_Corner[touchCalibrationCounter].y + 20,
//			COLOR_RED);
//		touchCalibrationCounter++;		//increase the calibration point's index 
//		TouchEventStatus = TOUCH_EVENT_HOLD; //change the touch event status artificially		
//		touch = 0;
//		HAL_Delay(200);
//	}
//	touchCalibrationCounter = 100;