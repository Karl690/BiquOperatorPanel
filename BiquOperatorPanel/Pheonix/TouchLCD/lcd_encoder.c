#include "main.h"
#include "lcd.h"
#include "GUI/gui.h"

uint8_t FiredEncodeButtonEvent = 0;
void EncoderButtonDownEvent()
{
	FiredEncodeButtonEvent = 1;
}

int counter = 0;
int encoderSt = 0; 

void EncoderWheelMove()
{ 
	int a = GPIO_GetLevel(LCD_ENCA_PIN);
	int b = GPIO_GetLevel(LCD_ENCB_PIN);
	int st = (b << 1) | a;
	if (encoderSt != st)
	{
		if ((encoderSt == 0 && st == 2) || (encoderSt == 1 && st == 0) 
			|| (encoderSt == 2 && st == 3) || (encoderSt == 3 && st == 1)) counter--;
		else counter++;
		encoderSt = st;
	}
}