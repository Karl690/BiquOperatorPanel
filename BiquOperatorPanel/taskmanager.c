/*
 * hyrel.c
 *
 *  Created on: Apr 28, 2022
 *      Author: hyrel
 *      this is the roundrobing scehdular
 *      to set the basic int interval search for
 *      HAL_SYSTICK_Config(SystemCoreClock
 *      it is in stm32h7xx_hal.c
 *      in the current version we set the value to 8000
 */
#include "main.h"
#include "taskmanager.h"
#include "TouchLCD/lcd_encoder.h"
#include "TouchLCD/Widgets/widget.h"
#include "TouchLCD/Widgets/button.h"
#include "Communication/serial.h"
uint32_t Seconds = 0;               // needed for heartbeat (number of seconds since boot)
uint16_t SliceCnt = 0;              // current slice being processed
uint16_t TaskTime[32]={0};			// last execution time
uint16_t MaxTaskTime[32]={0};       // Maximum execution time
uint16_t SliceOffset=0;

char* TestString;
uint32_t EncoderPressed = 0;
const PFUNC F1000HZ[NUM_1000HZ] =
{
	Spare,    // keep as last call in this array
	Spare,
	Spare, //CheckForSecsTxRx,
	EncoderWheelMove,
	CheckForUart2TxRx,
	CheckForUart3TxRx,
	CheckForUart4TxRx,
	ParseIncommingLineToSimpleData,
};


const PFUNC F100HZ[NUM_100HZ] =
{
	Spare,//loop_100Hz_simple_work, // keep as last call in this array
	Spare,
	Spare,
	Spare,
	ParseIncommingLineToSecsString,
	TestUart,//Spare,//CheckForUart3TxRx,
	CheckEncoderButton,
	LCD_ProcessTouchEvent,
};

const PFUNC F10HZ[NUM_10HZ] =
{
	Spare,
	Spare,
	Spare,
	Spare,
	Spare,
	SecsTimers,
	ParseIncommingLineToSecsString, //TestUart, //TestUart,
	BlinkButtonsTask,
};

const PFUNC F1HZ[NUM_1HZ] =
{
	Spare,
	Spare,
	blink,
	Spare,
	Spare,
	Spare,
	Spare,
	Spare,
};
/*
 * to make the slice scedular more effecient, we are going to use a binary counter, not base 10
 *
 */
//void TaskManager()
void func_SystickCallback()
{

	
	SliceCnt++;
	SliceOffset=SliceCnt&0x0007;  //precalculate the slice index into the jump table
	if(SliceOffset)
	{
		F1000HZ[SliceOffset]();//run the task
		return;//toggle pin so we can see on Oscillosclope and exit
	}
	if(SliceCnt&0x0038)
	{
		SliceOffset=(SliceCnt>>3) & 0x0007;
		F100HZ[SliceOffset]();
		SliceOffset+=8;
		return;//toggle pin so we can see on Oscillosclope and exit
	}

	if(SliceCnt&0x01C0)
	{
		SliceOffset=(SliceCnt>>6)  & 0x0007;
		F10HZ[SliceOffset]();
		SliceOffset+=16;
		return;//toggle pin so we can see on Oscillosclope and exit
	}

	SliceOffset=(SliceCnt>>9)  & 0x0007;
	F1HZ[SliceOffset]();
	SliceOffset+=24;
	return;//toggle pin so we can see on Oscillosclope and exit

}
void TestUart()
{

	//SendUartSecsString("A");
	//SendUartSimpleString("AB");
//	USART2->DR = (uint32_t)('A' & 0x00ff);
//	USART3->DR = (uint32_t)('A' & 0x00ff);
	//UART4->DR = (uint32_t)('A' & 0x00ff);
	//USART3->DR = 'A';
	//SendUartString("A");
}
void Spare (void)
{
	// placeholder call for empty slice
}
void blink(void)
{
    //widget_ToggleVisible((Widget*)&gL_Button1);
	Refresh = 1; //tell them we need to redraw the screen
}

void BlinkHeartBeat(void)
{
	HeartBeat++;
	if(HeartBeat&1)
	{
		//HeartBeat_Set;
	}
	else
	{
		//HeartBeat_Clr;
	}
}

void CheckEncoderButton()
{
	if (!GPIO_GetLevel(LCD_BTN_PIN))
	{
		EncoderPressed++;
		if (EncoderPressed % 100 == 0) { 
			NewScreenType = SCREEN_TOUCH_CALIBRATION;
			CalibrateScreenFlag = 1;
		}
		else if (EncoderPressed % 5 == 0) 
			EncoderButtonDownEvent();
		
	}
	else
		EncoderPressed = 0;
	
}

void BlinkButtonsTask(void) // it is called every 100ms
{
	for (uint16_t i = 0; i < LIST_MAX_LENGH; i++)
	{
		if (BlinkWidgetsList[i].widget == NULL) return;//no valid object in list, leave
		if (BlinkWidgetsList[i].numberOfTimesToblink)  //this object is supposed to be blinking
		{	
			
			BlinkWidgetsList[i].blinkCount--; //count down the blinks
			if (BlinkWidgetsList[i].blinkCount == 0 )
			{
				if (BlinkWidgetsList[i].numberOfTimesToblink != 0xff)//iff numberOfTimesToblink is 0xff, blink forever
				{ BlinkWidgetsList[i].numberOfTimesToblink--; }
				
				BlinkWidgetsList[i].widget->Checked = !BlinkWidgetsList[i].widget->Checked; // invert the checked status
				
//				//we reached full count, so lets change the backcolor
//				if (BlinkWidgetsList[i].numberOfTimesToblink & 1)
//				{
//					((Button*)BlinkWidgetsList[i].widget)->Checked = 1; //set state every other count cycle
//				}
//				else
//				{
//					((Button*)BlinkWidgetsList[i].widget)->Checked = 0; 
//				}
				BlinkWidgetsList[i].blinkCount = BlinkWidgetsList[i].blinkRate;
				BlinkWidgetsList[i].widget->RedrawMe = 1;
				Refresh = 1;
			}
		}else
		{
			//remove the widget in blink widget list.
			
			BlinkStopWidget(BlinkWidgetsList[i].widget);
		}
	}
}
//	for (uint16_t i = 0; i < LIST_MAX_LENGH; i++)
//	{
//		if (BlinkWidgetsList[i].widget == NULL) return;
//		if (BlinkWidgetsList[i].blinkCount % BlinkWidgetsList[i].blinkRate== 0) { 
//			BlinkWidgetsList[i].widget->HasFocus = !BlinkWidgetsList[i].widget->HasFocus; //invert the state
//			BlinkWidgetsList[i].widget->RedrawMe = 1;
//		}
//		uint16_t numberOfblinked = BlinkWidgetsList[i].blinkCount / (BlinkWidgetsList[i].blinkRate); //number of blinks, so far 
//		if (BlinkWidgetsList[i].numberOfTimesToblink != 0xFF && BlinkWidgetsList[i].numberOfTimesToblink <= numberOfblinked)
//		{
//			BlinkWidgetsList[i].widget->HasFocus = 0;
//			BlinkWidgetsList[i].widget->RedrawMe = 1;
//			widget_delete_blink_widget(BlinkWidgetsList[i].widget);
//		}
//		else
//			BlinkWidgetsList[i].blinkCount++;
//		
//	}


