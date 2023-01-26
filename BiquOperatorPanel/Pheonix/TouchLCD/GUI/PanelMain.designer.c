#include "main.h"
#include "PanelMain.designer.h"
#include "PanelMain.event.h"
#include "gui.h"
#include "icons.h"
#include "FontArial.h"
#include "TouchLCD/lcd_encoder.h"
char logtext[255] = { 0 };
uint32_t *PanelHandleList[32]; //empty panel list, pointer handles to structures

Panel Root_Panel;
Button gL_Button2;
Button gL_Button1;
Button glBtnPlus;
Button glBtnMinus;
Panel gL_Panel4;
Listbox gL_Listbox1;
Panel gL_Panel3;
Label lblTitle;
TabControl glTabMain;
Button glTabMainTab_0;
Panel glTabMainPanel_0;
Panel gL_Panel7;
DropdownList gL_DropdownList1;
Label gL_Label15;
Label gL_Label2;
Numeric gL_Numeric2;
Panel gL_Panel5;
DropdownList gL_DropdownList2;
Label gL_Label17;
Label gL_Label16;
Numeric glNumeric_SimplePort;
Button glTabMainTab_1;
Panel glTabMainPanel_1;
Button gL_Button6;
Button gL_Button5;
Button gL_Button4;
Button gL_Button3;
Button glTabMainTab_2;
Panel glTabMainPanel_2;
Panel gL_Panel1;
Edit gL_Edit11;
Edit gL_Edit10;
Label gL_Label1;
Label gL_Label3;
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

	gL_Button2.Type = BUTTON;
	strcpy(gL_Button2.Name, "gL_Button2");
	gL_Button2.Event_Down = NULL;
	gL_Button2.Event_Hold = NULL;
	gL_Button2.Event_Up   = glBtnApply_TouchEvent;
	gL_Button2.BackColor = RGB16(0, 22, 34);
	gL_Button2.ForeColor = RGB16(132, 225, 255);
	gL_Button2.BorderColor = RGB16(1, 103, 137);
	gL_Button2.CheckedColor = RGB16(62, 209, 255);
	gL_Button2.CheckedForeColor = RGB16(2, 46, 61);
	gL_Button2.BorderWidth = 1;
	gL_Button2.CornerRadius = 0;
	gL_Button2.Font = &Font20;
	gL_Button2.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button2.TextAlign = MiddleCenter;
	gL_Button2.Visible = 1;
	gL_Button2.RedrawMe = 1;
	gL_Button2.Location = (Point){ .x = 574, .y = 3 };
	gL_Button2.Size = (Size){ .width = 89, .height = 32 };
	strcpy(gL_Button2.Text, "APPLY");
	strcpy(gL_Button2.CheckedText, "");
	gL_Button2.Checked = 0;

	panel_add_child(&Root_Panel, &gL_Button2); //add to the panel




	gL_Button1.Type = BUTTON;
	strcpy(gL_Button1.Name, "gL_Button1");
	gL_Button1.Event_Down = NULL;
	gL_Button1.Event_Hold = NULL;
	gL_Button1.Event_Up   = glBtnSave_TouchEvent;
	gL_Button1.BackColor = RGB16(0, 22, 34);
	gL_Button1.ForeColor = RGB16(132, 225, 255);
	gL_Button1.BorderColor = RGB16(1, 103, 137);
	gL_Button1.CheckedColor = RGB16(62, 209, 255);
	gL_Button1.CheckedForeColor = RGB16(2, 46, 61);
	gL_Button1.BorderWidth = 1;
	gL_Button1.CornerRadius = 0;
	gL_Button1.Font = &Font20;
	gL_Button1.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button1.TextAlign = MiddleCenter;
	gL_Button1.Visible = 1;
	gL_Button1.RedrawMe = 1;
	gL_Button1.Location = (Point){ .x = 479, .y = 3 };
	gL_Button1.Size = (Size){ .width = 89, .height = 32 };
	strcpy(gL_Button1.Text, "SAVE");
	strcpy(gL_Button1.CheckedText, "");
	gL_Button1.Checked = 0;

	panel_add_child(&Root_Panel, &gL_Button1); //add to the panel




	glBtnPlus.Type = BUTTON;
	strcpy(glBtnPlus.Name, "glBtnPlus");
	glBtnPlus.Event_Down = NULL;
	glBtnPlus.Event_Hold = glBtnPlus_TouchEvent;
	glBtnPlus.Event_Up   = NULL;
	glBtnPlus.BackColor = RGB16(0, 22, 34);
	glBtnPlus.ForeColor = RGB16(132, 225, 255);
	glBtnPlus.BorderColor = RGB16(1, 103, 137);
	glBtnPlus.CheckedColor = RGB16(62, 209, 255);
	glBtnPlus.CheckedForeColor = RGB16(2, 46, 61);
	glBtnPlus.BorderWidth = 1;
	glBtnPlus.CornerRadius = 0;
	glBtnPlus.Font = &Font20;
	glBtnPlus.Padding = (PADDING) { 0, 0, 0, 0 };
	glBtnPlus.TextAlign = MiddleCenter;
	glBtnPlus.Visible = 1;
	glBtnPlus.RedrawMe = 1;
	glBtnPlus.Location = (Point){ .x = 679, .y = 3 };
	glBtnPlus.Size = (Size){ .width = 47, .height = 32 };
	strcpy(glBtnPlus.Text, "+");
	strcpy(glBtnPlus.CheckedText, "");
	glBtnPlus.Checked = 0;

	panel_add_child(&Root_Panel, &glBtnPlus); //add to the panel




	glBtnMinus.Type = BUTTON;
	strcpy(glBtnMinus.Name, "glBtnMinus");
	glBtnMinus.Event_Down = NULL;
	glBtnMinus.Event_Hold = glBtnMinus_TouchEvent;
	glBtnMinus.Event_Up   = NULL;
	glBtnMinus.BackColor = RGB16(0, 22, 34);
	glBtnMinus.ForeColor = RGB16(132, 225, 255);
	glBtnMinus.BorderColor = RGB16(1, 103, 137);
	glBtnMinus.CheckedColor = RGB16(62, 209, 255);
	glBtnMinus.CheckedForeColor = RGB16(2, 46, 61);
	glBtnMinus.BorderWidth = 1;
	glBtnMinus.CornerRadius = 0;
	glBtnMinus.Font = &Font20;
	glBtnMinus.Padding = (PADDING) { 0, 0, 0, 0 };
	glBtnMinus.TextAlign = MiddleCenter;
	glBtnMinus.Visible = 1;
	glBtnMinus.RedrawMe = 1;
	glBtnMinus.Location = (Point){ .x = 732, .y = 3 };
	glBtnMinus.Size = (Size){ .width = 47, .height = 32 };
	strcpy(glBtnMinus.Text, "-");
	strcpy(glBtnMinus.CheckedText, "");
	glBtnMinus.Checked = 0;

	panel_add_child(&Root_Panel, &glBtnMinus); //add to the panel




	gL_Panel4.Type = PANEL;
	strcpy(gL_Panel4.Name, "gL_Panel4");
	gL_Panel4.BackColor = RGB16(0, 22, 34);
	gL_Panel4.ForeColor = RGB16(122, 225, 255);
	gL_Panel4.BorderColor = RGB16(37, 87, 103);
	gL_Panel4.BorderWidth = 1;
	gL_Panel4.Location = (Point){ .x = 345, .y = 42 };
	gL_Panel4.Size = (Size){ .width = 434, .height = 328 };
	gL_Panel4.StackIndex = -1;
	gL_Panel4.CornerRadius = 5;
	gL_Panel4.Font = &Font20;
	strcpy(gL_Panel4.Text, "MESSAGES");
	gL_Panel4.Visible = 1;
	gL_Panel4.RedrawMe = 1;
	//add click event callbacks
	gL_Panel4.Event_Down = NULL;
	gL_Panel4.Event_Hold = NULL;
	gL_Panel4.Event_Up = NULL;
	//Components in this panel
	panel_update(&gL_Panel4);
	gL_Listbox1.Type = LISTBOX;
	strcpy(gL_Listbox1.Name, "gL_Listbox1");
	gL_Listbox1.BackColor = RGB16(0, 22, 34);
	gL_Listbox1.ForeColor = RGB16(122, 225, 255);
	gL_Listbox1.BorderColor = RGB16(0, 22, 34);
	gL_Listbox1.BorderWidth = 1;
	gL_Listbox1.Font = &Font16;
	gL_Listbox1.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Listbox1.Visible = 1;
	gL_Listbox1.RedrawMe = 1;
	gL_Listbox1.IsFocus = 0;
	gL_Listbox1.FocusBorderColor = RGB16(122, 225, 255);
	gL_Listbox1.RowOddColor = RGB16(0, 22, 34);
	gL_Listbox1.RowEvenColor = RGB16(10, 32, 34);
	gL_Listbox1.Location = (Point){ .x = 7, .y = 21 };
	gL_Listbox1.Size = (Size){ .width = 423, .height = 302 };
	listbox_update(&gL_Listbox1);

	panel_add_child(&gL_Panel4, &gL_Listbox1); //add to the panel




	panel_add_child(&Root_Panel, &gL_Panel4); //add to the panel





	gL_Panel3.Type = PANEL;
	strcpy(gL_Panel3.Name, "gL_Panel3");
	gL_Panel3.BackColor = RGB16(0, 22, 34);
	gL_Panel3.ForeColor = RGB16(122, 225, 255);
	gL_Panel3.BorderColor = RGB16(37, 87, 103);
	gL_Panel3.BorderWidth = 1;
	gL_Panel3.Location = (Point){ .x = 345, .y = 378 };
	gL_Panel3.Size = (Size){ .width = 434, .height = 89 };
	gL_Panel3.StackIndex = -1;
	gL_Panel3.CornerRadius = 5;
	gL_Panel3.Font = &Font20;
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
	lblTitle.Location = (Point){ .x = 14, .y = 13 };
	lblTitle.Size = (Size){ .width = 224, .height = 21 };
	strcpy(lblTitle.Text, "MEGASONIC HYPERCLEAN v1.14");
	//add click event callbacks
	lblTitle.Event_Down = NULL;
	lblTitle.Event_Hold = NULL;
	lblTitle.Event_Up = NULL;

	panel_add_child(&Root_Panel, &lblTitle); //add to the panel




	glTabMain.Type = TABCONTROL;
	strcpy(glTabMain.Name, "glTabMain");
	glTabMain.BackColor = RGB16(0, 22, 34);
	glTabMain.BorderColor = RGB16(13, 49, 61);
	glTabMain.BorderWidth = 1;
	glTabMain.Visible = 1;
	glTabMain.RedrawMe = 1;
	glTabMain.Location = (Point){ .x = 11, .y = 42 };
	glTabMain.Size = (Size){ .width = 330, .height = 425 };
	glTabMain.ItemSize = (Size){ .width = 100, .height = 30 };
	glTabMain.StackIndex = 0;

	glTabMainTab_0.Type = BUTTON;
	strcpy(glTabMainTab_0.Name, "glTabMainTab_0");
	glTabMainTab_0.Event_Down = NULL;
	glTabMainTab_0.Event_Hold = NULL;
	glTabMainTab_0.Event_Up   = NULL;
	glTabMainTab_0.BackColor = RGB16(2, 46, 61);
	glTabMainTab_0.ForeColor = RGB16(132, 225, 255);
	glTabMainTab_0.BorderColor = RGB16(1, 103, 137);
	glTabMainTab_0.CheckedColor = RGB16(62, 209, 255);
	glTabMainTab_0.CheckedForeColor = RGB16(2, 46, 61);
	glTabMainTab_0.BorderWidth = 1;
	glTabMainTab_0.CornerRadius = 0;
	glTabMainTab_0.Font = &Font20;
	glTabMainTab_0.Padding = (PADDING) { 4, 4, 4, 4 };
	glTabMainTab_0.TextAlign = MiddleCenter;
	glTabMainTab_0.Visible = 1;
	glTabMainTab_0.RedrawMe = 1;
	glTabMainTab_0.Location = (Point){ .x = 0, .y = 0 };
	glTabMainTab_0.Size = (Size){ .width = 100, .height = 30 };
	strcpy(glTabMainTab_0.Text, "CONN");
	strcpy(glTabMainTab_0.CheckedText, "");
	glTabMainTab_0.Checked = 0;


	gL_Panel7.Type = PANEL;
	strcpy(gL_Panel7.Name, "gL_Panel7");
	gL_Panel7.BackColor = RGB16(0, 22, 34);
	gL_Panel7.ForeColor = RGB16(122, 225, 255);
	gL_Panel7.BorderColor = RGB16(37, 87, 103);
	gL_Panel7.BorderWidth = 1;
	gL_Panel7.Location = (Point){ .x = 10, .y = 8 };
	gL_Panel7.Size = (Size){ .width = 316, .height = 144 };
	gL_Panel7.StackIndex = -1;
	gL_Panel7.CornerRadius = 5;
	gL_Panel7.Font = &Font20;
	strcpy(gL_Panel7.Text, "SECS SERIAL");
	gL_Panel7.Visible = 1;
	gL_Panel7.RedrawMe = 1;
	//add click event callbacks
	gL_Panel7.Event_Down = NULL;
	gL_Panel7.Event_Hold = NULL;
	gL_Panel7.Event_Up = NULL;
	//Components in this panel
	panel_update(&gL_Panel7);

	gL_DropdownList1.Type = DROPDOWNLIST;
	strcpy(gL_DropdownList1.Name, "gL_DropdownList1");
	gL_DropdownList1.BackColor = RGB16(0, 22, 34);
	gL_DropdownList1.ForeColor = RGB16(122, 225, 255);
	gL_DropdownList1.BorderColor = RGB16(1, 103, 137);
	gL_DropdownList1.BorderWidth = 1;
	gL_DropdownList1.CornerRadius = 0;
	gL_DropdownList1.Font = &Font20;
	gL_DropdownList1.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_DropdownList1.TextAlign = MiddleCenter;
	gL_DropdownList1.Visible = 1;
	gL_DropdownList1.RedrawMe = 1;
	gL_DropdownList1.Location = (Point){ .x = 170, .y = 72 };
	gL_DropdownList1.Size = (Size){ .width = 120, .height = 32 };
	gL_DropdownList1.FocusBackColor = RGB16(0, 175, 255);
	 ;
	gL_DropdownList1.FocusForeColor = RGB16(0, 0, 0);
	 ;
	gL_DropdownList1.FocusBorderColor = RGB16(2, 49, 72); 
	;
	gL_DropdownList1.IsFocus = 0;
	gL_DropdownList1.ValueType = DROPDOWNLIST_INT;
	dropdownlist_add_item(&gL_DropdownList1, "9600");
	dropdownlist_add_item(&gL_DropdownList1, "14400");
	dropdownlist_add_item(&gL_DropdownList1, "19200");
	dropdownlist_add_item(&gL_DropdownList1, "38400");
	dropdownlist_add_item(&gL_DropdownList1, "57600");
	dropdownlist_add_item(&gL_DropdownList1, "115200");
	gL_DropdownList1.SelectedIndex = 0;
	dropdownlist_update(&gL_DropdownList1);

	panel_add_child(&gL_Panel7, &gL_DropdownList1); //add to the panel




	gL_Label15.Type = LABEL;
	strcpy(gL_Label15.Name, "gL_Label15");
	gL_Label15.BackColor = RGB16(0, 22, 34);
	gL_Label15.ForeColor = RGB16(122, 225, 255);
	gL_Label15.BorderColor = RGB16(0, 0, 0);
	gL_Label15.BorderWidth = 0;
	gL_Label15.CornerRadius = 0;
	gL_Label15.Font = &Font20;
	gL_Label15.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label15.TextAlign = TopLeft;
	gL_Label15.Visible = 1;
	gL_Label15.RedrawMe = 1;
	gL_Label15.Location = (Point){ .x = 23, .y = 72 };
	gL_Label15.Size = (Size){ .width = 99, .height = 22 };
	strcpy(gL_Label15.Text, "BAUD");
	//add click event callbacks
	gL_Label15.Event_Down = NULL;
	gL_Label15.Event_Hold = NULL;
	gL_Label15.Event_Up = NULL;

	panel_add_child(&gL_Panel7, &gL_Label15); //add to the panel




	gL_Label2.Type = LABEL;
	strcpy(gL_Label2.Name, "gL_Label2");
	gL_Label2.BackColor = RGB16(0, 22, 34);
	gL_Label2.ForeColor = RGB16(122, 225, 255);
	gL_Label2.BorderColor = RGB16(0, 0, 0);
	gL_Label2.BorderWidth = 0;
	gL_Label2.CornerRadius = 0;
	gL_Label2.Font = &Font20;
	gL_Label2.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label2.TextAlign = TopLeft;
	gL_Label2.Visible = 1;
	gL_Label2.RedrawMe = 1;
	gL_Label2.Location = (Point){ .x = 23, .y = 33 };
	gL_Label2.Size = (Size){ .width = 99, .height = 22 };
	strcpy(gL_Label2.Text, "PORT");
	//add click event callbacks
	gL_Label2.Event_Down = NULL;
	gL_Label2.Event_Hold = NULL;
	gL_Label2.Event_Up = NULL;

	panel_add_child(&gL_Panel7, &gL_Label2); //add to the panel




	gL_Numeric2.Type = NUMERIC;
	strcpy(gL_Numeric2.Name, "gL_Numeric2");
	gL_Numeric2.BackColor = RGB16(0, 22, 34);
	gL_Numeric2.ForeColor = RGB16(122, 225, 255);
	gL_Numeric2.BorderColor = RGB16(1, 103, 137);
	gL_Numeric2.BorderWidth = 1;
	gL_Numeric2.CornerRadius = 1;
	gL_Numeric2.Font = &Font20;
	gL_Numeric2.Padding = (PADDING) { 5, 5, 5, 5 };
	gL_Numeric2.TextAlign = MiddleRight;
	gL_Numeric2.Visible = 1;
	gL_Numeric2.RedrawMe = 1;
	gL_Numeric2.Location = (Point){ .x = 170, .y = 26 };
	gL_Numeric2.Size = (Size){ .width = 120, .height = 32 };
	gL_Numeric2.FocusBackColor = RGB16(0, 175, 255);
	 ;
	gL_Numeric2.FocusForeColor = RGB16(0, 0, 0);
	 ;
	gL_Numeric2.FocusBorderColor = RGB16(2, 49, 72);
	 ;
	gL_Numeric2.IsFocus = 0;
	gL_Numeric2.Value = 0;
	gL_Numeric2.Step = 1.5;
	gL_Numeric2.MinValue = 0;
	gL_Numeric2.MaxValue = 100;
	numeric_update(&gL_Numeric2);

	panel_add_child(&gL_Panel7, &gL_Numeric2); //add to the panel




	panel_add_child(&glTabMainPanel_0, &gL_Panel7); //add to the panel





	gL_Panel5.Type = PANEL;
	strcpy(gL_Panel5.Name, "gL_Panel5");
	gL_Panel5.BackColor = RGB16(0, 22, 34);
	gL_Panel5.ForeColor = RGB16(122, 225, 255);
	gL_Panel5.BorderColor = RGB16(37, 87, 103);
	gL_Panel5.BorderWidth = 1;
	gL_Panel5.Location = (Point){ .x = 10, .y = 175 };
	gL_Panel5.Size = (Size){ .width = 316, .height = 144 };
	gL_Panel5.StackIndex = -1;
	gL_Panel5.CornerRadius = 5;
	gL_Panel5.Font = &Font20;
	strcpy(gL_Panel5.Text, "SIMPLE SERIAL");
	gL_Panel5.Visible = 1;
	gL_Panel5.RedrawMe = 1;
	//add click event callbacks
	gL_Panel5.Event_Down = NULL;
	gL_Panel5.Event_Hold = NULL;
	gL_Panel5.Event_Up = NULL;
	//Components in this panel
	panel_update(&gL_Panel5);

	gL_DropdownList2.Type = DROPDOWNLIST;
	strcpy(gL_DropdownList2.Name, "gL_DropdownList2");
	gL_DropdownList2.BackColor = RGB16(0, 22, 34);
	gL_DropdownList2.ForeColor = RGB16(122, 225, 255);
	gL_DropdownList2.BorderColor = RGB16(1, 103, 137);
	gL_DropdownList2.BorderWidth = 1;
	gL_DropdownList2.CornerRadius = 0;
	gL_DropdownList2.Font = &Font20;
	gL_DropdownList2.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_DropdownList2.TextAlign = MiddleCenter;
	gL_DropdownList2.Visible = 1;
	gL_DropdownList2.RedrawMe = 1;
	gL_DropdownList2.Location = (Point){ .x = 172, .y = 70 };
	gL_DropdownList2.Size = (Size){ .width = 120, .height = 32 };
	gL_DropdownList2.FocusBackColor = RGB16(0, 175, 255); 
	;
	gL_DropdownList2.FocusForeColor = RGB16(0, 0, 0);
	 ;
	gL_DropdownList2.FocusBorderColor = RGB16(2, 49, 72);
	 ;
	gL_DropdownList2.IsFocus = 0;
	gL_DropdownList2.ValueType = DROPDOWNLIST_INT;
	dropdownlist_add_item(&gL_DropdownList2, "9600");
	dropdownlist_add_item(&gL_DropdownList2, "14400");
	dropdownlist_add_item(&gL_DropdownList2, "19200");
	dropdownlist_add_item(&gL_DropdownList2, "38400");
	dropdownlist_add_item(&gL_DropdownList2, "57600");
	dropdownlist_add_item(&gL_DropdownList2, "115200");
	gL_DropdownList2.SelectedIndex = 0;
	dropdownlist_update(&gL_DropdownList2);

	panel_add_child(&gL_Panel5, &gL_DropdownList2); //add to the panel




	gL_Label17.Type = LABEL;
	strcpy(gL_Label17.Name, "gL_Label17");
	gL_Label17.BackColor = RGB16(0, 22, 34);
	gL_Label17.ForeColor = RGB16(122, 225, 255);
	gL_Label17.BorderColor = RGB16(0, 0, 0);
	gL_Label17.BorderWidth = 0;
	gL_Label17.CornerRadius = 0;
	gL_Label17.Font = &Font20;
	gL_Label17.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label17.TextAlign = TopLeft;
	gL_Label17.Visible = 1;
	gL_Label17.RedrawMe = 1;
	gL_Label17.Location = (Point){ .x = 23, .y = 72 };
	gL_Label17.Size = (Size){ .width = 99, .height = 22 };
	strcpy(gL_Label17.Text, "BAUD");
	//add click event callbacks
	gL_Label17.Event_Down = NULL;
	gL_Label17.Event_Hold = NULL;
	gL_Label17.Event_Up = NULL;

	panel_add_child(&gL_Panel5, &gL_Label17); //add to the panel




	gL_Label16.Type = LABEL;
	strcpy(gL_Label16.Name, "gL_Label16");
	gL_Label16.BackColor = RGB16(0, 22, 34);
	gL_Label16.ForeColor = RGB16(122, 225, 255);
	gL_Label16.BorderColor = RGB16(0, 0, 0);
	gL_Label16.BorderWidth = 0;
	gL_Label16.CornerRadius = 0;
	gL_Label16.Font = &Font20;
	gL_Label16.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label16.TextAlign = TopLeft;
	gL_Label16.Visible = 1;
	gL_Label16.RedrawMe = 1;
	gL_Label16.Location = (Point){ .x = 23, .y = 33 };
	gL_Label16.Size = (Size){ .width = 99, .height = 22 };
	strcpy(gL_Label16.Text, "PORT");
	//add click event callbacks
	gL_Label16.Event_Down = NULL;
	gL_Label16.Event_Hold = NULL;
	gL_Label16.Event_Up = NULL;

	panel_add_child(&gL_Panel5, &gL_Label16); //add to the panel




	glNumeric_SimplePort.Type = NUMERIC;
	strcpy(glNumeric_SimplePort.Name, "glNumeric_SimplePort");
	glNumeric_SimplePort.BackColor = RGB16(0, 22, 34);
	glNumeric_SimplePort.ForeColor = RGB16(122, 225, 255);
	glNumeric_SimplePort.BorderColor = RGB16(1, 103, 137);
	glNumeric_SimplePort.BorderWidth = 1;
	glNumeric_SimplePort.CornerRadius = 1;
	glNumeric_SimplePort.Font = &Font20;
	glNumeric_SimplePort.Padding = (PADDING) { 5, 5, 5, 5 };
	glNumeric_SimplePort.TextAlign = MiddleRight;
	glNumeric_SimplePort.Visible = 1;
	glNumeric_SimplePort.RedrawMe = 1;
	glNumeric_SimplePort.Location = (Point){ .x = 172, .y = 26 };
	glNumeric_SimplePort.Size = (Size){ .width = 118, .height = 29 };
	glNumeric_SimplePort.FocusBackColor = RGB16(0, 175, 255);
	 ;
	glNumeric_SimplePort.FocusForeColor = RGB16(0, 0, 0);
	 ;
	glNumeric_SimplePort.FocusBorderColor = RGB16(2, 49, 72); 
	;
	glNumeric_SimplePort.IsFocus = 0;
	glNumeric_SimplePort.Value = 0;
	glNumeric_SimplePort.Step = 3.1;
	glNumeric_SimplePort.MinValue = 0;
	glNumeric_SimplePort.MaxValue = 100;
	numeric_update(&glNumeric_SimplePort);

	panel_add_child(&gL_Panel5, &glNumeric_SimplePort); //add to the panel




	panel_add_child(&glTabMainPanel_0, &gL_Panel5); //add to the panel





	glTabMainPanel_0.Type = PANEL;
	strcpy(glTabMainPanel_0.Name, "glTabMainPanel_0");
	glTabMainPanel_0.BackColor = RGB16(0, 22, 34);
	glTabMainPanel_0.ForeColor = RGB16(105, 105, 105);
	glTabMainPanel_0.BorderColor = RGB16(13, 49, 61);
	glTabMainPanel_0.BorderWidth = 1;
	glTabMainPanel_0.Location = (Point){ .x = 0, .y = 30 };
	glTabMainPanel_0.Size = (Size){ .width = 322, .height = 387 };
	glTabMainPanel_0.StackIndex = -1;
	glTabMainPanel_0.CornerRadius = 0;
	glTabMainPanel_0.Font = &Font12;
	strcpy(glTabMainPanel_0.Text, "");
	glTabMainPanel_0.Visible = 1;
	glTabMainPanel_0.RedrawMe = 1;
	//add click event callbacks
	glTabMainPanel_0.Event_Down = NULL;
	glTabMainPanel_0.Event_Hold = NULL;
	glTabMainPanel_0.Event_Up = NULL;
	//Components in this panel
	panel_update(&glTabMainPanel_0);

	tabcontrol_add_child(&glTabMain, &glTabMainTab_0, &glTabMainPanel_0);

	glTabMainTab_1.Type = BUTTON;
	strcpy(glTabMainTab_1.Name, "glTabMainTab_1");
	glTabMainTab_1.Event_Down = NULL;
	glTabMainTab_1.Event_Hold = NULL;
	glTabMainTab_1.Event_Up   = NULL;
	glTabMainTab_1.BackColor = RGB16(2, 46, 61);
	glTabMainTab_1.ForeColor = RGB16(132, 225, 255);
	glTabMainTab_1.BorderColor = RGB16(1, 103, 137);
	glTabMainTab_1.CheckedColor = RGB16(62, 209, 255);
	glTabMainTab_1.CheckedForeColor = RGB16(2, 46, 61);
	glTabMainTab_1.BorderWidth = 1;
	glTabMainTab_1.CornerRadius = 0;
	glTabMainTab_1.Font = &Font20;
	glTabMainTab_1.Padding = (PADDING) { 4, 4, 4, 4 };
	glTabMainTab_1.TextAlign = MiddleCenter;
	glTabMainTab_1.Visible = 1;
	glTabMainTab_1.RedrawMe = 1;
	glTabMainTab_1.Location = (Point){ .x = 100, .y = 0 };
	glTabMainTab_1.Size = (Size){ .width = 100, .height = 30 };
	strcpy(glTabMainTab_1.Text, "FUNC");
	strcpy(glTabMainTab_1.CheckedText, "");
	glTabMainTab_1.Checked = 0;


	gL_Button6.Type = BUTTON;
	strcpy(gL_Button6.Name, "gL_Button6");
	gL_Button6.Event_Down = displaySoapstringButtonEvent;
	gL_Button6.Event_Hold = NULL;
	gL_Button6.Event_Up   = NULL;
	gL_Button6.BackColor = RGB16(0, 0, 0);
	gL_Button6.ForeColor = RGB16(132, 225, 255);
	gL_Button6.BorderColor = RGB16(255, 255, 0);
	gL_Button6.CheckedColor = RGB16(0, 0, 0);
	gL_Button6.CheckedForeColor = RGB16(0, 0, 0);
	gL_Button6.BorderWidth = 1;
	gL_Button6.CornerRadius = 4;
	gL_Button6.Font = &Font16;
	gL_Button6.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button6.TextAlign = MiddleCenter;
	gL_Button6.Visible = 1;
	gL_Button6.RedrawMe = 1;
	gL_Button6.Location = (Point){ .x = 16, .y = 233 };
	gL_Button6.Size = (Size){ .width = 189, .height = 48 };
	strcpy(gL_Button6.Text, "Display Soap string");
	strcpy(gL_Button6.CheckedText, "");
	gL_Button6.Checked = 0;

	panel_add_child(&glTabMainPanel_1, &gL_Button6); //add to the panel




	gL_Button5.Type = BUTTON;
	strcpy(gL_Button5.Name, "gL_Button5");
	gL_Button5.Event_Down = displayCalibrationButtonEvent;
	gL_Button5.Event_Hold = NULL;
	gL_Button5.Event_Up   = NULL;
	gL_Button5.BackColor = RGB16(0, 0, 0);
	gL_Button5.ForeColor = RGB16(132, 225, 255);
	gL_Button5.BorderColor = RGB16(255, 255, 0);
	gL_Button5.CheckedColor = RGB16(0, 0, 0);
	gL_Button5.CheckedForeColor = RGB16(0, 0, 0);
	gL_Button5.BorderWidth = 1;
	gL_Button5.CornerRadius = 4;
	gL_Button5.Font = &Font16;
	gL_Button5.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button5.TextAlign = MiddleCenter;
	gL_Button5.Visible = 1;
	gL_Button5.RedrawMe = 1;
	gL_Button5.Location = (Point){ .x = 16, .y = 161 };
	gL_Button5.Size = (Size){ .width = 189, .height = 48 };
	strcpy(gL_Button5.Text, "Display Calibration");
	strcpy(gL_Button5.CheckedText, "");
	gL_Button5.Checked = 0;

	panel_add_child(&glTabMainPanel_1, &gL_Button5); //add to the panel




	gL_Button4.Type = BUTTON;
	strcpy(gL_Button4.Name, "gL_Button4");
	gL_Button4.Event_Down = ShiftbitWritetestButtonEvent;
	gL_Button4.Event_Hold = NULL;
	gL_Button4.Event_Up   = NULL;
	gL_Button4.BackColor = RGB16(0, 0, 0);
	gL_Button4.ForeColor = RGB16(132, 225, 255);
	gL_Button4.BorderColor = RGB16(255, 255, 0);
	gL_Button4.CheckedColor = RGB16(0, 0, 0);
	gL_Button4.CheckedForeColor = RGB16(0, 0, 0);
	gL_Button4.BorderWidth = 1;
	gL_Button4.CornerRadius = 4;
	gL_Button4.Font = &Font16;
	gL_Button4.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button4.TextAlign = MiddleCenter;
	gL_Button4.Visible = 1;
	gL_Button4.RedrawMe = 1;
	gL_Button4.Location = (Point){ .x = 16, .y = 89 };
	gL_Button4.Size = (Size){ .width = 189, .height = 48 };
	strcpy(gL_Button4.Text, "ShiftBit write test");
	strcpy(gL_Button4.CheckedText, "");
	gL_Button4.Checked = 0;

	panel_add_child(&glTabMainPanel_1, &gL_Button4); //add to the panel




	gL_Button3.Type = BUTTON;
	strcpy(gL_Button3.Name, "gL_Button3");
	gL_Button3.Event_Down = eraseFlashButonEvent;
	gL_Button3.Event_Hold = NULL;
	gL_Button3.Event_Up   = NULL;
	gL_Button3.BackColor = RGB16(0, 0, 0);
	gL_Button3.ForeColor = RGB16(132, 225, 255);
	gL_Button3.BorderColor = RGB16(255, 255, 0);
	gL_Button3.CheckedColor = RGB16(0, 0, 0);
	gL_Button3.CheckedForeColor = RGB16(0, 0, 0);
	gL_Button3.BorderWidth = 1;
	gL_Button3.CornerRadius = 4;
	gL_Button3.Font = &Font16;
	gL_Button3.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Button3.TextAlign = MiddleCenter;
	gL_Button3.Visible = 1;
	gL_Button3.RedrawMe = 1;
	gL_Button3.Location = (Point){ .x = 16, .y = 17 };
	gL_Button3.Size = (Size){ .width = 189, .height = 48 };
	strcpy(gL_Button3.Text, "Erase Flash");
	strcpy(gL_Button3.CheckedText, "");
	gL_Button3.Checked = 0;

	panel_add_child(&glTabMainPanel_1, &gL_Button3); //add to the panel




	glTabMainPanel_1.Type = PANEL;
	strcpy(glTabMainPanel_1.Name, "glTabMainPanel_1");
	glTabMainPanel_1.BackColor = RGB16(0, 22, 34);
	glTabMainPanel_1.ForeColor = RGB16(105, 105, 105);
	glTabMainPanel_1.BorderColor = RGB16(13, 49, 61);
	glTabMainPanel_1.BorderWidth = 1;
	glTabMainPanel_1.Location = (Point){ .x = 0, .y = 30 };
	glTabMainPanel_1.Size = (Size){ .width = 322, .height = 387 };
	glTabMainPanel_1.StackIndex = -1;
	glTabMainPanel_1.CornerRadius = 0;
	glTabMainPanel_1.Font = &Font12;
	strcpy(glTabMainPanel_1.Text, "");
	glTabMainPanel_1.Visible = 1;
	glTabMainPanel_1.RedrawMe = 1;
	//add click event callbacks
	glTabMainPanel_1.Event_Down = NULL;
	glTabMainPanel_1.Event_Hold = NULL;
	glTabMainPanel_1.Event_Up = NULL;
	//Components in this panel
	panel_update(&glTabMainPanel_1);

	tabcontrol_add_child(&glTabMain, &glTabMainTab_1, &glTabMainPanel_1);

	glTabMainTab_2.Type = BUTTON;
	strcpy(glTabMainTab_2.Name, "glTabMainTab_2");
	glTabMainTab_2.Event_Down = NULL;
	glTabMainTab_2.Event_Hold = NULL;
	glTabMainTab_2.Event_Up   = NULL;
	glTabMainTab_2.BackColor = RGB16(2, 46, 61);
	glTabMainTab_2.ForeColor = RGB16(132, 225, 255);
	glTabMainTab_2.BorderColor = RGB16(1, 103, 137);
	glTabMainTab_2.CheckedColor = RGB16(62, 209, 255);
	glTabMainTab_2.CheckedForeColor = RGB16(2, 46, 61);
	glTabMainTab_2.BorderWidth = 1;
	glTabMainTab_2.CornerRadius = 0;
	glTabMainTab_2.Font = &Font20;
	glTabMainTab_2.Padding = (PADDING) { 4, 4, 4, 4 };
	glTabMainTab_2.TextAlign = MiddleCenter;
	glTabMainTab_2.Visible = 1;
	glTabMainTab_2.RedrawMe = 1;
	glTabMainTab_2.Location = (Point){ .x = 200, .y = 0 };
	glTabMainTab_2.Size = (Size){ .width = 100, .height = 30 };
	strcpy(glTabMainTab_2.Text, "VARS");
	strcpy(glTabMainTab_2.CheckedText, "");
	glTabMainTab_2.Checked = 0;


	gL_Panel1.Type = PANEL;
	strcpy(gL_Panel1.Name, "gL_Panel1");
	gL_Panel1.BackColor = RGB16(0, 22, 34);
	gL_Panel1.ForeColor = RGB16(122, 225, 255);
	gL_Panel1.BorderColor = RGB16(37, 87, 103);
	gL_Panel1.BorderWidth = 1;
	gL_Panel1.Location = (Point){ .x = 7, .y = 7 };
	gL_Panel1.Size = (Size){ .width = 346, .height = 373 };
	gL_Panel1.StackIndex = -1;
	gL_Panel1.CornerRadius = 5;
	gL_Panel1.Font = &Font20;
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
	gL_Edit11.Font = &Font20;
	gL_Edit11.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit11.TextAlign = MiddleRight;
	gL_Edit11.Visible = 1;
	gL_Edit11.RedrawMe = 1;
	gL_Edit11.Location = (Point){ .x = 203, .y = 334 };
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
	gL_Edit10.Font = &Font20;
	gL_Edit10.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit10.TextAlign = MiddleRight;
	gL_Edit10.Visible = 1;
	gL_Edit10.RedrawMe = 1;
	gL_Edit10.Location = (Point){ .x = 203, .y = 303 };
	gL_Edit10.Size = (Size){ .width = 101, .height = 27 };
	strcpy(gL_Edit10.Text, "###");
	edit_update(&gL_Edit10);

	panel_add_child(&gL_Panel1, &gL_Edit10); //add to the panel




	gL_Label1.Type = LABEL;
	strcpy(gL_Label1.Name, "gL_Label1");
	gL_Label1.BackColor = RGB16(0, 22, 34);
	gL_Label1.ForeColor = RGB16(122, 225, 255);
	gL_Label1.BorderColor = RGB16(0, 0, 0);
	gL_Label1.BorderWidth = 0;
	gL_Label1.CornerRadius = 0;
	gL_Label1.Font = &Font20;
	gL_Label1.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label1.TextAlign = TopLeft;
	gL_Label1.Visible = 1;
	gL_Label1.RedrawMe = 1;
	gL_Label1.Location = (Point){ .x = 15, .y = 23 };
	gL_Label1.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label1.Text, "Amplifier Unit# ");
	//add click event callbacks
	gL_Label1.Event_Down = NULL;
	gL_Label1.Event_Hold = NULL;
	gL_Label1.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label1); //add to the panel




	gL_Label3.Type = LABEL;
	strcpy(gL_Label3.Name, "gL_Label3");
	gL_Label3.BackColor = RGB16(0, 22, 34);
	gL_Label3.ForeColor = RGB16(122, 225, 255);
	gL_Label3.BorderColor = RGB16(0, 0, 0);
	gL_Label3.BorderWidth = 0;
	gL_Label3.CornerRadius = 0;
	gL_Label3.Font = &Font20;
	gL_Label3.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label3.TextAlign = TopLeft;
	gL_Label3.Visible = 1;
	gL_Label3.RedrawMe = 1;
	gL_Label3.Location = (Point){ .x = 15, .y = 54 };
	gL_Label3.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label3.Text, "Channel number");
	//add click event callbacks
	gL_Label3.Event_Down = NULL;
	gL_Label3.Event_Hold = NULL;
	gL_Label3.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label3); //add to the panel




	gL_Edit9.Type = EDIT;
	strcpy(gL_Edit9.Name, "gL_Edit9");
	gL_Edit9.BackColor = RGB16(13, 49, 61);
	gL_Edit9.ForeColor = RGB16(122, 225, 255);
	gL_Edit9.BorderColor = RGB16(9, 64, 101);
	gL_Edit9.BorderWidth = 1;
	gL_Edit9.CornerRadius = 3;
	gL_Edit9.Font = &Font20;
	gL_Edit9.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit9.TextAlign = MiddleRight;
	gL_Edit9.Visible = 1;
	gL_Edit9.RedrawMe = 1;
	gL_Edit9.Location = (Point){ .x = 203, .y = 272 };
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
	gL_Edit8.Font = &Font20;
	gL_Edit8.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit8.TextAlign = MiddleRight;
	gL_Edit8.Visible = 1;
	gL_Edit8.RedrawMe = 1;
	gL_Edit8.Location = (Point){ .x = 203, .y = 241 };
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
	gL_Edit7.Font = &Font20;
	gL_Edit7.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit7.TextAlign = MiddleRight;
	gL_Edit7.Visible = 1;
	gL_Edit7.RedrawMe = 1;
	gL_Edit7.Location = (Point){ .x = 203, .y = 210 };
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
	gL_Edit6.Font = &Font20;
	gL_Edit6.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit6.TextAlign = MiddleRight;
	gL_Edit6.Visible = 1;
	gL_Edit6.RedrawMe = 1;
	gL_Edit6.Location = (Point){ .x = 203, .y = 179 };
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
	gL_Edit5.Font = &Font20;
	gL_Edit5.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit5.TextAlign = MiddleRight;
	gL_Edit5.Visible = 1;
	gL_Edit5.RedrawMe = 1;
	gL_Edit5.Location = (Point){ .x = 203, .y = 148 };
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
	gL_Edit4.Font = &Font20;
	gL_Edit4.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit4.TextAlign = MiddleRight;
	gL_Edit4.Visible = 1;
	gL_Edit4.RedrawMe = 1;
	gL_Edit4.Location = (Point){ .x = 203, .y = 117 };
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
	gL_Edit3.Font = &Font20;
	gL_Edit3.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit3.TextAlign = MiddleRight;
	gL_Edit3.Visible = 1;
	gL_Edit3.RedrawMe = 1;
	gL_Edit3.Location = (Point){ .x = 203, .y = 86 };
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
	gL_Edit2.Font = &Font20;
	gL_Edit2.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit2.TextAlign = MiddleRight;
	gL_Edit2.Visible = 1;
	gL_Edit2.RedrawMe = 1;
	gL_Edit2.Location = (Point){ .x = 203, .y = 55 };
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
	gL_Edit1.Font = &Font20;
	gL_Edit1.Padding = (PADDING) { 4, 4, 4, 4 };
	gL_Edit1.TextAlign = MiddleRight;
	gL_Edit1.Visible = 1;
	gL_Edit1.RedrawMe = 1;
	gL_Edit1.Location = (Point){ .x = 203, .y = 24 };
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
	gL_Label14.Font = &Font20;
	gL_Label14.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label14.TextAlign = TopLeft;
	gL_Label14.Visible = 1;
	gL_Label14.RedrawMe = 1;
	gL_Label14.Location = (Point){ .x = 15, .y = 334 };
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
	gL_Label13.Font = &Font20;
	gL_Label13.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label13.TextAlign = TopLeft;
	gL_Label13.Visible = 1;
	gL_Label13.RedrawMe = 1;
	gL_Label13.Location = (Point){ .x = 15, .y = 303 };
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
	gL_Label12.Font = &Font20;
	gL_Label12.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label12.TextAlign = TopLeft;
	gL_Label12.Visible = 1;
	gL_Label12.RedrawMe = 1;
	gL_Label12.Location = (Point){ .x = 15, .y = 272 };
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
	gL_Label11.Font = &Font20;
	gL_Label11.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label11.TextAlign = TopLeft;
	gL_Label11.Visible = 1;
	gL_Label11.RedrawMe = 1;
	gL_Label11.Location = (Point){ .x = 15, .y = 241 };
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
	gL_Label10.Font = &Font20;
	gL_Label10.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label10.TextAlign = TopLeft;
	gL_Label10.Visible = 1;
	gL_Label10.RedrawMe = 1;
	gL_Label10.Location = (Point){ .x = 15, .y = 210 };
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
	gL_Label9.Font = &Font20;
	gL_Label9.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label9.TextAlign = TopLeft;
	gL_Label9.Visible = 1;
	gL_Label9.RedrawMe = 1;
	gL_Label9.Location = (Point){ .x = 15, .y = 179 };
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
	gL_Label8.Font = &Font20;
	gL_Label8.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label8.TextAlign = TopLeft;
	gL_Label8.Visible = 1;
	gL_Label8.RedrawMe = 1;
	gL_Label8.Location = (Point){ .x = 15, .y = 148 };
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
	gL_Label5.Font = &Font20;
	gL_Label5.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label5.TextAlign = TopLeft;
	gL_Label5.Visible = 1;
	gL_Label5.RedrawMe = 1;
	gL_Label5.Location = (Point){ .x = 15, .y = 117 };
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
	gL_Label4.Font = &Font20;
	gL_Label4.Padding = (PADDING) { 0, 0, 0, 0 };
	gL_Label4.TextAlign = TopLeft;
	gL_Label4.Visible = 1;
	gL_Label4.RedrawMe = 1;
	gL_Label4.Location = (Point){ .x = 15, .y = 86 };
	gL_Label4.Size = (Size){ .width = 160, .height = 22 };
	strcpy(gL_Label4.Text, "Frequency 1");
	//add click event callbacks
	gL_Label4.Event_Down = NULL;
	gL_Label4.Event_Hold = NULL;
	gL_Label4.Event_Up = NULL;

	panel_add_child(&gL_Panel1, &gL_Label4); //add to the panel




	panel_add_child(&glTabMainPanel_2, &gL_Panel1); //add to the panel





	glTabMainPanel_2.Type = PANEL;
	strcpy(glTabMainPanel_2.Name, "glTabMainPanel_2");
	glTabMainPanel_2.BackColor = RGB16(0, 22, 34);
	glTabMainPanel_2.ForeColor = RGB16(105, 105, 105);
	glTabMainPanel_2.BorderColor = RGB16(13, 49, 61);
	glTabMainPanel_2.BorderWidth = 1;
	glTabMainPanel_2.Location = (Point){ .x = 0, .y = 30 };
	glTabMainPanel_2.Size = (Size){ .width = 322, .height = 387 };
	glTabMainPanel_2.StackIndex = -1;
	glTabMainPanel_2.CornerRadius = 0;
	glTabMainPanel_2.Font = &Font12;
	strcpy(glTabMainPanel_2.Text, "");
	glTabMainPanel_2.Visible = 1;
	glTabMainPanel_2.RedrawMe = 1;
	//add click event callbacks
	glTabMainPanel_2.Event_Down = NULL;
	glTabMainPanel_2.Event_Hold = NULL;
	glTabMainPanel_2.Event_Up = NULL;
	//Components in this panel
	panel_update(&glTabMainPanel_2);

	tabcontrol_add_child(&glTabMain, &glTabMainTab_2, &glTabMainPanel_2);
	tabcontrol_update(&glTabMain);
	tabcontrol_select_panel(&glTabMain, 0);

	panel_add_child(&Root_Panel, &glTabMain); //add to the panel




	PanelHandleList[0] = (uint32_t*)&Root_Panel; //set the root panel
	PanelHandleList[1] = (uint32_t*)&gL_Panel4;
	PanelHandleList[2] = (uint32_t*)&gL_Panel3;
	PanelHandleList[3] = (uint32_t*)&glTabMainPanel_0;
	PanelHandleList[4] = (uint32_t*)&gL_Panel7;
	PanelHandleList[5] = (uint32_t*)&gL_Panel5;
	PanelHandleList[6] = (uint32_t*)&glTabMainPanel_1;
	PanelHandleList[7] = (uint32_t*)&glTabMainPanel_2;
	PanelHandleList[8] = (uint32_t*)&gL_Panel1;

}