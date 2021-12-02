// Justin Garrigus, 11-30-21

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

void vector_set(vector *v, unsigned long item, size_t index) {
	// Bytes stored in little-endian order. 
	// Treat 'data' is if it were a byte array.
	int current_index = index * v->data_size; 
	for (int i = 0; i < v->data_size; i++) 
		*((unsigned char*)v->data + current_index + i) = item >> 8 * i * 255; 
}

void vector_add(vector *v, unsigned long item) {
	if (v->count == v->capacity) {
		vector_increase_capacity(v); 
	}

	vector_set(v, item, v->count++); 
}

void* vector_addp(vector *v) {
	if (v->count == v->capacity) 
		vector_increase_capacity(v); 
	return vector_getp(v, v->count++); 
}

unsigned long vector_get(vector *v, size_t index) {
	// Construct data type of size 'buffer_size', bit-shifting bytes over
	// from data buffer. 
	unsigned long result = 0; 
	int current_index = index * v->data_size;
	for (int i = 0; i < v->data_size; i++) 
		result |= *((unsigned char*)v->data + current_index + i) << 8 * i; 
	return result; 
}

void vector_string(vector *v, char buffer[]) {
	buffer[0] = '['; 
	int buffer_index = 1; 
	char int_string[11]; // max value of unsigned long as a string (10 digits + null char) 
	buffer[0] = '['; 
	int item_index = 0; 
	int str_index; 
	while (item_index < v->capacity) {
		snprintf(int_string, 11, "%lu", vector_get(v, item_index++));
		str_index = 0;
		while (int_string[str_index] != '\0') 
			buffer[buffer_index++] = int_string[str_index++]; 
		buffer[buffer_index++] = ',';
		buffer[buffer_index++] = ' ';
	}
	buffer_index -= 2; // last spot shouldn't have comma after it 
	buffer[buffer_index++] = ']'; 
	buffer[buffer_index] = '\0'; 
}

int main() {
	char buffer[100]; 
	vector *v = vector_create(8, sizeof(int)); 
	
	*((int*)vector_addp(v)) = 1;
	*((int*)vector_addp(v)) = 2; 
	*((int*)vector_addp(v)) = 3; 
	vector_string(v, buffer);
	printf("%lu, %lu: %s\n", v->count, v->capacity, buffer); 

	*((int*)vector_addp(v)) = 4;
	*((int*)vector_addp(v)) = 5; 
	*((int*)vector_addp(v)) = 6; 
	vector_string(v, buffer);
	printf("%lu, %lu: %s\n", v->count, v->capacity, buffer); 
	
	*((int*)vector_getp(v, 0)) = 7;
	*((int*)vector_getp(v, 1)) = 8; 
	*((int*)vector_getp(v, 2)) = 9; 
	vector_string(v, buffer);
	printf("%lu, %lu: %s\n", v->count, v->capacity, buffer); 

	for (int i = 0; i < v->count; i++)
		printf("Item at {%d}: {%d}\n", i, (int)vector_get(v, i)); 

	vector_destroy(v); 
}
