#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "global.h"

void list_init(List* list)
{
	memset(list->RawData, 0, sizeof(void*) * LIST_SIZE);
	list->top = -1;
}

void list_add(List* list, void* data) {
	// Checking overflow state
	if (list->top == LIST_SIZE - 1) return; //Overflow State: can't add more elements into the stack
	else {
		//Enter element to be pushed into the stack
		list->top += 1;
		list->RawData[list->top] = data;
	}
}
void list_remove(List* list, uint16_t index)
{
	if (list->top == -1 || index > list->top)
		return ; // printf("Underflow State: Stack already empty, can't remove any element\n");
	else {
		if (index == list->top)
		{
			list->RawData[index] = 0;
			list->top--;
			return;
			
		}
		for (uint16_t i = index; i < list->top; i++)
		{
			list->RawData[i] = list->RawData[i + 1];
		}
		list->top -= 1;	
	}
}

void* list_peek(List* list, uint16_t index) {
	if (index >= LIST_SIZE) return NULL;
	return list->RawData[index];	
}

void list_free(List* stack)
{
	free((void*)stack);
}