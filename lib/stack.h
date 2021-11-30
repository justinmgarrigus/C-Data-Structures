// Justin Garrigus, 11-30-21

struct stack {
	int capacity; 
	int count; 
	int *items;
};

struct stack* stack_create(int initial_capacity);
void stack_destroy(struct stack *st); 
void stack_push(struct stack *st, int val);
void stack_print(struct stack *st);
int stack_pop(struct stack *st); 
