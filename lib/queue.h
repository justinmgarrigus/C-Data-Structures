// Justin Garrigus, 11-30-21

struct queue {
	int capacity; 
	int count; 
	int *items;
	int startIndex, endIndex;
};

struct queue* queue_create(int initial_capacity);
void queue_destroy(struct queue *q);
void queue_push(struct queue *q, int val);
void queue_print(struct queue *q);
int queue_pop(struct queue *q); 
