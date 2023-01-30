
#include "configure.h"
#include "main.h"
#include <ctype.h>
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

/*to store a entire soapstring sequence of multiple objects 
 *first get the starting point in memory for the next storage location
 *getSoapstring4kBlockAddress() // now we have the 4k block
 *FindNextSaveAddress() // find the first empty byte
 *for
 *writeValuePair()
 *Next
 **/
uint8_t* FindNexSaveAddress()  //get the current soap string's address
{	
	uint8_t* count = NULL;
	uint8_t* currentSoapstringBlockPointer = NULL;
	for (count = 0; count < SOAPSTRING_MAXBLOCKS; count += SOAPSTRING_BLOCKSIZE)
	{
		currentSoapstringBlockPointer = (uint8_t*)(SOAPSTRING_STARTADDRESS + (count * SOAPSTRING_BLOCKSIZE));
		if (*currentSoapstringBlockPointer == 0xff) //check if the first byte of the block is ascii charactor. 
		{
			//at this point, we found a 4k block that starts with 0xff, so it is empty
			//now we go back one block to find the end of valid data, and that is our starting point
			//for new valuepairs.
			if (count == 0)return currentSoapstringBlockPointer; //first byte i 128k page is empty. so leave
			for (count = 0; count < 4096; count++)
			{
				if (*currentSoapstringBlockPointer == 0xff)
				{
					return currentSoapstringBlockPointer;
				}
				currentSoapStringAddress++; //walk forward and check next byte
			}
			//if you get here, we are on 4096 byte boundry
			currentSoapStringAddress++; //walk forward and check next byte
			if (currentSoapStringAddress < SOAPSTRING_ENDADDRESS) 
			{
				return currentSoapstringBlockPointer;
			}
			{//get here and we have gotten to end of the page
				//copy last 4k block to Ram
				//erase entire 128k page
				//write 4kblock to first block of soap string ram.
				
			}
		
		}
	}
	return NULL; // it need to erase flash.
}

string readNextValuePair(uint32_t nextValuePairAddress)
{//returns the next valuepair string
	
}
//move the data from the source address to the target address.
void MoveData(uint8_t* target, uint8_t* source, uint16_t datasize)
{
	for (uint16_t i = 0; i < datasize; i++)
	{
		*target = source[i]; 
		target++;
	}
}



uint8_t* currentCalibrationAddress = NULL;
uint8_t* currentSoapStringAddress = NULL;
void save_LCD_Touch_Calibration_Data(void)
{
	currentCalibrationAddress = getCalibrationDataBlockAddress(); //get current pointer in storage
	if (currentCalibrationAddress == NULL)
	{
		//no valid data was found;
		currentCalibrationAddress = CALIBRATIONDATA_STARTADDRESS;
		if (*currentCalibrationAddress != 0xff)
		{
			saveSoapStringandEraseSector11(); //erase and copy old soap to new starting block	
			return;
		}
	}
	else
	{
		//we have found valid block,now disable it and then incrment to next block
		*currentCalibrationAddress = 0; //zero out old pointer, data no longer valid
		currentCalibrationAddress += CALIBRATIONDATA_BLOCKSIZE; //point to next place in storage
		if (currentCalibrationAddress > CALIBRATIONDATA_STARTADDRESS + CALIBRATIONDATA_SIZE)
		{
			//now we have reached past the 4k boundry and need to point back to the beginning
			saveSoapStringandEraseSector11();	
			return;
		}
	}
	//ok, when you get here, we should be pointing to 0xff values in the target storage memory
	MoveData(currentCalibrationAddress, (uint8_t*)&touchCalibrationInfo, sizeof(TouchCalibrationInfo));
}


void saveSoapStringTobuffer() //backup Soapstring from storage to FLASH.
{
	currentSoapStringAddress = FindNexSaveAddress(); //get the current soapstring in storage.
	if (!currentSoapStringAddress) {
		//Soapstring is not exsit in storage.		
		return; 
	}
	MoveData(SoapStringBuffer, currentSoapStringAddress, SOAPSTRING_BLOCKSIZE); // SoapString copy from storage's currentSoapStringAddress.
}

