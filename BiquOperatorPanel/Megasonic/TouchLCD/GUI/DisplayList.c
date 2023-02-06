#include "global.h"
#include "gui.h"
#include "displaylist.h"
#include "display.h"

char* AtofVariable="CmdQue[3] Variables";
char* displayTestString2="12345";
//	{(uint32_t)&_gs.CanRxCount1,         "CnRx Cnt", FUNC_INT, 		BLUE,	MAGENTA, 	0},
char TestString[] ="test String 12345";

float MaxFloatBarValue = 3.3;
float BarValue = 2.8;
LcdVariableInfo LcdVarsTable[] = {
	{(uint32_t)&HeartBeat,               	"HB      ", FUNC_INT32,		COLOR_WHITE,	COLOR_MAGENTA, 	0},	
	{(uint32_t)&BarValue,					"BAR01	 ", FUNC_BAR_FLOAT, COLOR_WHITE, COLOR_MAGENTA, &MaxFloatBarValue},	
	{(uint32_t)&BarValue, "BAR01	 ", FUNC_BAR_FLOAT, COLOR_WHITE, COLOR_RED, &MaxFloatBarValue},	
	{(uint32_t)&BarValue, "BAR02	 ", FUNC_BAR_FLOAT, COLOR_WHITE, COLOR_GREEN, &MaxFloatBarValue},	
	{(uint32_t)&BarValue, "BAR03	 ", FUNC_BAR_FLOAT, COLOR_WHITE, COLOR_BLUE, &MaxFloatBarValue},	
	{(uint32_t)&BarValue, "BAR04	 ", FUNC_BAR_FLOAT, COLOR_WHITE, COLOR_DARKRED, &MaxFloatBarValue},	
	{(uint32_t)&BarValue, "BAR05	 ", FUNC_BAR_FLOAT, COLOR_WHITE, COLOR_DARKBLUE, &MaxFloatBarValue},	
	{(uint32_t)&BarValue, "BAR06	 ", FUNC_BAR_FLOAT, COLOR_WHITE, COLOR_DARKVIOLET, &MaxFloatBarValue},	
	{(uint32_t)&BarValue, "BAR07	 ", FUNC_BAR_FLOAT, COLOR_WHITE, COLOR_GOLD, &MaxFloatBarValue},	
	{(uint32_t)&BarValue, "BAR08	 ", FUNC_BAR_FLOAT, COLOR_WHITE, COLOR_PALETURQUOISE, &MaxFloatBarValue},	
	{(uint32_t)&BarValue, "BAR09	 ", FUNC_BAR_FLOAT, COLOR_WHITE, COLOR_SPRINGGREEN, &MaxFloatBarValue},	
	{(uint32_t)&BarValue, "BAR10	 ", FUNC_BAR_FLOAT, COLOR_WHITE, COLOR_YELLOW, &MaxFloatBarValue},	
	{(uint32_t)&BarValue, "BAR11	 ", FUNC_BAR_FLOAT, COLOR_WHITE, COLOR_TEAL, &MaxFloatBarValue},	
	{(uint32_t)0,              			 "--------", FUNC_INT, 		COLOR_TOMATO,	COLOR_MAGENTA, 	0},

};

