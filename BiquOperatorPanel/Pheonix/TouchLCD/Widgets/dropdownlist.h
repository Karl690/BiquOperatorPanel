#pragma once
#include <stdint.h>
#include "widget.h"
#include "panel.h"

#define COMBO_MAX_ITEMS	10
typedef enum
{
	DROPDOWNLIST_STRING,
	DROPDOWNLIST_INT,
	DROPDOWNLIST_FLOAT,
}DROPDOWNLIST_TYPE;
typedef struct tagDropdownList
{
	//Commone properties
	WIDGETTYPE Type;
	char Name[WIDGET_MAX_TEXT_LENGTH];
	uint8_t RedrawMe; //0: Not redraw, 1: need to Redraw
	uint8_t Visible;
	uint8_t HasFocus;
	uint8_t Checked;
	Point Location;
	Size	Size;	
	Color16 BackColor;
	Color16 ForeColor;
	Color16 FocusBackColor;
	Color16 FocusForeColor;
	uint16_t BorderWidth;
	Color16 BorderColor;
	Color16 FocusBorderColor;
	PADDING		Padding;
	
	char Text[WIDGET_MAX_TEXT_LENGTH];
	Font* Font;
	TEXT_ALIGN	TextAlign;	

	void* Parent;
	CallbackTouchEventFunction	Event_Down;
	CallbackTouchEventFunction	Event_Hold;
	CallbackTouchEventFunction	Event_Up;
	
	
	//Label properties
	uint16_t CornerRadius;
	Point	CornerPoints[9];
	DROPDOWNLIST_TYPE ValueType;
	char	Values[COMBO_MAX_ITEMS][WIDGET_MAX_TEXT_LENGTH];
	uint16_t	SelectedIndex;
	uint16_t	ValuesNum;
}DropdownList;
DropdownList* combo_init();
void dropdownlist_destory(DropdownList* obj);
void dropdownlist_on_paint(DropdownList* obj, Point offset, Color16  backcolor);

void dropdownlist_add_item(DropdownList* obj, char* item);
void dropdownlist_remove_item(DropdownList* obj, uint16_t index);
void dropdownlist_select_item(DropdownList* obj, uint16_t index);
uint16_t dropdownlist_get_seletected_index(DropdownList* obj);
void dropdownlist_select_nextitem(DropdownList* obj);
void dropdownlist_select_previtem(DropdownList* obj);