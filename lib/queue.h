// Justin Garrigus, 11-30-21

typedef struct queue {
	int capacity; 
	int count; 
	int *items;
	int startIndex, endIndex;
} queue;

queue* queue_create(int initial_capacity);
void queue_destroy(queue *q);
void queue_push(queue *q, int val);
void queue_print(queue *q);
int queue_pop(queue *q); 
