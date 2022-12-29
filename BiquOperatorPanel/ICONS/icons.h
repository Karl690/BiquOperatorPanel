#include <stdint.h>

typedef struct _ICONINFO
{
	uint16_t width;
	uint16_t height;
	uint8_t* buffer;
}ICONINFO;

extern ICONINFO IconStart;