

/*! \file 
    The <stdint.h> header gives us types of a known width and signedness, like
    uint32_t and int16_t. These types can be very useful for
    matching the internal types of a processor, and for managing
    conversions from signed to unsigned types. The C/C++ standard has certain
    (very strict) rules for conversion between types, which are different from
    the rules of any particular CPU. In an extremely legalistic interpretation, the
    integer encoding is not necessarily twos complement, but we
    will mandate that all target architectures use a twos complement
    representation.
*/
#include <stdint.h>
#include <string>
#include <map>
#include <vector>

using namespace std;

typedef enum _instr_type{
  instr_R_type =0x1,
  instr_RT_type = 0x2,
  instr_J_type = 0x3,
  instr_I_type = 0x4
}instr_type;

/*
* MAP DEFINITIONS
*/
const std::map<std::string, uint32_t> r_to_op{
	{"SLL",0x0},
	{"SRL",0x02},
	{"SRA",0x03},
	{"SLLV",0x04},
	{"SRLV",0x06},
	{"SRAV",0x07},
	{"JR",0x08},
	{"JALR",0x09},
	{"MFHI",0x10},
	{"MTHI",0x11},
	{"MFLO",0x12},
	{"MTLO",0x13},
	{"MULT",0x18},
	{"MULTU",0x19},
	{"DIV",0x1a},
	{"DIVU",0x1b},
	{"ADD",0x20},
	{"ADDU",0x21},
	{"SUB",0x22},
	{"SUBU",0x23},
	{"AND",0x24},
	{"OR",0x25},
	{"XOR",0x26},
	{"NOR",0x27},
	{"SLT",0x2a},
	{"SLTU",0x2b}
};

const std::map<std::string, uint32_t> rt_to_op{
	{"BLTZ",0x0},
	{"BGEZ",0x1},
	{"BLTZAL", 0x10},
	{"BGEZAL", 0x11}
};

const std::map<std::string, uint32_t> ij_to_op{
	{"J",0x02},
	{"JAL",0x03},
	{"BEQ",0x04},
	{"BNE",0x05},
	{"BLEZ",0x06},
	{"BGTZ",0x07},
	{"ADDI",0x08},
	{"ADDIU",0x09},
	{"SLTI",0x0a},
	{"SLTIU",0x0b},
	{"ANDI",0x0c},
	{"ORI",0x0d},
	{"XORI",0x0e},
	{"LUI",0x0f},
	{"LB",0x20},
	{"LH",0x21},
	{"LWL",0x22},
	{"LW",0x23},
	{"LBU",0x24},
	{"LHU",0x25},
	{"LWR",0x26},
	{"SB",0x28},
	{"SH",0x29},
	{"SWL",0x2a},
	{"SW",0x2b},
	{"SWR",0x2e,}
};

/*!
 * Take in a list of params and function name and construct a bitstream for MIPS from it.
 * @param params - s,t,d,h for R-type; s,i for RT-type; j for J type; s,t,i for I type
 * @param func - string containing the function name
 * @return uint32_t bigendian bitstream to be written to memory.
 */
// CONSTRUCT BIT STREAM

uint32_t test_construct_bitstream(string func, const uint32_t type, const vector<uint32_t> &params){
	uint32_t bitstream=0x0;
	uint32_t s,t,d,h,i,j;
	//! 31:26, 25:21,
	switch(type){
	case instr_R_type: // R-type
		s = params[0]&0x1F;
		t = params[1]&0x1F;
		d = params[2]&0x1F;
		h = params[3]&0x1F;
		bitstream = 0x0 |  (s << 21) | (t << 16) | (d << 11) | (h<<6) | r_to_op.at(func);
		break;
	case instr_RT_type: // RT-type
		s = params[0];
		i = params[1];
		bitstream = 0x04000000 | (s << 21) | ((rt_to_op.at(func)&0xFFFF) << 16)| (i&0xFFFF);
		break;
	case instr_J_type: // J type
		j = params[0];
		bitstream = ij_to_op.at(func)<<26|(j&0x03FFFFFF);
		break;
	case instr_I_type: //I-type
		s = params[0];
		t = params[1];
		i = params[2];
		bitstream = ij_to_op.at(func)<<26|(s<<21)|(t<<16)|(i&0xFFFF);
		break;
	}
	bitstream = __builtin_bswap32(bitstream);
	return bitstream;
}
// END OF CONSTRUCT bitstream
