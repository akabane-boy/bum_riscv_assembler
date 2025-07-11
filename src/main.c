#include <stdio.h>
#include <stdio.h>
#include "../include/lut.h"
#include "../include/parser.h"
#include "../include/lexer.h"
#include "../include/encoder.h"
#include "../include/label.h"


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
	printf("Array of Instructions:\n");
	printf("-------------------------------------------\n");
	num_of_inst = parser_riscv(tokens, inst_arr);

	/* testing encoder */
	uint32_t r_num, i_num, b_num;
	r_num = encode_r_type(&inst_arr[1]);
	i_num = encode_i_type(&inst_arr[0]);
	b_num = encode_b_type(&inst_arr[4]);
	int_to_str_print(r_num);
	printf("\n");
	int_to_str_print(i_num);
	printf("\n");
	int_to_str_print(b_num);

	printf("\n-------------------------------------------\n");
	printf("Free-ing process:\n");
	printf("-------------------------------------------\n");
	free_tokens(tokens);
	free_Inst_arr(inst_arr, num_of_inst);

	return 0;
}
