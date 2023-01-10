/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "GPIO/pininit.h"
#include "TouchLCD/lcd.h"
#include "TouchLCD/GUI/gui.h"
#include "TouchLCD/GUI/display.h"
#include "TouchLCD/lcd_touch.h"
#include "TouchLCD/GUI/PanelMain.designer.h"
/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

uint32_t HeartBeat = 0;
SCREEN_TYPE CurretScreenType = SCREEN_MAIN;
SCREEN_TYPE NewScreenType = SCREEN_MAIN;
Panel* ActivPanel = NULL;

uint16_t Refresh = 0;
uint16_t CalibrateScreenFlag = 0;
uint32_t *PanelDisplayIndex = 0; //start by pointing to the root display panel

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
	
	lcd_touch_calibration_screen(0);
	
	ActivPanel = &Root_Panel; //set the top panel as boot screen
//	NewScreenType = SCREEN_MAIN;
//	CurretScreenType = SCREEN_MAIN;
//	ActivPanel = InitPanelMain();
//	panel_on_paint(ActivPanel, (Point){ 0, 0 }, 1);
	panel_on_paint((Panel*)ActivPanel, (Point){ 0, 0 }, 1); //draw whole panel this time
	while (1)
	{
		if (CalibrateScreenFlag)
		{
			lcd_touch_calibration_screen(1);
			CalibrateScreenFlag = 0;
			panel_on_paint((Panel*)ActivPanel, (Point){ 0, 0 }, 1); 
		}
		panel_on_paint((Panel*)ActivPanel, (Point){ 0, 0 }, 0); //redraw as required..
		Refresh = 0;
//		switch (PanelDisplayIndex)
//		if(CurretScreenType != NewScreenType) // it need to transform screen
//		{
//			switch (NewScreenType)
//			{
//			case SCREEN_TOUCH_CALIBRATION:
//				lcd_touch_calibration_screen(1);
//				NewScreenType = SCREEN_MAIN;			
//			default:
//				break;
//			}	
//			CurretScreenType = NewScreenType;
//			GUI_Clear(COLOR_BLACK);
//			switch (CurretScreenType)
//			{
//			case SCREEN_MAIN:
//				panel_on_paint(ActivPanel, (Point){ 0, 0 }, 1);
//				CurretScreenType = NewScreenType;
//				panel_touch_event_to_control(ActivPanel);
//			default:
//				break;
//			}
//		}else
//		{
//			panel_on_paint(ActivPanel, (Point){ 0, 0 }, 0);
//			panel_touch_event_to_control(ActivPanel);
//			
//		}
	
		HeartBeat++;
		if (BarValue > 3.3) BarValue = 0;
		BarValue += 0.1;
		HAL_Delay(100);
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
