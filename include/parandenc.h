#ifndef PARANDENC_H
#define PARANDENC_H

#include <stdio.h>
#include "parser.h"
#include "encoder.h"

void append_line_txt(int num);
void append_line_bin(uint32_t num);
int parandenc(char **tokens, Instruction *inst_arr);

#endif /* PARANDENC_H */
