// Justin Garrigus, 11-30-21

#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include "vector.h"

struct vector* vector_create(int initial_capacity) {
	struct vector *v = malloc(sizeof(struct vector)); 
	v->data = malloc(sizeof(v->data) * initial_capacity);
	v->count = 0;
	v->capacity = initial_capacity; 
}

void vector_destroy(vector *v) {
	free(v->data);
	free(v); 
}

void vector_double_capacity(struct vector *v) {
	v->data = realloc(v->data, sizeof(v->data) * v->capacity * 2);
	v->capacity *= 2; 
}

void vector_add(struct vector *v, int item) {
	if (v->count == v->capacity) {
		vector_double_capacity(v); 
	}

	v->data[v->count++] = item; 
}

int vector_set(struct vector *v, int item, int index) {
	if (index >= v->capacity)
		return -1; 
	v->data[index] = item; 
}

void vector_string(struct vector *v, char buffer[]) {
	buffer[0] = '['; 
	int buffer_index = 1; 
	char int_string[12]; // min value of integer as a string (11 digits + null char) 
	buffer[0] = '['; 
	int item_index = 0; 
	int str_index; 
	while (item_index < v->capacity) {
		snprintf(int_string, 12, "%d", v->data[item_index++]);
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

//int main() {
//	char buffer[100]; 
//	vector *v = vector_create(5); 
//	
//	vector_add(v, 1);
//	vector_add(v, 2);
//	vector_add(v, 3); 
//	vector_string(v, buffer);
//	printf("%d, %d: %s\n", v->count, v->capacity, buffer); 
//	
//	vector_add(v, 4);
//	vector_add(v, 5);
//	vector_add(v, 6);
//	vector_string(v, buffer);
//	printf("%d, %d: %s\n", v->count, v->capacity, buffer); 
//	
//	vector_set(v, 7, 0);
//	vector_set(v, 8, 1);
//	vector_set(v, 9, 2);
//	vector_string(v, buffer);
//	printf("%d, %d: %s\n", v->count, v->capacity, buffer); 
//
//	vector_destroy(v); 
//}
