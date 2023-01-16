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
		
		widget_update_value_int((Widget*)&gL_Label5, EncoderCount);
		
		//if(a == 0) listbox_append_row(&gL_Listbox1, "AAAAAAAAAAAAA");
		//if (b == 0) listbox_remove_row(&gL_Listbox1, 0);
		Refresh = 1;//tell them we need to redraw the screen
		//sprintf(gL_Label5.Text, "%d", EncoderCount);
		//gL_Label5.RedrawMe = 1;
		
	}
	
}