#ifndef LUT_H
#define LUT_H

#include <stdint.h> /* For uint8_t */
/* #include "./parser.h" */ /* Circular logic happen here. */

#define NUM_OF_MNEMONIC (sizeof(instruction_table) / sizeof(instruction_table[0]))

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

size_t get_num_of_mnemonic(void);
extern const InstLUTEntry instruction_table[];

InstLUTEntry *lookup_inst(const char *mnemonic);

#endif /* LUT_H */
