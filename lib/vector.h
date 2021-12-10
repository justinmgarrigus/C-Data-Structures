// Justin Garrigus, 11-30-21

typedef struct vector { 
	size_t capacity; 
	size_t count;
	size_t data_size; 
	void *data;
} vector;

vector* vector_create(size_t initial_capacity, size_t data_size);
void vector_destroy(vector *v);
void vector_string(vector *v, char *type, char buffer[]); 

void* vector_addp(vector *v); 
void* vector_getp(vector *v, size_t index); 

#define vector_add(vector, type, value) *((type*)vector_addp(vector)) = value
#define vector_set(vector, type, value, index) *((type*)vector_getp(vector, index)) = value
#define vector_get(vector, type, index) *((type*)vector_getp(vector, index)) 
