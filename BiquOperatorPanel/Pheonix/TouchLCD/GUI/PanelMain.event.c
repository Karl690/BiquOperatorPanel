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
	if (!currentSoapStringAddress) currentSoapStringAddress = getSoapstringBlockAddress(); //if Sapstring's address is NULL, get the real address for that
	listbox_clear(&gL_Listbox1); 
	
	char buf[WIDGET_MAX_TEXT_LENGTH] = { 0 };
	uint16_t charsOfLine = !glBtnSwitchSH.Checked ? 32 : 8; // in case of ASCII mode, it should be 32 charactor for each row, otherwise(hex mode), it should be 8 charactor.
	for (int idx = 0; idx < SOAPSTRING_BLOCKSIZE; idx += charsOfLine) {
		if (!glBtnSwitchSH.Checked) //this is ASCII MODE
			strncpy(buf, (uint8_t*)(currentSoapStringAddress + idx), charsOfLine);
		else 
			buffer2hexstring((uint8_t*)(currentSoapStringAddress + idx), buf, charsOfLine);
		listbox_append_row(&gL_Listbox1, buf);
		if (gL_Listbox1.RowCount >= LISTBOX_MAX_ROWS) break; //escape if list's buffer is over.
	}
}
void ShiftbitWritetestButtonEvent(void* sender, uint16_t x, uint16_t y)
{
	
}
void displayCalibrationButtonEvent(void* sender, uint16_t x, uint16_t y)
{
	if (!currentCalibrationAddress) currentCalibrationAddress = getCalibrationDataBlockAddress(); //if current calibration address is NULL, get the address of Calibration in storage.
	
	listbox_clear(&gL_Listbox1); // clear the listbox
	char buf[WIDGET_MAX_TEXT_LENGTH] = { 0 };
	uint16_t charsOfLine = !glBtnSwitchSH.Checked ? 32 : 8; // in case of ASCII mode, it should be 32 charactor for each row, otherwise(hex mode), it should be 8 charactor.
	for (uint16_t idx = 0; idx < CALIBRATIONDATA_BLOCKSIZE; idx += charsOfLine) { //added 8 charator in listbox as one row.
		if (!glBtnSwitchSH.Checked) //this is ASCII MODE
			strncpy(buf, (uint8_t*)(currentCalibrationAddress + idx), charsOfLine);
		else {
			buffer2hexstring((uint8_t*)(currentCalibrationAddress + idx), buf, charsOfLine); //convert buffer to hex string.
		}
		listbox_append_row(&gL_Listbox1, buf); // append the buffer 
		if (gL_Listbox1.RowCount >= LISTBOX_MAX_ROWS) break; //escape if list's buffer is over.
	}
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