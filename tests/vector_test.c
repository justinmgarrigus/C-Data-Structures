#include <stdio.h>  
#include <stdlib.h>
#include <string.h> 
#include "../lib/vector.h" 

int main() {
	char buffer[128]; 
	
	int initial_capacity; 
	printf("Initial capacity: "); 
	scanf("%d, ", &initial_capacity); 

	int type_size = 0;
	char type[3]; 
	char *type_format; 
	while (type_size == 0) {
		printf("Type: (i)nt, (c)har, (s)tring: "); 
		scanf("%2s", type); 

		if (type[0] == 'i') { type_size = sizeof(int); type_format = "%d"; } 
		else if (type[0] == 'c') { type_size = sizeof(char); type_format = "%c"; }
		else if (type[0] == 's') { type_size = sizeof(char*); type_format = "%s"; }
		else if (strlen(type) != 1) printf("Invalid type. Please enter a single letter.\n");
		else printf("Invalid type. Please enter either 'i', 'c', or 's'.\n"); 
	}

	vector *v = vector_create(initial_capacity, type_size); 
	
	char input[3]; 
	int val_int; 
	char val_string[64]; 
	int input_index;
	char *alloc_string; 
	while (1) {
		printf("---\nInput an operation (a)dd, (s)et, (d)isplay, (q)uit: "); 
		scanf("%2s", input);

		if (input[0] == 'a' || input[0] == 's') {
			printf("Input a value: "); 
			scanf("%63s", val_string); 

			switch (type[0]) {
				case 'i': 
					val_int = atoi(val_string); 
					if (val_int == 0 && input[0] != '0') {
						printf("Invalid input. Please enter an integer.\n"); 
						continue; 
					}
					break; 

				case 's': 
					alloc_string = malloc(sizeof(char) * strlen(val_string));
					strcpy(alloc_string, val_string);
					break; 
			}
			
			if (input[0] == 'a') {
				switch (type[0]) {
					case 'i': vector_add(v, int, val_int); break;
					case 'c': vector_add(v, char, val_string[0]); break;
					default: vector_add(v, char*, alloc_string); break; 
				}
			}
			else { 
				printf("Input an index: "); 
				scanf("%d", &input_index); 
				switch (type[0]) {
					case 'i': vector_set(v, int, val_int, input_index); break; 
					case 'c': vector_set(v, char, val_string[0], input_index); break;
					default: vector_set(v, char*, alloc_string, input_index); break; 
				}
			}
		}
		else if (input[0] == 'd') {
			vector_string(v, type_format, buffer); 
			printf("Count {%lu}, capacity {%lu}: %s\n", v->count, v->capacity, buffer);
		}
		else if (input[0] == 'q') {
			break; 
		}
		else if (strlen(type) != 1) { 
			printf("Invalid operation. Please enter a single letter.\n");
		}
		else { 
			printf("Invalid operation. Please enter either 'a', 's', or 'd'.\n"); 
		}
	}

	if (type[0] == 's') {
		// strings were dynamically allocated (in this example). 
		for (int i = 0; i < v->count; i++) {
			free(vector_get(v, char*, i));  
		}
	}

	vector_destroy(v); 
}
