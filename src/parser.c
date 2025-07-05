#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
			printf("This has colon.\n");
			*pos_of_colon =  '\0';
			printf("label: %s\n", tokens[i]);
			inst_arr[num_of_inst].label = strdup(tokens[i]);
		}

		/* R-type */
		/* add */
		if ((strcmp(tokens[i], "add")) == 0) {
			inst_arr[num_of_inst].opcode = strdup("add");
			inst_arr[num_of_inst].rd = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs1 = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs2 = strdup(tokens[++i]);
			num_of_inst++;
		}
		/* sub */
		else if ((strcmp(tokens[i], "sub")) == 0) {
			inst_arr[num_of_inst].opcode = strdup("sub");
			inst_arr[num_of_inst].rd = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs1 = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs2 = strdup(tokens[++i]);
			num_of_inst++;
		}
		/* sll rd = rs1 << rs2 */ 
		else if ((strcmp(tokens[i], "sll")) == 0) {
			inst_arr[num_of_inst].opcode = strdup("sll");
			inst_arr[num_of_inst].rd = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs1 = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs2 = strdup(tokens[++i]);
			num_of_inst++;
		}
		/* slt rd = (rs1 < rs2) ? 1 : 0  */ 
		else if ((strcmp(tokens[i], "slt")) == 0) { 
			inst_arr[num_of_inst].opcode = strdup("slt");
			inst_arr[num_of_inst].rd = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs1 = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs2 = strdup(tokens[++i]);
			num_of_inst++;
		}
		/* sltu rd = (rs1 < rs2 unsigned) */ 
		else if ((strcmp(tokens[i], "sltu")) == 0) {
			inst_arr[num_of_inst].opcode = strdup("sltu");
			inst_arr[num_of_inst].rd = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs1 = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs2 = strdup(tokens[++i]);
			num_of_inst++;
		}
		/* xor rd = (rs1 ^ rs2 ) */ 
		else if ((strcmp(tokens[i], "xor")) == 0) {
			inst_arr[num_of_inst].opcode = strdup("xor");
			inst_arr[num_of_inst].rd = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs1 = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs2 = strdup(tokens[++i]);
			num_of_inst++;
		}
		/* srl rd = rs1 >> rs2 logical */ 
		else if ((strcmp(tokens[i], "srl")) == 0) { 
			inst_arr[num_of_inst].opcode = strdup("srl");
			inst_arr[num_of_inst].rd = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs1 = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs2 = strdup(tokens[++i]);
			num_of_inst++;
		}
		/* sra rd = rs1 >> rs2 arithmetic */ 
		else if ((strcmp(tokens[i], "sra")) == 0) { 
			inst_arr[num_of_inst].opcode = strdup("sra");
			inst_arr[num_of_inst].rd = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs1 = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs2 = strdup(tokens[++i]);
			num_of_inst++;
		}
		/* or rd = rs1 | rs2 */ 
		else if ((strcmp(tokens[i], "or")) == 0) { 
			inst_arr[num_of_inst].opcode = strdup("or");
			inst_arr[num_of_inst].rd = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs1 = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs2 = strdup(tokens[++i]);
			num_of_inst++;
		}
		/* and rd = rs1 & rs2 */
		else if ((strcmp(tokens[i], "and")) == 0) { 
			inst_arr[num_of_inst].opcode = strdup("and");
			inst_arr[num_of_inst].rd = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs1 = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs2 = strdup(tokens[++i]);
			num_of_inst++;
		}
		
		/* I-type */
		/* addi rd = rs1 + imm */
		else if ((strcmp(tokens[i], "addi")) == 0) { 
			inst_arr[num_of_inst].opcode = strdup("addi");
			inst_arr[num_of_inst].rd = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs1 = strdup(tokens[++i]);
			inst_arr[num_of_inst].imme = strdup(tokens[++i]);
			num_of_inst++;
		}

		/* S-type */
		/* later or maybe not */

		/* B-type */
		/* beq Branch if equal */
		else if ((strcmp(tokens[i], "beq")) == 0) { 
			inst_arr[num_of_inst].opcode = strdup("beq");
			inst_arr[num_of_inst].rd = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs1 = strdup(tokens[++i]);
			inst_arr[num_of_inst].imme = strdup(tokens[++i]);
			num_of_inst++;
		}

		/* bnq Branch if not equal */
		else if ((strcmp(tokens[i], "bne")) == 0) { 
			inst_arr[num_of_inst].opcode = strdup("bne");
			inst_arr[num_of_inst].rd = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs1 = strdup(tokens[++i]);
			inst_arr[num_of_inst].rs2 = strdup(tokens[++i]);
			num_of_inst++;
		}

		/* U-type */
		/* later or maybe not */

		/* J-type */
		/* jal Jump and link */
		else if ((strcmp(tokens[i], "jal")) == 0) { 
			inst_arr[num_of_inst].opcode = strdup("jal");
			inst_arr[num_of_inst].rd = strdup(tokens[++i]);
			num_of_inst++;
		}

		/* temp for nop */
		else if ((strcmp(tokens[i], "nop")) == 0) { 
			inst_arr[num_of_inst].opcode = strdup("nop");
			num_of_inst++;
		}

		i++;

	}
	for (k = 0; k < num_of_inst; k++) {
		printf("{\n\t.label = %s\n\t.opcode = %s\n\t.rd = %s\n\t.rs1 = %s\n\t.rs2 = %s\n}\n",	
				inst_arr[k].label, inst_arr[k].opcode, inst_arr[k].rd,
				inst_arr[k].rs1, inst_arr[k].rs2
		);
	}
	return num_of_inst;
}
