#include "table.h"

void* row_slot(Table* table, uint32_t row_num)
{
	uint32_t page_num = row_num / ROWS_PER_PAGE;
	void* page = table->pages[page_num];
	if (page == NULL)
	{
		// Allocate memory only when we try to access the page
		page = table->pages[page_num] = malloc(PAGE_SIZE);
	}
	uint32_t row_offset = row_num % ROWS_PER_PAGE;
	uint32_t byte_offset = row_offset * ROW_SIZE;
	printf("-- %u -- %p\n", row_num, page+byte_offset);
	return page + byte_offset;
}

Table* new_table(void)
{
	Table* table = malloc(sizeof(Table));
	table->num_rows = 0;
	for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
	{
		table->pages[i] = NULL;
	}
	return table;
}
void free_table(Table* table)
{
	for (int i = 0; table->pages[i]; i++)
	{
		free(table->pages[i]);
	}
	free(table);
}
