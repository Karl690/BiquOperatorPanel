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
#include "PanelMain.event.h"
#include "../lcd_touch.h"

Numeric* SoapNudsList[30] = { 0 };
uint8_t* MemoryDumpDisplayAddress = NULL;

void initialize_SoapNudList()
{
	//assign the address of Nuds in Vars tab into list
	SoapNudsList[0] = &glNudVars00;
	SoapNudsList[1] = &glNudVars01;
	SoapNudsList[2] = &glNudVars02;
	SoapNudsList[3] = &glNudVars03;
	SoapNudsList[4] = &glNudVars04;
	SoapNudsList[5] = &glNudVars05;
	SoapNudsList[6] = &glNudVars06;
	SoapNudsList[7] = &glNudVars07;
	SoapNudsList[8] = &glNudVars08;
	SoapNudsList[9] = &glNudVars09;
	SoapNudsList[10] = NULL; //the end
}
	
void FindNextFlashSaveAddress()
{
	
}
//write the Nude name and value into Soap string
void WriteSoapValuePair(uint16_t pairIndex,  uint32_t address) 
{
	if (!SoapNudsList[pairIndex])  return;
	char stringValuePair[WIDGET_MAX_TEXT_LENGTH] = { 0 };
	
	sprintf(stringValuePair, "%s,%.3f;", SoapNudsList[pairIndex]->Name, SoapNudsList[pairIndex]->Value); // format: name,value;
	strcpy(address, stringValuePair); // connect the current nud name and value to soapstring.
}

void LoadSoapValuePare(uint16_t pairIndex, uint16_t address) 
{
	char stringValuePair[WIDGET_MAX_TEXT_LENGTH] = { 0 };
	
}


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
	else if (FocusedWidget && FocusedWidget->Type == LISTBOX)
	{
		PageUpListbox((Listbox*)FocusedWidget);
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
		dropdownlist_select_previtem((DropdownList*)FocusedWidget);
	}
	else if (FocusedWidget && FocusedWidget->Type == LISTBOX)
	{
		PageDownListbox((Listbox*)FocusedWidget);
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
	panel_set_focus_widget(&gL_Listbox1, 1); // focus the Listbox
	MemoryDumpDisplayAddress = getSoapstringBlockAddress(); //get current soapstring address
	gL_Listbox1.DispMode = DISPLAYMODE_Raw_ASCII;
	listbox_display_memorydata(&gL_Listbox1, MemoryDumpDisplayAddress);
}


void ShiftbitWritetestButtonEvent(void* sender, uint16_t x, uint16_t y)
{
	
}
void displayCalibrationButtonEvent(void* sender, uint16_t x, uint16_t y)
{
	panel_set_focus_widget(&gL_Listbox1, 1); // focus the Listbox
	MemoryDumpDisplayAddress = getCalibrationDataBlockAddress(); //get current soapstring address	
	gL_Listbox1.DispMode = DISPLAYMODE_HEX;
	listbox_display_memorydata(&gL_Listbox1, MemoryDumpDisplayAddress);
}

void PageDownListbox(Listbox* obj)
{
	if (MemoryDumpDisplayAddress == NULL) return; //do nothing
	
	MemoryDumpDisplayAddress += listbox_get_charsofline(obj) * LISTBOX_MAX_ROWS; // increase the addres for one page of Lisbox becasue it is different according to display mode.
	listbox_display_memorydata(obj, MemoryDumpDisplayAddress);
}
void PageUpListbox(Listbox* obj)
{
	if (MemoryDumpDisplayAddress == NULL) return; //do nothing
	
	MemoryDumpDisplayAddress -= listbox_get_charsofline(obj) * LISTBOX_MAX_ROWS; // decrease the addres for one page of Lisbox becasue it is different according to display mode.
	listbox_display_memorydata(obj, MemoryDumpDisplayAddress);
}
