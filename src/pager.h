#ifndef PAGERHEADER
#define PAGERHEADER

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// pager.c

#define TABLE_MAX_PAGES 100

typedef struct
{
	int file_descriptor;
	uint32_t file_length;
	void* pages[TABLE_MAX_PAGES];
} Pager;

Pager* pager_open(const char* filename);
void* get_page(Pager* pager, uint32_t page_num);
void* pager_flush(Pager* pager, uint32_t page_num, uint32_t size);

#endif
