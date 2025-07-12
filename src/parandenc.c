#include "../include/parandenc.h"

void append_line_txt(int num)
{
	FILE *fptr = NULL;
	fptr = fopen("example.txt", "a");

	if (fptr == NULL) {
		fprintf(stderr, "Error while opening file");
		exit(EXIT_FAILURE);
	}

	for (int i = 31; i >= 0; i--) {
		fputc(((num >> i & 0b1) ? '1' : '0'), fptr);
	}
	fputc('\n', fptr);

	fclose(fptr);
}

void append_line_bin(uint32_t num)
{
	FILE *fptr = NULL;
	fptr = fopen("example.bin", "ab");

	if (fptr == NULL) {
		fprintf(stderr, "Error while opening file");
		exit(EXIT_FAILURE);
	}

	fwrite(&num, sizeof(uint32_t), 1, fptr);

	fclose(fptr);
}

int parandenc(char **tokens, Instruction *inst_arr)
{
	int i = 0, num_of_inst  = 0, k = 0;
	char *pos_of_colon = NULL;
	/* Initialize instruction array */
	memset(inst_arr, 0, sizeof(inst_arr) * MAX_INST);

	while (tokens[i] != NULL) { /* Operates to all tokens. */
		/* checks label */
		if ((pos_of_colon = strchr(tokens[i], ':')) != NULL) {
			*pos_of_colon =  '\0';
			printf("Found Label: %s\n", tokens[i]);
			inst_arr[num_of_inst].label = strdup(tokens[i++]);
		}
		
		/* R-type */
		if (
			(strcmp(tokens[i], "add")) == 0 ||
			(strcmp(tokens[i], "sub")) == 0 ||
			(strcmp(tokens[i], "sll")) == 0 ||
			(strcmp(tokens[i], "slt")) == 0 ||
			(strcmp(tokens[i], "sltu")) == 0 ||
			(strcmp(tokens[i], "xor")) == 0 ||
			(strcmp(tokens[i], "srl")) == 0 ||
			(strcmp(tokens[i], "sra")) == 0 ||
			(strcmp(tokens[i], "or")) == 0 ||
			(strcmp(tokens[i], "and")) == 0) {
			if (!parse_r_type(tokens, &i, inst_arr, &num_of_inst)) {
				fprintf(stderr, "Parsing error");
				exit(EXIT_FAILURE);
			}
			append_line_txt(encode_r_type(&inst_arr[--num_of_inst]));
			append_line_bin(encode_r_type(&inst_arr[num_of_inst]));
			num_of_inst++;

		}
		

		/* I-type */
		else if (
			(strcmp(tokens[i], "addi")) == 0 ||
			(strcmp(tokens[i], "andi")) == 0 ||
			(strcmp(tokens[i], "ori")) == 0 ||
			(strcmp(tokens[i], "xori")) == 0 ||
			(strcmp(tokens[i], "slli")) == 0 ||
			(strcmp(tokens[i], "srli")) == 0 ||
			(strcmp(tokens[i], "srai")) == 0 ||
			(strcmp(tokens[i], "lb")) == 0 ||
			(strcmp(tokens[i], "lh")) == 0 ||
			(strcmp(tokens[i], "lw")) == 0 ||
			(strcmp(tokens[i], "jalr")) == 0) {
			if (!parse_i_type(tokens, &i, inst_arr, &num_of_inst)) {
				fprintf(stderr, "Parsing error");
				exit(EXIT_FAILURE);
			}
			append_line_txt(encode_i_type(&inst_arr[--num_of_inst]));
			append_line_bin(encode_i_type(&inst_arr[num_of_inst]));
			num_of_inst++;
		}

		/* S-type */
		else if (
			(strcmp(tokens[i], "sb")) == 0 ||
			(strcmp(tokens[i], "sh")) == 0 ||
			(strcmp(tokens[i], "sw")) == 0) {
			if (!parse_s_type(tokens, &i, inst_arr, &num_of_inst)) {
				printf("Parsing error\n");
				exit(EXIT_FAILURE);
			}
		}

		/* B-type */
		else if (
			(strcmp(tokens[i], "beq")) == 0 ||
			(strcmp(tokens[i], "bne")) == 0 ||
			(strcmp(tokens[i], "blt")) == 0 ||
			(strcmp(tokens[i], "bge")) == 0 ||
			(strcmp(tokens[i], "bltu")) == 0 ||
			(strcmp(tokens[i], "bgeu")) == 0) {
			if (!parse_b_type(tokens, &i, inst_arr, &num_of_inst)) {
				printf("Parsing error\n");
				exit(EXIT_FAILURE);
			}
			append_line_txt(encode_b_type(&inst_arr[--num_of_inst]));
			append_line_bin(encode_b_type(&inst_arr[num_of_inst]));
			num_of_inst++;

		}

		/* U-type */
		else if (
			(strcmp(tokens[i], "lui")) == 0 ||
			(strcmp(tokens[i], "auipc")) == 0) {
			if (!parse_u_type(tokens, &i, inst_arr, &num_of_inst))
				printf("Parsing error\n");
		}

		/* J-type */
		else if (
			(strcmp(tokens[i], "jal")) == 0) {
			if (!parse_j_type(tokens, &i, inst_arr, &num_of_inst)) {
				printf("Parsing error\n");
				exit(EXIT_FAILURE);
			}
			append_line_txt(encode_j_type(&inst_arr[--num_of_inst]));
			append_line_bin(encode_j_type(&inst_arr[num_of_inst]));
			num_of_inst++;
		}

		/* NOP-type */
		else if (
			(strcmp(tokens[i], "nop")) == 0) {
			if (!parse_nop_type(tokens, &i, inst_arr, &num_of_inst)) {
				printf("Parsing error\n");
				exit(EXIT_FAILURE);
			}
			append_line_txt(encode_i_type(&inst_arr[--num_of_inst]));
			append_line_bin(encode_i_type(&inst_arr[num_of_inst]));
			num_of_inst++;
		}

		/* INVALID */
		else {
			fprintf(stderr, "Invalid syntax: %s\n", tokens[i]);
		}
		
		i++;

	}
	printf("num_of_inst after all par and enc: %d\n", num_of_inst);
	for (k = 0; k < num_of_inst; k++) {
		printf("{\n\t.pc = %d\n\t.label = %s\n\t.opcode = %s\n\t.rd = %s\n\t.rs1 = %s\n\t.rs2 = %s\n\t.imme = %s\n\t.lut: %s\n}\n",	
				inst_arr[k].pc, inst_arr[k].label, inst_arr[k].opcode, inst_arr[k].rd,
				inst_arr[k].rs1, inst_arr[k].rs2, inst_arr[k].imme,
				inst_arr[k].lut->mnemonic

		);
	}
	return num_of_inst;
}
