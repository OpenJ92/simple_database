#include <string.h>
#include <stdio.h>

#include "statement.h"

void statement_dispatch(InputBuffer* input_buffer, Table* table)
{
	Statement statement;
	switch (prepare_statement(input_buffer, &statement))
	{
		case (PREPARE_SUCCESS):
			execute_statement(&statement, table); break;	
		case (PREPARE_UNRECOGNIZED_STATEMENT):
			printf(
				"Unrecognized keyword at the start of '%s'\n", 
				input_buffer->buffer
			      );
			break;
		case (PREPARE_STRING_TOO_LONG):
		{
			printf("STRING_TOO_LONG\n"); break;
		}
		case (PREPARE_NEGATIVE_ID):
		{
			printf("PREPARE_NEGATIVE_ID\n"); break;
		}
		case (PREPARE_SYNTAX_ERROR):
			printf("SYNTAX ERROR!\n"); break;
	}
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement)
{
	if (strncmp(input_buffer->buffer, "insert", 6) == 0)
	{
		return prepare_insert(input_buffer, statement);
	}
	if (strcmp(input_buffer->buffer, "select") == 0)
	{
		statement->type = STATEMENT_SELECT;
		return PREPARE_SUCCESS;
	}
	return PREPARE_UNRECOGNIZED_STATEMENT;
}


PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement)
{
	statement->type = STATEMENT_INSERT;
	// How are we going to generalize this to calls to generated tables?
	char* keyword = strtok(input_buffer->buffer, " ");
	char* id_string = strtok(NULL, " ");
	char* username = strtok(NULL, " ");
	char* email = strtok(NULL, " ");

	// check validity of insert statement
	if (id_string == NULL | username == NULL | email == NULL)
	{ return PREPARE_SYNTAX_ERROR; }

	int id = atoi(id_string);
	if (id < 0)
	{ return PREPARE_NEGATIVE_ID; }
	if (strlen(username) > COLUMN_USERNAME_SIZE)
	{ return PREPARE_STRING_TOO_LONG; }
	if (strlen(email) > COLUMN_USERNAME_SIZE)
	{ return PREPARE_STRING_TOO_LONG; }

	statement->row_to_insert.id = id;
	strcpy(statement->row_to_insert.username, username);
	strcpy(statement->row_to_insert.email, email);

	return PREPARE_SUCCESS;
}

ExecuteResult execute_insert(Statement* statement, Table* table)
{
	if (table->num_rows >= TABLE_MAX_ROWS)
	{
		return EXECUTE_TABLE_FULL;
	}

	Row* row_to_insert = &(statement->row_to_insert);
	serialize_row(row_to_insert, row_slot(table, table->num_rows));
	table->num_rows += 1;
	
	return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement* statement, Table* table)
{
	Row row;
	for (uint32_t i = 0; i < table->num_rows; i++)
	{
		deserialize_row(row_slot(table, i), &row);
		print_row(&row);
	}
	return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement* statement, Table* table)
{
	switch (statement->type)
	{
		case (STATEMENT_INSERT):
			return execute_insert(statement, table);
		case (STATEMENT_SELECT):
			return execute_select(statement, table);
	}
}
