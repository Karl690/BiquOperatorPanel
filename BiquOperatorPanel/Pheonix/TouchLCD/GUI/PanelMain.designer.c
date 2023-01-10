#include "main.h"
#include "PanelMain.designer.h"
#include "gui.h"
#include "icons.h"
#include "FontArial.h"
#include "TouchLCD/lcd_encoder.h"
char logtext[255] = { 0 };
uint32_t *PanelHandleList[32]; //empty panel list, pointer handles to structures
Panel Root_Panel;
Panel gL_Panel1;
Label gL_Label5;
Label gL_Label4;
Label gL_Label3;
Label gL_Label2;
Label gL_Label1;
Button gL_Button1;

void onCallback_gl_Button2_Up(uint32_t x, uint32_t y)
{
}
void onCallback_gl_Button2_Down(uint32_t x, uint32_t y)
{
	sprintf(logtext, "onCallback_gl_Button2_Down( %d %d)", x, y);
	GUI_DrawString(10, 10, logtext, &Font16, COLOR_LIME, COLOR_BLACK);
}





void  InitPanelMain()
{	

	Root_Panel.Type = PANEL;
	strcpy(Root_Panel.Name, "Root_Panel");
	Root_Panel.BackColor = RGB16(240, 240, 240);
	Root_Panel.ForeColor = RGB16(0, 0, 0);
	Root_Panel.BorderColor = RGB16(0, 139, 139);
	Root_Panel.BorderWidth = 2;
	Root_Panel.Location = (Point){ .x = 3, .y = 3 };
	Root_Panel.Size = (Size){ .width = 800, .height = 480 };
	Root_Panel.StackIndex = -1;
	Root_Panel.Visible = 1;
	Root_Panel.RedrawMe = 1;

	gL_Panel1.Type = PANEL;
	strcpy(gL_Panel1.Name, "gL_Panel1");
	gL_Panel1.BackColor = RGB16(240, 240, 240);
	gL_Panel1.ForeColor = RGB16(0, 0, 0);
	gL_Panel1.BorderColor = RGB16(0, 139, 139);
	gL_Panel1.BorderWidth = 2;
	gL_Panel1.Location = (Point){ .x = 3, .y = 3 };
	gL_Panel1.Size = (Size){ .width = 800, .height = 480 };
	gL_Panel1.StackIndex = -1;
	gL_Panel1.Visible = 1;
	gL_Panel1.RedrawMe = 1;
	//Components in this panel


	gL_Label5.Type = LABEL;
	strcpy(gL_Label5.Name, "gL_Label5");
	gL_Label5.BackColor = RGB16(240, 240, 240);
	gL_Label5.ForeColor = RGB16(0, 0, 0);
	gL_Label5.BorderColor = RGB16(0, 139, 139);
	gL_Label5.BorderWidth = 0;
	gL_Label5.CornerRadius = 0;
	gL_Label5.Font = &Font24;
	gL_Label5.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label5.TextAlign = TopLeft;
	gL_Label5.Visible = 1;
	gL_Label5.RedrawMe = 1;
	gL_Label5.Location = (Point){ .x = 12, .y = 150 };
	gL_Label5.Size = (Size){ .width = 157, .height = 44 };
	strcpy(gL_Label5.Text, "24 POINT");

	panel_add_child(&gL_Panel1, &gL_Label5); //add to the panel

	gL_Label4.Type = LABEL;
	strcpy(gL_Label4.Name, "gL_Label4");
	gL_Label4.BackColor = RGB16(240, 240, 240);
	gL_Label4.ForeColor = RGB16(0, 0, 0);
	gL_Label4.BorderColor = RGB16(0, 139, 139);
	gL_Label4.BorderWidth = 0;
	gL_Label4.CornerRadius = 0;
	gL_Label4.Font = &Font20;
	gL_Label4.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label4.TextAlign = TopLeft;
	gL_Label4.Visible = 1;
	gL_Label4.RedrawMe = 1;
	gL_Label4.Location = (Point){ .x = 37, .y = 108 };
	gL_Label4.Size = (Size){ .width = 108, .height = 37 };
	strcpy(gL_Label4.Text, "20 point");

	panel_add_child(&gL_Panel1, &gL_Label4); //add to the panel

	gL_Label3.Type = LABEL;
	strcpy(gL_Label3.Name, "gL_Label3");
	gL_Label3.BackColor = RGB16(240, 240, 240);
	gL_Label3.ForeColor = RGB16(0, 0, 0);
	gL_Label3.BorderColor = RGB16(0, 139, 139);
	gL_Label3.BorderWidth = 0;
	gL_Label3.CornerRadius = 0;
	gL_Label3.Font = &Font16;
	gL_Label3.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label3.TextAlign = TopLeft;
	gL_Label3.Visible = 1;
	gL_Label3.RedrawMe = 1;
	gL_Label3.Location = (Point){ .x = 47, .y = 72 };
	gL_Label3.Size = (Size){ .width = 87, .height = 30 };
	strcpy(gL_Label3.Text, "16 Point");

	panel_add_child(&gL_Panel1, &gL_Label3); //add to the panel

	gL_Label2.Type = LABEL;
	strcpy(gL_Label2.Name, "gL_Label2");
	gL_Label2.BackColor = RGB16(240, 240, 240);
	gL_Label2.ForeColor = RGB16(0, 0, 0);
	gL_Label2.BorderColor = RGB16(0, 139, 139);
	gL_Label2.BorderWidth = 0;
	gL_Label2.CornerRadius = 0;
	gL_Label2.Font = &Font12;
	gL_Label2.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label2.TextAlign = TopLeft;
	gL_Label2.Visible = 1;
	gL_Label2.RedrawMe = 1;
	gL_Label2.Location = (Point){ .x = 59, .y = 41 };
	gL_Label2.Size = (Size){ .width = 64, .height = 24 };
	strcpy(gL_Label2.Text, "12 point");

	panel_add_child(&gL_Panel1, &gL_Label2); //add to the panel

	gL_Label1.Type = LABEL;
	strcpy(gL_Label1.Name, "gL_Label1");
	gL_Label1.BackColor = RGB16(240, 240, 240);
	gL_Label1.ForeColor = RGB16(0, 0, 0);
	gL_Label1.BorderColor = RGB16(0, 139, 139);
	gL_Label1.BorderWidth = 0;
	gL_Label1.CornerRadius = 0;
	gL_Label1.Font = &Font8;
	gL_Label1.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label1.TextAlign = TopLeft;
	gL_Label1.Visible = 1;
	gL_Label1.RedrawMe = 1;
	gL_Label1.Location = (Point){ .x = 73, .y = 17 };
	gL_Label1.Size = (Size){ .width = 38, .height = 17 };
	strcpy(gL_Label1.Text, "8 point");

	panel_add_child(&gL_Panel1, &gL_Label1); //add to the panel

	gL_Button1.Type = BUTTON;
	strcpy(gL_Button1.Name, "gL_Button1");
	gL_Button1.Event_Down = NULL;
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
	gL_Button1.Visible = 1;
	gL_Button1.RedrawMe = 1;
	gL_Button1.Location = (Point){ .x = 41, .y = 213 };
	gL_Button1.Size = (Size){ .width = 99, .height = 89 };
	strcpy(gL_Button1.Text, "Send");

	panel_add_child(&gL_Panel1, &gL_Button1); //add to the panel

	panel_add_child(&Root_Panel, &gL_Panel1);
	
	PanelHandleList[0] =(uint32_t*) &Root_Panel;//set the root panel
	PanelHandleList[1] = (uint32_t*) &gL_Panel1; //set the root panel




}