#include "main.h"
#include "PanelMain.designer.h"
#include "gui.h"
#include "icons.h"
#include "FontArial.h"
#include "TouchLCD/lcd_encoder.h"
char logtext[255] = { 0 };

Panel * MainPanel = NULL;
void onCallback_gl_Button2_Up(uint32_t x, uint32_t y)
{
}
void onCallback_gl_Button2_Down(uint32_t x, uint32_t y)
{
	sprintf(logtext, "onCallback_gl_Button2_Down( %d %d)", x, y);
	GUI_DrawString(10, 10, logtext, &Font16, COLOR_LIME, COLOR_BLACK);
}

Panel gL_Panel1;
Label gL_Label5;
Button gL_Button1;

Panel* InitPanelMain()
{	
	gL_Panel1.Type = PANEL;
	strcpy(gL_Panel1.Name, "gL_Panel1");
	gL_Panel1.Visible = 1;
	gL_Panel1.BackColor = RGB16(240, 240, 240);
	gL_Panel1.ForeColor = RGB16(0, 0, 0);
	gL_Panel1.BorderColor = RGB16(0, 139, 139);
	gL_Panel1.BorderWidth = 2;
	gL_Panel1.Location = (Point){ .x = 3, .y = 3 };
	gL_Panel1.Size = (Size){ .width = 600, .height = 480 };
	gL_Panel1.StackIndex = -1;
	//Components in this panel

	
	gL_Label5.Type = LABEL;
	gL_Label5.Visible = 1;
	strcpy(gL_Label5.Name, "gL_Label5");
	gL_Label5.BackColor = RGB16(240, 240, 240);
	gL_Label5.ForeColor = RGB16(0, 0, 0);
	gL_Label5.BorderColor = RGB16(0, 139, 139);
	gL_Label5.BorderWidth = 0;
	gL_Label5.CornerRadius = 0;
	gL_Label5.Font = &Font24;
	gL_Label5.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label5.TextAlign = TopLeft;
	gL_Label5.Location = (Point){ .x = 12, .y = 150 };
	gL_Label5.Size = (Size){ .width = 157, .height = 44 };
	strcpy(gL_Label5.Text, "24 POINT");
	panel_add_child(&gL_Panel1, &gL_Label5); //add to the panel

	
	
	gL_Button1.Type = BUTTON;
	gL_Button1.Visible = 1;
	strcpy(gL_Button1.Name, "gL_Button1");
	gL_Button1.Event_Down = onCallback_gl_Button2_Down;
	gL_Button1.Event_Hold = NULL;
	gL_Button1.Event_Up   = NULL;
	gL_Button1.BackColor = RGB16(255, 0, 0);
	gL_Button1.ForeColor = RGB16(0, 0, 0);
	gL_Button1.BorderColor = RGB16(0, 139, 139);
	gL_Button1.CheckedColor = RGB16(255, 0, 0);
	gL_Button1.BorderWidth = 2;
	gL_Button1.CornerRadius = 0;
	gL_Button1.Font = &Font20;
	gL_Button1.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button1.TextAlign = MiddleCenter;
	gL_Button1.Location = (Point){ .x = 19, .y = 364 };
	gL_Button1.Size = (Size){ .width = 99, .height = 89 };
	strcpy(gL_Button1.Text, "Send");
	panel_add_child(&gL_Panel1, &gL_Button1); //add to the panel
	MainPanel = &gL_Panel1;
	return &gL_Panel1;// return the intialized panel instance.
}