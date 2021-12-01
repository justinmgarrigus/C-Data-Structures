// Justin Garrigus, 11-30-21

typedef struct vector { 
	int capacity; 
	int count;
	int *data;
} vector;

vector* vector_create(int initial_capacity);
void vector_destroy(vector *v);
void vector_add(vector *v, int item);
int vector_set(vector *v, int item, int index);
void vector_string(vector *v, char buffer[]); 
