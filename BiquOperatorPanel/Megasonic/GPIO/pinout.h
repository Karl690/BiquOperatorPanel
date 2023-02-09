#include "pins.h"


// XPT2046 Software SPI pins for touch screen
// It needs CS/SCK/MISO/MOSI for Software SPI and TPEN for pen interrupt
#define XPT2046_CS   PE6
#define XPT2046_SCK  PE5
#define XPT2046_MISO PE4
#define XPT2046_MOSI PE3
#define XPT2046_TPEN PC13

// W25Qxx SPI Flash Memory pins
#define W25Qxx_SPEED  0
#define W25Qxx_SPI    _SPI3
#define W25Qxx_CS_PIN PB6

#define LCD_ENCA_PIN   PA8
#define LCD_ENCB_PIN   PC9
#define LCD_BTN_PIN    PC8

//UART Pins
#define USART1_TX_PIN PA9
#define USART1_RX_PIN PA10
#define USART2_TX_PIN PA2
#define USART2_RX_PIN PA3
#define USART3_TX_PIN PB10
#define USART3_RX_PIN PB11
#define UART4_TX_PIN  PC10
#define UART4_RX_PIN  PC11
#define UART5_TX_PIN  PC12
#define UART5_RX_PIN  PD2
#define USART6_TX_PIN PG14
#define USART6_RX_PIN PG9