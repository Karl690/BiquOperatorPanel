#pragma once
#include <stdint.h>
#include "configure.h"



void GUIBUF_Init();
void GUIBUF_Clear(uint16_t color, uint16_t* buf, Size bufsize);
void GUIBUF_DrawPoint(uint16_t x, uint16_t y, uint16_t color, uint16_t* buf, Size bufsize);
void GUIBUF_HLine(uint16_t x1, uint16_t y, uint16_t x2, uint16_t color, uint16_t* buf, Size bufsize);
void GUIBUF_VLine(uint16_t x, uint16_t y1, uint16_t y2, uint16_t color, uint16_t* buf, Size bufsize);
void GUIBUF_DrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint16_t* buf, Size bufsize);
void GUIBUF_FillRect(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color, uint16_t* buf, Size bufsize);
void GUIBUF_WriteBuffer(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint8_t* data, uint16_t* buf, Size bufsize);
void GUIBUF_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint16_t* buf, Size bufsize);
void GUIBUF_DrawPolygon(Point* points, uint16_t num, uint16_t color, Point offset, uint16_t* buf, Size bufsize);
void GUIBUF_DrawChar(uint16_t X, uint16_t Y, uint8_t chr, Font* font, uint16_t color, uint16_t bgcolor, uint16_t* buf, Size bufsize); // fontSize must be 20 or 32
void GUIBUF_DrawString(uint16_t X, uint16_t Y, char *str, Font* font, uint16_t color, uint16_t bgcolor, uint16_t* buf, Size bufsize);


