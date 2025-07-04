#include <stdio.h>
#include "./lexer.c" /* my lexer */

#define MAX_TOKEN 256

int main(void)
{
	FILE *fptr = NULL;
	char *tokens[MAX_TOKEN];
	int num_tokens;

	num_tokens = lexer_riscv(fptr, "../example.s", tokens);

	for (int i = 0; i < num_tokens; i++) {
		printf("%s\n", tokens[i]);
	}

	free_tokens(tokens, num_tokens);


	return 0;
}
