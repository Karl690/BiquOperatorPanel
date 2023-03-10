#pragma once
#include <stdint.h>

typedef struct
{
	volatile uint16_t LCD_REG;
	volatile uint16_t LCD_RAM;
} LCD_TypeDef;

#define LCD_BASE        ((uint32_t)(0x60000000 | 0x00FFFFFE))  // 1111 1111 1111 1111 1111 1110
#define LCD             ((LCD_TypeDef *) LCD_BASE)

#define LCD_WR_REG(regval) do{ LCD->LCD_REG = regval; }while(0)
#define LCD_WR_DATA(data)  do{ LCD->LCD_RAM = data; }while(0)



#define FSMC_AccessMode_A                        ((uint32_t)0x00000000)
#define FSMC_AccessMode_B                        ((uint32_t)0x10000000) 
#define FSMC_AccessMode_C                        ((uint32_t)0x20000000)
#define FSMC_AccessMode_D                        ((uint32_t)0x30000000)
#define IS_FSMC_ACCESS_MODE(MODE) (((MODE) == FSMC_AccessMode_A) || \
                                   ((MODE) == FSMC_AccessMode_B) || \
                                   ((MODE) == FSMC_AccessMode_C) || \
                                   ((MODE) == FSMC_AccessMode_D))
	
#define FSMC_Bank1_NORSRAM1                             ((uint32_t)0x00000000)
#define FSMC_Bank1_NORSRAM2                             ((uint32_t)0x00000002)
#define FSMC_Bank1_NORSRAM3                             ((uint32_t)0x00000004)
#define FSMC_Bank1_NORSRAM4                             ((uint32_t)0x00000006)
	
#define FSMC_DataAddressMux_Disable                       ((uint32_t)0x00000000)
#define FSMC_DataAddressMux_Enable                        ((uint32_t)0x00000002)
#define IS_FSMC_MUX(MUX) (((MUX) == FSMC_DataAddressMux_Disable) || \
                          ((MUX) == FSMC_DataAddressMux_Enable))
	
#define FSMC_MemoryDataWidth_8b                         ((uint32_t)0x00000000)
#define FSMC_MemoryDataWidth_16b                        ((uint32_t)0x00000010)
#define IS_FSMC_MEMORY_WIDTH(WIDTH) (((WIDTH) == FSMC_MemoryDataWidth_8b) || \
                                     ((WIDTH) == FSMC_MemoryDataWidth_16b))
	
#define FSMC_BurstAccessMode_Disable                    ((uint32_t)0x00000000)
#define FSMC_BurstAccessMode_Enable                     ((uint32_t)0x00000100)
#define IS_FSMC_BURSTMODE(STATE) (((STATE) == FSMC_BurstAccessMode_Disable) || \
                                  ((STATE) == FSMC_BurstAccessMode_Enable))
	
#define FSMC_WaitSignalPolarity_Low                     ((uint32_t)0x00000000)
#define FSMC_WaitSignalPolarity_High                    ((uint32_t)0x00000200)
#define IS_FSMC_WAIT_POLARITY(POLARITY) (((POLARITY) == FSMC_WaitSignalPolarity_Low) || \
                                         ((POLARITY) == FSMC_WaitSignalPolarity_High))

#define FSMC_MemoryType_SRAM                     ((uint32_t)0x00000000)
#define FSMC_MemoryType_PSRAM                    ((uint32_t)0x00000004)
#define FSMC_MemoryType_NOR                      ((uint32_t)0x00000008)
#define IS_FSMC_MEMORY(MEMORY) (((MEMORY) == FSMC_MemoryType_SRAM) || \
                                ((MEMORY) == FSMC_MemoryType_PSRAM)|| \
                                ((MEMORY) == FSMC_MemoryType_NOR))
/** @defgroup FSMC_Wrap_Mode 
  * @{
  */
#define FSMC_WrapMode_Disable                    ((uint32_t)0x00000000)
#define FSMC_WrapMode_Enable                     ((uint32_t)0x00000400) 
#define IS_FSMC_WRAP_MODE(MODE) (((MODE) == FSMC_WrapMode_Disable) || \
                                 ((MODE) == FSMC_WrapMode_Enable))
	
