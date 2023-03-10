#include "main.h"
#include "numeric.h"

void numeric_update(Numeric* obj)
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
	sprintf(obj->Text, "%d", obj->Value);
}
void numeric_on_paint(Numeric* obj, Point offset, Color16  backcolor)
{	
	obj->RedrawMe = 0;
	Point pos = { offset.x + obj->Location.x, offset.y + obj->Location.y };
	GUI_FillRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, obj->HasFocus ? obj->FocusBackColor : obj->BackColor);
	if (obj->BorderWidth > 0)
	{
		//GUI_DrawRect(pos.x, pos.y, pos.x + edit->Size.width, pos.y + edit->Size.height, edit->BorderColor);
		GUI_DrawPolygon(obj->CornerPoints, sizeof(obj->CornerPoints) / sizeof(Point), obj->HasFocus?obj->FocusBorderColor: obj->BorderColor, pos);
	}
	
	widget_draw_string(obj->Text,
		pos.x,
		pos.y,
		obj->Size.width,
		obj->Size.height,
		&obj->Padding,
		obj->Font,
		obj->TextAlign, 
		obj->HasFocus?obj->FocusForeColor: obj->ForeColor,
		obj->HasFocus?obj->FocusBackColor: obj->BackColor);
}

void numeric_set_min_max(Numeric* obj, int min, int max)
{
	obj->MaxValue = max;
	obj->MinValue = min;
}

void numeric_increment(Numeric* obj)
{
	if (obj->Value == obj->MaxValue) return; // do nothing
	if (obj->Value + obj->Step <= obj->MaxValue)
	{
		obj->Value += obj->Step;
	}
	else
	{
		obj->Value = obj->MaxValue;
	}
	sprintf(obj->Text, "%.02f", obj->Value);
	obj->RedrawMe = 1;
}

void numeric_decrement(Numeric* obj)
{
	if (obj->Value == obj->MinValue) return; // do nothing
	if (obj->Value - obj->Step > obj->MinValue)
	{
		obj->Value -= obj->Step;
	}
	else
	{
		obj->Value = obj->MinValue;
	}
	sprintf(obj->Text, "%.02f", obj->Value);
	obj->RedrawMe = 1;
}


void numeric_set_value(Numeric* obj, float value)
{
	if (value < obj->MinValue && value >= obj->MaxValue) return;
	obj->Value = value;
	sprintf(obj->Text, "%.02f", obj->Value);
	obj->RedrawMe = 1;
}