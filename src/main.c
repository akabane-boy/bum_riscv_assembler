#include <stdio.h>
#include <stdio.h>
#include "../include/lut.h"
#include "../include/parser.h"
#include "../include/lexer.h"
#include "../include/encoder.h"
#include "../include/label.h"
#include "../include/parandenc.h"


int main(void)
{
	FILE *fptr = NULL;
	char *tokens[MAX_TOKEN];
	Instruction inst_arr[MAX_INST];
	int i = 0;
	int num_of_inst = 0;

	printf("\n**My RISC-V Assembler**\n\n");
	printf("-------------------------------------------\n");
	printf("Lexer starts:\n");
	printf("-------------------------------------------\n");
	lexer_riscv(fptr, "./example.s", tokens);

	while (tokens[i] != NULL) {
		printf("Token #%d: %s\n", i, tokens[i]);
		i++;
	}

	printf("\n-------------------------------------------\n");
	printf("Parse and Encode:\n");
	printf("-------------------------------------------\n");
	num_of_inst = parandenc(tokens, inst_arr);


	printf("\n-------------------------------------------\n");
	printf("Free-ing process:\n");
	printf("-------------------------------------------\n");
	free_tokens(tokens);
	free_Inst_arr(inst_arr, num_of_inst);

	return 0;
}
