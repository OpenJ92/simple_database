#include <string.h>
#include <stdio.h>

#include "statement.h"

void statement_dispatch(InputBuffer* input_buffer)
{
	Statement statement;
	switch (prepare_statement(input_buffer, &statement))
	{
		case (PREPARE_SUCCESS):
			execute_statement(&statement); printf("Executed.\n");
			break;	
		case (PREPARE_UNRECOGNIZED_STATEMENT):
			printf(
				"Unrecognized keyword at the start of '%s'\n", 
				input_buffer->buffer
			      );
			break;
		case (PREPARE_SYNTAX_ERROR):
			printf("SYNTAX ERROR!\n");
			break;
	}
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement)
{
	if (strncmp(input_buffer->buffer, "insert", 6) == 0)
	{
		statement->type = STATEMENT_INSERT;
		int args_assigned = 
		sscanf(
			  input_buffer->buffer, 
			  "inserted %d, %s, %s", 
			  &(statement->row_to_insert.id),
			  statement->row_to_insert.username,
			  statement->row_to_insert.email
		      );
		printf(
		       "inserted %d, %s, %s \n",
		       statement->row_to_insert.id,
		       statement->row_to_insert.username,
		       statement->row_to_insert.email
		      );
		if (args_assigned == 1) { return PREPARE_SYNTAX_ERROR; }
		return PREPARE_SUCCESS;
	}
	if (strcmp(input_buffer->buffer, "select") == 0)
	{
		statement->type = STATEMENT_SELECT;
		return PREPARE_SUCCESS;
	}
	return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement)
{
	printf("statement execution: %i \n", statement->type);
	switch (statement->type)
	{
		case (STATEMENT_INSERT):
			printf("This is where we would do an insert.\n");
			break;
		case (STATEMENT_SELECT):
			printf("This is where we would do a select.\n");
			break;
	}
}
