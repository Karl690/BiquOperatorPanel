#include "stm32f407xx.h"
#include "TouchLCD_4xx.h"
#include "GPIO/pins.h"
#include "GPIO/GPIO_Init.h"
#include "configure.h"


/**
  * @brief  Initializes the FSMC NOR/SRAM Banks according to the specified
  *         parameters in the FSMC_NORSRAMInitStruct.
  * @param  FSMC_NORSRAMInitStruct : pointer to a FSMC_NORSRAMInitTypeDef structure
  *         that contains the configuration information for the FSMC NOR/SRAM 
  *         specified Banks.                       
  * @retval None
  */

void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct)
{ 
	uint32_t tmpbcr = 0, tmpbtr = 0, tmpbwr = 0;

	/* Check the parameters */
	
	/* Get the BTCR register value */
	tmpbcr = FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank];

	/* Clear MBKEN, MUXEN, MTYP, MWID, FACCEN, BURSTEN, WAITPOL, WRAPMOD, WAITCFG, WREN,
	         WAITEN, EXTMOD, ASYNCWAIT, CBURSTRW and CCLKEN bits */
	tmpbcr &= ((uint32_t)~(FSMC_BCR1_MBKEN    | FSMC_BCR1_MUXEN    | FSMC_BCR1_MTYP     | \
	                       FSMC_BCR1_MWID      | FSMC_BCR1_FACCEN   | FSMC_BCR1_BURSTEN  | \
	                       FSMC_BCR1_WAITPOL   | FSMC_BCR1_WRAPMOD  | FSMC_BCR1_WAITCFG  | \
	                       FSMC_BCR1_WREN      | FSMC_BCR1_WAITEN   | FSMC_BCR1_EXTMOD   | \
	                       FSMC_BCR1_ASYNCWAIT | FSMC_BCR1_CBURSTRW));

	/* Bank1 NOR/SRAM control register configuration */ 
	tmpbcr |= (uint32_t)FSMC_NORSRAMInitStruct->FSMC_DataAddressMux |
	          FSMC_NORSRAMInitStruct->FSMC_MemoryType |
	          FSMC_NORSRAMInitStruct->FSMC_MemoryDataWidth |
	          FSMC_NORSRAMInitStruct->FSMC_BurstAccessMode |
	          FSMC_NORSRAMInitStruct->FSMC_AsynchronousWait |
	          FSMC_NORSRAMInitStruct->FSMC_WaitSignalPolarity |
	          FSMC_NORSRAMInitStruct->FSMC_WrapMode |
	          FSMC_NORSRAMInitStruct->FSMC_WaitSignalActive |
	          FSMC_NORSRAMInitStruct->FSMC_WriteOperation |
	          FSMC_NORSRAMInitStruct->FSMC_WaitSignal |
	          FSMC_NORSRAMInitStruct->FSMC_ExtendedMode |
	          FSMC_NORSRAMInitStruct->FSMC_WriteBurst;
			
	FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank] = tmpbcr;
  
	if (FSMC_NORSRAMInitStruct->FSMC_MemoryType == FSMC_MemoryType_NOR)
	{
		FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank] |= (uint32_t)BCR_FACCEN_Set;
	}
  
	/* Get the BTCR register value */
	tmpbtr = FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank + 1];

	/* Clear ADDSET, ADDHLD, DATAST, BUSTURN, CLKDIV, DATLAT and ACCMOD bits */
	tmpbtr &= ((uint32_t)~(FSMC_BTR1_ADDSET | FSMC_BTR1_ADDHLD | FSMC_BTR1_DATAST | \
	                     FSMC_BTR1_BUSTURN | FSMC_BTR1_CLKDIV | FSMC_BTR1_DATLAT | \
	                     FSMC_BTR1_ACCMOD));
					   
	/* Bank1 NOR/SRAM timing register configuration */
	tmpbtr |= (uint32_t)FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressSetupTime |
	          (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressHoldTime << 4) |
	          (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataSetupTime << 8) |
	          (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_BusTurnAroundDuration << 16) |
	          (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_CLKDivision << 20) |
	          (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataLatency << 24) |
	           FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AccessMode;
            
	FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank + 1] = tmpbtr;
	
	/* Bank1 NOR/SRAM timing register for write configuration, if extended mode is used */
	if (FSMC_NORSRAMInitStruct->FSMC_ExtendedMode == FSMC_ExtendedMode_Enable)
	{
		
		/* Get the BWTR register value */
		tmpbwr = FSMC_Bank1E->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank];
    
		/* Clear ADDSET, ADDHLD, DATAST, BUSTURN, and ACCMOD bits */
		tmpbwr &= ((uint32_t)~(FSMC_BWTR1_ADDSET | FSMC_BWTR1_ADDHLD | FSMC_BWTR1_DATAST | \
		                       FSMC_BWTR1_BUSTURN | FSMC_BWTR1_ACCMOD));
    
		tmpbwr |= (uint32_t)FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressSetupTime |
		                   (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressHoldTime << 4) |
		                   (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataSetupTime << 8) |
		                   (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_BusTurnAroundDuration << 16) |
		                    FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AccessMode;
    
		FSMC_Bank1E->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank] = tmpbwr;
	}
	else
	{
		FSMC_Bank1E->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank] = 0x0FFFFFFF;
	}
}


