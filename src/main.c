#include <stdio.h>
#include "./lexer.c" /* my lexer */

#define MAX_TOKEN 256

int main(void)
{
	FILE *fptr = NULL;
	char *tokens[MAX_TOKEN];
	int i = 0;

	lexer_riscv(fptr, "../example.s", tokens);

	while (tokens[i] != NULL) {
		printf("%s\n", tokens[i]);
		i++;
	}

	free_tokens(tokens);


	return 0;
}
