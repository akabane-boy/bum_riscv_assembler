#include <stdio.h>
#include "../include/parser.h"
#include "../include/lexer.h"


int main(void)
{
	FILE *fptr = NULL;
	char *tokens[MAX_TOKEN];
	Instruction inst_arr[MAX_INST];
	int i = 0;
	int num_of_inst = 0;

	lexer_riscv(fptr, "./example.s", tokens);

	while (tokens[i] != NULL) {
		printf("Token's coming!: %s\n", tokens[i]);
		i++;
	}

	num_of_inst = parser_riscv(tokens, inst_arr);

	free_tokens(tokens);
	free_Inst_arr(inst_arr, num_of_inst);

	return 0;
}
