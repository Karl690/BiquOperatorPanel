
#pragma once
#include <stdint.h>
#include "configure.h"
//#if defined(FK_407) || defined(CORE_407I)

typedef enum
{ 
	FLASH_BUSY            = 1,
	FLASH_ERROR_PGS_A,
	FLASH_ERROR_PGP_A,
	FLASH_ERROR_PGA_A,
	FLASH_ERROR_WRP_A,
	FLASH_ERROR_PROGRAM_A,
	FLASH_ERROR_OPERATION_A,
	FLASH_COMPLETE
}FLASH_Status;

#define VoltageRange_1        ((uint8_t)0x00)  /*!< Device operating range: 1.8V to 2.1V */
#define VoltageRange_2        ((uint8_t)0x01)  /*!<Device operating range: 2.1V to 2.7V */
#define VoltageRange_3        ((uint8_t)0x02)  /*!<Device operating range: 2.7V to 3.6V */
#define VoltageRange_4        ((uint8_t)0x03)  /*!<Device operating range: 2.7V to 3.6V + External Vpp */

#define FLASH_PSIZE_BYTE           ((uint32_t)0x00000000)
#define FLASH_PSIZE_HALF_WORD      ((uint32_t)0x00000100)
#define FLASH_PSIZE_WORD           ((uint32_t)0x00000200)
#define FLASH_PSIZE_DOUBLE_WORD    ((uint32_t)0x00000300)
#define CR_PSIZE_MASK              ((uint32_t)0xFFFFFCFF)


#define FLASH_Sector_0     ((uint16_t)0x0000) /*!< Sector Number 0 */
#define FLASH_Sector_1     ((uint16_t)0x0008) /*!< Sector Number 1 */
#define FLASH_Sector_2     ((uint16_t)0x0010) /*!< Sector Number 2 */
#define FLASH_Sector_3     ((uint16_t)0x0018) /*!< Sector Number 3 */
#define FLASH_Sector_4     ((uint16_t)0x0020) /*!< Sector Number 4 */
#define FLASH_Sector_5     ((uint16_t)0x0028) /*!< Sector Number 5 */
#define FLASH_Sector_6     ((uint16_t)0x0030) /*!< Sector Number 6 */
#define FLASH_Sector_7     ((uint16_t)0x0038) /*!< Sector Number 7 */
#define FLASH_Sector_8     ((uint16_t)0x0040) /*!< Sector Number 8 */
#define FLASH_Sector_9     ((uint16_t)0x0048) /*!< Sector Number 9 */
#define FLASH_Sector_10    ((uint16_t)0x0050) /*!< Sector Number 10 */
#define FLASH_Sector_11    ((uint16_t)0x0058) /*!< Sector Number 11 */
//GB XXX added to cover 429
#define FLASH_Sector_22    ((uint16_t)0x00B0) /*!< Sector Number 22 */
#define FLASH_Sector_23    ((uint16_t)0x00B8) /*!< Sector Number 23 */

#define RDP_KEY                  ((uint16_t)0x00A5)
#define FLASH_KEY1               ((uint32_t)0x45670123)
#define FLASH_KEY2               ((uint32_t)0xCDEF89AB)
#define FLASH_OPT_KEY1           ((uint32_t)0x08192A3B)
#define FLASH_OPT_KEY2           ((uint32_t)0x4C5D6E7F)

#define FLASH_FLAG_EOP                 ((uint32_t)0x00000001)  /*!< FLASH End of Operation flag */
#define FLASH_FLAG_OPERR               ((uint32_t)0x00000002)  /*!< FLASH operation Error flag */
#define FLASH_FLAG_WRPERR              ((uint32_t)0x00000010)  /*!< FLASH Write protected error flag */
#define FLASH_FLAG_PGAERR              ((uint32_t)0x00000020)  /*!< FLASH Programming Alignment error flag */
#define FLASH_FLAG_PGPERR              ((uint32_t)0x00000040)  /*!< FLASH Programming Parallelism error flag  */
#define FLASH_FLAG_PGSERR              ((uint32_t)0x00000080)  /*!< FLASH Programming Sequence error flag  */
#define FLASH_FLAG_BSY                 ((uint32_t)0x00010000)  /*!< FLASH Busy flag */ 


#define FLASH_PAGE_SIZE		0x400
#define FLASH_LAST_SECTOR 	FLASH_Sector_7
#define FLASH_LAST_ADDRESS	FLASH_BASE + 0x60000


#define BYTE2UINT32(a,b,c,d) 			((a << 24) + (b << 16) + (c << 8) + d)
#define BYTES2UINT32(a)					(((*(uint8_t*)(a+3)) << 24) + ((*(uint8_t*)(a+2)) << 16) + ((*(uint8_t*)(a+1)) << 8) + ((*(uint8_t*)(a+0)) << 0))

uint8_t read_memory(uint32_t addr, uint8_t* data, uint32_t len);
uint8_t write_memory(uint32_t addr, uint8_t* data, uint32_t len);
uint8_t erase_memory();
void memory_Init();
void ReadFlash8Bytes(uint32_t addr, uint8_t* data); //data is 8bytes.
uint32_t ReadFlash(uint32_t addr);
uint8_t WriteFlash8Bytes(uint32_t addr, uint8_t* data);
uint8_t WriteFlash(uint32_t address, uint32_t data);
uint8_t EraseFlash(uint32_t sector);



#define CALIBRATIONDATA_STARTADDRESS 0x20000000 + 0x10000   //we use RAM after 64kbye because the ram before 64k could be already use.
#define CALIBRATIONDATA_BLOCKSIZE	128
#define CALIBRATIONDATA_SIZE		4096	//4k
uint8_t* getCalibrationDataBlockAddress(); //get the Current calibration address
uint8_t* findCalibrationDataBlockAddress(); // find the avaible next address of Calibration
void writeCalibrationdata(uint8_t* address, uint8_t* data, uint16_t datasize);
//#endif