#define FSMC_AsynchronousWait_Disable            ((uint32_t)0x00000000)
#define FSMC_AsynchronousWait_Enable             ((uint32_t)0x00008000)
#define IS_FSMC_ASYNWAIT(STATE) (((STATE) == FSMC_AsynchronousWait_Disable) || \
                                 ((STATE) == FSMC_AsynchronousWait_Enable))
	
#define FSMC_WaitSignalActive_BeforeWaitState    ((uint32_t)0x00000000)
#define FSMC_WaitSignalActive_DuringWaitState    ((uint32_t)0x00000800) 
#define IS_FSMC_WAIT_SIGNAL_ACTIVE(ACTIVE) (((ACTIVE) == FSMC_WaitSignalActive_BeforeWaitState) || \
                                            ((ACTIVE) == FSMC_WaitSignalActive_DuringWaitState))
	
#define FSMC_WaitSignal_Disable                  ((uint32_t)0x00000000)
#define FSMC_WaitSignal_Enable                   ((uint32_t)0x00002000) 
#define IS_FSMC_WAITE_SIGNAL(SIGNAL) (((SIGNAL) == FSMC_WaitSignal_Disable) || \
                                      ((SIGNAL) == FSMC_WaitSignal_Enable))
	
#define FSMC_WriteBurst_Disable                  ((uint32_t)0x00000000)
#define FSMC_WriteBurst_Enable                   ((uint32_t)0x00080000) 
#define IS_FSMC_WRITE_BURST(BURST) (((BURST) == FSMC_WriteBurst_Disable) || \
                                    ((BURST) == FSMC_WriteBurst_Enable))
	
#define FSMC_WriteOperation_Disable                     ((uint32_t)0x00000000)
#define FSMC_WriteOperation_Enable                      ((uint32_t)0x00001000)
#define IS_FSMC_WRITE_OPERATION(OPERATION) (((OPERATION) == FSMC_WriteOperation_Disable) || \
                                            ((OPERATION) == FSMC_WriteOperation_Enable))  
	
#define FSMC_ExtendedMode_Disable                ((uint32_t)0x00000000)
#define FSMC_ExtendedMode_Enable                 ((uint32_t)0x00004000)

#define IS_FSMC_EXTENDED_MODE(MODE) (((MODE) == FSMC_ExtendedMode_Disable) || \
                                     ((MODE) == FSMC_ExtendedMode_Enable)) 
	
	/* FSMC BCRx Mask */
#define BCR_MBKEN_Set                       ((uint32_t)0x00000001)
#define BCR_MBKEN_Reset                     ((uint32_t)0x000FFFFE)
#define BCR_FACCEN_Set                      ((uint32_t)0x00000040)

/* FSMC PCRx Mask */
#define PCR_PBKEN_Set                       ((uint32_t)0x00000004)
#define PCR_PBKEN_Reset                     ((uint32_t)0x000FFFFB)
#define PCR_ECCEN_Set                       ((uint32_t)0x00000040)
#define PCR_ECCEN_Reset                     ((uint32_t)0x000FFFBF)
#define PCR_MemoryType_NAND                 ((uint32_t)0x00000008)
/** 
  * @brief  Timing parameters For NOR/SRAM Banks  
  */
typedef struct
{
	uint32_t FSMC_AddressSetupTime; /*!< Defines the number of HCLK cycles to configure
	                                           the duration of the address setup time. 
	                                           This parameter can be a value between 0 and 0xF.
	                                           @note This parameter is not used with synchronous NOR Flash memories. */

	uint32_t FSMC_AddressHoldTime; /*!< Defines the number of HCLK cycles to configure
	                                           the duration of the address hold time.
	                                           This parameter can be a value between 0 and 0xF. 
	                                           @note This parameter is not used with synchronous NOR Flash memories.*/

	uint32_t FSMC_DataSetupTime; /*!< Defines the number of HCLK cycles to configure
	                                           the duration of the data setup time.
	                                           This parameter can be a value between 0 and 0xFF.
	                                           @note This parameter is used for SRAMs, ROMs and asynchronous multiplexed NOR Flash memories. */

	uint32_t FSMC_BusTurnAroundDuration; /*!< Defines the number of HCLK cycles to configure
	                                           the duration of the bus turnaround.
	                                           This parameter can be a value between 0 and 0xF.
	                                           @note This parameter is only used for multiplexed NOR Flash memories. */

	uint32_t FSMC_CLKDivision; /*!< Defines the period of CLK clock output signal, expressed in number of HCLK cycles.
	                                           This parameter can be a value between 1 and 0xF.
	                                           @note This parameter is not used for asynchronous NOR Flash, SRAM or ROM accesses. */

	uint32_t FSMC_DataLatency; /*!< Defines the number of memory clock cycles to issue
	                                           to the memory before getting the first data.
	                                           The parameter value depends on the memory type as shown below:
	                                            - It must be set to 0 in case of a CRAM
	                                            - It is don't care in asynchronous NOR, SRAM or ROM accesses
	                                            - It may assume a value between 0 and 0xF in NOR Flash memories
	                                              with synchronous burst mode enable */

	uint32_t FSMC_AccessMode; /*!< Specifies the asynchronous access mode. 
	                                           This parameter can be a value of @ref FSMC_Access_Mode */
}FSMC_NORSRAMTimingInitTypeDef;