void writeOldsoapstringFromBuffertoflashblock() //save the soapstring in storage
{
	uint8_t* currentSoapstringAddress = FindNexSaveAddress(); //get the current soapstring in storage.
	if (!currentSoapstringAddress)
	{	
		currentSoapstringAddress = SOAPSTRING_STARTADDRESS; 
	}
	else
	{
		*currentSoapstringAddress = 0x0; //set flag as that is old block
		currentSoapstringAddress += SOAPSTRING_BLOCKSIZE; // move to next block
		if (currentSoapstringAddress + SOAPSTRING_BLOCKSIZE > SOAPSTRING_ENDADDRESS)
		{
			currentSoapstringAddress = SOAPSTRING_STARTADDRESS;
			saveSoapStringandEraseSector11(); // it need to erase storage.
			return;
		}
	}	
	//copy the SoapstringBuffer to storage.
	MoveData(currentSoapstringAddress, (uint8_t*)&SoapStringBuffer, SOAPSTRING_BLOCKSIZE); 
}

	
void FindNextFlashSaveAddress()
{
	
}

void WriteSoapString()
{
	uint32_t SoapstringAddress = FindNexSaveAddress();
	for (uint16_t i = 0; SoapNudsList[i] != NULL; i++)
	{
		
	}
}
//write the Nude name and value into Soap string
void WriteSoapValuePair(uint16_t pairIndex, uint32_t address) 
{
	if (!SoapNudsList[pairIndex])  return;
	char stringValuePair[WIDGET_MAX_TEXT_LENGTH] = { 0 };
	
	sprintf(stringValuePair, "%s,%.3f;", SoapNudsList[pairIndex]->Name, SoapNudsList[pairIndex]->Value); // format: name,value;
	strcpy(address, stringValuePair); // connect the current nud name and value to soapstring.
}

void LoadSoapValuePare(uint16_t pairIndex, uint16_t address) 
{
	char stringValuePair[WIDGET_MAX_TEXT_LENGTH] = { 0 };
	
}


void eraseStorage()
{
	/// Erase storaage .. to do
	currentCalibrationAddress = CALIBRATIONDATA_STARTADDRESS;
	currentSoapStringAddress = SOAPSTRING_STARTADDRESS;
}
void saveSoapStringandEraseSector11() // I think this function name is not correct.
{
	saveSoapStringTobuffer(); //backup soapstring in storage to buffer
	eraseStorage(); //erase the storage and set the address as start.
	MoveData(currentCalibrationAddress, &touchCalibrationInfo, CALIBRATIONDATA_BLOCKSIZE); //copy calibration buffer  to storage
	MoveData(currentSoapStringAddress, &SoapStringBuffer, SOAPSTRING_BLOCKSIZE); //copy soapstring buffer to storage
	//writeOldsoapstringFromBuffertoflashblock[1] ;//todo
}

void clearcalibrtionData()
{
	uint8_t* workPointer = CALIBRATIONDATA_STARTADDRESS;
	for (int count = 0; count = 0x0fff; count++)
	{
		*workPointer = 0xff;
		workPointer++;
	}
}
uint8_t checkForValidLCDCalibrationData(void)
{
	//if it finds it, it will refresh the structure from storage
	//read_memory(0, (uint8_t*)&touchCalibrationInfo, sizeof(TouchCalibrationInfo));
	//if (touchCalibrationInfo.IsValid != 0x80) return 0;
	//uint32_t* currentCalibrationAddress = NULL;
	currentCalibrationAddress  = getCalibrationDataBlockAddress();
	if (currentCalibrationAddress == 0) return 0;//was a disaster and we did not find valid data
	if (*currentCalibrationAddress == 0x80)
	{
		//it is valid data, so lets update
		MoveData((uint8_t*)&touchCalibrationInfo, currentCalibrationAddress, sizeof(TouchCalibrationInfo)); //update working variables from storage
		return 1;//updated so report successfully found and updated
	}
	return 0; //invalid address
}

#endif
