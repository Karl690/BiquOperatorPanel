#include "../GUI/gui.h"
#include "edit.h"
#include "Panel.h"

void edit_destory(Edit* edit)
{
	free(edit);
}
void edit_update(Edit* edit)
{
	//update corner points.
	edit->CornerPoints[0] = (Point) { 0, edit->CornerRadius };
	edit->CornerPoints[1] = (Point){ 0, edit->Size.height - edit->CornerRadius - 1 };
	edit->CornerPoints[2] = (Point) { edit->CornerRadius, edit->Size.height - 1 };
	edit->CornerPoints[3] = (Point) { edit->Size.width - edit->CornerRadius - 1, edit->Size.height - 1 };
	edit->CornerPoints[4] = (Point) { edit->Size.width - 1, edit->Size.height - edit->CornerRadius - 1 };
	edit->CornerPoints[5] = (Point) { edit->Size.width - 1, edit->CornerRadius };
	edit->CornerPoints[6] = (Point) { edit->Size.width - edit->CornerRadius - 1, 0 };
	edit->CornerPoints[7] = (Point) { edit->CornerRadius, 0 };
	edit->CornerPoints[8] = (Point) { 0, edit->CornerRadius };
}
void edit_on_paint(Edit* edit, Panel* Parent)
{	
	edit->RedrawMe = 0;
	Point pos = { Parent->Location.x + edit->Location.x, Parent->Location.y + edit->Location.y };
	GUI_FillRect(pos.x, pos.y, pos.x + edit->Size.width, pos.y + edit->Size.height, edit->BackColor);
	if (edit->BorderWidth > 0)
	{
		//GUI_DrawRect(pos.x, pos.y, pos.x + edit->Size.width, pos.y + edit->Size.height, edit->BorderColor);
		GUI_DrawPolygon(edit->CornerPoints, sizeof(edit->CornerPoints) / sizeof(Point), edit->BorderColor, pos);
	}
	if (!edit->Text) return;
	widget_draw_string(edit->Text,
		pos.x,
		pos.y,
		edit->Size.width,
		edit->Size.height,
		&edit->Padding,
		edit->Font,
		edit->TextAlign, 
		edit->ForeColor,
		edit->BackColor);
		
}