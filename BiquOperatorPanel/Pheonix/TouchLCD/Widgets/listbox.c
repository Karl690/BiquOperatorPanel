#include "../GUI/gui.h"
#include <ctype.h>
#include "listbox.h"
#include "Panel.h"


uint8_t DrawMemoryDumpflag = 0;//used to signal that it is time to add 12 lines formatted to this listbox
int16_t FirstLineToDisplay = 0;//set the default first line to display at 0,
void listbox_destory(Listbox* obj)
{
	free(obj);
}
void listbox_update(Listbox* obj)
{
	//update corner points.
	obj->FirstLineToDisplay = 0;
}

void listbox_clear(Listbox* obj)
{
	obj->RowCount = 0;
	obj->RedrawMe = 1;
	FirstLineToDisplay = 0;
}

void listbox_change_display_mode(Listbox* obj, uint8_t mode)
{
	obj->DispMode = mode;
	obj->RedrawMe = 1;
}
void listbox_remove_row(Listbox* obj, uint16_t index)
{
	if (index == 0 && obj->RowCount == 1)
	{
		obj->RowCount = 0;
		obj->RedrawMe = 1;
		FirstLineToDisplay = 0;
		return;
		
	}
	if (index >= obj->RowCount) return;
	uint16_t i;
	for (i = index + 1; i < obj->RowCount; i++)
	{
		strcpy(obj->RowData[i - 1], obj->RowData[i]);
	}
	obj->RowCount--;
	obj->RedrawMe = 1;
}
void listbox_append_row(Listbox* obj, char* data)
{
	if (obj->RowCount > LISTBOX_MAX_ROWS)
	{	
		//remove the first element
		for (uint16_t i = 1; i < LISTBOX_MAX_ROWS; i++)
		{
			strcpy((char*)obj->RowData[i - 1], obj->RowData[i]);
		}
		//add the data at the last element
		strcpy((char*)obj->RowData[LISTBOX_MAX_ROWS - 1], data);
	}
	else
	{	
		strcpy((char*)obj->RowData[obj->RowCount], data);
		obj->RowCount++;
	}
	obj->RedrawMe = 1;
}
void listbox_append_row_buffer(Listbox* obj, uint8_t* data, uint16_t size) //size must be smaller than WIDGET_MAX_TEXT_LENGTH
{
	if (obj->RowCount > LISTBOX_MAX_ROWS)
	{	
		//remove the first element
		for (uint16_t i = 1; i < LISTBOX_MAX_ROWS; i++)
		{
			memcpy(obj->RowData[i - 1], obj->RowData[i], size);
		}
		//add the data at the last element
		memcpy(obj->RowData[LISTBOX_MAX_ROWS - 1], data, size);
	}
	else
	{	
		memcpy(obj->RowData[obj->RowCount], data, size);
		obj->RowCount++;
	}
	obj->RedrawMe = 1;
}
void listbox_on_paint(Listbox* obj, Point offset, Color16  backcolor)
{	
	obj->RedrawMe = 0;//clear redraw flag
	Point pos = { offset.x + obj->Location.x, offset.y + obj->Location.y };//pointToSCREEN()
	//fill in background
	GUI_FillRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, obj->BackColor);
	//if boarder is valid, i.e width>0, we can draw the border now
	if (obj->BorderWidth > 0)
	{
		GUI_DrawRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, obj->HasFocus?obj->FocusBorderColor: obj->BorderColor);
	}
	uint16_t row_height = obj->Font->Height + 4;//font height in pixels
	int16_t row_bottom = pos.y + obj->BorderWidth + obj->Padding.top; //first pixel in the display, however we need to offset by border and padd
	uint16_t NuberOfLinesToDisplay = (obj->Size.height / row_height);
	uint16_t Padding = obj->BorderWidth;//marke the area inside the border where we can start drawing
	char buf[WIDGET_MAX_TEXT_LENGTH] = { 0 };
	uint16_t LeftSideLimit  = pos.x + obj->BorderWidth + obj->Padding.left; //drawing space
	uint16_t RightSideLimit = pos.x + obj->Size.width - (obj->BorderWidth + obj->Padding.right); //can draw betwen these limits
	for (int rowCount = 0; rowCount < NuberOfLinesToDisplay;rowCount++)
	{
		if ((rowCount + obj->FirstLineToDisplay) >= obj->RowCount) break;//past the end of the list, so leave
		if (rowCount % 2 == 1)
		{//odd rows
			GUI_FillRect(LeftSideLimit,	row_bottom,//left start for this line rectantle
					RightSideLimit, row_bottom + row_height,  //right 
							obj->RowEvenColor);	
		}	
		GUI_DrawString(LeftSideLimit, row_bottom,//point to start drawing from
			obj->RowData[rowCount+obj->FirstLineToDisplay],
			obj->Font,
			obj->ForeColor,
			rowCount %2 == 1? obj->RowEvenColor: obj->BackColor);
		row_bottom += row_height;
	}
}

