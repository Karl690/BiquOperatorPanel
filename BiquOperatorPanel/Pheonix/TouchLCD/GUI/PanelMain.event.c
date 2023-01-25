#include "configure.h"
#include "main.h"
#include "global.h"


#include "../Widgets/Widget.h"
#include "../Widgets/panel.h"
#include "../Widgets/label.h"
#include "../Widgets/edit.h"
#include "../Widgets/button.h"
#include "../Widgets/listbox.h"
#include "../Widgets/tabcontrol.h"
#include "../Widgets/panel.h"
#include "../Widgets/numeric.h"
#include "../Widgets/dropdownlist.h"
#include "PanelMain.designer.h"
#include "../lcd_touch.h"

void glBtnPlus_TouchEvent(void* sender, uint16_t x, uint16_t y)
{
	if (FocusedWidget && FocusedWidget->Type == NUMERIC)
	{
		numeric_increment((Numeric*)FocusedWidget);
	}
	else if (FocusedWidget && FocusedWidget->Type == DROPDOWNLIST)
	{
		dropdownlist_select_nextitem((DropdownList*)FocusedWidget);
	}
}
void glBtnMinus_TouchEvent(void* sender, uint16_t x, uint16_t y)
{
	if (FocusedWidget && FocusedWidget->Type == NUMERIC)
	{
		numeric_decrement((Numeric*)FocusedWidget);
	}
	else if (FocusedWidget && FocusedWidget->Type == DROPDOWNLIST)
	{
		dropdownlist_select_previtem ((DropdownList*)FocusedWidget);
	}
}

void glBtnSave_TouchEvent(void* sender, uint16_t x, uint16_t y)
{
	
}

void glBtnApply_TouchEvent(void* sender, uint16_t x, uint16_t y)
{
	
}

void eraseFlashButonEvent(void* sender, uint16_t x, uint16_t y)
{
}
void displaySoapstringButtonEvent(void* sender, uint16_t x, uint16_t y)
{
	MemoryDumpDisplayAddress = getSoapstringBlockAddress(); //get current soapstring address
	displayMemoryData(DISPLAYMODE_Raw_ASCII);
}

void displayMemoryData(uint16_t displayMode)
{//displays memory contents in either ascii , raw ascii, hex
	//t the real address for that
	listbox_clear(&gL_Listbox1); 
	
	char buf[WIDGET_MAX_TEXT_LENGTH] = { 0 };
	uint16_t DisplayDataLength = 50;
	if (displayMode == DISPLAYMODE_Raw_ASCII)DisplayDataLength = 32;//raw ascii, only 32 bytes per line, plus address
	if (displayMode == DISPLAYMODE_HEX)DisplayDataLength = 8; //hex ascii, only 8 bytes per line, plus address
	uint8_t* WorkingAddress = MemoryDumpDisplayAddress;//get the starting pointer
	for (int count = 0; count < 12; count++)  //display 12 lines at a time 
	{
		switch (displayMode)
		{
		case DISPLAYMODE_ASCII     :strncpy(buf, WorkingAddress, DisplayDataLength); break;//formatted string
		case DISPLAYMODE_Raw_ASCII :strncpy(buf, WorkingAddress, DisplayDataLength); break;//just 32 char of ascii
		case DISPLAYMODE_HEX       :buffer2hexstring(WorkingAddress, buf, DisplayDataLength); break;//hex dump 5 bytes at a time		}
		}
		listbox_append_row(&gL_Listbox1, buf);//add to listbox for display
	}
	Refresh = 0;//leave flag that we have changed a widget and refresh should be called
}

void ShiftbitWritetestButtonEvent(void* sender, uint16_t x, uint16_t y)
{
	
}
void displayCalibrationButtonEvent(void* sender, uint16_t x, uint16_t y)
{
	MemoryDumpDisplayAddress = getCalibrationDataBlockAddress(); //get current soapstring address
	displayMemoryData(DISPLAYMODE_HEX);
}

void PageDownButtonEvent(void* sender, uint16_t x, uint16_t y)
{
	listbox_move_down_line(&gL_Listbox1);
}
void PageUpButtonEvent(void* sender, uint16_t x, uint16_t y)
{
	listbox_move_up_line(&gL_Listbox1);
}
void SwitchSHButtonEvent(void* sender, uint16_t x, uint16_t y)
{
	glBtnSwitchSH.Checked = glBtnSwitchSH.Checked ==1?0:1;
	glBtnSwitchSH.RedrawMe = 1;
}