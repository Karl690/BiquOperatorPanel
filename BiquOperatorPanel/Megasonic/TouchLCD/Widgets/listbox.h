#pragma once
#include <stdint.h>
#include "widget.h"
#include "panel.h"

#define LISTBOX_MAX_ROWS 12

typedef struct tagListbox
{
	//Commone properties
	WIDGETTYPE Type;
	char Name[WIDGET_MAX_TEXT_LENGTH];
	uint8_t RedrawMe; //0: Not redraw, 1: need to Redraw
	uint8_t Visible;//visible property, set to 0 to avoid repainting
	uint8_t HasFocus;
	uint8_t Checked;
	Point Location;//location in reference to the parent container in Pixels.
	Size	Size;	//XY size in Pixels
	Color16 BackColor;
	Color16 ForeColor;
	Color16 FocusBackColor;
	Color16 FocusForeColor;
	uint16_t BorderWidth;
	Color16 BorderColor;
	Color16 FocusBorderColor;
	PADDING		Padding;//dead space required in pixel, in between bounds and graphics elements
	
	char Text[WIDGET_MAX_TEXT_LENGTH];//max line length
	Font* Font;//default font
	TEXT_ALIGN	TextAlign;	//sets position of text to be drawn, not sure it works in this obj.

	void* Parent;//parent container of this obj
	CallbackTouchEventFunction	Event_Down;
	CallbackTouchEventFunction	Event_Hold;
	CallbackTouchEventFunction	Event_Up;
	CallbackEncoderEventFunction Event_Encoder;
	
	//Listbox properties		
	Color16 RowOddColor;//
	Color16 RowEvenColor;//allows contrast display by alternating the back color of each row
	uint8_t RowData[LISTBOX_MAX_ROWS][WIDGET_MAX_TEXT_LENGTH];
	int16_t FirstLineToDisplay; //when scrolling,this is the first line in the list to display
	uint16_t RowCount;//number of Items in the list
	uint8_t	DispMode; //specify the display mdoe (Ascill or Hex) 
	uint8_t*	CurrentMemoryAddressToDisplay;// Memory address to display, it changed when scroll
	uint8_t*	FirstMemoryAddressToDispay;//by display function it set.
	
}Listbox;

void listbox_destory(Listbox* obj);
void listbox_update(Listbox* obj);
void listbox_on_paint(Listbox* obj, Point offset, Color16  backcolor);
void listbox_clear(Listbox* obj);
void listbox_append_row(Listbox* obj, char*);	//append the string
void listbox_append_row_buffer(Listbox* obj, uint8_t* data, uint16_t size); // append the binary data
void listbox_remove_row(Listbox* obj, uint16_t index);

void listbox_move_up_line(Listbox* obj);
void listbox_move_down_line(Listbox* obj);

uint16_t listbox_get_charsofline(Listbox* obj);
void listbox_set_memoryaddress(Listbox* obj, uint8_t* address);
void listbox_display_memorydata(Listbox* obj, uint8_t* memoryaddress);

void listbox_memorydata_go_backward(Listbox* obj);
void listbox_memorydata_go_foreward(Listbox* obj);