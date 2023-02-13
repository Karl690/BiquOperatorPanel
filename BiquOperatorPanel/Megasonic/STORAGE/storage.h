#pragma once
#include "main.h"

typedef enum
{
	STORAGE_RAM,			/*Ram Storage           */
	STORAGE_ONCHIP_FLASH,	/*onchip flash, usually last sector of flash*/
	STORAGE_W25Q,			/*wqw25 serial flash chip*/
	STORAGE_SDCARD
} STORAGTYPEDEF ;

#define STORAGE_IN_FLASH 1
#ifndef STORAGE_IN_FLASH
/* Macro and function for operating(save/load) Calibration data in Ram */
#define CALIBRATIONDATA_STARTADDRESS (uint8_t*)(0x20000000 + 0x10000)   //we use RAM after 64kbye because the ram before 64k could be already use.
#define CALIBRATIONDATA_BLOCKSIZE	64
#define CALIBRATIONDATA_SIZE		4096	//4k
/* Macro and function for operating(save/load) Calibration data */
#define SOAPSTRING_STARTADDRESS (uint8_t*)(0x20000000 + 0x11000)   //Soapstring address would be started from 68K(0x11000) range of RAM.
#define SOAPSTRING_BLOCKSIZE	4096					//4k
#define SOAPSTRING_MAXBLOCKS     2                      //2 blocks for ram, 120 or flash
#define SOAPSTRING_ENDADDRESS	SOAPSTRING_STARTADDRESS + 0x2000	// for 407, RAM size is 128K. 
#else
/* Macro and function for operating(save/load) Calibration data in Flash */
#define CALIBRATIONDATA_STARTADDRESS (uint8_t*)0x80E0000    //we use Flash starting at beginning of last 128k block of memory
#define CALIBRATIONDATA_BLOCKSIZE	64
#define CALIBRATIONDATA_SIZE		0x1000	//4k
/* Macro and function for operating(save/load) Calibration data */
#define SOAPSTRING_STARTADDRESS (uint8_t*)(0x80E0000 + 0x1000)   //Soapstring address would be started from 68K(0x11000) range of RAM.
#define SOAPSTRING_BLOCKSIZE	0x1000					//4k
#define SOAPSTRING_MAXBLOCKS    15                     //2 blocks for ram, 120 or flash
#define SOAPSTRING_ENDADDRESS	SOAPSTRING_STARTADDRESS + 0xE000	// for 407, RAM size is 128K. 
#endif


extern uint8_t storageIndex; //used to control WHERE storage is taking place, ram, onchipflash, wq,sdio

uint8_t* getCalibrationDataBlockAddress(); //get the Current calibration address









//#define SOAPSTRING_USABLE_RANGE				12 * 1024 //for flash
uint8_t* FindNexSaveSoapstringAddress(); //get the availabe address of soapstring
uint8_t* FindCurrentSoapstringAddress(); //get the current soap string's address
void SaveData(uint8_t* address, uint8_t* data, uint16_t datasize);

void save_LCD_Touch_Calibration_Data(void);
uint8_t checkForValidLCDCalibrationData(void);
void saveSoapStringandEraseSector11(void);
void eraseStorage();
void eraseRamStorage();
void eraseFlashStorage();
void WriteSoapStringToStorage();
void LoadSoapStringFromStorage();

void SaveData(uint8_t* target, uint8_t* source, uint16_t datasize);
void SaveDataToRam(uint8_t* target, uint8_t* source, uint16_t datasize);
void SaveDataToOnChipFlash(uint8_t* target, uint8_t* source, uint16_t datasize);
void SaveDataToW25Q(uint8_t* target, uint8_t* source, uint16_t datasize);
void SaveDataToSDIOCard(uint8_t* target, uint8_t* source, uint16_t datasize);
//#endif
