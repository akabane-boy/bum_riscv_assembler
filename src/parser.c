#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/parser.h"

void free_Inst(Instruction inst)
{
	printf("Freeing opcode: %p\n", inst.opcode);
	free(inst.opcode);
	printf("Freeing rd: %p\n", inst.rd);
	free(inst.rd);
	printf("Freeing rs1: %p\n", inst.rs1);
	free(inst.rs1);
	printf("Freeing rs2: %p\n", inst.rs2);
	free(inst.rs2);
	printf("Freeing imme: %p\n", inst.imme);
	free(inst.imme);
	printf("Freeing label: %p\n", inst.label);
	free(inst.label);
}

void free_Inst_arr(Instruction *inst_arr, int num_of_inst)
{
	int i;
	for (i = 0; i < num_of_inst; i++) {
		free_Inst(inst_arr[i]);
	}
}

/* returns true for x0 ~ x31 */
bool is_valid_register(char *token)
{
	if (token[0] != 'x') return false;
	char *endptr;
	long num;
	num = strtol(token + 1, &endptr, 10);
	if (*endptr == '\0' && 0 <= num && num < 32) return true;
	else return false;
}

/* is_valid_immediate */
bool is_valid_immediate(char *token, InstType type)
{
	char *endptr;
	long num;
	num = strtol(token, &endptr, 0);
	bool is_label = (*endptr != '\0'); /* not a number */
	switch (type) {
		case TYPE_I:
			/* I: 12-bit signed */
			return (-0x800 <= num && num <= 0x7FF);
			break;
		case TYPE_S:
			/* S: 12-bit signed */
			return (-0x800 <= num && num <= 0x7FF);
			break;
		case TYPE_B:
			/* B: 13-bit signed (aligned) */
			/* LSB must be 0. => num%2==0 */
			return is_label || (-0x1000 <= num && num <= 0xFFE && (num % 2 == 0));
			break;
		case TYPE_U:
			/* U: 20-bit unsigned */
			return (0 <= num && num <= 0xFFFFF);
			break;
		case TYPE_J:
			/* J: 21-bit signed (aligned) */
			return is_label || (-0x10000 <= num && num <= 0xFFFFE && (num % 2 == 0));
			break;
		default:
			return false;
	}
}

/* 
 * Create seperate parsing function for different types.
 */

/* 
 * Parse R-type
 */
int parse_r_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst) {
	/* Later, check if immediate is valid or not (register implemented) */
	inst_arr[*num_of_inst].opcode = strdup(tokens[*i]);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rd = strdup(tokens[*i]);
	else
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rs1 = strdup(tokens[*i]);
	else
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rs2 = strdup(tokens[*i]);
	else
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
	/* Set inst type */
	inst_arr[*num_of_inst].type = TYPE_R;
	(*num_of_inst)++; /* If parsing successes, num_of_inst must be incremented. */
	/* If parsing successes, return 1 (true) */
	return 1;
}

/* 
 * Parse I-type
 */
int parse_i_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst) {
	/* Later, check if immediate is valid or not (register implemented) */
	inst_arr[*num_of_inst].opcode = strdup(tokens[*i]);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rd = strdup(tokens[*i]);
	else
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rs1 = strdup(tokens[*i]);
	else
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
	if (is_valid_immediate(tokens[++*i], TYPE_I))
		inst_arr[*num_of_inst].imme = strdup(tokens[*i]);
	else
		fprintf(stderr, "Invalid immediate %s at tokens[%d]\n", tokens[*i], *i);
	/* Set inst type */
	inst_arr[*num_of_inst].type = TYPE_I;
	(*num_of_inst)++; /* If parsing successes, num_of_inst must be incremented. */
	/* If parsing successes, return 1 (true) */
	return 1;
}

/* 
 * Parse S-type
 */
int parse_s_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst) {
	/* Later, check if immediate is valid or not (register implemented) */
	inst_arr[*num_of_inst].opcode = strdup(tokens[*i]);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rs1 = strdup(tokens[*i]);
	else
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rs2 = strdup(tokens[*i]);
	else
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
	if (is_valid_immediate(tokens[++*i], TYPE_S))
		inst_arr[*num_of_inst].imme = strdup(tokens[*i]);
	else
		fprintf(stderr, "Invalid immediate %s at tokens[%d]\n", tokens[*i], *i);
	/* Set inst type */
	inst_arr[*num_of_inst].type = TYPE_S;
	(*num_of_inst)++; /* If parsing successes, num_of_inst must be incremented. */
	/* If parsing successes, return 1 (true) */
	return 1;
}

/* 
 * Parse B-type
 */
int parse_b_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst) {
	/* Later, check if immediate is valid or not (register implemented) */
	inst_arr[*num_of_inst].opcode = strdup(tokens[*i]);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rs1 = strdup(tokens[*i]);
	else
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rs2 = strdup(tokens[*i]);
	else
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
	if (is_valid_immediate(tokens[++*i], TYPE_B))
		inst_arr[*num_of_inst].imme = strdup(tokens[*i]);
	else
		fprintf(stderr, "Invalid immediate %s at tokens[%d]\n", tokens[*i], *i);
	/* Set inst type */
	inst_arr[*num_of_inst].type = TYPE_B;
	(*num_of_inst)++; /* If parsing successes, num_of_inst must be incremented. */
	/* If parsing successes, return 1 (true) */
	return 1;
}

/* 
 * Parse U-type
 */
