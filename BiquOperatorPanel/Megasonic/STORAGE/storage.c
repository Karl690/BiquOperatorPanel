
#include "main.h"
#include "storage.h"


uint8_t storageIndex=0; //used to control WHERE storage is taking place, ram, onchipflash, wq,sdio

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


uint8_t* FindNexSaveSoapstringAddress()  //get the current soap string's address
{	
	uint32_t count = 0;
	uint8_t* currentSoapstringBlockPointer = NULL;
	for (count = 0; count < SOAPSTRING_MAXBLOCKS; count++)
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
			if (currentSoapStringAddress < (uint8_t*)SOAPSTRING_ENDADDRESS) 
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

void MoveData(uint8_t* target, uint8_t* source, uint16_t datasize)
{//moves data to storage device
	switch (storageIndex)
	{
	case STORAGE_RAM :
		MoveDataToRam(target, source, datasize);break;
	case STORAGE_ONCHIP_FLASH:
		MoveDataToOnChipFlash(target, source, datasize); break;	
	case STORAGE_W25Q :
		MoveDataToW25Q(target, source, datasize); break;
	case STORAGE_SDCARD :
		MoveDataToSDIOCard(target, source, datasize); break;
	}
}
//move the data from the source address to the target address.
void MoveDataToRam(uint8_t* target, uint8_t* source, uint16_t datasize)
{
	for (uint16_t i = 0; i < datasize; i++)
	{
		*target = source[i]; 
		target++;
	}
}
void MoveDataToOnChipFlash(uint8_t* target, uint8_t* source, uint16_t datasize)
{
	write_flash((uint32_t)target, source, datasize);//write the data to the flash module
}

void MoveDataToW25Q(uint8_t* target, uint8_t* source, uint16_t datasize)
{
	
}

void MoveDataToSDIOCard(uint8_t* target, uint8_t* source, uint16_t datasize)
{
}


uint8_t* currentCalibrationAddress = NULL;
uint8_t* currentSoapStringAddress = NULL;
void save_LCD_Touch_Calibration_Data(void)
{
	currentCalibrationAddress = getCalibrationDataBlockAddress(); //get current pointer in storage
	if (currentCalibrationAddress == NULL)
	{
		//no valid data was found;
		currentCalibrationAddress = (uint8_t*)CALIBRATIONDATA_STARTADDRESS;
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
		if (currentCalibrationAddress > (uint8_t*)(CALIBRATIONDATA_STARTADDRESS + CALIBRATIONDATA_SIZE))
		{
			//now we have reached past the 4k boundry and need to point back to the beginning
			saveSoapStringandEraseSector11();	
			return;
		}
	}
	//ok, when you get here, we should be pointing to 0xff values in the target storage memory
	MoveDataToRam(currentCalibrationAddress, (uint8_t*)&touchCalibrationInfo, sizeof(TouchCalibrationInfo));
}


void saveSoapStringTobuffer() //backup Soapstring from storage to FLASH.
{
	currentSoapStringAddress = FindNexSaveSoapstringAddress(); //get the current soapstring in storage.
	if (!currentSoapStringAddress) //Soapstring is not exsit in storage.		
	return; 
	
	MoveDataToRam(SoapStringBuffer, currentSoapStringAddress, SOAPSTRING_BLOCKSIZE); // SoapString copy from storage's currentSoapStringAddress.
}

void writeOldsoapstringFromBuffertoflashblock() //save the soapstring in storage
{
	uint8_t* currentSoapstringAddress = FindNexSaveSoapstringAddress(); //get the current soapstring in storage.
	if (!currentSoapstringAddress)
	{	
		currentSoapstringAddress = (uint8_t*)SOAPSTRING_STARTADDRESS; 
	}
	else
	{
		*currentSoapstringAddress = 0x0; //set flag as that is old block
		currentSoapstringAddress += SOAPSTRING_BLOCKSIZE; // move to next block
		if (currentSoapstringAddress + SOAPSTRING_BLOCKSIZE > (uint8_t*)SOAPSTRING_ENDADDRESS)
		{
			currentSoapstringAddress = (uint8_t*)SOAPSTRING_STARTADDRESS;
			saveSoapStringandEraseSector11(); // it need to erase storage.
			return;
		}
	}	
	//copy the SoapstringBuffer to storage.
	MoveDataToRam(currentSoapstringAddress, (uint8_t*)&SoapStringBuffer, SOAPSTRING_BLOCKSIZE); 
}

	



//write the Nude name and value into Soap string
uint16_t WriteSoapValuePair(uint16_t pairIndex, uint8_t* address) 
{
	if (!SoapNudsList[pairIndex])  return 0;
	char stringValuePair[WIDGET_MAX_TEXT_LENGTH] = { 0 };
	
	sprintf(stringValuePair, "%s,%.3f;", SoapNudsList[pairIndex]->Name, SoapNudsList[pairIndex]->Value); // format: name,value;
	uint16_t len = strlen(stringValuePair);
	if (address + len >= (uint8_t*)SOAPSTRING_ENDADDRESS) return 0; //out of memory
	//memcpy(address, stringValuePair, len); // copy the var pair's string to the address	
	MoveDataToRam(address, (uint8_t*)stringValuePair, len);
	return len;
	
}

void eraseSoapStringData_copyCalibrationDataTobeginning()
{
	//so we need to 
//1. take a deep breath  :-)
	//2. copyLastCalibrationDataToRamBuffer // we dont need this because we have already the buffer in Flash.  touchCalibrationInfo is load on Power on.
	eraseRamStorage(); //3. erase flash
	save_LCD_Touch_Calibration_Data(); //4. writeTempCalibrationDataToFlash(START_OF_CALIBRATION_DATA);
}
void eraseSoapStringData_CopySoapstringbeginning()
{
	//so we need to 
	//1. take a deep breath  :-)
	LoadSoapStringFromStorage(); //2. copyLastSoapStringToRamBuffer
	eraseRamStorage(); //3. erase flash
	WriteSoapStringToStorage(); //4. writeTempSoapStringToFlash(SOAPSTRING_STARTADDRESS);
	
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
		SizeOfMySoapString += len; //add up the total string length	
	}
	return SizeOfMySoapString;
}
void WriteSoapStringToStorage()
{
	uint8_t* SoapstringAddress = FindNexSaveSoapstringAddress(); //find where the empty flash starts
	if (!SoapstringAddress) return; // do nothing if it did not found out the address to write soapstring
	//lvana please check to see if there is enough room for the soapstring to write

	uint16_t writtenBytes = 0;
	*SoapstringAddress = 0x4; //put EOT charactor
	SoapstringAddress++; //increase the address 
	for (uint16_t i = 0; SoapNudsList[i] != NULL; i++)
	{
		writtenBytes = WriteSoapValuePair(i, SoapstringAddress); //write the varpairs at the address of storage
		if (writtenBytes == 0)
		{
			//if we get here, we just blew past the end of the flashstorage space
			//so we need to erase and point again
			eraseSoapStringData_copyCalibrationDataTobeginning();
			SoapstringAddress = (uint8_t*)SOAPSTRING_STARTADDRESS;
			i = 0xffff;
			continue;
			//break;							//stop the write soapstring
		}
		
		//I didn't know if I should call the function to get the next address here, so I just increased the address.
		SoapstringAddress += writtenBytes; //increase the address as written length.
	
	}
}


