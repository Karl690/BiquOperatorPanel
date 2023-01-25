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

uint8_t* MemoryDumpDisplayAddress = NULL;

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
	gL_Listbox1.DispMode = DISPLAYMODE_Raw_ASCII;
	listbox_display_memorydata(&gL_Listbox1, MemoryDumpDisplayAddress);
}


void ShiftbitWritetestButtonEvent(void* sender, uint16_t x, uint16_t y)
{
	
}
void displayCalibrationButtonEvent(void* sender, uint16_t x, uint16_t y)
{
	MemoryDumpDisplayAddress = getCalibrationDataBlockAddress(); //get current soapstring address
	gL_Listbox1.DispMode = DISPLAYMODE_HEX;
	listbox_display_memorydata(&gL_Listbox1, MemoryDumpDisplayAddress);
}

void PageDownButtonEvent(void* sender, uint16_t x, uint16_t y)
{
	if (MemoryDumpDisplayAddress == NULL) return; //do nothing
	
	MemoryDumpDisplayAddress += listbox_get_charsofline(&gL_Listbox1); // increase the number of characters in a line for Lisbox becasue it is different according to display mode.
	listbox_display_memorydata(&gL_Listbox1, MemoryDumpDisplayAddress);
}
void PageUpButtonEvent(void* sender, uint16_t x, uint16_t y)
{
	if (MemoryDumpDisplayAddress == NULL) return; //do nothing
	
	MemoryDumpDisplayAddress -= listbox_get_charsofline(&gL_Listbox1); // decrease get the number of characters in a line for Lisbox becasue it is different according to display mode.
	listbox_display_memorydata(&gL_Listbox1, MemoryDumpDisplayAddress);
}
void SwitchSHButtonEvent(void* sender, uint16_t x, uint16_t y)
{
	glBtnSwitchSH.Checked = glBtnSwitchSH.Checked ==1?0:1;
	glBtnSwitchSH.RedrawMe = 1;
}