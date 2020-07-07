#ifndef STATEMENTHEADER
#define STATEMENTHEADER

#include "repl.h"
#include "row.h"

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
	PREPARE_SYNTAX_ERROR
} PrepareResult;

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);
void execute_statement(Statement* statement);
void statement_dispatch(InputBuffer* input_buffer);

#endif