/** 
  * @brief  FSMC NOR/SRAM Init structure definition
  */
typedef struct
{
	uint32_t FSMC_Bank; /*!< Specifies the NOR/SRAM memory bank that will be used.
	                                        This parameter can be a value of @ref FSMC_NORSRAM_Bank */

	uint32_t FSMC_DataAddressMux; /*!< Specifies whether the address and data values are
	                                        multiplexed on the data bus or not. 
	                                        This parameter can be a value of @ref FSMC_Data_Address_Bus_Multiplexing */

	uint32_t FSMC_MemoryType; /*!< Specifies the type of external memory attached to
	                                        the corresponding memory bank.
	                                        This parameter can be a value of @ref FSMC_Memory_Type */

	uint32_t FSMC_MemoryDataWidth; /*!< Specifies the external memory device width.
	                                        This parameter can be a value of @ref FSMC_Data_Width */

	uint32_t FSMC_BurstAccessMode; /*!< Enables or disables the burst access mode for Flash memory,
	                                        valid only with synchronous burst Flash memories.
	                                        This parameter can be a value of @ref FSMC_Burst_Access_Mode */

	uint32_t FSMC_AsynchronousWait; /*!< Enables or disables wait signal during asynchronous transfers,
	                                        valid only with asynchronous Flash memories.
	                                        This parameter can be a value of @ref FSMC_AsynchronousWait */                                          

	uint32_t FSMC_WaitSignalPolarity; /*!< Specifies the wait signal polarity, valid only when accessing
	                                        the Flash memory in burst mode.
	                                        This parameter can be a value of @ref FSMC_Wait_Signal_Polarity */

	uint32_t FSMC_WrapMode; /*!< Enables or disables the Wrapped burst access mode for Flash
	                                        memory, valid only when accessing Flash memories in burst mode.
	                                        This parameter can be a value of @ref FSMC_Wrap_Mode */

	uint32_t FSMC_WaitSignalActive; /*!< Specifies if the wait signal is asserted by the memory one
	                                        clock cycle before the wait state or during the wait state,
	                                        valid only when accessing memories in burst mode. 
	                                        This parameter can be a value of @ref FSMC_Wait_Timing */

	uint32_t FSMC_WriteOperation; /*!< Enables or disables the write operation in the selected bank by the FSMC. 
	                                        This parameter can be a value of @ref FSMC_Write_Operation */

	uint32_t FSMC_WaitSignal; /*!< Enables or disables the wait state insertion via wait
	                                        signal, valid for Flash memory access in burst mode. 
	                                        This parameter can be a value of @ref FSMC_Wait_Signal */

	uint32_t FSMC_ExtendedMode; /*!< Enables or disables the extended mode.
	                                        This parameter can be a value of @ref FSMC_Extended_Mode */

	uint32_t FSMC_WriteBurst; /*!< Enables or disables the write burst operation.
	                                        This parameter can be a value of @ref FSMC_Write_Burst */ 

	FSMC_NORSRAMTimingInitTypeDef* FSMC_ReadWriteTimingStruct; /*!< Timing Parameters for write and read access if the  Extended Mode is not used*/  

	FSMC_NORSRAMTimingInitTypeDef* FSMC_WriteTimingStruct; /*!< Timing Parameters for write access if the  Extended Mode is used*/      
}FSMC_NORSRAMInitTypeDef;




uint16_t LCD_RD_DATA(void);

void Setup_LCD_Hardware();
