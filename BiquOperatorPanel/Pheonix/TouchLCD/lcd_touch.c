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
TOUCH_EVENT_TYPE TouchEventStatus;
void LCD_ProcessTouchEvent()
{
	
	if (!XPT2046_Read_Pen())
	{
		if (touch >= 10)  // 20ms
		{
			if (TouchEventStatus == TOUCH_EVENT_NONE) TouchEventStatus = TOUCH_EVENT_DOWN;
			else if (TouchEventStatus == TOUCH_EVENT_DOWN) TouchEventStatus = TOUCH_EVENT_HOLD;
			else TouchEventStatus = TOUCH_EVENT_HOLD;
			touchScreenIsPress = 1;
			lcd_touch_get_coordinates(&TouchPointX, &TouchPointY);
		}
		else
		{
			touch++;
		}
	}
	else
	{
		if (TouchEventStatus == TOUCH_EVENT_DOWN || TouchEventStatus == TOUCH_EVENT_HOLD) 
		{
			TouchEventStatus = TOUCH_EVENT_UP;
			touch++;
		}
		else if (TouchEventStatus == TOUCH_EVENT_UP)
		{
			if (touch >= 10)
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
	uint16_t tp_x = XPT2046_Repeated_Compare_AD(CMD_RDX);
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



uint8_t* currentCalibrationAddress = NULL;
uint8_t* currentSoapStringAddress = NULL;
void save_LCD_Touch_Calibration_Data(void)
{
	currentCalibrationAddress = getCalibrationDataBlockAddress(); //get current pointer in storage
	if (currentCalibrationAddress == NULL)
	{
		//no valid data was found;
		currentCalibrationAddress = CALIBRATIONDATA_STARTADDRESS;
		if (*currentCalibrationAddress != 0xff)
		{
			saveSoapStringandEraseSector11();//erase and copy old soap to new starting block	
			return;
		}
	}
	else
	{//we have found valid block,now disable it and then incrment to next block
		*currentCalibrationAddress = 0;//zero out old pointer, data no longer valid
		currentCalibrationAddress += CALIBRATIONDATA_BLOCKSIZE; //point to next place in storage
		if (currentCalibrationAddress > CALIBRATIONDATA_STARTADDRESS + CALIBRATIONDATA_SIZE)
		{//now we have reached past the 4k boundry and need to point back to the beginning
			saveSoapStringandEraseSector11();	
			return;
		}
	}
//ok, when you get here, we should be pointing to 0xff values in the target storage memory
	MoveData(currentCalibrationAddress, (uint8_t*)&touchCalibrationInfo, sizeof(TouchCalibrationInfo));
}


void saveSoapStringTobuffer() //backup Soapstring from storage to FLASH.
{
	currentSoapStringAddress = getSoapstringBlockAddress(); //get the current soapstring in storage.
	if (!currentSoapStringAddress) {
		//Soapstring is not exsit in storage.		
		return; 
	}
	MoveData(SoapStringBuffer, currentSoapStringAddress, SOAPSTRING_BLOCKSIZE); // SoapString copy from storage's currentSoapStringAddress.
}

void writeOldsoapstringFromBuffertoflashblock() //save the soapstring in storage
{
	uint8_t* currentSoapstringAddress = getSoapstringBlockAddress(); //get the current soapstring in storage.
	if (!currentSoapstringAddress)
	{	
		currentSoapstringAddress = SOAPSTRING_STARTADDRESS; 
	}
	else
	{
		*currentSoapstringAddress = 0x0; //set flag as that is old block
		currentSoapstringAddress += SOAPSTRING_BLOCKSIZE; // move to next block
		if (currentSoapstringAddress + SOAPSTRING_BLOCKSIZE > SOAPSTRING_ENDADDRESS)
		{
			currentSoapstringAddress = SOAPSTRING_STARTADDRESS;
			saveSoapStringandEraseSector11(); // it need to erase storage.
			return;
		}
	}	
	//copy the SoapstringBuffer to storage.
	MoveData(currentSoapstringAddress, (uint8_t*)&SoapStringBuffer, SOAPSTRING_BLOCKSIZE); 
}

void eraseStorage()
{
	/// Erase storaage .. to do
	currentCalibrationAddress = CALIBRATIONDATA_STARTADDRESS;
	currentSoapStringAddress = SOAPSTRING_STARTADDRESS;
}
void saveSoapStringandEraseSector11() // I think this function name is not correct.
{
	saveSoapStringTobuffer();	//backup soapstring in storage to buffer
	eraseStorage();					//erase the storage and set the address as start.
	MoveData(currentCalibrationAddress, &touchCalibrationInfo, CALIBRATIONDATA_BLOCKSIZE); //copy calibration buffer  to storage
	MoveData(currentSoapStringAddress, &SoapStringBuffer, SOAPSTRING_BLOCKSIZE);  //copy soapstring buffer to storage
	//writeOldsoapstringFromBuffertoflashblock[1] ;//todo
}

uint8_t checkForValidLCDCalibrationData(void)
{//if it finds it, it will refresh the structure from storage
	//read_memory(0, (uint8_t*)&touchCalibrationInfo, sizeof(TouchCalibrationInfo));
	//if (touchCalibrationInfo.IsValid != 0x80) return 0;
	//uint32_t* currentCalibrationAddress = NULL;
	currentCalibrationAddress  = getCalibrationDataBlockAddress();
	if (currentCalibrationAddress==0) return 0;//was a disaster and we did not find valid data
	if (*currentCalibrationAddress == 0x80)
	{
		//it is valid data, so lets update
		MoveData((uint8_t*)&touchCalibrationInfo, currentCalibrationAddress, sizeof(TouchCalibrationInfo)); //update working variables from storage
		return 1;//updated so report successfully found and updated
	}
	return 0; //invalid address
}

void CalibratLcdTouchPanel()
{//starts the screen calibration	
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
	
	touchCalibrationCounter = 0;
	while (touchCalibrationCounter < 3)
	{//we loop until 3 points are pressed
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
	
	touchCalibrationInfo.IsValid = 0x80;//update in structure that it is now valid data
	save_LCD_Touch_Calibration_Data();//save to storage
}
