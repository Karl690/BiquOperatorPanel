#include <stdint.h>

#define LEFT_PADDING 5
#define RIGHT_PADDING 5
#define PADDING 5
#define VALUE_POS	100
#define LCD_LINESIZE	18
#define GUI_FONT_SIZE	16

#define COLOR_BLACK				0x0000 //COLOR_BLACK = 0,
#define COLOR_WHITE				0xFFFF //COLOR_WHITE = 1,
#define COLOR_RED				0xF800 //COLOR_RED = 2,
#define COLOR_LIME				0x07E0 //COLOR_LIME = 3,
#define COLOR_BLUE				0x001F //COLOR_BLUE = 4,
#define COLOR_YELLOW			0xFFE0 //COLOR_YELLOW = 5,
#define COLOR_CYAN				0x07FF //COLOR_CYAN = 6,
#define COLOR_MAGENTA			0xF81F //COLOR_MAGENTA = 7,
#define COLOR_SILVER			0xC618 //COLOR_SILVER = 8,
#define COLOR_GRAY				0x8410 //COLOR_GRAY = 9,
#define COLOR_MAROON			0x8000 //COLOR_MAROON = 10,
#define COLOR_OLIVE				0x8400 //COLOR_OLIVE = 11,
#define COLOR_GREEN				0x0400 //COLOR_GREEN = 12,
#define COLOR_PURPLE			0x8010 //COLOR_PURPLE = 13,
#define COLOR_TEAL				0x0410 //COLOR_TEAL = 14,
#define COLOR_NAVY				0x0010 //COLOR_NAVY = 15,
#define COLOR_DARKRED			0x8800 //COLOR_DARKRED = 16,
#define COLOR_TOMATO			0xFB08 //COLOR_TOMATO = 17,
#define COLOR_GOLD				0xFEA0 //COLOR_GOLD = 18,
#define COLOR_YELLOWGREEN		0x9E66 //COLOR_YELLOWGREEN = 19,
#define COLOR_FORESTGREEN		0x2444 //COLOR_FORESTGREEN = 20,
#define COLOR_SPRINGGREEN		0x07EF //COLOR_SPRINGGREEN = 21,
#define COLOR_DARKCYAN			0x0451 //COLOR_DARKCYAN =22,
#define COLOR_PALETURQUOISE		0xAF7D //COLOR_PALETURQUOISE = 23,
#define COLOR_POWDERBLUE		0xB71C //COLOR_POWDERBLUE = 24,
#define COLOR_DEEPSKYBLUE		0x05FF //COLOR_DEEPSKYBLUE = 25,
#define COLOR_LIGHTSKYBLUE		0x867F //COLOR_LIGHTSKYBLUE = 26,
#define	COLOR_DARKBLUE			0x0011 //COLOR_DARKBLUE = 27,
#define COLOR_MEDINUSLATEBLUE	0x7B5D //COLOR_MEDINUSLATEBLUE = 28,
#define COLOR_DARKVIOLET		0x901A //COLOR_DARKVIOLET = 29,
#define COLOR_PLUM				0xDD1B //COLOR_PLUM = 30,
#define COLOR_BEIGE				0xF7BB //COLOR_BEIGE = 31,

#define RGB16(r, g, b) (((r & 0x1F) << 11) | ((g & 0x3F) << 5) | (b & 0x1F))

void GUI_Clear(uint16_t color);
void GUI_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void GUI_HLine(uint16_t x1, uint16_t y, uint16_t x2, uint16_t color);
void GUI_VLine(uint16_t x, uint16_t y1, uint16_t y2, uint16_t color);
void GUI_DrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void GUI_FillRect(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color);
void GUI_WriteBuffer(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint8_t* data);
void GUI_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void GUI_DrawChar(uint16_t X, uint16_t Y, uint8_t chr, uint16_t color);
void GUI_DrawString(uint16_t X, uint16_t Y, char *str, uint16_t color);

