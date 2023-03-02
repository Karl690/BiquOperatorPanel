#pragma once

#include "configure.h"

#ifdef CORE_407I
#include "GPIO/4xx/pins_4xx.h"


extern uint16_t Home_X_Status;
extern uint16_t Home_Y_Status;
extern uint16_t Home_Z_Status;
extern uint16_t Home_A_Status;
extern uint16_t Home_B_Status;
extern uint16_t Home_C_Status;

////////////////////////////////////////////////////////////////////////////////
//X motor definitions
#define X_Step_Pin 			(PIN_PORT_A | PIN_NUM_04 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define X_Step_Port         GPIOA
#define X_Step_Set       	GPIOA->BSRR = PIN_MASK_04 //index to the set bit register
#define X_Step_Clr       	GPIOA->BSRR = (uint32_t)PIN_MASK_04 << 16 //index to the Clear bit register
//
#define X_Dir_Pin 			(PIN_PORT_C | PIN_NUM_05 | PIN_INIT_LOW | OUTPUT_PP_50MHZ)  //
#define X_Dir_Port          GPIOC
#define X_Dir_Set 			GPIOC->BSRR = PIN_MASK_05 //index to the set bit register
#define X_Dir_Clr 			GPIOC->BSRR = (uint32_t)PIN_MASK_05 <<16 //index to the Clear bit register
//
#define X_Home_Pin 			(PIN_PORT_E | PIN_NUM_06 | PIN_INIT_NONE | INPUT_PULLUP)  //
#define X_Home_Mask			1<<(X_Home_Pin & 0x000f)
#define X_Home_Port         GPIOE
#define X_Home_Read			Home_X_Status= (X_Home_Port->IDR) & (X_Home_Mask);

//Y motor definitions
#define Y_Step_Pin 			(PIN_PORT_A | PIN_NUM_08 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define Y_Step_Port         GPIOA
#define Y_Step_Set       	GPIOA->BSRR = PIN_MASK_08 //index to the set bit register
#define Y_Step_Clr       	GPIOA->BSRR = (uint32_t)PIN_MASK_08 <<16 //index to the Clear bit register
//
#define Y_Dir_Pin 			(PIN_PORT_G | PIN_NUM_15 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define Y_Dir_Port          GPIOG
#define Y_Dir_Set 			GPIOG->BSRR = PIN_MASK_15 //index to the set bit register
#define Y_Dir_Clr 			GPIOG->BSRR = (uint32_t)PIN_MASK_15 <<16 //index to the Clear bit register
//
#define Y_Home_Pin 			(PIN_PORT_C | PIN_NUM_03 | PIN_INIT_NONE | INPUT_PULLUP)  //
#define Y_Home_Mask			1<<(Y_Home_Pin & 0x000f)
#define Y_Home_Port         GPIOC
#define Y_Home_Read			Home_Y_Status= (Y_Home_Port->IDR) & (Y_Home_Mask);

//Z motor definitions
#define Z_Step_Pin 			(PIN_PORT_A | PIN_NUM_10 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define Z_Step_Port         GPIOA
#define Z_Step_Set       	GPIOA->BSRR = PIN_MASK_10 //index to the set bit register
#define Z_Step_Clr       	GPIOA->BSRR = (uint32_t)PIN_MASK_10 <<16 //index to the Clear bit register
//
#define Z_Dir_Pin 			(PIN_PORT_F | PIN_NUM_08 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define Z_Dir_Port          GPIOF
#define Z_Dir_Set 			GPIOF->BSRR = PIN_MASK_08 //index to the set bit register
#define Z_Dir_Clr 			GPIOF->BSRR = (uint32_t)PIN_MASK_08 <<16 //index to the Clear bit register
//
#define Z_Home_Pin 			(PIN_PORT_G | PIN_NUM_10 | PIN_INIT_NONE | INPUT_PULLUP)  //
#define Z_Home_Mask			1<<(Z_Home_Pin & 0x000f)
#define Z_Home_Port         GPIOG
#define Z_Home_Read			Home_Z_Status= (Z_Home_Port->IDR) & (Z_Home_Mask);

