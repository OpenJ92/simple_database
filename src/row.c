#include <string.h>

#include "row.h"


void serialize_row(Row* source, void* destination)
{
	memcpy(destination + AID_OFFSET, &(source->id), AID_SIZE);
	memcpy(destination + AUSERNAME_OFFSET, &(source->username), AUSERNAME_SIZE);
	memcpy(destination + AEMAIL_OFFSET, &(source->email), AEMAIL_SIZE);
}

void deserialize_row(void* source, Row* destination)
{
	memcpy(&(destination->id), source + AID_OFFSET, AID_SIZE);
	memcpy(&(destination->username), source + AUSERNAME_OFFSET, AUSERNAME_SIZE);
	memcpy(&(destination->email), source + AEMAIL_OFFSET, AEMAIL_SIZE);
}
