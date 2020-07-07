#ifndef ROWHEADER
#define ROWHEADER

#include <stdint.h>

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct
{
	uint32_t id;
	char username[COLUMN_USERNAME_SIZE];
	char email[COLUMN_EMAIL_SIZE];
} Row;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

static const uint32_t AID_SIZE = size_of_attribute(Row, id);
static const uint32_t AUSERNAME_SIZE = size_of_attribute(Row,username);
static const uint32_t AEMAIL_SIZE = size_of_attribute(Row, email);
static const uint32_t AID_OFFSET = 0;
static const uint32_t AUSERNAME_OFFSET = AID_OFFSET + AID_SIZE;
static const uint32_t AEMAIL_OFFSET = AUSERNAME_OFFSET + AUSERNAME_SIZE;
static const uint32_t AROW_SIZE = AID_SIZE + AUSERNAME_SIZE + AEMAIL_SIZE;

void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);
#endif
