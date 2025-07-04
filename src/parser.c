#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/parser.h"

void free_Inst(Instruction inst)
{
	free(inst.opcode);
	free(inst.rd);
	free(inst.rs1);
	free(inst.rs2);
	free(inst.imme);
	free(inst.label);
}

void parser_riscv(char **tokens)
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
	int i = 0, j = 0, k = 0;
	Instruction inst_arr[128] = {0};

	while (tokens[i] != NULL) { /* Operates to all tokens. */
		/* First, I will do R-type only. */
		if ((strcmp(tokens[i], "add")) == 0) { /* if ==add */
			inst_arr[j].opcode = strdup("add");
			inst_arr[j].rd= strdup(tokens[++i]);
			inst_arr[j].rs1 = strdup(tokens[++i]);
			inst_arr[j].rs2 = strdup(tokens[++i]);
			inst_arr[j].label =  NULL;
			j++;
		}
		i++;

	}
	for (k = 0; k < j; k++) {
		printf("{\n\t.opcode = %s\n\t.rd = %s\n\t.rs1 = %s\n\t.rs2 = %s\n}\n",	
				inst_arr[k].opcode, inst_arr[k].rd,
				inst_arr[k].rs1, inst_arr[k].rs2
		);
		free_Inst(inst_arr[k]);
	}
}
