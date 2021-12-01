// Justin Garrigus, 11-30-21

typedef struct vector { 
	size_t capacity; 
	size_t count;
	size_t data_size; 
	void *data;
} vector;

vector* vector_create(size_t initial_capacity, size_t data_size);
void vector_destroy(vector *v);
void vector_set(vector *v, unsigned long item, size_t index); 
void vector_add(vector *v, unsigned long item);
unsigned long vector_get(vector *v, size_t index); 
void vector_string(vector *v, char buffer[]); 
