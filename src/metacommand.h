#ifndef METACOMMANDHEADER
#define METACOMMANDHEADER
	
#include "repl.h"

typedef enum 
{
	META_COMMAND_SUCCESS,
	META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

MetaCommandResult do_meta_command(InputBuffer* input_buffer);
void metacommand_dispatch(InputBuffer* input_buffer);

#endif
