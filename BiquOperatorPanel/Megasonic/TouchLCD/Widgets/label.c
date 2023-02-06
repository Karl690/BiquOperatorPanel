#include "main.h"
#include "label.h"

void label_destory(Label* obj)
{
	free(obj);
}

void label_on_paint(Label* obj, Point offset, Color16  backcolor)
{	
	obj->RedrawMe = 0;
	Point pos = { offset.x + obj->Location.x, offset.y + obj->Location.y };
	GUI_FillRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, obj->BackColor);
	if (obj->BorderWidth > 0)
	{
		GUI_DrawRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, obj->BorderColor);
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