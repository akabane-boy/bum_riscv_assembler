#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include "./inst.h"

#define MAX_INST 128

void free_Inst(Instruction inst);
void free_Inst_arr(Instruction *inst, int num_of_inst);
bool is_valid_register(char *token);
int parse_r_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst);
int parse_i_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst);
int parse_s_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst);
int parse_b_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst);
int parse_u_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst);
int parse_j_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst);
int parse_nop_type(char **tokens, int *i, Instruction *inst_arr, int *num_of_inst); 
int parser_riscv(char **tokens, Instruction *inst_arr);

#endif /* PARSER_H */
