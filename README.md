# bum_riscv_assembler

**bum_riscv_assembler** is a simple RISC-V assembler in C.

Aims to learn how assembler works and get C programming experience.

	
## Instruction format
Logical (assembly) order
### R-type:
add, sub, and, or, sll, slt, sra, xor

| opcode | rd | funct3 | rs1 | rs2 | funct7 |
| --------- | --------- | --------- | --------- | --------- | --------- |
| 7 | 5 | 3 | 5 | 5 | 7 |


### I-type:
addi, andi, ori, lb, ln, lw, jalr

| opcode | rd | funct3 | rs1 | imm[11:0] |
| --------- | --------- | --------- | --------- | --------- |
| 7 | 5 | 3 | 5 | 12 |

### S-type:
sb, sh, sw

| opcode | imm[4:0] | funct3 | rs1 | rs2 | imm[11:5] |
| --------- | --------- | --------- | --------- | --------- | --------- |
| 7 | 5 | 3 | 5 | 5 | 7 |

### B-type:
beq, bne, blt, bge, bltu, bgeu

| opcode | imm | imm[4:1] | funct3 | rs1 | rs2 | imm[10:5] | imm |
| --------- | --------- | --------- | --------- | --------- | --------- | --------- | --------- |
| 7 | 1 | 4 | 3 | 5 | 5 | 6 | 1 |

### U-type:
lui, auipc

| opcode | rd | imm[31:12] |
| --------- | --------- | --------- |
| 7 | 5 | 20 |

### J-type:
jal

| opcode | rd  | imm[19:12] | imm | imm[10:1] | imm |
| --------- | --------- | --------- | --------- | --------- | --------- |
| 7 | 5 | 8 | 1 | 10 | 1 |

## Process
This section illustrates how **bum_riscv_assembler works**.

1. Get a assembly file.
2. getline() and tokenize.
3. Identify instruction mnemonic.
4. Verify legal syntax.
5. Create array of Instruction consists of instruction fields.
6. Later...

## TODO:
- Instruction table (LUT)
- Improve error handling
- Need to fix parser.c inst_arr[*num_of_inst].lut = lookup_inst(inst)arr[*num_of_inst].opcode);

## IN PROGRESS
- parser.c

## DONE
- lexer.c
