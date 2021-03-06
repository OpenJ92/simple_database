#ifndef STATEMENTHEADER
#define STATEMENTHEADER

// statement.c
#include "repl.h"
#include "row.h"
#include "table.h"

typedef enum
{
	STATEMENT_INSERT,
	STATEMENT_SELECT
} StatementType;

typedef struct
{
	StatementType type;
	Row row_to_insert; // only used in insert statements
} Statement;

typedef enum 
{
	PREPARE_SUCCESS,
	PREPARE_UNRECOGNIZED_STATEMENT,
	PREPARE_SYNTAX_ERROR,
	PREPARE_STRING_TOO_LONG,
	PREPARE_NEGATIVE_ID
} PrepareResult;

typedef enum
{
	EXECUTE_TABLE_FULL,
	EXECUTE_SUCCESS
} ExecuteResult;

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);
PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement);
ExecuteResult execute_insert(Statement* statement, Table* table);
ExecuteResult execute_select(Statement* statement, Table* table);
ExecuteResult execute_statement(Statement* statement, Table* table);
void statement_dispatch(InputBuffer* input_buffer, Table* table);

#endif
