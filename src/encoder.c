/* 
 * Input: Array of Instructions
 * Process: determine types -> encode_*_type(); -> return uint32_t
 * Output: One instruction -> One uint32_t -> convert to string of 0s, 1s. -> print
 */
#include "../include/encoder.h"
#include "../include/label.h"

/*
 * 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
 */

uint32_t encode_r_type(const Instruction *inst)
{
	/* funct7
	 * rs2 5
	 * rs1 5
	 * funct3 3
	 * rd 5
	 * opcode 7
	 */
	long rs2_num;
	long rs1_num;
	long rd_num;

	/* encode registers like x0, x13, x20 into 0, 13, 20 */
	rs2_num = strtol(inst->rs2 + 1, NULL, 10);
	rs1_num = strtol(inst->rs1 + 1, NULL, 10);
	rd_num = strtol(inst->rd + 1, NULL, 10);

	return (inst->lut->funct7 << 25) | /*(*inst).(*lut).funct3; */
	(rs2_num << 20) |
	(rs1_num << 15) |
	(inst->lut->funct3 << 12) |
	(rd_num << 7) |
	(inst->lut->opcode);
}
uint32_t encode_i_type(const Instruction *inst)
{
	/*
	 * imm[11:0] 12
	 * rs1 5
	 * funct3 3
	 * rd 5
	 * opcode 7
	 */

	/* encode register to long */
	long rs1_num;
	long rd_num;
	rs1_num = strtol(inst->rs1 + 1, NULL, 10);
	rd_num = strtol(inst->rd + 1, NULL, 10);

	/* encode immediate to long */
	long imm_num;
	imm_num = strtol(inst->imme, NULL, 10);

	/* ORDER: imm, rs1, funct3, rd, opcode */
	return (imm_num << 20) |
	(rs1_num << 15) |
	(inst->lut->funct3 << 17) |
	(rd_num << 7) |
	(inst->lut->opcode);
}
/*
uint32_t encode_s_type(const Instruction *inst)
*/
uint32_t encode_b_type(const Instruction *inst)
{
	int imm_num; /* immediate is 13-bit here */
	int imm_one, imm_six, imm_four, imm_last_one;

	/* encode imm into integer by using hash table */
	for (int i = 0; i < label_count; i++) {
		if (strcmp(inst->imme, label_table[i].label) == 0) {
			imm_num = label_table[i].address;
			break;
		}
	}

	long rs1_num, rs2_num;
	rs1_num = strtol(inst->rs1 + 1, NULL, 10);
	rs2_num = strtol(inst->rs2 + 1, NULL, 10);

	imm_num = imm_num >> 1; /* make it 12-bit */
	/* divide? imm_num */
	imm_one = imm_num >> 11;
	imm_six = imm_num >> 5 & 0b0111111;
	imm_four = imm_num >> 1 & 0b00000001111;
	imm_last_one = imm_num & 0b000000000001;

	return (imm_one << 31) |
	(imm_six << 25) |
	(rs2_num << 20) |
	(rs1_num << 15) |
	(inst->lut->funct3 << 12) |
	(imm_four << 8) |
	(imm_last_one << 7) |
	(inst->lut->opcode);

}
/*
uint32_t encode_u_type(const Instruction *inst)
uint32_t encode_j_type(const Instruction *inst)
uint32_t encode_nop_type(const Instruction *inst)
*/

void int_to_str_print(uint32_t num)
{
	for (int i = 31; i >= 0; i--) {
		printf("%c", (num & (1U << i)) ? '1' : '0');
	}
}

/*
void write_str_to_txt();
void encode_insts(); 
*/
