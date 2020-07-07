#ifndef REPLHEADER
#define REPLHEADER

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
	char* buffer;
	size_t buffer_length;
	ssize_t input_length;
} InputBuffer;

void REPL(void);
void print_prompt(void);
void read_input(InputBuffer* input_buffer);
void close_input_buffer(InputBuffer* input_buffer);
InputBuffer* new_input_buffer(void);

#endif
