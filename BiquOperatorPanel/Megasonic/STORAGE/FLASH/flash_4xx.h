
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

/******************  Bits definition for FLASH_SR register  *****************/
#ifndef FLASH_SR_EOP
#define FLASH_SR_EOP                         ((uint32_t)0x00000001)//end of operation, i.e. erase complete
#define FLASH_SR_SOP                         ((uint32_t)0x00000002)//operation error,basic access error
#define FLASH_SR_WRPERR                      ((uint32_t)0x00000010)//write protect error, illegal access
#define FLASH_SR_PGAERR                      ((uint32_t)0x00000020)//program alignment error,can not cross block
#define FLASH_SR_PGPERR                      ((uint32_t)0x00000040)//parallelism error, write not aligned
#define FLASH_SR_PGSERR                      ((uint32_t)0x00000080)//programming sequence error,key not properly written
#define FLASH_SR_BSY                         ((uint32_t)0x00010000)//busy, working on write or erase
#endif
//Bits 31 : 17    Reserved, must be kept cleared.
//Bit 16 BSY :    Busy
//                This bit indicates that a Flash memory operation is in progress to / from one bank.It is set at the
//                beginning of a Flash memory operation and cleared when the operation finishes or an error occurs.
//                0 : no Flash memory operation ongoing
//                1 : Flash memory operation ongoing
//Bits 15 : 9     Reserved, must be kept cleared.
//
//Bit 8 RDERR :   Proprietary readout protection(PCROP) error
//                Set by hardware when a read access through the D - bus is performed to an address belonging
//                to a proprietary readout protected Flash sector.
//                Cleared by writing 1.
//Bit 7 PGSERR : Programming sequence error
//                Set by hardware when a write access to the Flash memory is performed by the code while the
//                control register has not been correctly configured.
//                Cleared by writing 1
//Bit 6 PGPERR :	Programming parallelism error
//				Set by hardware when the size of the access(byte, half - word, word, double word) during the
//				program sequence does not correspond to the parallelism configuration PSIZE(x8,x16,x32, x64).
//				Cleared by writing 1.
//Bit 5 PGAERR :	Programming alignment error
//				Set by hardware when the data to program cannot be contained in the same 128 - bit Flash memory row.
//				Cleared by writing 1.
//Bit 4 WRPERR :	Write protection error
//				Set by hardware when an address to be erased / programmed belongs to a write - protected part
//				of the Flash memory.
//				Cleared by writing 1.
//Bits 3 : 2		Reserved, must be kept cleared.
//Bit 1 OPERR :	Operation error
//				Set by hardware when a flash operation(programming / erase / read) request is detected and
//				can not be run because of parallelism, alignment, write or read(PCROP) protection error.This
//				bit is set only if error interrupts are enabled(ERRIE = 1).
//Bit 0 EOP :		End of operation
//				Set by hardware when one or more Flash memory operations(program / erase) has / have
//				completed successfully.It is set only if the end of operation interrupts are enabled(EOPIE = 1).
//				Cleared by writing a 1 


#define VoltageRange_1        ((uint8_t)0x00)  /*!< Device operating range: 1.8V to 2.1V */
#define VoltageRange_2        ((uint8_t)0x01)  /*!<Device operating range: 2.1V to 2.7V */
#define VoltageRange_3        ((uint8_t)0x02)  /*!<Device operating range: 2.7V to 3.6V */
#define VoltageRange_4        ((uint8_t)0x03)  /*!<Device operating range: 2.7V to 3.6V + External Vpp */
#ifndef  FLASH_PSIZE_BYTE
#define FLASH_PSIZE_BYTE           ((uint32_t)0x00000000)
#define FLASH_PSIZE_HALF_WORD      ((uint32_t)0x00000100)
#define FLASH_PSIZE_WORD           ((uint32_t)0x00000200)
#define FLASH_PSIZE_DOUBLE_WORD    ((uint32_t)0x00000300)
#define CR_PSIZE_MASK              ((uint32_t)0xFFFFFCFF)
#endif

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
#ifndef FLASH_KEY1
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
#endif

#define FLASH_PAGE_SIZE		0x400
#define FLASH_LAST_SECTOR 	FLASH_Sector_11    
#define FLASH_LAST_ADDRESS	FLASH_BASE + 0xE0000 // if sector is 7, this would be 0x60000


#define BYTE2UINT32(a,b,c,d) 			((a << 24) + (b << 16) + (c << 8) + d)
#define BYTES2UINT32(a)					(((*(uint8_t*)(a+3)) << 24) + ((*(uint8_t*)(a+2)) << 16) + ((*(uint8_t*)(a+1)) << 8) + ((*(uint8_t*)(a+0)) << 0))

uint8_t read_flash(uint32_t addr, uint8_t* data, uint32_t len);
uint8_t write_flash(uint32_t addr, uint8_t* data, uint32_t len);
uint8_t erase_flash();
void memory_Init();
void ReadFlash8Bytes(uint32_t addr, uint8_t* data); //data is 8bytes.
uint8_t WriteFlash8Bytes(uint32_t addr, uint8_t* data);

