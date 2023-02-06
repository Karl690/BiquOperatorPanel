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
	if (obj->Visible == 0) return;
	Color16 foreColor, backColor, borderColor;
	if (obj->Checked)
	{
		backColor = obj->CheckedBackColor; foreColor = obj->CheckedForeColor; borderColor = obj->CheckedBorderColor;
	}
	else if (obj->HasFocus)
	{
		backColor = obj->FocusBackColor; foreColor = obj->FocusForeColor; borderColor = obj->FocusBorderColor;
	}
	else {
		backColor = obj->BackColor; foreColor = obj->ForeColor; borderColor = obj->BorderColor;
	}
	//button is visible,so add the border and text please
	GUI_FillRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, backColor);
	if (obj->BorderWidth > 0)
	{
		GUI_DrawRect(pos.x, pos.y, pos.x + obj->Size.width, pos.y + obj->Size.height, borderColor);
	}
	if (strlen(obj->CheckedText) == 0) strcpy(obj->CheckedText, obj->Text);
	widget_draw_string(obj->Checked?  obj->CheckedText: obj->Text,
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