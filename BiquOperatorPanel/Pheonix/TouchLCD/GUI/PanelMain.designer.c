#include "main.h"
#include "PanelMain.designer.h"
#include "gui.h"
#include "icons.h"
#include "FontArial.h"
#include "TouchLCD/lcd_encoder.h"
char logtext[255] = { 0 };
uint32_t *PanelHandleList[32]; //empty panel list, pointer handles to structures

Panel Root_Panel;
Button gL_Button3;
Button gL_Button2;
Button gL_Button1;
Label lblTitle;
Panel gL_Panel3;
Panel gL_Panel2;
Listbox gL_Listbox1;
Button gL_Button5;
Button gL_Button4;
Panel gL_Panel1;
Edit gL_Edit11;
Edit gL_Edit10;
Edit gL_Edit9;
Edit gL_Edit8;
Edit gL_Edit7;
Edit gL_Edit6;
Edit gL_Edit5;
Edit gL_Edit4;
Edit gL_Edit3;
Edit gL_Edit2;
Edit gL_Edit1;
Label gL_Label14;
Label gL_Label13;
Label gL_Label12;
Label gL_Label11;
Label gL_Label10;
Label gL_Label9;
Label gL_Label8;
Label gL_Label5;
Label gL_Label4;
Label gL_Label3;
Label gL_Label2;



