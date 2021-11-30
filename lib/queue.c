// Justin Garrigus, 11-30-21

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct queue* queue_create(int initial_capacity) {
	struct queue *q = malloc(sizeof(struct queue)); 
	q->capacity = initial_capacity; 
	q->count = 0;
	q->startIndex = 0;
	q->endIndex = 0;
	q->items = malloc(sizeof(q->items) * initial_capacity); 
	return q; 
}

void queue_destroy(struct queue *q) {
	free(q->items);
	free(q); 
}

void double_capacity(struct queue *q) {
	q->items = realloc(q->items, sizeof(q->items) * q->capacity * 2); 
	for (int index = 0; index < q->endIndex; index++)
		q->items[q->capacity + index] = q->items[index]; 
	q->endIndex = q->capacity + q->startIndex; 
	q->capacity = 2 * q->capacity; 
}

void queue_push(struct queue *q, int val) {
	if (q->count == q->capacity) {
		double_capacity(q); 
	}
	q->items[q->endIndex] = val; 
	q->endIndex = (q->endIndex + 1) % q->capacity; 
	q->count++; 
}

void queue_print(struct queue *q) {
	printf("["); 
	int numPrinted = 0;
	while (numPrinted < q->count - 1) {
		printf("%d, ", q->items[(q->startIndex + numPrinted) % q->capacity]);
		numPrinted++; 
	}
	if (q->count > 0)
		printf("%d", q->items[(q->startIndex + numPrinted) % q->capacity]); 
	printf("]");
}

int queue_pop(struct queue *q) {
	int item = q->items[q->startIndex]; 
	q->startIndex = (q->startIndex + 1) % q->capacity;
	q->count--; 
	return item;
}

//int main() {
//	struct queue *q = queue_create(5);
//	
//	queue_push(q, 1);
//	queue_push(q, 2);
//	queue_push(q, 3);
//	printf("%d, %d: ", q->count, q->capacity); 
//	queue_print(q);
//	printf("\n"); 
//	
//	queue_push(q, 4);
//	queue_push(q, 5);
//	queue_push(q, 6);
//	queue_push(q, 7);
//	printf("%d, %d: ", q->count, q->capacity); 
//	queue_print(q);
//	printf("\n"); 
//
//	printf("Pop: %d\n", queue_pop(q));
//	printf("Pop: %d\n", queue_pop(q));
//	printf("Pop: %d\n", queue_pop(q)); 
//	printf("%d, %d: ", q->count, q->capacity);
//	queue_print(q);
//	printf("\n"); 
//
//	queue_push(q, 8);
//	queue_push(q, 9);
//	queue_push(q, 10); 
//	printf("%d, %d: ", q->count, q->capacity); 
//	queue_print(q);
//	printf("\n");
//
//	while (q->count > 0)
//		printf("Pop: %d\n", queue_pop(q));
//	
//	queue_destroy(q); 	
//}
