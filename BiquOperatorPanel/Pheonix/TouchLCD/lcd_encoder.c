#include "main.h"
#include "lcd.h"
#include "GUI/gui.h"

uint8_t FiredEncodeButtonEvent = 0;
void EncoderButtonDownEvent()
{
	CalibrateScreenFlag = 1;
	FiredEncodeButtonEvent = 1;
}

int EncoderCount = 0;
int encoderSt = 0; 
int encoderlastRead = 0;

void EncoderWheelMove()
{ 
	int a = GPIO_GetLevel(LCD_ENCA_PIN);
	int b = GPIO_GetLevel(LCD_ENCB_PIN);
	int st = (b << 1) | a;
	if (st == 3)
	{	
		encoderlastRead = 0;
		return;//nothing changing
	}

	if (encoderlastRead == 0)
	{
		if (a == 0)EncoderCount++;
		if (b == 0)EncoderCount--;
		encoderlastRead = st;
		
		
		if (FocusedWidget && FocusedWidget->Type == NUMERIC)
		{
			if (a == 0) numeric_increment((Numeric*)FocusedWidget);	
			if (b == 0) numeric_decrement((Numeric*)FocusedWidget);	
		}else if (FocusedWidget && FocusedWidget->Type == DROPDOWNLIST)
		{
			if (a == 0) dropdownlist_select_nextitem((DropdownList*)FocusedWidget);	
			if (b == 0) dropdownlist_select_previtem((DropdownList*)FocusedWidget);	
		}
		//Refresh = 1;//tell them we need to redraw the screen
		
	}
	
}