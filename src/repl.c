#include "repl.h"

#include "metacommand.h"
#include "statement.h"
#include "table.h"

void REPL(void)
{
	Table* table = new_table();
	InputBuffer* input_buffer = new_input_buffer();

	while (true)
	{
		print_prompt();
		read_input(input_buffer);

		if (input_buffer->buffer[0] == '.')
		{
			metacommand_dispatch(input_buffer, table);
		}
		else
		{
			statement_dispatch(input_buffer, table);
		}
	}
}


InputBuffer* new_input_buffer(void)
{
	InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
	input_buffer->buffer = NULL;
	input_buffer->buffer_length = 0;
	input_buffer->input_length = 0;

	return input_buffer;
} 

void print_prompt(void) { printf("db > "); }

void read_input(InputBuffer* input_buffer)
{
	ssize_t bytes_read = 
		getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

	if (bytes_read <= 0)
	{
		printf("Error reading input.\n");
		exit(EXIT_FAILURE);
	}

	input_buffer->input_length = bytes_read - 1;
	input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer)
{
	free(input_buffer->buffer);
	free(input_buffer);
}
