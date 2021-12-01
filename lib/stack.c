// Justin Garrigus, 11-30-21

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stack* stack_create(int initial_capacity) {
	stack *st = malloc(sizeof(stack)); 
	st->capacity = initial_capacity; 
	st->count = 0; 
	st->items = malloc(sizeof(st->items) * initial_capacity); 
	return st; 
}

void stack_destroy(stack *st) {
	free(st->items);
	free(st);
}

void double_capacity(stack *st) {
	st->items = realloc(st->items, sizeof(st->items) * st->capacity * 2); 
	st->capacity = 2 * st->capacity; 
}

void stack_push(stack *st, int val) {
	if (st->count == st->capacity) {
		double_capacity(st); 
	}
	st->items[st->count++] = val; 
}

void stack_print(stack *st) {
	printf("["); 
	for (int i = 0; i < st->count - 1; i++)
		printf("%d, ", st->items[i]);
	if (st->count > 0)
		printf("%d", st->items[st->count-1]); 
	printf("]"); 
}

int stack_pop(stack *st) {
	st->count--; 
	return st->items[st->count];
}

//int main() {
//	stack *st = stack_create(5);
//	
//	stack_push(st, 1);
//	stack_push(st, 2);
//	stack_push(st, 3);
//	printf("%d, %d: ", st->count, st->capacity); 
//	stack_print(st);
//	printf("\n"); 
//	
//	stack_push(st, 4);
//	stack_push(st, 5);
//	stack_push(st, 6);
//	stack_push(st, 7);
//	printf("%d, %d: ", st->count, st->capacity); 
//	stack_print(st);
//	printf("\n"); 
//
//	printf("Pop: %d\n", stack_pop(st));
//	printf("Pop: %d\n", stack_pop(st));
//	printf("Pop: %d\n", stack_pop(st)); 
//	printf("%d, %d: ", st->count, st->capacity);
//	stack_print(st);
//	printf("\n"); 
//
//	stack_push(st, 8);
//	stack_push(st, 9);
//	stack_push(st, 10); 
//	printf("%d, %d: ", st->count, st->capacity); 
//	stack_print(st);
//	printf("\n");
//
//	while (st->count > 0)
//		printf("Pop: %d\n", stack_pop(st));
//	
//	stack_destroy(st); 	
//}
