/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "GPIO/pininit.h"
#include "TouchLCD/lcd.h"
#include "TouchLCD/GUI/gui.h"
#include "TouchLCD/GUI/display.h"
#include "TouchLCD/lcd_touch.h"
#include "TouchLCD/GUI/PanelMain.designer.h"
#include "TouchLCD/GUI/PanelMain.event.h"
#include "TouchLCD/Widgets/panel.h"
#include "taskmanager.h"
/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

uint32_t HeartBeat = 0;
SCREEN_TYPE CurretScreenType = SCREEN_MAIN;
SCREEN_TYPE NewScreenType = SCREEN_MAIN;
Panel* ActivPanel = NULL;

uint16_t Refresh = 0;
uint16_t CalibrateScreenFlag = 0;//calibration flag 0= none, 1=first corner,2=second corner, 3=3rd corner
uint32_t *PanelDisplayIndex = 0; //start by pointing to the root display panel

uint8_t SoapStringBuffer[SOAPSTRING_BLOCKSIZE] = { 0};
TouchCalibrationInfo touchCalibrationInfo;

Numeric* SoapNudsList[30] = { 0 };
// lvana create struct for Widget_blinkControl 
// *widget, byte blinkRate, byte numberOfTimesToblink
//make new method for 10hz loop, call it   BlinkTroll();
//blinkRate is how blink interval in .1 sec, so 5 would blink 1 x per second, .5 on, and .5 off
//numberOfTimesToblink is how many times it will turn on and off
//if set to -1,it is continous

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_FSMC_Init(void);

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/
	
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init(); //my code 
	
  /* Configure the system clock */
    SystemClock_Config();
	
	SysTick_Config(SystemCoreClock / SYSTICKS_PER_SECOND);
	//SCB->VTOR = VECT_TAB_FLASH;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

  /* Initialize all configured peripherals */
    MX_GPIO_Init();

	XPT2046_Init();
	W25Qxx_Init();
	Init_LCD();   // their code
	
	Init_GPIO();
	InitPanelMain();//set up gid widgets
	
	//erase_memory(); //at first time, erase and all byte would be 0xff.
	//return 0;        // at next time, comment  62 and 63 line .
//	uint8_t data[10] = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9 };	
//	write_memory(FLASH_LAST_ADDRESS, data, 10); //Please put a breakpoint. and here you can check the memory map with Memory View.
//	
//	return 0;
	//clearcalibrtionData();
	InitializeCalibrationParameters();
	initializeSoapNudList();
	if (!checkForValidLCDCalibrationData()) CalibrateScreenFlag = 1; //if stored data is not good, please force calibration screen
		
	ActivPanel = &Root_Panel; //set the top panel as boot screen
	
	while (1)
	{
		if (CalibrateScreenFlag)
		{
			CalibratLcdTouchPanel(); //start the touch panel calibration
			continue;
		}

		panel_on_paint((Panel*)ActivPanel, Root_Panel.Location, Root_Panel.BackColor, 0); //redraw as required..
		
		if(touchScreenIsPress)
			panel_touch_event_to_control(ActivPanel, (Point){0, 0});
		
		Refresh = 0;
		HeartBeat++;
		if (BarValue > 3.3) BarValue = 0;
		BarValue += 0.1;
		HAL_Delay(50);
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
								| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