int parse_u_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst) {
	/* Later, check if immediate is valid or not (register implemented) */
	inst_arr[*num_of_inst].opcode = strdup(tokens[*i]);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rd = strdup(tokens[*i]);
	else
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
	if (is_valid_immediate(tokens[++*i], TYPE_U))
		inst_arr[*num_of_inst].imme = strdup(tokens[*i]);
	else 
		fprintf(stderr, "Invalid immediate %s at tokens[%d]\n", tokens[*i], *i);
	/* Set inst type */
	inst_arr[*num_of_inst].type = TYPE_U;
	(*num_of_inst)++; /* If parsing successes, num_of_inst must be incremented. */
	/* If parsing successes, return 1 (true) */
	return 1;
}

/* 
 * Parse J-type
 */
int parse_j_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst) {
	/* Later, check if immediate is valid or not (register implemented) */
	inst_arr[*num_of_inst].opcode = strdup(tokens[*i]);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rd = strdup(tokens[*i]);
	else
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
	if (is_valid_immediate(tokens[++*i], TYPE_J))
		inst_arr[*num_of_inst].imme = strdup(tokens[*i]);
	else
		fprintf(stderr, "Invalid immediate %s at tokens[%d]\n", tokens[*i], *i);
	/* Set inst type */
	inst_arr[*num_of_inst].type = TYPE_J;
	(*num_of_inst)++; /* If parsing successes, num_of_inst must be incremented. */
	/* If parsing successes, return 1 (true) */
	return 1;
}

/* 
 * Parse NOP-type
 */
int parse_nop_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst) {
	/* Acts like addi with (addi x0, x0, 0) which does nothing (pseudo-instruction). Advancing the program counter. */
	inst_arr[*num_of_inst].opcode = strdup(tokens[*i]); 
	inst_arr[*num_of_inst].rd = strdup("0");
	inst_arr[*num_of_inst].rs1 = strdup("0");
	inst_arr[*num_of_inst].imme = strdup("0");
	/* Set inst type */
	inst_arr[*num_of_inst].type = TYPE_NOP;
	(*num_of_inst)++; /* If parsing successes, num_of_inst must be incremented. */
	/* If parsing successes, return 1 (true) */
	return 1;
}



/* 
 * Gets array of tokens.
 * Modify them to a Instruction array.
 * Return number of Instructions.
 */
int parser_riscv(char **tokens, Instruction *inst_arr)
{
	/*
	 * R-type:
	 * add, sub, and, or, sll, slt, sra, xor
	 *
	 * opcode 7, rd 5, funct3 3, rs1 5, rs2 5, funct7 7
	 */

	/*
	 * I-type:
	 * addi, andi, ori, lb, ln, lw, jalr
	 *
	 * opcode 7, rd 5, funct3 3, rs1 5, imm[11:0] 12
	 */

	/* S-type:
	 * sb, sh, sw
	 *
	 * opcode 7, imm[4:0] 5, funct3 3, rs1 5, rs2 5, imm[11:5] 7
	 */

	/* B-type:
	 * beq, bne, blt, bge, bltu, bgeu
	 *
	 * opcode 7, imm 1, imm[4:1] 4, funct3 3, rs1 5, rs2 5, imm[10:5] 6, imm 1
	 */

	/* U-type:
	 * lui, auipc
	 *
	 * opcode 7, rd 5, imm[31:12] 20
	 */

	/* J-type:
	 * jal
	 *
	 * opcode 7, rd 5, imm[19:12] 8, imm 1, imm[10:1] 10, imm 1
	 */

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
			if (!parse_r_type(tokens, &i, inst_arr, &num_of_inst))
				printf("Parsing error\n");
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
			if (!parse_i_type(tokens, &i, inst_arr, &num_of_inst))
				printf("Parsing error\n");
		}

		/* S-type */
		else if (
			(strcmp(tokens[i], "sb")) == 0 ||
			(strcmp(tokens[i], "sh")) == 0 ||
			(strcmp(tokens[i], "sw")) == 0) {
			if (!parse_s_type(tokens, &i, inst_arr, &num_of_inst))
				printf("Parsing error\n");
		}

		/* B-type */
		else if (
			(strcmp(tokens[i], "beq")) == 0 ||
			(strcmp(tokens[i], "bne")) == 0 ||
			(strcmp(tokens[i], "blt")) == 0 ||
			(strcmp(tokens[i], "bge")) == 0 ||
			(strcmp(tokens[i], "bltu")) == 0 ||
			(strcmp(tokens[i], "bgeu")) == 0) {
			if (!parse_b_type(tokens, &i, inst_arr, &num_of_inst))
				printf("Parsing error\n");
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
			if (!parse_j_type(tokens, &i, inst_arr, &num_of_inst))
				printf("Parsing error\n");
		}

		/* NOP-type */
		else if (
			(strcmp(tokens[i], "nop")) == 0) {
			if (!parse_nop_type(tokens, &i, inst_arr, &num_of_inst))
				printf("Parsing error\n");
		}

		/* INVALID */
		else {
			fprintf(stderr, "Invalid syntax: %s\n", tokens[i]);
		}
		
		i++;

	}
	for (k = 0; k < num_of_inst; k++) {
		printf("{\n\t.label = %s\n\t.opcode = %s\n\t.rd = %s\n\t.rs1 = %s\n\t.rs2 = %s\n\t.imme = %s\n}\n",	
				inst_arr[k].label, inst_arr[k].opcode, inst_arr[k].rd,
				inst_arr[k].rs1, inst_arr[k].rs2, inst_arr[k].imme
		);
	}
	return num_of_inst;
}
