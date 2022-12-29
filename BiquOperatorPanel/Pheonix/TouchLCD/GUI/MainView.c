#include "gui.h"
#include "icons.h"
void UpdateMainView()
{
	GUI_WriteBuffer(100, 100, IconStart.width, IconStart.height, IconStart.buffer);
}