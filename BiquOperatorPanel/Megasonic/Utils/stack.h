#include <stdint.h>
#define  STACK_SIZE 10
typedef struct tagStack
{
	void* RawData[STACK_SIZE];
	uint16_t top;
}Stack;


void stack_init(Stack* stack);
void stack_push(Stack* stack, void* data);
void* stack_pop(Stack* stack);
void* stack_peek(Stack* stack);
void stack_free(Stack* stack);