//A motor definitions
#define A_Step_Pin 			(PIN_PORT_A | PIN_NUM_03 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define A_Step_Port         GPIOA
#define A_Step_Set       	GPIOA->BSRR = PIN_MASK_03 //index to the set bit register
#define A_Step_Clr       	GPIOA->BSRR = (uint32_t)PIN_MASK_03 << 16 //index to the Clear bit register
//
#define A_Dir_Pin 			(PIN_PORT_G | PIN_NUM_11 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define A_Dir_Port          GPIOG
#define A_Dir_Set 			GPIOG->BSRR = PIN_MASK_11 //index to the set bit register
#define A_Dir_Clr 			GPIOG->BSRR = (uint32_t)PIN_MASK_11 << 16 //index to the Clear bit register
//
#define A_Home_Pin 			(PIN_PORT_G | PIN_NUM_14 | PIN_INIT_NONE | INPUT_PULLUP)  //
#define A_Home_Mask			1<<(A_Home_Pin & 0x000f)
#define A_Home_Port         GPIOG
#define A_Home_Read			Home_A_Status= (A_Home_Port->IDR) & (A_Home_Mask);

//B motor definitions
#define B_Step_Pin 			(PIN_PORT_C | PIN_NUM_04 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define B_Step_Port         GPIOC
#define B_Step_Set       	GPIOC->BSRR = PIN_MASK_04 //index to the set bit register
#define B_Step_Clr       	GPIOC->BSRR = (uint32_t)PIN_MASK_04 << 16 //index to the Clear bit register
//
#define B_Dir_Pin 			(PIN_PORT_B | PIN_NUM_00 | PIN_INIT_LOW | OUTPUT_PP_50MHZ )  //
#define B_Dir_Port          GPIOB
#define B_Dir_Set 			GPIOB->BSRR = PIN_MASK_00 //index to the set bit register
#define B_Dir_Clr 			GPIOB->BSRR = (uint32_t)PIN_MASK_00 << 16 //index to the Clear bit register
//
#define B_Home_Pin 			(PIN_PORT_E | PIN_NUM_07 | PIN_INIT_NONE | INPUT_PULLUP)  //
#define B_Home_Mask			1<<(B_Home_Pin & 0x000f)
#define B_Home_Port         GPIOE
#define B_Home_Read			Home_B_Status= (B_Home_Port->IDR) & (B_Home_Mask);
//
//generic I/O pin_port
//B motor definitions
#define HeartBeat_Pin       (OUTPUT_PP_50MHZ  | PIN_PORT_F | PIN_NUM_15)
#define HeartBeat_Set       GPIOF->BSRR = PIN_MASK_15 //index to the set bit register
#define HeartBeat_Clr       GPIOF->BSRR = (uint32_t)PIN_MASK_15 << 16 //index to the Clear bit register
//
//#define BKLT_Pin 			(PIN_PORT_D | PIN_NUM_15 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ )  //contrast
//#define BKLT_Port           GPIOD
//#define BKLT_Set       		GPIOD->BSRR = PIN_MASK_15 //index to the set bit register
//#define BKLT_Clr       		GPIOD->BSRR = (uint32)PIN_MASK_15 << 16 //index to the Clear bit register

//adc pins
#define ADC2_03_PA3        (PIN_PORT_A | PIN_NUM_03 | PIN_INIT_NONE | ANALOG_FLOATING) //
#define ADC2_04_PA4        (PIN_PORT_A | PIN_NUM_04 | PIN_INIT_NONE | ANALOG_FLOATING)
#define ADC2_05_PA5        (PIN_PORT_A | PIN_NUM_05 | PIN_INIT_NONE | ANALOG_FLOATING)
#define ADC2_06_PA6         (PIN_PORT_A | PIN_NUM_06 | PIN_INIT_NONE | ANALOG_FLOATING) //feedrate override
#define ADC2_09_PB1         (PIN_PORT_B | PIN_NUM_01 | PIN_INIT_NONE | ANALOG_FLOATING)
#define ADC2_15_PC5         (PIN_PORT_C | PIN_NUM_05 | PIN_INIT_NONE | ANALOG_FLOATING)

