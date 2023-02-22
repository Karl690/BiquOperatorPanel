#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "global.h"

void stack_init(Stack* stack)
{
	memset(stack->RawData, 0, sizeof(void*) * STACK_SIZE);
	stack->top = -1;
}

void stack_push(Stack* stack, void* data) {
	// Checking overflow state
	if (stack->top == STACK_SIZE - 1) return; //Overflow State: can't add more elements into the stack
	else {
		//Enter element to be pushed into the stack
		stack->top += 1;
		stack->RawData[stack->top] = data;
	}
}
void* stack_pop(Stack* stack)
{
	if (stack->top == -1)
		return NULL; // printf("Underflow State: Stack already empty, can't remove any element\n");
	else {
		void* result = stack->RawData[stack->top]; //printf("Popping %d out of the stack\n", x);
		stack->top -= 1;
		return result;
	}
	return NULL;
}

void* stack_peek(Stack* stack) {
	if (stack->top == -1) return NULL;
	return stack->RawData[stack->top];	
}

void stack_free(Stack* stack)
{
	free((void*)stack);
}