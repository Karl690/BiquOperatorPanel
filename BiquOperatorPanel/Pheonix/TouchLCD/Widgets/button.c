#include "../GUI/gui.h"
#include "button.h"
#include "panel.h"

Button* button_init(Widget* parent)
{
	Button* button = (Button*)malloc(sizeof(Button));
	button->Type = LABEL;
	button->Location = (Point) { 0, 0 };
	button->Size = (Size) { 0, 0 };
	button->Parent = parent;
	return button;
}
void button_destory(Button* button)
{
	free(button);
}

void button_check(Button* button, uint8_t isCheck)
{
	button->Checked = isCheck;
	button->RedrawMe = 1;
}

void button_on_paint(Button* button, Point offset, Color16  backcolor)
{
	uint16_t WidgetBackColor = backcolor;
	if (button->Visible) WidgetBackColor = button->BackColor;	
	Point pos = { offset.x + button->Location.x, offset.y + button->Location.y };
	GUI_FillRect(pos.x, pos.y, pos.x + button->Size.width, pos.y + button->Size.height, WidgetBackColor);
	button->RedrawMe = 0;//we are repainting this, so turn off the redraw property
	{
		if (button->Visible == 0) return;
		//button is visible,so add the border and text please
		GUI_FillRect(pos.x, pos.y, pos.x + button->Size.width, pos.y + button->Size.height, button->Checked?button->CheckedColor: button->BackColor);
		if (button->BorderWidth > 0)
		{
			GUI_DrawRect(pos.x, pos.y, pos.x + button->Size.width, pos.y + button->Size.height, button->BorderColor);
		}
		
		widget_draw_string(button->Text,
			pos.x,
			pos.y,
			button->Size.width,
			button->Size.height,
			&button->Padding,
			button->Font,
			button->TextAlign, 
			button->Checked ? button->CheckedForeColor : button->ForeColor,
			button->Checked ? button->CheckedColor : button->BackColor);
	}
}