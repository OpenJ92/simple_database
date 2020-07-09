#include "src/repl.h"

int main(int argc, char* argv[])
{
	if (argc < 2) { exit(EXIT_FAILURE); };
	char* filename = argv[1];
	REPL(filename); return 0;
}
