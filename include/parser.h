#ifndef PARSER_H
#define PARSER_H
#define MAX_INST 128

typedef struct {
	char *opcode;
	char *rd;
	char *rs1;
	char *rs2;
	char *imme;
	char *label; /* e.g. loop: */
} Instruction;

void free_Inst(Instruction inst);
void free_Inst_arr(Instruction *inst, int num_of_inst);
int parser_riscv(char **tokens, Instruction *inst_arr);

#endif /* PARSER_H */