void  InitPanelMain()
{
	Root_Panel.Type = PANEL;
	strcpy(Root_Panel.Name, "Root_Panel");
	Root_Panel.BackColor = RGB16(0, 22, 34);
	Root_Panel.ForeColor = RGB16(105, 105, 105);
	Root_Panel.BorderColor = RGB16(255, 255, 255);
	Root_Panel.BorderWidth = 0;
	Root_Panel.Location = (Point){ .x = 0, .y = 0 };
	Root_Panel.Size = (Size){ .width = 800, .height = 480 };
	Root_Panel.StackIndex = -1;
	Root_Panel.CornerRadius = 0;
	Root_Panel.Font = &Font12;
	strcpy(Root_Panel.Text, "");
	Root_Panel.Visible = 1;
	Root_Panel.RedrawMe = 1;
	//add click event callbacks
	Root_Panel.Event_Down = NULL;
	Root_Panel.Event_Hold = NULL;
	Root_Panel.Event_Up = NULL;
	//Components in this panel
	panel_update(&Root_Panel);

	gL_Button3.Type = BUTTON;
	strcpy(gL_Button3.Name, "gL_Button3");
	gL_Button3.Event_Down = NULL;
	gL_Button3.Event_Hold = NULL;
	gL_Button3.Event_Up   = NULL;
	gL_Button3.BackColor = RGB16(4, 38, 52);
	gL_Button3.ForeColor = RGB16(132, 225, 255);
	gL_Button3.BorderColor = RGB16(1, 103, 137);
	gL_Button3.CheckedColor = RGB16(62, 209, 255);
	gL_Button3.CheckedForeColor = RGB16(2, 46, 61);
	gL_Button3.BorderWidth = 1;
	gL_Button3.CornerRadius = 0;
	gL_Button3.Font = &Font16;
	gL_Button3.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button3.TextAlign = MiddleCenter;
	gL_Button3.Visible = 1;
	gL_Button3.RedrawMe = 1;
	gL_Button3.Location = (Point){ .x = 236, .y = 39 };
	gL_Button3.Size = (Size){ .width = 120, .height = 24 };
	strcpy(gL_Button3.Text, "Frequencies");
	gL_Button3.Checked = 0;

	panel_add_child(&Root_Panel, &gL_Button3); //add to the panel

	gL_Button2.Type = BUTTON;
	strcpy(gL_Button2.Name, "gL_Button2");
	gL_Button2.Event_Down = NULL;
	gL_Button2.Event_Hold = NULL;
	gL_Button2.Event_Up   = NULL;
	gL_Button2.BackColor = RGB16(4, 38, 52);
	gL_Button2.ForeColor = RGB16(132, 225, 255);
	gL_Button2.BorderColor = RGB16(1, 103, 137);
	gL_Button2.CheckedColor = RGB16(62, 209, 255);
	gL_Button2.CheckedForeColor = RGB16(2, 46, 61);
	gL_Button2.BorderWidth = 1;
	gL_Button2.CornerRadius = 0;
	gL_Button2.Font = &Font16;
	gL_Button2.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button2.TextAlign = MiddleCenter;
	gL_Button2.Visible = 1;
	gL_Button2.RedrawMe = 1;
	gL_Button2.Location = (Point){ .x = 118, .y = 39 };
	gL_Button2.Size = (Size){ .width = 120, .height = 24 };
	strcpy(gL_Button2.Text, "Recipe Data");
	gL_Button2.Checked = 0;

	panel_add_child(&Root_Panel, &gL_Button2); //add to the panel

	gL_Button1.Type = BUTTON;
	strcpy(gL_Button1.Name, "gL_Button1");
	gL_Button1.Event_Down = NULL;
	gL_Button1.Event_Hold = NULL;
	gL_Button1.Event_Up   = NULL;
	gL_Button1.BackColor = RGB16(4, 38, 52);
	gL_Button1.ForeColor = RGB16(132, 225, 255);
	gL_Button1.BorderColor = RGB16(1, 103, 137);
	gL_Button1.CheckedColor = RGB16(62, 209, 255);
	gL_Button1.CheckedForeColor = RGB16(2, 46, 61);
	gL_Button1.BorderWidth = 1;
	gL_Button1.CornerRadius = 0;
	gL_Button1.Font = &Font16;
	gL_Button1.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button1.TextAlign = MiddleCenter;
	gL_Button1.Visible = 1;
	gL_Button1.RedrawMe = 1;
	gL_Button1.Location = (Point){ .x = 10, .y = 39 };
	gL_Button1.Size = (Size){ .width = 110, .height = 24 };
	strcpy(gL_Button1.Text, "Live Data");
	gL_Button1.Checked = 1;

	panel_add_child(&Root_Panel, &gL_Button1); //add to the panel

	lblTitle.Type = LABEL;
	strcpy(lblTitle.Name, "lblTitle");
	lblTitle.BackColor = RGB16(0, 22, 34);
	lblTitle.ForeColor = RGB16(122, 225, 255);
	lblTitle.BorderColor = RGB16(0, 0, 0);
	lblTitle.BorderWidth = 0;
	lblTitle.CornerRadius = 0;
	lblTitle.Font = &Font16;
	lblTitle.Padding = (PADDING) { 0, 0, 0, 0 };
	lblTitle.TextAlign = TopLeft;
	lblTitle.Visible = 1;
	lblTitle.RedrawMe = 1;
	lblTitle.Location = (Point){ .x = 5, .y = 7 };
	lblTitle.Size = (Size){ .width = 224, .height = 21 };
	strcpy(lblTitle.Text, "MEGASONIC HYPERCLEAN v1.14");
	//add click event callbacks
	lblTitle.Event_Down = NULL;
	lblTitle.Event_Hold = NULL;
	lblTitle.Event_Up = NULL;

	panel_add_child(&Root_Panel, &lblTitle); //add to the panel

	gL_Panel3.Type = PANEL;
	strcpy(gL_Panel3.Name, "gL_Panel3");
	gL_Panel3.BackColor = RGB16(0, 22, 34);
	gL_Panel3.ForeColor = RGB16(122, 225, 255);
	gL_Panel3.BorderColor = RGB16(37, 87, 103);
	gL_Panel3.BorderWidth = 1;
	gL_Panel3.Location = (Point){ .x = 364, .y = 350 };
	gL_Panel3.Size = (Size){ .width = 411, .height = 105 };
	gL_Panel3.StackIndex = -1;
	gL_Panel3.CornerRadius = 5;
	gL_Panel3.Font = &Font16;
	strcpy(gL_Panel3.Text, "DEVICE INFO");
	gL_Panel3.Visible = 1;
	gL_Panel3.RedrawMe = 1;
	//add click event callbacks
	gL_Panel3.Event_Down = NULL;
	gL_Panel3.Event_Hold = NULL;
	gL_Panel3.Event_Up = NULL;
	//Components in this panel
	panel_update(&gL_Panel3);

	panel_add_child(&Root_Panel, &gL_Panel3); //add to the panel

	gL_Panel2.Type = PANEL;
	strcpy(gL_Panel2.Name, "gL_Panel2");
	gL_Panel2.BackColor = RGB16(0, 22, 34);
	gL_Panel2.ForeColor = RGB16(122, 225, 255);
	gL_Panel2.BorderColor = RGB16(37, 87, 103);
	gL_Panel2.BorderWidth = 1;
	gL_Panel2.Location = (Point){ .x = 364, .y = 52 };
	gL_Panel2.Size = (Size){ .width = 411, .height = 290 };
	gL_Panel2.StackIndex = -1;
	gL_Panel2.CornerRadius = 5;
	gL_Panel2.Font = &Font16;
	strcpy(gL_Panel2.Text, "MESSAGE");
	gL_Panel2.Visible = 1;
	gL_Panel2.RedrawMe = 1;
	//add click event callbacks
	gL_Panel2.Event_Down = NULL;
	gL_Panel2.Event_Hold = NULL;
	gL_Panel2.Event_Up = NULL;
	//Components in this panel
	panel_update(&gL_Panel2);

	gL_Listbox1.Type = LISTBOX;
	strcpy(gL_Listbox1.Name, "gL_Listbox1");
	gL_Listbox1.BackColor = RGB16(10, 22, 34);
	gL_Listbox1.ForeColor = RGB16(122, 225, 255);
	gL_Listbox1.BorderColor = RGB16(0, 0, 0);
	gL_Listbox1.BorderWidth = 0;
	gL_Listbox1.Font = &Font16;
	gL_Listbox1.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Listbox1.Visible = 1;
	gL_Listbox1.RedrawMe = 1;
	gL_Listbox1.Location = (Point){ .x = 9, .y = 50 };
	gL_Listbox1.Size = (Size){ .width = 393, .height = 227 };
	edit_update(&gL_Listbox1);

	panel_add_child(&gL_Panel2, &gL_Listbox1); //add to the panel

	gL_Button5.Type = BUTTON;
	strcpy(gL_Button5.Name, "gL_Button5");
	gL_Button5.Event_Down = NULL;
	gL_Button5.Event_Hold = NULL;
	gL_Button5.Event_Up   = NULL;
	gL_Button5.BackColor = RGB16(4, 38, 52);
	gL_Button5.ForeColor = RGB16(132, 225, 255);
	gL_Button5.BorderColor = RGB16(1, 103, 137);
	gL_Button5.CheckedColor = RGB16(62, 209, 255);
	gL_Button5.CheckedForeColor = RGB16(2, 46, 61);
	gL_Button5.BorderWidth = 1;
	gL_Button5.CornerRadius = 0;
	gL_Button5.Font = &Font16;
	gL_Button5.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button5.TextAlign = MiddleCenter;
	gL_Button5.Visible = 1;
	gL_Button5.RedrawMe = 1;
	gL_Button5.Location = (Point){ .x = 121, .y = 19 };
	gL_Button5.Size = (Size){ .width = 120, .height = 24 };
	strcpy(gL_Button5.Text, "STATISTICS");
	gL_Button5.Checked = 0;

	panel_add_child(&gL_Panel2, &gL_Button5); //add to the panel

	gL_Button4.Type = BUTTON;
	strcpy(gL_Button4.Name, "gL_Button4");
	gL_Button4.Event_Down = NULL;
	gL_Button4.Event_Hold = NULL;
	gL_Button4.Event_Up   = NULL;
	gL_Button4.BackColor = RGB16(4, 38, 52);
	gL_Button4.ForeColor = RGB16(132, 225, 255);
	gL_Button4.BorderColor = RGB16(1, 103, 137);
	gL_Button4.CheckedColor = RGB16(62, 209, 255);
	gL_Button4.CheckedForeColor = RGB16(2, 46, 61);
	gL_Button4.BorderWidth = 1;
	gL_Button4.CornerRadius = 0;
	gL_Button4.Font = &Font16;
	gL_Button4.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button4.TextAlign = MiddleCenter;
	gL_Button4.Visible = 1;
	gL_Button4.RedrawMe = 1;
	gL_Button4.Location = (Point){ .x = 13, .y = 19 };
	gL_Button4.Size = (Size){ .width = 110, .height = 24 };
	strcpy(gL_Button4.Text, "GENERAL LOG");
	gL_Button4.Checked = 1;

	panel_add_child(&gL_Panel2, &gL_Button4); //add to the panel

	panel_add_child(&Root_Panel, &gL_Panel2); //add to the panel

	gL_Panel1.Type = PANEL;
	strcpy(gL_Panel1.Name, "gL_Panel1");
	gL_Panel1.BackColor = RGB16(0, 22, 34);
	gL_Panel1.ForeColor = RGB16(122, 225, 255);
	gL_Panel1.BorderColor = RGB16(37, 87, 103);
	gL_Panel1.BorderWidth = 1;
	gL_Panel1.Location = (Point){ .x = 10, .y = 71 };
	gL_Panel1.Size = (Size){ .width = 346, .height = 383 };
	gL_Panel1.StackIndex = -1;
	gL_Panel1.CornerRadius = 5;
	gL_Panel1.Font = &Font16;
	strcpy(gL_Panel1.Text, "LIVE DATA");
	gL_Panel1.Visible = 1;
	gL_Panel1.RedrawMe = 1;
	//add click event callbacks
	gL_Panel1.Event_Down = NULL;
	gL_Panel1.Event_Hold = NULL;
	gL_Panel1.Event_Up = NULL;
	//Components in this panel
	panel_update(&gL_Panel1);

	gL_Edit11.Type = EDIT;
	strcpy(gL_Edit11.Name, "gL_Edit11");
	gL_Edit11.BackColor = RGB16(13, 49, 61);
	gL_Edit11.ForeColor = RGB16(122, 225, 255);
	gL_Edit11.BorderColor = RGB16(9, 64, 101);
	gL_Edit11.BorderWidth = 1;
	gL_Edit11.CornerRadius = 3;
	gL_Edit11.Font = &Font16;
	gL_Edit11.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit11.TextAlign = MiddleRight;
	gL_Edit11.Visible = 1;
	gL_Edit11.RedrawMe = 1;
	gL_Edit11.Location = (Point){ .x = 223, .y = 342 };
	gL_Edit11.Size = (Size){ .width = 101, .height = 27 };
	strcpy(gL_Edit11.Text, "###");
	edit_update(&gL_Edit11);

	panel_add_child(&gL_Panel1, &gL_Edit11); //add to the panel

	gL_Edit10.Type = EDIT;
	strcpy(gL_Edit10.Name, "gL_Edit10");
	gL_Edit10.BackColor = RGB16(13, 49, 61);
	gL_Edit10.ForeColor = RGB16(122, 225, 255);
	gL_Edit10.BorderColor = RGB16(9, 64, 101);
	gL_Edit10.BorderWidth = 1;
	gL_Edit10.CornerRadius = 3;
	gL_Edit10.Font = &Font16;
	gL_Edit10.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit10.TextAlign = MiddleRight;
	gL_Edit10.Visible = 1;
	gL_Edit10.RedrawMe = 1;
	gL_Edit10.Location = (Point){ .x = 223, .y = 311 };
	gL_Edit10.Size = (Size){ .width = 101, .height = 27 };
	strcpy(gL_Edit10.Text, "###");
	edit_update(&gL_Edit10);

	panel_add_child(&gL_Panel1, &gL_Edit10); //add to the panel

	gL_Edit9.Type = EDIT;
	strcpy(gL_Edit9.Name, "gL_Edit9");
	gL_Edit9.BackColor = RGB16(13, 49, 61);
	gL_Edit9.ForeColor = RGB16(122, 225, 255);
	gL_Edit9.BorderColor = RGB16(9, 64, 101);
	gL_Edit9.BorderWidth = 1;
	gL_Edit9.CornerRadius = 3;
	gL_Edit9.Font = &Font16;
	gL_Edit9.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit9.TextAlign = MiddleRight;
	gL_Edit9.Visible = 1;
	gL_Edit9.RedrawMe = 1;
	gL_Edit9.Location = (Point){ .x = 223, .y = 280 };
	gL_Edit9.Size = (Size){ .width = 101, .height = 27 };
	strcpy(gL_Edit9.Text, "###");
	edit_update(&gL_Edit9);

	panel_add_child(&gL_Panel1, &gL_Edit9); //add to the panel

	gL_Edit8.Type = EDIT;
	strcpy(gL_Edit8.Name, "gL_Edit8");
	gL_Edit8.BackColor = RGB16(13, 49, 61);
	gL_Edit8.ForeColor = RGB16(122, 225, 255);
	gL_Edit8.BorderColor = RGB16(9, 64, 101);
	gL_Edit8.BorderWidth = 1;
	gL_Edit8.CornerRadius = 3;
	gL_Edit8.Font = &Font16;
	gL_Edit8.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit8.TextAlign = MiddleRight;
	gL_Edit8.Visible = 1;
	gL_Edit8.RedrawMe = 1;
	gL_Edit8.Location = (Point){ .x = 223, .y = 249 };
	gL_Edit8.Size = (Size){ .width = 101, .height = 27 };
	strcpy(gL_Edit8.Text, "###");
	edit_update(&gL_Edit8);

	panel_add_child(&gL_Panel1, &gL_Edit8); //add to the panel

	gL_Edit7.Type = EDIT;
	strcpy(gL_Edit7.Name, "gL_Edit7");
	gL_Edit7.BackColor = RGB16(13, 49, 61);
	gL_Edit7.ForeColor = RGB16(122, 225, 255);
	gL_Edit7.BorderColor = RGB16(9, 64, 101);
	gL_Edit7.BorderWidth = 1;
	gL_Edit7.CornerRadius = 3;
	gL_Edit7.Font = &Font16;
	gL_Edit7.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit7.TextAlign = MiddleRight;
	gL_Edit7.Visible = 1;
	gL_Edit7.RedrawMe = 1;
	gL_Edit7.Location = (Point){ .x = 223, .y = 218 };
	gL_Edit7.Size = (Size){ .width = 101, .height = 27 };
	strcpy(gL_Edit7.Text, "###");
	edit_update(&gL_Edit7);

	panel_add_child(&gL_Panel1, &gL_Edit7); //add to the panel

	gL_Edit6.Type = EDIT;
	strcpy(gL_Edit6.Name, "gL_Edit6");
	gL_Edit6.BackColor = RGB16(13, 49, 61);
	gL_Edit6.ForeColor = RGB16(122, 225, 255);
	gL_Edit6.BorderColor = RGB16(9, 64, 101);
	gL_Edit6.BorderWidth = 1;
	gL_Edit6.CornerRadius = 3;
	gL_Edit6.Font = &Font16;
	gL_Edit6.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit6.TextAlign = MiddleRight;
	gL_Edit6.Visible = 1;
	gL_Edit6.RedrawMe = 1;
	gL_Edit6.Location = (Point){ .x = 223, .y = 187 };
	gL_Edit6.Size = (Size){ .width = 101, .height = 27 };
	strcpy(gL_Edit6.Text, "###");
	edit_update(&gL_Edit6);

	panel_add_child(&gL_Panel1, &gL_Edit6); //add to the panel

	gL_Edit5.Type = EDIT;
	strcpy(gL_Edit5.Name, "gL_Edit5");
	gL_Edit5.BackColor = RGB16(13, 49, 61);
	gL_Edit5.ForeColor = RGB16(122, 225, 255);
	gL_Edit5.BorderColor = RGB16(9, 64, 101);
	gL_Edit5.BorderWidth = 1;
	gL_Edit5.CornerRadius = 3;
	gL_Edit5.Font = &Font16;
	gL_Edit5.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit5.TextAlign = MiddleRight;
	gL_Edit5.Visible = 1;
	gL_Edit5.RedrawMe = 1;
	gL_Edit5.Location = (Point){ .x = 223, .y = 156 };
	gL_Edit5.Size = (Size){ .width = 101, .height = 27 };
	strcpy(gL_Edit5.Text, "###");
	edit_update(&gL_Edit5);

	panel_add_child(&gL_Panel1, &gL_Edit5); //add to the panel

	gL_Edit4.Type = EDIT;
	strcpy(gL_Edit4.Name, "gL_Edit4");
	gL_Edit4.BackColor = RGB16(13, 49, 61);
	gL_Edit4.ForeColor = RGB16(122, 225, 255);
	gL_Edit4.BorderColor = RGB16(9, 64, 101);
	gL_Edit4.BorderWidth = 1;
	gL_Edit4.CornerRadius = 3;
	gL_Edit4.Font = &Font16;
	gL_Edit4.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit4.TextAlign = MiddleRight;
	gL_Edit4.Visible = 1;
	gL_Edit4.RedrawMe = 1;
	gL_Edit4.Location = (Point){ .x = 223, .y = 125 };
	gL_Edit4.Size = (Size){ .width = 101, .height = 27 };
	strcpy(gL_Edit4.Text, "###");
	edit_update(&gL_Edit4);

	panel_add_child(&gL_Panel1, &gL_Edit4); //add to the panel

	gL_Edit3.Type = EDIT;
	strcpy(gL_Edit3.Name, "gL_Edit3");
	gL_Edit3.BackColor = RGB16(13, 49, 61);
	gL_Edit3.ForeColor = RGB16(122, 225, 255);
	gL_Edit3.BorderColor = RGB16(9, 64, 101);
	gL_Edit3.BorderWidth = 1;
	gL_Edit3.CornerRadius = 3;
	gL_Edit3.Font = &Font16;
	gL_Edit3.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit3.TextAlign = MiddleRight;
	gL_Edit3.Visible = 1;
	gL_Edit3.RedrawMe = 1;
	gL_Edit3.Location = (Point){ .x = 223, .y = 94 };
	gL_Edit3.Size = (Size){ .width = 101, .height = 27 };
	strcpy(gL_Edit3.Text, "###");
	edit_update(&gL_Edit3);

	panel_add_child(&gL_Panel1, &gL_Edit3); //add to the panel

	gL_Edit2.Type = EDIT;
	strcpy(gL_Edit2.Name, "gL_Edit2");
	gL_Edit2.BackColor = RGB16(13, 49, 61);
	gL_Edit2.ForeColor = RGB16(122, 225, 255);
	gL_Edit2.BorderColor = RGB16(9, 64, 101);
	gL_Edit2.BorderWidth = 1;
	gL_Edit2.CornerRadius = 3;
	gL_Edit2.Font = &Font16;
	gL_Edit2.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit2.TextAlign = MiddleRight;
	gL_Edit2.Visible = 1;
	gL_Edit2.RedrawMe = 1;
	gL_Edit2.Location = (Point){ .x = 223, .y = 63 };
	gL_Edit2.Size = (Size){ .width = 101, .height = 27 };
	strcpy(gL_Edit2.Text, "###");
	edit_update(&gL_Edit2);

	panel_add_child(&gL_Panel1, &gL_Edit2); //add to the panel

	gL_Edit1.Type = EDIT;
	strcpy(gL_Edit1.Name, "gL_Edit1");
	gL_Edit1.BackColor = RGB16(13, 49, 61);
	gL_Edit1.ForeColor = RGB16(122, 225, 255);
	gL_Edit1.BorderColor = RGB16(9, 64, 101);
	gL_Edit1.BorderWidth = 1;
	gL_Edit1.CornerRadius = 3;
	gL_Edit1.Font = &Font16;
	gL_Edit1.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit1.TextAlign = MiddleRight;
	gL_Edit1.Visible = 1;
	gL_Edit1.RedrawMe = 1;
	gL_Edit1.Location = (Point){ .x = 223, .y = 32 };
	gL_Edit1.Size = (Size){ .width = 101, .height = 27 };
	strcpy(gL_Edit1.Text, "###");
	edit_update(&gL_Edit1);

	panel_add_child(&gL_Panel1, &gL_Edit1); //add to the panel

	gL_Label14.Type = LABEL;
	strcpy(gL_Label14.Name, "gL_Label14");
	gL_Label14.BackColor = RGB16(0, 22, 34);
	gL_Label14.ForeColor = RGB16(122, 225, 255);
	gL_Label14.BorderColor = RGB16(0, 0, 0);
	gL_Label14.BorderWidth = 0;
	gL_Label14.CornerRadius = 0;
	gL_Label14.Font = &Font16;
	gL_Label14.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label14.TextAlign = TopLeft;
	gL_Label14.Visible = 1;
	gL_Label14.RedrawMe = 1;
	gL_Label14.Location = (Point){ .x = 15, .y = 342 };
	gL_Label14.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label14.Text, "Status");
	//add click event callbacks
	gL_Label14.Event_Down = NULL;
	gL_Label14.Event_Hold = NULL;
	gL_Label14.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label14); //add to the panel

	gL_Label13.Type = LABEL;
	strcpy(gL_Label13.Name, "gL_Label13");
	gL_Label13.BackColor = RGB16(0, 22, 34);
	gL_Label13.ForeColor = RGB16(122, 225, 255);
	gL_Label13.BorderColor = RGB16(0, 0, 0);
	gL_Label13.BorderWidth = 0;
	gL_Label13.CornerRadius = 0;
	gL_Label13.Font = &Font16;
	gL_Label13.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label13.TextAlign = TopLeft;
	gL_Label13.Visible = 1;
	gL_Label13.RedrawMe = 1;
	gL_Label13.Location = (Point){ .x = 15, .y = 311 };
	gL_Label13.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label13.Text, "TC2");
	//add click event callbacks
	gL_Label13.Event_Down = NULL;
	gL_Label13.Event_Hold = NULL;
	gL_Label13.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label13); //add to the panel

	gL_Label12.Type = LABEL;
	strcpy(gL_Label12.Name, "gL_Label12");
	gL_Label12.BackColor = RGB16(0, 22, 34);
	gL_Label12.ForeColor = RGB16(122, 225, 255);
	gL_Label12.BorderColor = RGB16(0, 0, 0);
	gL_Label12.BorderWidth = 0;
	gL_Label12.CornerRadius = 0;
	gL_Label12.Font = &Font16;
	gL_Label12.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label12.TextAlign = TopLeft;
	gL_Label12.Visible = 1;
	gL_Label12.RedrawMe = 1;
	gL_Label12.Location = (Point){ .x = 15, .y = 280 };
	gL_Label12.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label12.Text, "TC1");
	//add click event callbacks
	gL_Label12.Event_Down = NULL;
	gL_Label12.Event_Hold = NULL;
	gL_Label12.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label12); //add to the panel

	gL_Label11.Type = LABEL;
	strcpy(gL_Label11.Name, "gL_Label11");
	gL_Label11.BackColor = RGB16(0, 22, 34);
	gL_Label11.ForeColor = RGB16(122, 225, 255);
	gL_Label11.BorderColor = RGB16(0, 0, 0);
	gL_Label11.BorderWidth = 0;
	gL_Label11.CornerRadius = 0;
	gL_Label11.Font = &Font16;
	gL_Label11.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label11.TextAlign = TopLeft;
	gL_Label11.Visible = 1;
	gL_Label11.RedrawMe = 1;
	gL_Label11.Location = (Point){ .x = 15, .y = 249 };
	gL_Label11.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label11.Text, "Bath Temp");
	//add click event callbacks
	gL_Label11.Event_Down = NULL;
	gL_Label11.Event_Hold = NULL;
	gL_Label11.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label11); //add to the panel

	gL_Label10.Type = LABEL;
	strcpy(gL_Label10.Name, "gL_Label10");
	gL_Label10.BackColor = RGB16(0, 22, 34);
	gL_Label10.ForeColor = RGB16(122, 225, 255);
	gL_Label10.BorderColor = RGB16(0, 0, 0);
	gL_Label10.BorderWidth = 0;
	gL_Label10.CornerRadius = 0;
	gL_Label10.Font = &Font16;
	gL_Label10.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label10.TextAlign = TopLeft;
	gL_Label10.Visible = 1;
	gL_Label10.RedrawMe = 1;
	gL_Label10.Location = (Point){ .x = 15, .y = 218 };
	gL_Label10.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label10.Text, "Power2");
	//add click event callbacks
	gL_Label10.Event_Down = NULL;
	gL_Label10.Event_Hold = NULL;
	gL_Label10.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label10); //add to the panel

	gL_Label9.Type = LABEL;
	strcpy(gL_Label9.Name, "gL_Label9");
	gL_Label9.BackColor = RGB16(0, 22, 34);
	gL_Label9.ForeColor = RGB16(122, 225, 255);
	gL_Label9.BorderColor = RGB16(0, 0, 0);
	gL_Label9.BorderWidth = 0;
	gL_Label9.CornerRadius = 0;
	gL_Label9.Font = &Font16;
	gL_Label9.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label9.TextAlign = TopLeft;
	gL_Label9.Visible = 1;
	gL_Label9.RedrawMe = 1;
	gL_Label9.Location = (Point){ .x = 15, .y = 187 };
	gL_Label9.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label9.Text, "Power1");
	//add click event callbacks
	gL_Label9.Event_Down = NULL;
	gL_Label9.Event_Hold = NULL;
	gL_Label9.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label9); //add to the panel

	gL_Label8.Type = LABEL;
	strcpy(gL_Label8.Name, "gL_Label8");
	gL_Label8.BackColor = RGB16(0, 22, 34);
	gL_Label8.ForeColor = RGB16(122, 225, 255);
	gL_Label8.BorderColor = RGB16(0, 0, 0);
	gL_Label8.BorderWidth = 0;
	gL_Label8.CornerRadius = 0;
	gL_Label8.Font = &Font16;
	gL_Label8.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label8.TextAlign = TopLeft;
	gL_Label8.Visible = 1;
	gL_Label8.RedrawMe = 1;
	gL_Label8.Location = (Point){ .x = 15, .y = 156 };
	gL_Label8.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label8.Text, "Frequency 2 ");
	//add click event callbacks
	gL_Label8.Event_Down = NULL;
	gL_Label8.Event_Hold = NULL;
	gL_Label8.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label8); //add to the panel

	gL_Label5.Type = LABEL;
	strcpy(gL_Label5.Name, "gL_Label5");
	gL_Label5.BackColor = RGB16(0, 22, 34);
	gL_Label5.ForeColor = RGB16(122, 225, 255);
	gL_Label5.BorderColor = RGB16(0, 0, 0);
	gL_Label5.BorderWidth = 0;
	gL_Label5.CornerRadius = 0;
	gL_Label5.Font = &Font16;
	gL_Label5.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label5.TextAlign = TopLeft;
	gL_Label5.Visible = 1;
	gL_Label5.RedrawMe = 1;
	gL_Label5.Location = (Point){ .x = 15, .y = 125 };
	gL_Label5.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label5.Text, "TC6");
	//add click event callbacks
	gL_Label5.Event_Down = NULL;
	gL_Label5.Event_Hold = NULL;
	gL_Label5.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label5); //add to the panel

	gL_Label4.Type = LABEL;
	strcpy(gL_Label4.Name, "gL_Label4");
	gL_Label4.BackColor = RGB16(0, 22, 34);
	gL_Label4.ForeColor = RGB16(122, 225, 255);
	gL_Label4.BorderColor = RGB16(0, 0, 0);
	gL_Label4.BorderWidth = 0;
	gL_Label4.CornerRadius = 0;
	gL_Label4.Font = &Font16;
	gL_Label4.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label4.TextAlign = TopLeft;
	gL_Label4.Visible = 1;
	gL_Label4.RedrawMe = 1;
	gL_Label4.Location = (Point){ .x = 15, .y = 94 };
	gL_Label4.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label4.Text, "Frequency 1");
	//add click event callbacks
	gL_Label4.Event_Down = NULL;
	gL_Label4.Event_Hold = NULL;
	gL_Label4.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label4); //add to the panel

	gL_Label3.Type = LABEL;
	strcpy(gL_Label3.Name, "gL_Label3");
	gL_Label3.BackColor = RGB16(0, 22, 34);
	gL_Label3.ForeColor = RGB16(122, 225, 255);
	gL_Label3.BorderColor = RGB16(0, 0, 0);
	gL_Label3.BorderWidth = 0;
	gL_Label3.CornerRadius = 0;
	gL_Label3.Font = &Font16;
	gL_Label3.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label3.TextAlign = TopLeft;
	gL_Label3.Visible = 1;
	gL_Label3.RedrawMe = 1;
	gL_Label3.Location = (Point){ .x = 15, .y = 63 };
	gL_Label3.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label3.Text, "Channel number");
	//add click event callbacks
	gL_Label3.Event_Down = NULL;
	gL_Label3.Event_Hold = NULL;
	gL_Label3.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label3); //add to the panel

	gL_Label2.Type = LABEL;
	strcpy(gL_Label2.Name, "gL_Label2");
	gL_Label2.BackColor = RGB16(0, 22, 34);
	gL_Label2.ForeColor = RGB16(122, 225, 255);
	gL_Label2.BorderColor = RGB16(0, 0, 0);
	gL_Label2.BorderWidth = 0;
	gL_Label2.CornerRadius = 0;
	gL_Label2.Font = &Font16;
	gL_Label2.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label2.TextAlign = TopLeft;
	gL_Label2.Visible = 1;
	gL_Label2.RedrawMe = 1;
	gL_Label2.Location = (Point){ .x = 15, .y = 32 };
	gL_Label2.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label2.Text, "Amplifier Unit#");
	//add click event callbacks
	gL_Label2.Event_Down = NULL;
	gL_Label2.Event_Hold = NULL;
	gL_Label2.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label2); //add to the panel

	panel_add_child(&Root_Panel, &gL_Panel1); //add to the panel

	PanelHandleList[0] = (uint32_t*)&Root_Panel; //set the root panel
	PanelHandleList[1] = (uint32_t*)&gL_Panel3;
	PanelHandleList[2] = (uint32_t*)&gL_Panel2;
	PanelHandleList[3] = (uint32_t*)&gL_Panel1;

}