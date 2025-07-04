#include <stdio.h>
#include "../include/parser.h"
#include "../include/lexer.h"

#define MAX_TOKEN 256

int main(void)
{
	FILE *fptr = NULL;
	char *tokens[MAX_TOKEN];
	int i = 0;

	lexer_riscv(fptr, "./example.s", tokens);

	while (tokens[i] != NULL) {
		printf("Token's coming!: %s\n", tokens[i]);
		i++;
	}

	parser_riscv(tokens);

	free_tokens(tokens);


	return 0;
}
