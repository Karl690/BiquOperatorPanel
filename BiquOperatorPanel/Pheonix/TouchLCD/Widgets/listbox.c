#include "../GUI/gui.h"
#include "listbox.h"
#include "Panel.h"

uint16_t* list_row_buffer = NULL;
void listbox_destory(Listbox* listbox)
{
	free(listbox);
}
void listbox_update(Listbox* listbox)
{
	//update corner points.
	listbox->CurrentDrawYPos = 0;
	uint16_t row_height = listbox->Font->Height + 4;
	list_row_buffer = (uint16_t*)malloc(row_height * listbox->Size.width * 2);
}
void listbox_remove_row(Listbox* listbox, uint16_t index)
{
	if (index == 0 && listbox->RowCount == 1)
	{
		listbox->RowCount = 0;
		listbox->RedrawMe = 1;
		return;
		
	}
	if (index >= listbox->RowCount) return;
	uint16_t i;
	for (i = index + 1; i < listbox->RowCount; i++)
	{
		strcpy(listbox->RowData[i - 1], listbox->RowData[i]);
	}
	listbox->RowCount--;
	listbox->RedrawMe = 1;
}
void listbox_append_row(Listbox* listbox, char* data)
{
	if (listbox->RowCount > LISTBOX_MAX_ROWS)
	{	
		//remove the first element
		for (uint16_t i = 1; i < LISTBOX_MAX_ROWS; i++)
		{
			strcpy(listbox->RowData[i - 1], listbox->RowData[i]);
		}
		//add the data at the last element
		strcpy(listbox->RowData[LISTBOX_MAX_ROWS - 1], data);
	}
	else
	{	
		strcpy(listbox->RowData[listbox->RowCount], data);
		listbox->RowCount++;
	}
	listbox->RedrawMe = 1;
}
void listbox_on_paint(Listbox* listbox, Point offset, Color16  backcolor)
{	
	listbox->RedrawMe = 0;
	Point pos = { offset.x + listbox->Location.x, offset.y + listbox->Location.y };
	GUI_FillRect(pos.x, pos.y, pos.x + listbox->Size.width, pos.y + listbox->Size.height, listbox->BackColor);
	if (listbox->BorderWidth > 0)
	{
		GUI_DrawRect(pos.x, pos.y, pos.x + listbox->Size.width, pos.y + listbox->Size.height, listbox->BorderColor);
	}
	
	uint16_t row_height = listbox->Font->Height + 4;
	uint16_t row_bottom = listbox->CurrentDrawYPos;
	uint16_t row_index = 0;
	while (1)
	{
		if (row_index >= listbox->RowCount) break;
		if (row_bottom >= listbox->Size.height) break;
		if (row_bottom >= 0) 
		{
			if (row_index % 2 == 0)
			{
				GUI_FillRect(pos.x,
					pos.y +row_bottom, 
					pos.x + listbox->Size.width,
					pos.y+row_bottom + row_height, 
					row_index %2 == 1? listbox->RowEvenColor: listbox->RowOddColor);	
			}
			GUI_DrawString(pos.x + 2,
				pos.y + 2 + row_bottom,
				listbox->RowData[row_index],
				listbox->Font,
				listbox->ForeColor,
				row_index %2 == 1? listbox->RowEvenColor: listbox->RowOddColor);
		}
		row_bottom += row_height;
		row_index++;
	}
}