//find the start address of VarpairList with the end address
//address is the end address
uint8_t* FindVarPairListAddress(uint8_t* address) 
{
	uint8_t* StartAddress = address - 1; // this address would go down 
	for (StartAddress = address; StartAddress >= (uint8_t*)SOAPSTRING_STARTADDRESS; StartAddress--)
	{
		if (*StartAddress == 0x04) return StartAddress;		
	}
	return NULL;
}

uint8_t ParseVarPairstring(uint16_t  VarpairIndex, char* varpairstring) 
{
	uint8_t result = 0, index = 0;
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
	for (uint8_t* StartAddress = EndSoapstringAddress - 1; StartAddress >= (uint8_t*)SOAPSTRING_STARTADDRESS; StartAddress--)
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
	for (uint8_t* address = StartSoapstringAddress; address < EndSoapstringAddress; address++)
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
		if (VarPairAddress - VarPair > WIDGET_MAX_TEXT_LENGTH) // 
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
	//determines if we are using RAM or Flash for storage, then erases correct secotors
#ifdef 	STORAGE_IN_FLASH
	eraseFlashStorage(); //normal operation from Flash storage
#else	
	eraseRamStorage(); //working with Ram storage, so erase the ram.
#endif
}
void eraseFlashStorage()
{
	erase_flash();
}
void eraseRamStorage()
{
	/// Erase storaage .. to do

	currentCalibrationAddress = (uint8_t*)CALIBRATIONDATA_STARTADDRESS;
	currentSoapStringAddress = (uint8_t*)SOAPSTRING_STARTADDRESS;
	
	for (uint8_t* i = CALIBRATIONDATA_STARTADDRESS; i < (uint8_t*)CALIBRATIONDATA_STARTADDRESS + CALIBRATIONDATA_SIZE; i++) 
		*(uint8_t*)i = 0xFF;
	
	for (uint8_t* i = SOAPSTRING_STARTADDRESS; i < (uint8_t*)SOAPSTRING_ENDADDRESS; i++) 
		*(uint8_t*)i = 0xFF;
}
void saveSoapStringandEraseSector11() // I think this function name is not correct.
{
	saveSoapStringTobuffer(); //backup soapstring in storage to buffer
	eraseRamStorage(); //erase the storage and set the address as start.
	MoveDataToRam(currentCalibrationAddress, (uint8_t*)&touchCalibrationInfo, CALIBRATIONDATA_BLOCKSIZE); //copy calibration buffer  to storage
	MoveDataToRam(currentSoapStringAddress, (uint8_t*)&SoapStringBuffer, SOAPSTRING_BLOCKSIZE); //copy soapstring buffer to storage
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
		MoveDataToRam((uint8_t*)&touchCalibrationInfo, currentCalibrationAddress, sizeof(TouchCalibrationInfo)); //update working variables from storage
		return 1;//updated so report successfully found and updated
	}
	return 0; //invalid address
}
