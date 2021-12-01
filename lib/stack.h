// Justin Garrigus, 11-30-21

typedef struct stack {
	int capacity; 
	int count; 
	int *items;
} stack;

stack* stack_create(int initial_capacity);
void stack_destroy(stack *st); 
void stack_push(stack *st, int val);
void stack_print(stack *st);
int stack_pop(stack *st); 
