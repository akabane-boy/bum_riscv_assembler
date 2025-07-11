#ifndef INST_H
#define INST_H

#include <stdint.h>

typedef enum {
	TYPE_R,
	TYPE_I,
	TYPE_S,
	TYPE_B,
	TYPE_U,
	TYPE_J,
	TYPE_NOP,
	TYPE_INVALID
} InstType;

typedef struct {
	const char* mnemonic;
	uint8_t opcode;
	uint8_t funct3;
	uint8_t funct7;
	InstType type;
} InstLUTEntry;

typedef struct {
	int pc; /* might use negative value due to beq of bne */
	char *opcode;
	char *rd;
	char *rs1;
	char *rs2;
	char *imme;
	char *label; /* e.g. loop: */
	char *label_ref; /* If inst. uses the label, store it here. So that it can be used in parser. */
	const InstLUTEntry *lut;
} Instruction;

#endif /* INST_H */
