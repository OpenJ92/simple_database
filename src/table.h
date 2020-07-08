#include <stdint.h>
#include <stdlib.h>

#ifndef TABLEHEADER
#define TABLEHEADER

#include "row.h"

#define TABLE_MAX_PAGES 100
static const uint32_t PAGE_SIZE = 4096; // representing 4 kilobytes
static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

typedef struct
{
	uint32_t num_rows;
	void* pages[TABLE_MAX_PAGES];
} Table;

void* row_slot(Table* table, uint32_t row_num);

#endif
