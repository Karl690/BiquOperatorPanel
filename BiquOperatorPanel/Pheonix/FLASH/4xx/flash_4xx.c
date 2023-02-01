
#include "configure.h"
#include "main.h"
#include <ctype.h>
#include <stdlib.h>
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
uint8_t* FindNexSaveSoapstringAddress()  //get the current soap string's address
{	
	uint32_t count = 0;
	uint8_t* currentSoapstringBlockPointer = NULL;
	for (count = 0; count < SOAPSTRING_MAXBLOCKS; count ++)
	{
		currentSoapstringBlockPointer = (uint8_t*)(SOAPSTRING_STARTADDRESS + (count * SOAPSTRING_BLOCKSIZE));
		if (*currentSoapstringBlockPointer == 0xff) //check if the first byte of the block is ascii charactor. 
		{
			//at this point, we found a 4k block that starts with 0xff, so it is empty
			//now we go back one block to find the end of valid data, and that is our starting point
			//for new valuepairs.
			if (count == 0)return currentSoapstringBlockPointer; //first byte i 128k page is empty. so leave

			currentSoapstringBlockPointer -= SOAPSTRING_BLOCKSIZE; //point to the beginning of the block before
			//now starting with the first byte, we look for the first 0xff , 
			//that is where we will start writing new data
			for (count = 0; count < 4096; count++)
			{
				if (*currentSoapstringBlockPointer == 0xff)
				{
					return currentSoapstringBlockPointer;
				}
				currentSoapstringBlockPointer++; //walk forward and check next byte
			}
			//if you get here, we are on 4096 byte boundry
			currentSoapStringAddress++; //walk forward and check next byte
			if (currentSoapStringAddress < SOAPSTRING_ENDADDRESS) 
			{
				return currentSoapstringBlockPointer;
			}
			{
				//get here and we have gotten to end of the page
				//copy last 4k block to Ram
				//erase entire 128k page
				//write 4kblock to first block of soap string ram.
			}
		
		}
	}
	return NULL; // it need to erase flash.
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
	currentSoapStringAddress = FindNexSaveSoapstringAddress(); //get the current soapstring in storage.
	if (!currentSoapStringAddress) //Soapstring is not exsit in storage.		
		return; 
	
	MoveData(SoapStringBuffer, currentSoapStringAddress, SOAPSTRING_BLOCKSIZE); // SoapString copy from storage's currentSoapStringAddress.
}