#define CAN1_RX             (PIN_AF_CAN1      | PIN_PORT_B | PIN_NUM_08 | PIN_PUPPD_PULLUP)
#define CAN1_TX             (PIN_AF_CAN1      | PIN_PORT_B | PIN_NUM_09)
#define CAN2_RX             (PIN_PUPPD_PULLUP   | PIN_PORT_B | PIN_NUM_05)
#define CAN2_TX             (OUTPUT_PP_50MHZ  | PIN_PORT_B | PIN_NUM_06 | PIN_INIT_HIGH)

#define LED_CAN_TX          (OUTPUT_PP_50MHZ  | PIN_PORT_G | PIN_NUM_01)
#define LED_CAN_TX_ON		GPIOG->BSRR = PIN_MASK_01
#define LED_CAN_TX_OFF		GPIOG->BSRR = PIN_MASK_01 << 16

//Pnp Spi for feeders
#define PnP_Enable		   (PIN_PORT_A | PIN_NUM_09  | PIN_INIT_LOW  | OUTPUT_PP_50MHZ)
#define PnP_Enable_Set     GPIOA->BSRR = PIN_MASK_09                 //index to the set bit register
#define PnP_Enable_Clr     GPIOA->BSRR = (uint32_t)PIN_MASK_09 << 16 //index to the Clear bit register

#define PnP_Rclk		   (PIN_PORT_C | PIN_NUM_11  | PIN_INIT_LOW  | OUTPUT_PP_50MHZ)
#define PnP_Rclk_Set       GPIOC->BSRR = PIN_MASK_11                  //index to the set bit register
#define PnP_Rclk_Clr       GPIOC->BSRR = (uint32_t)PIN_MASK_11 << 16 //index to the Clear bit register

#define UserKey1_Pin 	   (PIN_PORT_C | PIN_NUM_08  |INPUT_PULLUP )  //
#define UserKey1_Port       GPIOC
#define UserKey1_Read		UserKey1_Status = (UserKey1_Port->IDR) & (PIN_MASK_08);

#define UserKey2_Pin 	   (PIN_PORT_C | PIN_NUM_09  |INPUT_PULLUP )  //
#define UserKey2_Port       GPIOC
#define UserKey2_Read		UserKey2_Status= (UserKey2_Port->IDR) & (PIN_MASK_09);

#define SPI1_LCD_RST			(PIN_PORT_C | PIN_NUM_00 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI1_LCD_RS				(PIN_PORT_C | PIN_NUM_03 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI1_LCD_CS				(PIN_PORT_B | PIN_NUM_07 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI1_LCD_MOSI			(PIN_PORT_C | PIN_NUM_01 | PIN_AF_SPI1)
#define SPI1_LCD_SCK			(PIN_PORT_D | PIN_NUM_03 | PIN_AF_SPI1)

#define SPI2_LCD_RST			(PIN_PORT_C | PIN_NUM_00 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI2_LCD_RS				(PIN_PORT_C | PIN_NUM_11 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI2_LCD_CS				(PIN_PORT_E | PIN_NUM_02 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI2_LCD_MOSI			(PIN_PORT_C | PIN_NUM_12 | PIN_AF_SPI2)
#define SPI2_LCD_SCK			(PIN_PORT_C | PIN_NUM_10 | PIN_AF_SPI2)

#define SPI3_LCD_RST			(PIN_PORT_C | PIN_NUM_00 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI3_LCD_RS				(PIN_PORT_A | PIN_NUM_09 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI3_LCD_CS				(PIN_PORT_C | PIN_NUM_11 | PIN_INIT_HIGH | OUTPUT_PP_50MHZ)
#define SPI3_LCD_MOSI			(PIN_PORT_C | PIN_NUM_12 | PIN_AF_SPI3)
#define SPI3_LCD_SCK			(PIN_PORT_C | PIN_NUM_10 | PIN_AF_SPI3)
#endif //
