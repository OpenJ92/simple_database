#include "pager.h"

Pager* pager_open(const char* filename)
{
	int fd = open( 
		       filename,
		       O_RDWR | O_CREAT, // read/write mode | create file DNE
		       S_IWUSR | S_IRUSR // user write permis | user read permis
		     );

	if (fd == -1)
	{
		printf("Unable to open file\n");
		exit(EXIT_FAILURE);
	}

	off_t file_length = lseek(fd, 0, SEEK_END);

	Pager* pager = malloc(sizeof(Pager)); // Heap
	pager->file_descriptor = fd;
	pager->file_length = file_length;

	for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
	{
		pager->pages[i] = NULL;
	}

	return pager;
}

void* get_page(Pager* pager, uint32_t page_num)
{
	if (page_num > TABLE_MAX_PAGES)
	{
		printf("Tried to fetch page number out of bounds. %d > %d\n"
		        , page_num
			, TABLE_MAX_PAGES);
		exit(EXIT_FAILURE);
	}

	if (pager->pages[page_num] == NULL)
	{
		// cache miss. Allocate memory and load from file.
		void* page = malloc(4096);
		uint32_t num_pages = pager->file_length / 4096;

		// Save partial page at the end of the file.
		if (pager->file_length % 4096)
		{
			num_pages += 1;
		}
	
		if (page_num <= num_pages)
		{
			lseek(pager->file_descriptor, page_num * 4096, SEEK_SET);
			ssize_t bytes_read = read(pager->file_descriptor
						  , page
						  , 4096
						 );
			if (bytes_read == -1)
			{
				printf("Error reading file: %d\n", errno);
				exit(EXIT_FAILURE);
			}
		}
		pager->pages[page_num] = page;
	}

	return pager->pages[page_num];
}

void* pager_flush(Pager* pager, uint32_t page_num, uint32_t size)
{
	if (pager->pages[page_num] == NULL)
	{
		printf("Tried to flush null page\n");
		exit(EXIT_FAILURE);
	}

	off_t offset = lseek(pager->file_descriptor, page_num*4096, SEEK_SET);

	if (offset == -1)
	{
		printf("Error in seeking: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	ssize_t bytes_written = 
		write(pager->file_descriptor, pager->pages[page_num], size);

	if (bytes_written == -1)
	{
		printf("Error in writing: %d\n", errno);
		exit(EXIT_FAILURE);
	}
}
