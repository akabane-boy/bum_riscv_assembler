#ifndef PARSER_H
#define PARSER_H

typedef struct {
	char *opcode;
	char *rd;
	char *rs1;
	char *rs2;
	char *imme;
	char *label; /* e.g. loop: */
} Instruction;

void parser_riscv(char **tokens);

#endif /* PARSER_H */