//move a line up
void listbox_move_up_line(Listbox* obj) 
{
	if (obj->FirstLineToDisplay < 1)return;
	FirstLineToDisplay--;
	obj->RedrawMe = 1;
}
//move a line down
void listbox_move_down_line(Listbox* obj) 
{
	if (obj->FirstLineToDisplay == obj->RowCount )return;
	FirstLineToDisplay++;
	obj->RedrawMe = 1;
}


//get the number of characters for a line
uint16_t listbox_get_charsofline(Listbox* obj) 
{
	uint16_t DisplayDataLength = 40;//WIDGET_MAX_TEXT_LENGTH;
	if (obj->DispMode == DISPLAYMODE_Raw_ASCII) DisplayDataLength = 32; //raw ascii, only 32 bytes per line, plus address
	else if(obj->DispMode ==  DISPLAYMODE_HEX)		DisplayDataLength = 8; //hex ascii, only 8 bytes per line, plus address
	return DisplayDataLength;
}
void listbox_set_memoryaddress(Listbox* obj, uint8_t* address)
{
	//set the memory address to Listbox
	obj->FirstMemoryAddressToDispay = address;
	obj->CurrentMemoryAddressToDisplay = address;
	listbox_display_memorydata(obj, address);
}
void listbox_display_memorydata(Listbox* obj, uint8_t* memoryaddress)
{
	obj->CurrentMemoryAddressToDisplay = memoryaddress; //set the current memory address to this object
	//displays memory contents in either ascii , raw ascii, hex
	//t the real address for that
	obj->RowCount = 0; // clear list's array .
	
	uint8_t* buf = NULL;
	uint16_t DisplayDataLength = listbox_get_charsofline(obj); // get the number of charactor in a line.
	
	uint8_t* WorkingAddress = memoryaddress; //get the starting pointer
	for (int count = 0; count < LISTBOX_MAX_ROWS; count++)  //display 12 lines at a time 
	{
		buf = &obj->RowData[count]; 
		memset(buf, 0, WIDGET_MAX_TEXT_LENGTH); //reset the buffer.
		switch (obj->DispMode)
		{
		case DISPLAYMODE_ASCII     : 
		case DISPLAYMODE_Raw_ASCII : {
				//strncpy(buf, WorkingAddress, DisplayDataLength); break;//just 32 char of ascii
				for (uint16_t i = 0; i < DisplayDataLength; i++) {
					if (WorkingAddress[i] == 0 || WorkingAddress[i] == 0xff) break; // this means the end of string
					if(isascii(WorkingAddress[i])) buf[i] = WorkingAddress[i]; //if it is asscii charactor, put the letter
					else buf[i] = '?'; //otherwise , '?'
				}
			}
			break;
		case DISPLAYMODE_HEX       : buffer2hexstring(WorkingAddress, buf, DisplayDataLength); break;//hex dump 5 bytes at a time		}
		case DISPLAYMODE_VARPAIR	: 
			{
				DisplayDataLength = 0;
				sprintf(buf, "%08X  ", (uint32_t)WorkingAddress); //set the address of Memory
				buf += 10; //added 8 charactor of address string and two space  [000000  ]
				for (uint16_t i = 0; i < WIDGET_MAX_TEXT_LENGTH -10; i++)
				{	
					if (*(WorkingAddress + i) == ';')  //find out the ';'
					{
						DisplayDataLength++;
						break;
					}
					
					buf[i] = *(WorkingAddress + i);
					DisplayDataLength++;
				}
			break;
			}
		}
		obj->RowCount++; //increase the row count
		//listbox_append_row(obj, buf); //add to listbox for display
		WorkingAddress += DisplayDataLength;
	}
	obj->RedrawMe = 1;
	//Refresh = 0; //leave flag that we have changed a widget and refresh should be called
}

//go foreward as one line
void listbox_memorydata_go_foreward(Listbox* obj)
{
	uint16_t DisplayDataLength = listbox_get_charsofline(obj); // get the number of charactor in a line.
	uint8_t* nextAddress = obj->CurrentMemoryAddressToDisplay + DisplayDataLength;
	if (*nextAddress == 0xff) {
		//go to the first address
		nextAddress = obj->FirstMemoryAddressToDispay;
	}
	listbox_display_memorydata(obj, nextAddress);
}
//go backward as one line
void listbox_memorydata_go_backward(Listbox* obj)
{
	uint16_t DisplayDataLength = listbox_get_charsofline(obj); // get the number of charactor in a line.
	uint8_t* nextAddress = obj->CurrentMemoryAddressToDisplay - DisplayDataLength;
	if (*nextAddress == 0xff) return; // nothing because it is not data range
	listbox_display_memorydata(obj, nextAddress);
	
}