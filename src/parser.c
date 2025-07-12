#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../include/lut.h"
#include "../include/label.h"

labelEntry label_table[MAX_LABEL_TABLE];
int label_count = 0;

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

/* Check if it has a label, if so, add labelEntry to label_table[] */
void add_label_table(Instruction *inst)
{
	if (inst->label != NULL) { /* if it has label */
		label_table[label_count].label = strdup(inst->label);
		label_table[label_count].address = inst->pc;
		label_count++;
	}
}

/* 
 * Create seperate parsing function for different types.
 */

/* 
 * Parse R-type
 */
int parse_r_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst) {
	inst_arr[*num_of_inst].opcode = strdup(tokens[*i]);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rd = strdup(tokens[*i]);
	else {
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rs1 = strdup(tokens[*i]);
	else {
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rs2 = strdup(tokens[*i]);
	else {
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	/* Set InstLUTEntry */
	inst_arr[*num_of_inst].lut = lookup_inst(inst_arr[*num_of_inst].opcode);
	/* Set PC */
	inst_arr[*num_of_inst].pc = *num_of_inst * 4;
	/* Configure label_table if it has label */
	add_label_table(&inst_arr[*num_of_inst]);
	/* If parsing successes, num_of_inst must be incremented. */
	(*num_of_inst)++; 
	/* If parsing successes, return 1 (true) */
	return 1;
}

/* 
 * Parse I-type
 */
int parse_i_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst) {
	inst_arr[*num_of_inst].opcode = strdup(tokens[*i]);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rd = strdup(tokens[*i]);
	else {
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rs1 = strdup(tokens[*i]);
	else {
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	if (is_valid_immediate(tokens[++*i], TYPE_I))
		inst_arr[*num_of_inst].imme = strdup(tokens[*i]);
	else {
		fprintf(stderr, "Invalid immediate %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	/* Set InstLUTEntry */
	inst_arr[*num_of_inst].lut = lookup_inst(inst_arr[*num_of_inst].opcode);
	/* Set PC */
	inst_arr[*num_of_inst].pc = *num_of_inst * 4;
	/* Configure label_table if it has label */
	add_label_table(&inst_arr[*num_of_inst]);
	/* If parsing successes, num_of_inst must be incremented. */
	(*num_of_inst)++; 
	/* If parsing successes, return 1 (true) */
	return 1;
}

/* 
 * Parse S-type
 */
int parse_s_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst) {
	inst_arr[*num_of_inst].opcode = strdup(tokens[*i]);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rs1 = strdup(tokens[*i]);
	else {
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rs2 = strdup(tokens[*i]);
	else {
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	if (is_valid_immediate(tokens[++*i], TYPE_S))
		inst_arr[*num_of_inst].imme = strdup(tokens[*i]);
	else {
		fprintf(stderr, "Invalid immediate %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	/* Set InstLUTEntry */
	inst_arr[*num_of_inst].lut = lookup_inst(inst_arr[*num_of_inst].opcode);
	/* Set PC */
	inst_arr[*num_of_inst].pc = *num_of_inst * 4;
	/* Configure label_table if it has label */
	add_label_table(&inst_arr[*num_of_inst]);
	/* If parsing successes, num_of_inst must be incremented. */
	(*num_of_inst)++; 
	/* If parsing successes, return 1 (true) */
	return 1;
}

/* 
 * Parse B-type
 */
int parse_b_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst) {
	inst_arr[*num_of_inst].opcode = strdup(tokens[*i]);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rs1 = strdup(tokens[*i]);
	else {
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rs2 = strdup(tokens[*i]);
	else {
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	if (is_valid_immediate(tokens[++*i], TYPE_B))
		inst_arr[*num_of_inst].imme = strdup(tokens[*i]);
	else {
		fprintf(stderr, "Invalid immediate %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	/* Set InstLUTEntry */
	inst_arr[*num_of_inst].lut = lookup_inst(inst_arr[*num_of_inst].opcode);
	/* Set PC */
	inst_arr[*num_of_inst].pc = *num_of_inst * 4;
	/* Configure label_table if it has label */
	add_label_table(&inst_arr[*num_of_inst]);
	/* If parsing successes, num_of_inst must be incremented. */
	(*num_of_inst)++; 
	/* If parsing successes, return 1 (true) */
	return 1;
}

/* 
 * Parse U-type
 */
int parse_u_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst) {
	inst_arr[*num_of_inst].opcode = strdup(tokens[*i]);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rd = strdup(tokens[*i]);
	else {
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	if (is_valid_immediate(tokens[++*i], TYPE_U))
		inst_arr[*num_of_inst].imme = strdup(tokens[*i]);
	else  {
		fprintf(stderr, "Invalid immediate %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	/* Set InstLUTEntry */
	inst_arr[*num_of_inst].lut = lookup_inst(inst_arr[*num_of_inst].opcode);
	/* Set PC */
	inst_arr[*num_of_inst].pc = *num_of_inst * 4;
	/* Configure label_table if it has label */
	add_label_table(&inst_arr[*num_of_inst]);
	/* If parsing successes, num_of_inst must be incremented. */
	(*num_of_inst)++; 
	/* If parsing successes, return 1 (true) */
	return 1;
}

/* 
 * Parse J-type
 */
int parse_j_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst) {
	inst_arr[*num_of_inst].opcode = strdup(tokens[*i]);
	if (is_valid_register(tokens[++*i]))
		inst_arr[*num_of_inst].rd = strdup(tokens[*i]);
	else {
		fprintf(stderr, "Invalid register %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	if (is_valid_immediate(tokens[++*i], TYPE_J))
		inst_arr[*num_of_inst].imme = strdup(tokens[*i]);
	else {
		fprintf(stderr, "Invalid immediate %s at tokens[%d]\n", tokens[*i], *i);
		exit(EXIT_FAILURE);
	}
	/* Set InstLUTEntry */
	inst_arr[*num_of_inst].lut = lookup_inst(inst_arr[*num_of_inst].opcode);
	/* Set PC */
	inst_arr[*num_of_inst].pc = *num_of_inst * 4;
	/* Configure label_table if it has label */
	add_label_table(&inst_arr[*num_of_inst]);
	/* If parsing successes, num_of_inst must be incremented. */
	(*num_of_inst)++; 
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
	/* Set InstLUTEntry */
	inst_arr[*num_of_inst].lut = lookup_inst(inst_arr[*num_of_inst].opcode);
	/* Set PC */
	inst_arr[*num_of_inst].pc = *num_of_inst * 4;
	/* Configure label_table if it has label */
	add_label_table(&inst_arr[*num_of_inst]);
	/* If parsing successes, num_of_inst must be incremented. */
	(*num_of_inst)++; 
	/* If parsing successes, return 1 (true) */
	return 1;
}