void writeOldsoapstringFromBuffertoflashblock() //save the soapstring in storage
{
	uint8_t* currentSoapstringAddress = FindNexSaveSoapstringAddress(); //get the current soapstring in storage.
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

	



//write the Nude name and value into Soap string
uint16_t WriteSoapValuePair(uint16_t pairIndex, uint8_t* address) 
{
	if (!SoapNudsList[pairIndex])  return 0;
	char stringValuePair[WIDGET_MAX_TEXT_LENGTH] = { 0 };
	
	sprintf(stringValuePair, "%s,%.3f;", SoapNudsList[pairIndex]->Name, SoapNudsList[pairIndex]->Value); // format: name,value;
	uint16_t len = strlen(stringValuePair);
	if (address + len >= SOAPSTRING_ENDADDRESS) return 0; //out of memory
	
	memcpy(address, stringValuePair, len); // copy the var pair's string to the address	
	return len;
	
}

void eraseSoapStringData_copyCalibrationDataTobeginning()
{
	//so we need to 
//1. take a deep breath  :-)
	//2. copyLastCalibrationDataToRamBuffer // we dont need this because we have already the buffer in Flash.  touchCalibrationInfo is load on Power on.
	eraseStorage();//3. erase flash
	save_LCD_Touch_Calibration_Data(); //4. writeTempCalibrationDataToFlash(START_OF_CALIBRATION_DATA);
}
void eraseSoapStringData_CopySoapstringbeginning()
{
	//so we need to 
	//1. take a deep breath  :-)
	LoadSoapStringFromStorage();	//2. copyLastSoapStringToRamBuffer
	eraseStorage();					//3. erase flash
	WriteSoapStringToStorage();		//4. writeTempSoapStringToFlash(SOAPSTRING_STARTADDRESS);
	
}


/*lvana , the expected memory storage format is
 *0x04 start of soapstring char
 *firstObjectName,firstObjectvalue.tostring();
 *secondObjectName,secondObjectValue.tostring90;      note the , and the ; are atual chars in this
 *0xff                                                end of the soap string
 **/
uint32_t calculateSoapStringSize()
{
	uint32_t SizeOfMySoapString = 0;
	char CalcString[60];
	
	for (uint16_t pairIndex = 0; SoapNudsList[pairIndex] != NULL; pairIndex++)
	{
		if (!SoapNudsList[pairIndex])  continue;
		uint16_t writtenBytes = 0;
		sprintf(CalcString, "%s,%.3f;", SoapNudsList[pairIndex]->Name, SoapNudsList[pairIndex]->Value); // format: name,value;
		uint16_t len = strlen(CalcString);
		SizeOfMySoapString += len;//add up the total string length	
	}
	return SizeOfMySoapString;
}
void WriteSoapStringToStorage()
{
	uint8_t* SoapstringAddress = FindNexSaveSoapstringAddress();//find where the empty flash starts
	if (!SoapstringAddress) return; // do nothing if it did not found out the address to write soapstring
	//lvana please check to see if there is enough room for the soapstring to write

	uint16_t writtenBytes = 0;
	*SoapstringAddress = 0x4; //put EOT charactor
	SoapstringAddress++; //increase the address 
	for (uint16_t i = 0; SoapNudsList[i] != NULL; i++)
	{
		writtenBytes = WriteSoapValuePair(i, SoapstringAddress); //write the varpairs at the address of storage
		if (writtenBytes == 0)
		{//if we get here, we just blew past the end of the flashstorage space
			//so we need to erase and point again
			eraseSoapStringData_copyCalibrationDataTobeginning();
			SoapstringAddress = SOAPSTRING_STARTADDRESS;
			i = 0xffff;
			continue;
			//break;							//stop the write soapstring
		}
		
		//I didn't know if I should call the function to get the next address here, so I just increased the address.
		SoapstringAddress += writtenBytes;							//increase the address as written length.
	
	}
}


//find the start address of VarpairList with the end address
//address is the end address
uint8_t* FindVarPairListAddress(uint8_t* address) 
{
	uint8_t* StartAddress = address - 1; // this address would go down 
	for (StartAddress = address; StartAddress >= SOAPSTRING_STARTADDRESS; StartAddress--)
	{
		if (*StartAddress == 0x04) return StartAddress;		
	}
	return NULL;
}

uint8_t ParseVarPairstring(uint16_t  VarpairIndex, char* varpairstring) 
{
	uint8_t result = 0, index =0;
	uint16_t len = strlen(varpairstring);
	uint8_t name[WIDGET_MAX_TEXT_LENGTH / 2] = { 0 };
	uint8_t value[WIDGET_MAX_TEXT_LENGTH / 2] = { 0 };
	for (index = 0; index < len; index++)
	{
		if (varpairstring[index] == ',')
		{
			strncpy(name, varpairstring, index);
			strncpy(value, varpairstring + index + 1, len - index - 2); //minus 2 becasue it include ',' and ';'
			if (strcmp(name, (char*)&SoapNudsList[VarpairIndex]->Name[0]) != 0) break; // it means that is not for the control
			float fvalue = atof(value);
			numeric_set_value(SoapNudsList[VarpairIndex], fvalue); //set the value to control
			result = 1;
			break;
		}
	}
	return 1;
}

uint8_t* FindCurrentSoapstringAddress()
{
	uint8_t* EndSoapstringAddress = FindNexSaveSoapstringAddress();
	if (EndSoapstringAddress == NULL) return NULL;
	for (uint8_t* StartAddress = EndSoapstringAddress - 1; StartAddress >= SOAPSTRING_STARTADDRESS; StartAddress--)
	{
		if (*StartAddress == 0x04) return StartAddress;		
	}
	return NULL;
}
void LoadSoapStringFromStorage() 
{
	uint8_t* EndSoapstringAddress = FindNexSaveSoapstringAddress();
	if (!EndSoapstringAddress) return; //do nothing
	uint8_t* StartSoapstringAddress = FindVarPairListAddress(EndSoapstringAddress); //with the end of Soapstring, find out the start address of soapstring
	if (!StartSoapstringAddress) return; //do nothing because it means that it does not find out the address.
	char VarPair[WIDGET_MAX_TEXT_LENGTH] = { 0 };
	StartSoapstringAddress++; // add  1 because the first byte is 0x04
	
	uint8_t flag  = 1;
	char* VarPairAddress = VarPair;
	uint16_t VarpairIndex = 0;
	for (uint8_t* address = StartSoapstringAddress; address < EndSoapstringAddress; address ++)
	{
		if (*address == ';')
		{
			//at this point we parse the Varpair string and put the value at the corresponding control
			ParseVarPairstring(VarpairIndex, VarPair);
			VarpairIndex++; 
			memset(VarPair, 0, WIDGET_MAX_TEXT_LENGTH); //reset the buffer.
			VarPairAddress = VarPair; //set the first address of Buffer at VarPairAddress
			if (VarpairIndex >= LIST_MAX_LENGH || SoapNudsList[VarpairIndex] == NULL) break; //escape, in this case
			continue;
		}
		*VarPairAddress = *address;
		if (VarPairAddress - VarPair > WIDGET_MAX_TEXT_LENGTH ) // 
		{
			break; // it means that is not normal.
		}
		else
		{
			VarPairAddress++;	
		}
	}
}


void eraseStorage()
{
	/// Erase storaage .. to do
	currentCalibrationAddress = CALIBRATIONDATA_STARTADDRESS;
	currentSoapStringAddress = SOAPSTRING_STARTADDRESS;
	
	for (uint32_t i = CALIBRATIONDATA_STARTADDRESS; i < CALIBRATIONDATA_STARTADDRESS + CALIBRATIONDATA_SIZE; i++) 
		*(uint8_t*)i = 0xFF;
	
	for (uint32_t i = SOAPSTRING_STARTADDRESS; i < SOAPSTRING_ENDADDRESS; i++) 
		*(uint8_t*)i = 0xFF;
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
