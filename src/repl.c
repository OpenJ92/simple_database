#include "repl.h"

#include "metacommand.h"
#include "statement.h"

void REPL(void)
{
	InputBuffer* input_buffer = new_input_buffer();

	while (true)
	{
		print_prompt();
		read_input(input_buffer);

		// We're now running into circular include problems and the dispatcher should be defined elsewhere
		// so that we have no dependancies on metacommand and statement definitions in our repl file. 
		// Perhaps we should move these switch statements into thier respective files.
		//
		// meta-command dispatcher -- perhaps these should be placed into seperate dispatch files.
		if (input_buffer->buffer[0] == '.' )
		{
			metacommand_dispatch(input_buffer);
		}
		else
		{
			statement_dispatch(input_buffer);
		}

		// statement processor -- perhaps these should be placed into seperate dispatch files.
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
	// Note below the meaning of the inputs and the expected output of this element.
	// We're getting the number of bytes read here, but what happens to the data at
	// the read line? I see! The allocation of the data occurs in getline given that
	// we passed the pointer to pointer to buffer as the first argument. It's a change
	// of state!
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
	// Here we're freeing memory that was allocated to the Heap assosiated to the 
	// InputBuffer type.
	free(input_buffer->buffer);
	free(input_buffer);
}
