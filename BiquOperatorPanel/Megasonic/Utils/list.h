#include <stdint.h>
#define  LIST_SIZE 30
typedef struct tagList
{
	void* RawData[LIST_SIZE];
	uint16_t top;
}List;


void list_init(List* list);
void list_add(List* list, void* data);
void list_remove(List* list, uint16_t index);
void list_free(List* list);