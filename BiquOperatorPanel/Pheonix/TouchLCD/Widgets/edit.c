#include "../GUI/gui.h"
#include "edit.h"
#include "Panel.h"

void edit_destory(Edit* obj)
{
	free(obj);
}
void edit_update(Edit* obj)
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
}
void edit_on_paint(Edit* obj, Point offset, Color16  backcolor)
{	
	obj->RedrawMe = 0;
	Point pos = { offset.x + obj->Location.x, offset.y + obj->Location.y };
	GUI_FillRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, obj->BackColor);
	if (obj->BorderWidth > 0)
	{
		//GUI_DrawRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, obj->BorderColor);
		GUI_DrawPolygon(obj->CornerPoints, sizeof(obj->CornerPoints) / sizeof(Point), obj->BorderColor, pos);
	}
	if (!obj->Text) return;
	widget_draw_string(obj->Text,
		pos.x,
		pos.y,
		obj->Size.width,
		obj->Size.height,
		&obj->Padding,
		obj->Font,
		obj->TextAlign, 
		obj->ForeColor,
		obj->BackColor);
		
}