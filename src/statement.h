#ifndef STATEMENTHEADER
#define STATEMENTHEADER

#include <string.h>

#include "repl.h"

	typedef enum
	{
		STATEMENT_INSERT,
		STATEMENT_SELECT
	} StatementType;
	
	typedef struct
	{
		StatementType type;
	} Statement;
	
	typedef enum 
	{
		PREPARE_SUCCESS,
		PREPARE_UNRECOGNIZED_STATEMENT
	} PrepareResult;
	
	PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);
	void execute_statement(Statement* statement);

#endif