void FSMC_NORSRAMCmd(uint32_t FSMC_Bank, uint8_t NewState)
{
	if (NewState != 0)
	{
		/* Enable the selected NOR/SRAM Bank by setting the PBKEN bit in the BCRx register */
		FSMC_Bank1->BTCR[FSMC_Bank] |= BCR_MBKEN_Set;
	}
	else
	{
		/* Disable the selected NOR/SRAM Bank by clearing the PBKEN bit in the BCRx register */
		FSMC_Bank1->BTCR[FSMC_Bank] &= BCR_MBKEN_Reset;
	}
}

void Setup_LCD_Hardware()
{
	
	RCC->AHB3ENR |= RCC_AHB3ENR_FSMCEN;
	RCC->AHB3RSTR &= ~(RCC_AHB3ENR_FSMCEN);
	   
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN;
	RCC->AHB1RSTR &= ~(RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN);
	
	// fsmc 16bit data pins
	GPIO_InitSet(PD0, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PD1, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PD8, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PD9, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PD10, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PD14, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PD15, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PE7, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PE8, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PE9, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PE10, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PE11, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PE12, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PE13, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PE14, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PE15, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);

	/*Configure the control line corresponding to FSMC
	* PD4-FSMC_NOE :LCD-RD
	* PD5-FSMC_NWE :LCD-WR
	* PD7-FSMC_NE1 :LCD-CS
	* PE2-FSMC_A23 :LCD-RS   LCD-RS data or cmd
	*/
	GPIO_InitSet(PD4, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	GPIO_InitSet(PD5, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);

#ifdef MKS_TFT35_V1_0  // different pinout for MKS_TFT35_V1_0
	GPIO_InitSet(PD12, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
#else
	GPIO_InitSet(PE2, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
#endif
	GPIO_InitSet(PD7, MGPIO_MODE_AF_PP, GPIO_AF_FSMC);
	

	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef readWriteTiming, writeTiming;

	//RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

	readWriteTiming.FSMC_AddressSetupTime = 0x01; // Address setup time (ADDSET) is 2 HCLK 1 / 36M = 27ns
	readWriteTiming.FSMC_AddressHoldTime = 0x00;
	readWriteTiming.FSMC_DataSetupTime = 0x0f;
	readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
	readWriteTiming.FSMC_CLKDivision = 0x00;
	readWriteTiming.FSMC_DataLatency = 0x00;
	readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A; // Mode A

	writeTiming.FSMC_AddressSetupTime = 0x00; // Address setup time (ADDSET) is 1 HCLK
	writeTiming.FSMC_AddressHoldTime = 0x00;
	writeTiming.FSMC_DataSetupTime = TFTLCD_DRIVER_SPEED; // Data save time
	writeTiming.FSMC_BusTurnAroundDuration = 0x00;
	writeTiming.FSMC_CLKDivision = 0x00;
	writeTiming.FSMC_DataLatency = 0x00;
	writeTiming.FSMC_AccessMode = FSMC_AccessMode_A; // Mode A

	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1; // Select the address of the external storage area
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // Configure whether the data and address lines are multiplexed
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR; // Configure the type of external storage
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b; // Set the data width of the FSMC interface

	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable; // Configure access mode
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low; // Configure the polarity of the wait signal
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable; // Configure whether to use non-alignment
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState; // Configure when to wait for signals
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable; // Configure whether to use wait signals
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; // Configure whether to allow burst writes

	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable; // Configuration write operation enabled
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // Configure whether to use extended mode

	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; // Read timing
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming; // Write timing

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
	// Enable FSMC Bank1_SRAM Bank
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, 1);
}