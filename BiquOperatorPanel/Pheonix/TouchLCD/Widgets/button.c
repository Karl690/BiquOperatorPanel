#include "../GUI/gui.h"
#include "button.h"
#include "panel.h"

Button* button_init(Widget* parent)
{
	Button* obj = (Button*)malloc(sizeof(Button));
	obj->Type = LABEL;
	obj->Location = (Point) { 0, 0 };
	obj->Size = (Size) { 0, 0 };
	obj->Parent = parent;
	return obj;
}
void button_destory(Button* obj)
{
	free(obj);
}

void button_check(Button* obj, uint8_t isCheck)
{
	obj->Checked = isCheck;
	obj->RedrawMe = 1;
}

void button_on_paint(Button* obj, Point offset, Color16  backcolor)
{
	uint16_t WidgetBackColor = backcolor;
	if (obj->Visible) WidgetBackColor = obj->BackColor;	
	Point pos = { offset.x + obj->Location.x, offset.y + obj->Location.y };
	GUI_FillRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, WidgetBackColor);
	obj->RedrawMe = 0;//we are repainting this, so turn off the redraw property
	{
		if (obj->Visible == 0) return;
		//button is visible,so add the border and text please
		GUI_FillRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, obj->Checked?obj->CheckedColor: obj->BackColor);
		if (obj->BorderWidth > 0)
		{
			GUI_DrawRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, obj->BorderColor);
		}
		
		widget_draw_string(obj->Text,
			pos.x,
			pos.y,
			obj->Size.width,
			obj->Size.height,
			&obj->Padding,
			obj->Font,
			obj->TextAlign, 
			obj->Checked ? obj->CheckedForeColor : obj->ForeColor,
			obj->Checked ? obj->CheckedColor : obj->BackColor);
	}
}