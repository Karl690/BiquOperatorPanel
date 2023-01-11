#include "main.h"
#include "PanelMain.designer.h"
#include "gui.h"
#include "icons.h"
#include "FontArial.h"
#include "TouchLCD/lcd_encoder.h"
char logtext[255] = { 0 };
uint32_t *PanelHandleList[32]; //empty panel list, pointer handles to structures

Panel Root_Panel;
Panel gL_Panel2;
Button gL_Button8;
Button gL_Button7;
Button gL_Button6;
Button gL_Button5;
Button gL_Button4;
Button gL_Button3;
Button gL_Button2;
Panel gL_Panel1;
Label gL_Label5;
Label gL_Label4;
Label gL_Label3;
Label gL_Label2;
Label gL_Label1;
Button gL_Button1;



void  InitPanelMain()
{
	Root_Panel.Type = PANEL;
	strcpy(Root_Panel.Name, "Root_Panel");
	Root_Panel.BackColor = RGB16(0, 0, 0);
	Root_Panel.ForeColor = RGB16(0, 0, 0);
	Root_Panel.BorderColor = RGB16(0, 139, 139);
	Root_Panel.BorderWidth = 2;
	Root_Panel.Location = (Point){ .x = 0, .y = 0 };
	Root_Panel.Size = (Size){ .width = 800, .height = 480 };
	Root_Panel.StackIndex = -1;
	Root_Panel.Visible = 1;
	Root_Panel.RedrawMe = 1;
	//Components in this panel


	gL_Panel2.Type = PANEL;
	strcpy(gL_Panel2.Name, "gL_Panel2");
	gL_Panel2.BackColor = RGB16(255, 255, 255);
	gL_Panel2.ForeColor = RGB16(0, 0, 0);
	gL_Panel2.BorderColor = RGB16(0, 139, 139);
	gL_Panel2.BorderWidth = 2;
	gL_Panel2.Location = (Point){ .x = 313, .y = 28 };
	gL_Panel2.Size = (Size){ .width = 454, .height = 404 };
	gL_Panel2.StackIndex = -1;
	gL_Panel2.Visible = 1;
	gL_Panel2.RedrawMe = 1;
	//Components in this panel


	gL_Button8.Type = BUTTON;
	strcpy(gL_Button8.Name, "gL_Button8");
	gL_Button8.Event_Down = NULL;
	gL_Button8.Event_Hold = NULL;
	gL_Button8.Event_Up   = NULL;
	gL_Button8.BackColor = RGB16(105, 105, 105);
	gL_Button8.ForeColor = RGB16(0, 0, 0);
	gL_Button8.BorderColor = RGB16(0, 139, 139);
	gL_Button8.CheckedColor = RGB16(105, 105, 105);
	gL_Button8.BorderWidth = 2;
	gL_Button8.CornerRadius = 0;
	gL_Button8.Font = &Font16;
	gL_Button8.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button8.TextAlign = MiddleCenter;
	gL_Button8.Visible = 1;
	gL_Button8.RedrawMe = 1;
	gL_Button8.Location = (Point){ .x = 4, .y = 346 };
	gL_Button8.Size = (Size){ .width = 125, .height = 50 };
	strcpy(gL_Button8.Text, "Button7");

	panel_add_child(&gL_Panel2, &gL_Button8); //add to the panel

	gL_Button7.Type = BUTTON;
	strcpy(gL_Button7.Name, "gL_Button7");
	gL_Button7.Event_Down = NULL;
	gL_Button7.Event_Hold = NULL;
	gL_Button7.Event_Up   = NULL;
	gL_Button7.BackColor = RGB16(105, 105, 105);
	gL_Button7.ForeColor = RGB16(0, 0, 0);
	gL_Button7.BorderColor = RGB16(0, 139, 139);
	gL_Button7.CheckedColor = RGB16(105, 105, 105);
	gL_Button7.BorderWidth = 2;
	gL_Button7.CornerRadius = 0;
	gL_Button7.Font = &Font16;
	gL_Button7.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button7.TextAlign = MiddleCenter;
	gL_Button7.Visible = 1;
	gL_Button7.RedrawMe = 1;
	gL_Button7.Location = (Point){ .x = 4, .y = 289 };
	gL_Button7.Size = (Size){ .width = 125, .height = 50 };
	strcpy(gL_Button7.Text, "Button6");

	panel_add_child(&gL_Panel2, &gL_Button7); //add to the panel

	gL_Button6.Type = BUTTON;
	strcpy(gL_Button6.Name, "gL_Button6");
	gL_Button6.Event_Down = NULL;
	gL_Button6.Event_Hold = NULL;
	gL_Button6.Event_Up   = NULL;
	gL_Button6.BackColor = RGB16(105, 105, 105);
	gL_Button6.ForeColor = RGB16(0, 0, 0);
	gL_Button6.BorderColor = RGB16(0, 139, 139);
	gL_Button6.CheckedColor = RGB16(105, 105, 105);
	gL_Button6.BorderWidth = 2;
	gL_Button6.CornerRadius = 0;
	gL_Button6.Font = &Font16;
	gL_Button6.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button6.TextAlign = MiddleCenter;
	gL_Button6.Visible = 1;
	gL_Button6.RedrawMe = 1;
	gL_Button6.Location = (Point){ .x = 4, .y = 232 };
	gL_Button6.Size = (Size){ .width = 125, .height = 50 };
	strcpy(gL_Button6.Text, "Button5");

	panel_add_child(&gL_Panel2, &gL_Button6); //add to the panel

	gL_Button5.Type = BUTTON;
	strcpy(gL_Button5.Name, "gL_Button5");
	gL_Button5.Event_Down = NULL;
	gL_Button5.Event_Hold = NULL;
	gL_Button5.Event_Up   = NULL;
	gL_Button5.BackColor = RGB16(105, 105, 105);
	gL_Button5.ForeColor = RGB16(0, 0, 0);
	gL_Button5.BorderColor = RGB16(0, 139, 139);
	gL_Button5.CheckedColor = RGB16(105, 105, 105);
	gL_Button5.BorderWidth = 2;
	gL_Button5.CornerRadius = 0;
	gL_Button5.Font = &Font16;
	gL_Button5.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button5.TextAlign = MiddleCenter;
	gL_Button5.Visible = 1;
	gL_Button5.RedrawMe = 1;
	gL_Button5.Location = (Point){ .x = 4, .y = 175 };
	gL_Button5.Size = (Size){ .width = 125, .height = 50 };
	strcpy(gL_Button5.Text, "Button4");

	panel_add_child(&gL_Panel2, &gL_Button5); //add to the panel

	gL_Button4.Type = BUTTON;
	strcpy(gL_Button4.Name, "gL_Button4");
	gL_Button4.Event_Down = NULL;
	gL_Button4.Event_Hold = NULL;
	gL_Button4.Event_Up   = NULL;
	gL_Button4.BackColor = RGB16(105, 105, 105);
	gL_Button4.ForeColor = RGB16(0, 0, 0);
	gL_Button4.BorderColor = RGB16(0, 139, 139);
	gL_Button4.CheckedColor = RGB16(105, 105, 105);
	gL_Button4.BorderWidth = 2;
	gL_Button4.CornerRadius = 0;
	gL_Button4.Font = &Font16;
	gL_Button4.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button4.TextAlign = MiddleCenter;
	gL_Button4.Visible = 1;
	gL_Button4.RedrawMe = 1;
	gL_Button4.Location = (Point){ .x = 4, .y = 118 };
	gL_Button4.Size = (Size){ .width = 125, .height = 50 };
	strcpy(gL_Button4.Text, "Button3");

	panel_add_child(&gL_Panel2, &gL_Button4); //add to the panel

	gL_Button3.Type = BUTTON;
	strcpy(gL_Button3.Name, "gL_Button3");
	gL_Button3.Event_Down = NULL;
	gL_Button3.Event_Hold = NULL;
	gL_Button3.Event_Up   = NULL;
	gL_Button3.BackColor = RGB16(105, 105, 105);
	gL_Button3.ForeColor = RGB16(0, 0, 0);
	gL_Button3.BorderColor = RGB16(0, 139, 139);
	gL_Button3.CheckedColor = RGB16(105, 105, 105);
	gL_Button3.BorderWidth = 2;
	gL_Button3.CornerRadius = 0;
	gL_Button3.Font = &Font16;
	gL_Button3.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button3.TextAlign = MiddleCenter;
	gL_Button3.Visible = 1;
	gL_Button3.RedrawMe = 1;
	gL_Button3.Location = (Point){ .x = 4, .y = 61 };
	gL_Button3.Size = (Size){ .width = 125, .height = 50 };
	strcpy(gL_Button3.Text, "Button2");

	panel_add_child(&gL_Panel2, &gL_Button3); //add to the panel

	gL_Button2.Type = BUTTON;
	strcpy(gL_Button2.Name, "gL_Button2");
	gL_Button2.Event_Down = NULL;
	gL_Button2.Event_Hold = NULL;
	gL_Button2.Event_Up   = NULL;
	gL_Button2.BackColor = RGB16(255, 0, 0);
	gL_Button2.ForeColor = RGB16(0, 0, 0);
	gL_Button2.BorderColor = RGB16(0, 139, 139);
	gL_Button2.CheckedColor = RGB16(255, 0, 0);
	gL_Button2.BorderWidth = 2;
	gL_Button2.CornerRadius = 0;
	gL_Button2.Font = &Font16;
	gL_Button2.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button2.TextAlign = MiddleCenter;
	gL_Button2.Visible = 1;
	gL_Button2.RedrawMe = 1;
	gL_Button2.Location = (Point){ .x = 4, .y = 4 };
	gL_Button2.Size = (Size){ .width = 125, .height = 50 };
	strcpy(gL_Button2.Text, "Button1");

	panel_add_child(&gL_Panel2, &gL_Button2); //add to the panel

	panel_add_child(&Root_Panel, &gL_Panel2); //add to the panel

	gL_Panel1.Type = PANEL;
	strcpy(gL_Panel1.Name, "gL_Panel1");
	gL_Panel1.BackColor = RGB16(255, 255, 255);
	gL_Panel1.ForeColor = RGB16(0, 0, 0);
	gL_Panel1.BorderColor = RGB16(0, 139, 139);
	gL_Panel1.BorderWidth = 2;
	gL_Panel1.Location = (Point){ .x = 50, .y = 28 };
	gL_Panel1.Size = (Size){ .width = 241, .height = 404 };
	gL_Panel1.StackIndex = -1;
	gL_Panel1.Visible = 1;
	gL_Panel1.RedrawMe = 1;
	//Components in this panel


	gL_Label5.Type = LABEL;
	strcpy(gL_Label5.Name, "gL_Label5");
	gL_Label5.BackColor = RGB16(255, 255, 255);
	gL_Label5.ForeColor = RGB16(0, 0, 0);
	gL_Label5.BorderColor = RGB16(0, 139, 139);
	gL_Label5.BorderWidth = 0;
	gL_Label5.CornerRadius = 0;
	gL_Label5.Font = &Font24;
	gL_Label5.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label5.TextAlign = TopLeft;
	gL_Label5.Visible = 1;
	gL_Label5.RedrawMe = 1;
	gL_Label5.Location = (Point){ .x = 16, .y = 185 };
	gL_Label5.Size = (Size){ .width = 157, .height = 44 };
	strcpy(gL_Label5.Text, "24 POINT");

	panel_add_child(&gL_Panel1, &gL_Label5); //add to the panel

	gL_Label4.Type = LABEL;
	strcpy(gL_Label4.Name, "gL_Label4");
	gL_Label4.BackColor = RGB16(255, 255, 255);
	gL_Label4.ForeColor = RGB16(0, 0, 0);
	gL_Label4.BorderColor = RGB16(0, 139, 139);
	gL_Label4.BorderWidth = 0;
	gL_Label4.CornerRadius = 0;
	gL_Label4.Font = &Font20;
	gL_Label4.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label4.TextAlign = TopLeft;
	gL_Label4.Visible = 1;
	gL_Label4.RedrawMe = 1;
	gL_Label4.Location = (Point){ .x = 49, .y = 133 };
	gL_Label4.Size = (Size){ .width = 108, .height = 37 };
	strcpy(gL_Label4.Text, "20 point");

	panel_add_child(&gL_Panel1, &gL_Label4); //add to the panel

	gL_Label3.Type = LABEL;
	strcpy(gL_Label3.Name, "gL_Label3");
	gL_Label3.BackColor = RGB16(255, 255, 255);
	gL_Label3.ForeColor = RGB16(0, 0, 0);
	gL_Label3.BorderColor = RGB16(0, 139, 139);
	gL_Label3.BorderWidth = 0;
	gL_Label3.CornerRadius = 0;
	gL_Label3.Font = &Font16;
	gL_Label3.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label3.TextAlign = TopLeft;
	gL_Label3.Visible = 1;
	gL_Label3.RedrawMe = 1;
	gL_Label3.Location = (Point){ .x = 63, .y = 89 };
	gL_Label3.Size = (Size){ .width = 87, .height = 30 };
	strcpy(gL_Label3.Text, "16 Point");

	panel_add_child(&gL_Panel1, &gL_Label3); //add to the panel

	gL_Label2.Type = LABEL;
	strcpy(gL_Label2.Name, "gL_Label2");
	gL_Label2.BackColor = RGB16(255, 255, 255);
	gL_Label2.ForeColor = RGB16(0, 0, 0);
	gL_Label2.BorderColor = RGB16(0, 139, 139);
	gL_Label2.BorderWidth = 0;
	gL_Label2.CornerRadius = 0;
	gL_Label2.Font = &Font12;
	gL_Label2.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label2.TextAlign = TopLeft;
	gL_Label2.Visible = 1;
	gL_Label2.RedrawMe = 1;
	gL_Label2.Location = (Point){ .x = 79, .y = 50 };
	gL_Label2.Size = (Size){ .width = 64, .height = 24 };
	strcpy(gL_Label2.Text, "12 point");

	panel_add_child(&gL_Panel1, &gL_Label2); //add to the panel

	gL_Label1.Type = LABEL;
	strcpy(gL_Label1.Name, "gL_Label1");
	gL_Label1.BackColor = RGB16(255, 255, 255);
	gL_Label1.ForeColor = RGB16(0, 0, 0);
	gL_Label1.BorderColor = RGB16(0, 139, 139);
	gL_Label1.BorderWidth = 0;
	gL_Label1.CornerRadius = 0;
	gL_Label1.Font = &Font8;
	gL_Label1.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label1.TextAlign = TopLeft;
	gL_Label1.Visible = 1;
	gL_Label1.RedrawMe = 1;
	gL_Label1.Location = (Point){ .x = 97, .y = 21 };
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
	gL_Button1.Location = (Point){ .x = 55, .y = 262 };
	gL_Button1.Size = (Size){ .width = 132, .height = 110 };
	strcpy(gL_Button1.Text, "Send");

	panel_add_child(&gL_Panel1, &gL_Button1); //add to the panel

	panel_add_child(&Root_Panel, &gL_Panel1); //add to the panel

	PanelHandleList[0] = (uint32_t*)&Root_Panel; //set the root panel
	PanelHandleList[1] = (uint32_t*)&gL_Panel2;
	PanelHandleList[2] = (uint32_t*)&gL_Panel1;

}