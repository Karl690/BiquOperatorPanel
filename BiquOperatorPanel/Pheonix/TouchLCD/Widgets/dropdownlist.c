#include "../GUI/gui.h"
#include "dropdownlist.h"
#include "Panel.h"

void dropdownlist_update(DropdownList* obj)
{
	//update corner points.
	obj->CornerPoints[0] = (Point) { 0, obj->CornerRadius };
	obj->CornerPoints[1] = (Point){ 0, obj->Size.height - obj->CornerRadius - 1 };
	obj->CornerPoints[2] = (Point) { obj->CornerRadius, obj->Size.height - 1 };
	obj->CornerPoints[3] = (Point) { obj->Size.width - obj->CornerRadius - 1, obj->Size.height - 1 };
	obj->CornerPoints[4] = (Point) { obj->Size.width - 1, obj->Size.height - obj->CornerRadius - 1 };
	obj->CornerPoints[5] = (Point) { obj->Size.width - 1, obj->CornerRadius };
	obj->CornerPoints[6] = (Point) { obj->Size.width - obj->CornerRadius - 1, 0 };
	obj->CornerPoints[7] = (Point) { obj->CornerRadius, 0 };
	obj->CornerPoints[8] = (Point) { 0, obj->CornerRadius };
	if (obj->SelectedIndex < COMBO_MAX_ITEMS)
		strcpy(obj->Text, obj->Values[obj->SelectedIndex]);
	
//	char a[][32] = { "a", "b", "c" };
}
void dropdownlist_on_paint(DropdownList* obj, Point offset, Color16  backcolor)
{	
	obj->RedrawMe = 0;
	Point pos = { offset.x + obj->Location.x, offset.y + obj->Location.y };
	
	Color16 foreColor, backColor, borderColor;
	if (obj->Checked)
	{
		backColor = obj->FocusBackColor; foreColor = obj->FocusForeColor; borderColor = obj->FocusBorderColor;
	}
	else if (obj->HasFocus)
	{
		backColor = obj->FocusBackColor; foreColor = obj->FocusForeColor; borderColor = obj->FocusBorderColor;
	}
	else {
		backColor = obj->BackColor; foreColor = obj->ForeColor; borderColor = obj->BorderColor;
	}
	GUI_FillRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, backColor);
	if (obj->BorderWidth > 0)
	{
		//GUI_DrawRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, obj->BorderColor);
		GUI_DrawPolygon(obj->CornerPoints, sizeof(obj->CornerPoints) / sizeof(Point), borderColor, pos);
	}
	
	widget_draw_string(obj->Text,
		pos.x,
		pos.y,
		obj->Size.width,
		obj->Size.height,
		&obj->Padding,
		obj->Font,
		obj->TextAlign, 
		foreColor,
		backColor);
}

void dropdownlist_add_item(DropdownList* obj, char* item)
{
	if (obj->ValuesNum + 1 < COMBO_MAX_ITEMS)
	{
		strcpy(obj->Values[obj->ValuesNum], item);
		obj->ValuesNum++;
	}
}
void dropdownlist_remove_item(DropdownList* obj, uint16_t index)
{
	if (index >= obj->ValuesNum) return; //do nothing because the data is not exist
	
	for (uint16_t i = index; i < obj->ValuesNum - 1; i++)
	{
		strcpy(obj->Values[i], obj->Values[i + 1]);
	}
	obj->ValuesNum--;
}

void dropdownlist_select_item(DropdownList* obj, uint16_t index)
{
	if (index < obj->ValuesNum)
	{
		obj->SelectedIndex = index;
		obj->RedrawMe = 1;
	}
}
uint16_t dropdownlist_get_seletected_index(DropdownList* obj)
{
	return obj->SelectedIndex;
}
void dropdownlist_select_nextitem(DropdownList* obj)
{
	if (obj->SelectedIndex + 1 < obj->ValuesNum)
	{	
		obj->SelectedIndex++;
		strcpy(obj->Text, obj->Values[obj->SelectedIndex]);
		obj->RedrawMe = 1;
	}
}

void dropdownlist_select_previtem(DropdownList* obj)
{
	if (obj->SelectedIndex - 1 >= 0)
	{	
		obj->SelectedIndex--;
		strcpy(obj->Text, obj->Values[obj->SelectedIndex]);
		obj->RedrawMe = 1;
	}
}