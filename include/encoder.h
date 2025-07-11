#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h> /* For uint32_t */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./inst.h"

uint32_t encode_r_type(const Instruction *inst);
uint32_t encode_i_type(const Instruction *inst);
uint32_t encode_b_type(const Instruction *inst);
void int_to_str_print(uint32_t num);

#endif /* ENCODER_H */
