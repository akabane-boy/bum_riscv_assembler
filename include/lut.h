#ifndef LUT_H
#define LUT_H

#include <stdint.h> /* For uint8_t */
#include "./inst.h"

#define NUM_OF_MNEMONIC (sizeof(instruction_table) / sizeof(instruction_table[0]))

size_t get_num_of_mnemonic(void);
extern const InstLUTEntry instruction_table[];
const InstLUTEntry *lookup_inst(const char *mnemonic);

#endif /* LUT_H */
