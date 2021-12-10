// Justin Garrigus

#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include "vector.h"

vector* vector_create(size_t initial_capacity, size_t data_size) {
	vector *v = malloc(sizeof(vector)); 
	v->data = malloc(data_size * initial_capacity);
	v->data_size = data_size; 
	v->count = 0;
	v->capacity = initial_capacity; 
}

void vector_destroy(vector *v) {
	free(v->data);
	free(v); 
}

void vector_increase_capacity(vector *v) {
	v->data = realloc(v->data, v->data_size * v->capacity * 2);
	v->capacity *= 2; 
}

void* vector_getp(vector *v, size_t index) {
	return ((char*)v->data + v->data_size * index); 
}

void* vector_addp(vector *v) {
	if (v->count == v->capacity) 
		vector_increase_capacity(v); 
	return vector_getp(v, v->count++); 
}

void vector_string(vector *v, char* type, char buffer[]) {
	const int value_max_length = 20; 

	buffer[0] = '['; 
	int buffer_index = 1; 
	
	char value_buffer[value_max_length]; 
	int item_index = 0; 
	int str_index; 
	
	// only useful if type is string. 
	int i; 
	char *str_val; 

	while (item_index < v->count) {
		switch (type[1]) {
			case 'c': 
				value_buffer[0] = vector_get(v, char, item_index++); 
				value_buffer[1] = '\0'; 
				break; 

			case 's':
				i = 0;
				str_val = vector_get(v, char*, item_index++); 
				while (str_val[i] != '\0' && i < value_max_length) {
					value_buffer[i] = str_val[i++]; 
				}
				value_buffer[i] = '\0'; 
				break; 

			case 'p': 
				snprintf(value_buffer, value_max_length, type, vector_get(v, void*, item_index++)); 
				break; 

			default:
				snprintf(value_buffer, value_max_length, "%d", vector_get(v, int, item_index++)); 
				break;
		}
		
		str_index = 0;
		while (value_buffer[str_index] != '\0') 
			buffer[buffer_index++] = value_buffer[str_index++];
		
		buffer[buffer_index++] = ',';
		buffer[buffer_index++] = ' ';
	}
	
	buffer_index -= 2; // last spot shouldn't have comma after it 
	buffer[buffer_index++] = ']'; 
	buffer[buffer_index] = '\0'; 
}
