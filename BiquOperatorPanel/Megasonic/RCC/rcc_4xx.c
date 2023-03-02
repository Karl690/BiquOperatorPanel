#include "configure.h"
#if defined(BIQU_407) || defined(FK_407) || defined(CORE_407I)
#include "rcc_4xx.h"

//volatile uint32_t usTicks=0;

void Init_RCC()
{
	//SysTick_Config(SystemCoreClock / 4000);//slice timer has lowest interrupt priority

	//Enable All GPIOs clock
	uint32_t rcc = (uint32_t)(RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN |
							RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN |
							RCC_AHB1ENR_GPIOFEN | RCC_AHB1ENR_GPIOGEN |
							RCC_AHB1ENR_GPIOIEN);


	RCC->AHB1ENR |= (rcc);
	RCC->AHB1RSTR &= ~(rcc);

	//Enable Timer Clock
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC->APB2RSTR &= ~RCC_APB2ENR_TIM1EN;

	rcc = RCC_APB1ENR_TIM12EN | RCC_APB1ENR_TIM13EN | RCC_APB1ENR_TIM14EN;//enable clocks for timers
	RCC->APB1ENR |= rcc;
	RCC->AHB1RSTR &= ~(rcc);
}


static __I uint8_t APBAHBPrescTable[16] = { 0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9 };
//void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
//{
//	uint32_t tmp = 0, presc = 0, pllvco = 0, pllp = 2, pllsource = 0, pllm = 2;
//#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)  
//	uint32_t pllr = 2;
//#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx */
//  
//	/* Get SYSCLK source -------------------------------------------------------*/
//	tmp = RCC->CFGR & RCC_CFGR_SWS;
//  
//	switch (tmp)
//	{
//	case 0x00:  /* HSI used as system clock source */
//		RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
//		break;
//	case 0x04:  /* HSE used as system clock  source */
//		RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
//		break;
//	case 0x08:  /* PLL P used as system clock  source */
//    
//	  /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLLM) * PLLN
//	  SYSCLK = PLL_VCO / PLLP
//	  */    
//		pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
//		pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
//    
//		if (pllsource != 0)
//		{
//			/* HSE used as PLL clock source */
//			pllvco = (HSE_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
//		}
//		else
//		{
//			/* HSI used as PLL clock source */
//			pllvco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);      
//		}
//    
//		pllp = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> 16) + 1) * 2;
//		RCC_Clocks->SYSCLK_Frequency = pllvco / pllp;
//		break;
//
//#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
//	case 0x0C:  /* PLL R used as system clock  source */
//	  /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLLM) * PLLN
//	  SYSCLK = PLL_VCO / PLLR
//	  */    
//		pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
//		pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
//    
//		if (pllsource != 0)
//		{
//			/* HSE used as PLL clock source */
//			pllvco = (HSE_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
//		}
//		else
//		{
//			/* HSI used as PLL clock source */
//			pllvco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);      
//		}
//    
//		pllr = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> 28) + 1) * 2;
//		RCC_Clocks->SYSCLK_Frequency = pllvco / pllr;    
//		break;
//#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx */
//    
//	default:
//		RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
//		break;
//	}
//	/* Compute HCLK, PCLK1 and PCLK2 clocks frequencies ------------------------*/
//  
//	/* Get HCLK prescaler */
//	tmp = RCC->CFGR & RCC_CFGR_HPRE;
//	tmp = tmp >> 4;
//	presc = APBAHBPrescTable[tmp];
//	/* HCLK clock frequency */
//	RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;
//
//	/* Get PCLK1 prescaler */
//	tmp = RCC->CFGR & RCC_CFGR_PPRE1;
//	tmp = tmp >> 10;
//	presc = APBAHBPrescTable[tmp];
//	/* PCLK1 clock frequency */
//	RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
//
//	/* Get PCLK2 prescaler */
//	tmp = RCC->CFGR & RCC_CFGR_PPRE2;
//	tmp = tmp >> 13;
//	presc = APBAHBPrescTable[tmp];
//	/* PCLK2 clock frequency */
//	RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
//}

void RCC_AHB1PeriphClockCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_RCC_AHB1_CLOCK_PERIPH(RCC_AHB1Periph));

	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		RCC->AHB1ENR |= RCC_AHB1Periph;
	}
	else
	{
		RCC->AHB1ENR &= ~RCC_AHB1Periph;
	}
}
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_RCC_APB2_RESET_PERIPH(RCC_APB2Periph));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		RCC->APB2RSTR |= RCC_APB2Periph;
	}
	else
	{
		RCC->APB2RSTR &= ~RCC_APB2Periph;
	}
}

void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		RCC->APB1RSTR |= RCC_APB1Periph;
	}
	else
	{
		RCC->APB1RSTR &= ~RCC_APB1Periph;
	}
}
#endif
