#include "gui.h"
#include "icons.h"
#include "../Widgets/Widget.h"
#include "../Widgets/panel.h"
#include "../Widgets/label.h"
#include "../Widgets/button.h"

#include "font.h"


void InitPanelMain()
{
	Panel gL_Panel2;
	panel_init(&gL_Panel2); 
	gL_Panel2.BackColor = RGB16(192, 192, 192);
	gL_Panel2.Location = (Point){ .x = 380, .y = 93 };
	gL_Panel2.Size = (Size){ .width = 200, .height = 317 };
	//Components in this panel
	Button gL_Button2;
	gL_Button2.Type = BUTTON;
	gL_Button2.Event_Down = NULL;
	gL_Button2.Event_Hold = NULL;
	gL_Button2.Event_Up   = NULL;
	gL_Button2.BackColor = RGB16(255, 0, 0);
	gL_Button2.ForeColor = RGB16(0, 0, 0);
	gL_Button2.BorderColor = RGB16(0, 139, 139);
	gL_Button2.CheckedColor = RGB16(255, 0, 0);
	gL_Button2.BorderWidth = 10;
	gL_Button2.CornerRadius = 50;
	gL_Button2.Font = &Font20;
	gL_Button2.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button2.TextAlign = MiddleCenter;
	gL_Button2.Location = (Point){ .x = 16, .y = 96 };
	gL_Button2.Size = (Size){ .width = 160, .height = 128 };
	strcpy(gL_Button2.Text, "FIRE1");
	panel_add_child(&gL_Panel2, &gL_Button2); //add to the panel


	// now we insert the paint events
	panel_on_paint(&gL_Panel2, (Point){ 0, 0 });



}