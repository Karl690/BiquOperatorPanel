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


uint8_t* MemoryDumpDisplayAddress = NULL;

void initializeSoapNudList()
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
	SoapNudsList[10] = &glNudVars10;
	SoapNudsList[11] = NULL; //the end
}


void glBtnPlus_TouchEvent(void* sender, long unsigned int x, long unsigned int y)
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
void glBtnMinus_TouchEvent(void* sender, long unsigned int x, long unsigned int y)
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

void glBtnSave_TouchEvent(void* sender, long unsigned int x, long unsigned int y)
{
	
}

void glBtnApply_TouchEvent(void* sender, long unsigned int x, long unsigned int y)
{
	
}

void eraseFlashButonEvent(void* sender, long unsigned int x, long unsigned int y)
{
	BlinkStartWidget(sender, 5, 5); //blink 5 times every 0.5s
	eraseStorage();
}
void LoadSoapstringButtonEvent(void* sender, long unsigned int x, long unsigned int y)
{
	BlinkStartWidget(sender, 5, 10); //blink 5 times every 0.5s
	
	LoadSoapStringFromStorage();
}
void SaveSoapstringButtonEvent(void* sender, long unsigned int x, long unsigned int y)
{
	BlinkStartWidget(sender, 5, 5); //blink 5 times every 0.5s
	
	WriteSoapStringToStorage();
	//lvana 
	//blinkThisButton(*sender,5,5);//blink the button to acknowledge it was pressed.
}
void displaySoapstringButtonEvent(void* sender, long unsigned int x, long unsigned int y)
{
	BlinkStartWidget(sender, 5, 5); //blink 5 times every 0.5s
	
	panel_set_focus_widget((Widget*)&gL_Listbox1, 1); // focus the Listbox
	MemoryDumpDisplayAddress = FindCurrentSoapstringAddress() + 1; //get current soapstring address , because the first byte is 0x04, it add 1.
	if (MemoryDumpDisplayAddress < (uint8_t*)SOAPSTRING_STARTADDRESS) return; //do not exist soapstring in storage
	
	gL_Listbox1.DispMode = glDropdownDisplayMode.SelectedIndex;// 0:DISPLAYMODE_HEX, 1: DISPLAYMODE_Raw_ASCII 2: VARPAIR;
	
	listbox_set_memoryaddress(&gL_Listbox1, MemoryDumpDisplayAddress);
}

void ChangeDisplayModeListEvent(void* sender)
{
	panel_set_focus_widget((Widget*)&gL_Listbox1, 1); // focus the Listbox
	BlinkStartWidget(sender, 5, 5); //blink 5 times every 0.5s
	gL_Listbox1.DispMode = glDropdownDisplayMode.SelectedIndex; // 0:DISPLAYMODE_ASCII, 1: DISPLAYMODE_Raw_ASCII 2: DISPLAYMODE_HEX, 3: DISPLAYMODE_VARPAIR;
	
	listbox_display_memorydata(&gL_Listbox1, gL_Listbox1.CurrentMemoryAddressToDisplay); //display with list's memory address
}

void ShiftbitWritetestButtonEvent(void* sender, long unsigned int x, long unsigned int y)
{
	
}
void displayCalibrationButtonEvent(void* sender, long unsigned int x, long unsigned int y)
{
	panel_set_focus_widget((Widget*)&gL_Listbox1, 1); // focus the Listbox
	MemoryDumpDisplayAddress = getCalibrationDataBlockAddress(); //get current soapstring address	
	if (MemoryDumpDisplayAddress == NULL) return; //do not exist calibration data in storage
	gL_Listbox1.DispMode = DISPLAYMODE_HEX; // 0:DISPLAYMODE_HEX, 1: DISPLAYMODE_Raw_ASCII 2: VARPAIR;
	listbox_set_memoryaddress(&gL_Listbox1, MemoryDumpDisplayAddress);
}

void PageDownListbox(Listbox* obj)
{
	listbox_memorydata_go_foreward(obj);
}
void PageUpListbox(Listbox* obj)
{
	listbox_memorydata_go_backward(obj);
}
