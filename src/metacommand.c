#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "metacommand.h"

void metacommand_dispatch(InputBuffer* buffer, Table* table)
{
	switch (do_meta_command(buffer, table))
	{
		case (META_COMMAND_SUCCESS):
			break;
		case (META_COMMAND_UNRECOGNIZED_COMMAND):
			printf("Unrecognized command '%s'\n", buffer->buffer);
			break;
	}
}

MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table)
{
	if (strcmp(input_buffer->buffer, ".exit") == 0)
	{
		db_close(table);
		printf("G'night!\n"); exit(EXIT_SUCCESS);
	}
	else
	{
		return META_COMMAND_UNRECOGNIZED_COMMAND;
	}
}
