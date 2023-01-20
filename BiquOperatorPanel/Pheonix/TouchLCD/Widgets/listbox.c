#include "../GUI/gui.h"
#include "listbox.h"
#include "Panel.h"

uint16_t* list_row_buffer = NULL;
void listbox_destory(Listbox* obj)
{
	free(obj);
}
void listbox_update(Listbox* obj)
{
	//update corner points.
	obj->CurrentDrawYPos = 0;
	uint16_t row_height = obj->Font->Height + 4;
	list_row_buffer = (uint16_t*)malloc(row_height * obj->Size.width * 2);
}
void listbox_remove_row(Listbox* obj, uint16_t index)
{
	if (index == 0 && obj->RowCount == 1)
	{
		obj->RowCount = 0;
		obj->RedrawMe = 1;
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
			strcpy(obj->RowData[i - 1], obj->RowData[i]);
		}
		//add the data at the last element
		strcpy(obj->RowData[LISTBOX_MAX_ROWS - 1], data);
	}
	else
	{	
		strcpy(obj->RowData[obj->RowCount], data);
		obj->RowCount++;
	}
	obj->RedrawMe = 1;
}
void listbox_on_paint(Listbox* obj, Point offset, Color16  backcolor)
{	
	obj->RedrawMe = 0;
	Point pos = { offset.x + obj->Location.x, offset.y + obj->Location.y };
	GUI_FillRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, obj->BackColor);
	if (obj->BorderWidth > 0)
	{
		GUI_DrawRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, obj->BorderColor);
	}
	
	uint16_t row_height = obj->Font->Height + 4;
	uint16_t row_bottom = obj->CurrentDrawYPos;
	uint16_t row_index = 0;
	while (1)
	{
		if (row_index >= obj->RowCount) break;
		if (row_bottom >= obj->Size.height) break;
		if (row_bottom >= 0) 
		{
			if (row_index % 2 == 0)
			{
				GUI_FillRect(pos.x,
					pos.y +row_bottom, 
					pos.x + obj->Size.width,
					pos.y+row_bottom + row_height, 
					row_index %2 == 1? obj->RowEvenColor: obj->RowOddColor);	
			}
			GUI_DrawString(pos.x + 2,
				pos.y + 2 + row_bottom,
				obj->RowData[row_index],
				obj->Font,
				obj->ForeColor,
				row_index %2 == 1? obj->RowEvenColor: obj->RowOddColor);
		}
		row_bottom += row_height;
		row_index++;
	}
}

