
#include "configure.h"
//#if defined(FK_407) || defined(CORE_407I)
#ifdef USE_FLASH
//#include "taskmanager.h"
#include "flash_4xx.h"
void FLASH_Unlock(void)
{
	if ((FLASH->CR & FLASH_CR_LOCK) != RESET)
	{
		/* Authorize the FLASH Registers access */
		FLASH->KEYR = FLASH_KEY1;
		FLASH->KEYR = FLASH_KEY2;
	}  
}

/**
  * @brief  Locks the FLASH control register access
  * @param  None
  * @retval None
  */
void FLASH_Lock(void)
{
	/* Set the LOCK Bit to lock the FLASH Registers access */
	FLASH->CR |= FLASH_CR_LOCK;
}

FLASH_Status FLASH_GetStatus(void)
{
	FLASH_Status flashstatus = FLASH_COMPLETE;
  
	if ((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY) 
	{
		flashstatus = FLASH_BUSY;
	}
	else 
	{  
		if ((FLASH->SR & FLASH_FLAG_WRPERR) != (uint32_t)0x00)
		{ 
			flashstatus = FLASH_ERROR_WRP_A;
		}
		else 
		{
			if ((FLASH->SR & (uint32_t)0xEF) != (uint32_t)0x00)
			{
				flashstatus = FLASH_ERROR_PROGRAM_A; 
			}
			else
			{
				if ((FLASH->SR & FLASH_FLAG_OPERR) != (uint32_t)0x00)
				{
					flashstatus = FLASH_ERROR_OPERATION_A;
				}
				else
				{
					flashstatus = FLASH_COMPLETE;
				}
			}
		}
	}
	/* Return the FLASH Status */
	return flashstatus;
}
FLASH_Status FLASH_WaitForLastOperationA(void)
{ 
	__IO FLASH_Status status = FLASH_COMPLETE;
   
	/* Check for the FLASH Status */
	status = FLASH_GetStatus();

	/* Wait for the FLASH operation to complete by polling on BUSY flag to be reset.
	   Even if the FLASH operation fails, the BUSY flag will be reset and an error
	   flag will be set */
	while (status == FLASH_BUSY)
	{
		status = FLASH_GetStatus();
	}
	/* Return the operation status */
	return status;
}

#define SECTOR_MASK               ((uint32_t)0xFFFFFF07)
FLASH_Status FLASH_EraseSector(uint32_t FLASH_Sector, uint8_t VoltageRange)
{
	uint32_t tmp_psize = 0x0;
	FLASH_Status status = FLASH_COMPLETE;

	/* Check the parameters */
	assert_param(IS_FLASH_SECTOR(FLASH_Sector));
	assert_param(IS_VOLTAGERANGE(VoltageRange));
  
	if (VoltageRange == VoltageRange_1)
	{
		tmp_psize = FLASH_PSIZE_BYTE;
	}
	else if (VoltageRange == VoltageRange_2)
	{
		tmp_psize = FLASH_PSIZE_HALF_WORD;
	}
	else if (VoltageRange == VoltageRange_3)
	{
		tmp_psize = FLASH_PSIZE_WORD;
	}
	else
	{
		tmp_psize = FLASH_PSIZE_DOUBLE_WORD;
	}
	/* Wait for last operation to be completed */
	status = FLASH_WaitForLastOperationA();
  
	if (status == FLASH_COMPLETE)
	{ 
		/* if the previous operation is completed, proceed to erase the sector */
		FLASH->CR &= CR_PSIZE_MASK;
		FLASH->CR |= tmp_psize;
		FLASH->CR &= SECTOR_MASK;
		FLASH->CR |= FLASH_CR_SER | FLASH_Sector;
		FLASH->CR |= FLASH_CR_STRT;
    
		/* Wait for last operation to be completed */
		status = FLASH_WaitForLastOperationA();
    
		/* if the erase operation is completed, disable the SER Bit */
		FLASH->CR &= (~FLASH_CR_SER);
		FLASH->CR &= SECTOR_MASK; 
	}
	/* Return the Erase Status */
	return status;
}

FLASH_Status FLASH_ProgramByte(uint32_t Address, uint8_t Data)
{
	FLASH_Status status = FLASH_COMPLETE;

	/* Check the parameters */
	//assert_param(IS_FLASH_ADDRESS(Address));

	/* Wait for last operation to be completed */
	status = FLASH_WaitForLastOperationA();
  
	if (status == FLASH_COMPLETE)
	{
		/* if the previous operation is completed, proceed to program the new data */
		FLASH->CR &= CR_PSIZE_MASK;
		FLASH->CR |= FLASH_PSIZE_BYTE;
		FLASH->CR |= FLASH_CR_PG;
  
		*(__IO uint8_t*)Address = Data;
        
		/* Wait for last operation to be completed */
		status = FLASH_WaitForLastOperationA();

		/* if the program operation is completed, disable the PG Bit */
		FLASH->CR &= (~FLASH_CR_PG);
	} 

	/* Return the Program Status */
	return status;
}


uint8_t EraseFlash(uint32_t sector)
{
	FLASH_Unlock();
	FLASH_Status status = FLASH_EraseSector(FLASH_LAST_SECTOR, VoltageRange_3);	
	//status = FLASH_ProgramByte(FLASH_LAST_ADDRESS, 0x50);
	//status = FLASH_ProgramByte(FLASH_LAST_ADDRESS+1, 0x60);
	FLASH_Lock();
	return status;
}

uint8_t read_memory(uint32_t addr, uint8_t* data, uint32_t len) {

	for(uint16_t i = 0; i < len; i ++) {
		data[i] = *(__IO uint8_t*)(FLASH_LAST_ADDRESS + addr  + i);

	}
	return SUCCESS;
}

uint8_t write_memory( uint32_t addr, uint8_t* data, uint32_t len )
{
	uint8_t result = SUCCESS;
	FLASH_Unlock();
	FLASH_Status status;	
	for(uint8_t i = 0; i < len; i ++)
	{
		//if(data[i] == 0x0 || data[i] == 0xff) break;
		status  = FLASH_ProgramByte(FLASH_LAST_ADDRESS + addr + i, data[i]);
		if (status != FLASH_COMPLETE)
		{
			result = ERROR;			
			break;
		}
	}

	FLASH_Lock();
	return result;
}

uint8_t erase_memory()
{
	EraseFlash(FLASH_LAST_SECTOR);
}

uint8_t* FindCurrentCalibrationDataAddress()
{
	uint16_t i = 0;	
	uint8_t* currentcalibrationDataBlockPointer = NULL;
	for (i = 0; i < CALIBRATIONDATA_SIZE; i += CALIBRATIONDATA_BLOCKSIZE)
	{
		currentcalibrationDataBlockPointer = (uint8_t*)(CALIBRATIONDATA_STARTADDRESS + i);
		//three possible values here  0=old table, 0x80=current table,0ff=emptytable 
		if (*currentcalibrationDataBlockPointer != 0x80)
		{
			return currentcalibrationDataBlockPointer;
		}
	}
	return NULL; // it need to erase flash.
}
uint8_t* getCalibrationDataBlockAddress()
{
	uint16_t i = 0;	
	uint8_t* currentcalibrationDataBlockPointer = NULL;
	for (i = 0; i < CALIBRATIONDATA_SIZE; i += CALIBRATIONDATA_BLOCKSIZE)
	{
		currentcalibrationDataBlockPointer = (uint8_t*)(CALIBRATIONDATA_STARTADDRESS + i);
		if (*currentcalibrationDataBlockPointer == 0x80)
		{
			return currentcalibrationDataBlockPointer;
		}
	}
	return NULL; // it need to erase flash.
}
void MoveData(uint8_t* address, uint8_t* data, uint16_t datasize)
{
	for (uint16_t i = 0; i < datasize; i++)
	{
		*address = data[i];
		address++;
	}
}

#endif
//#endif
