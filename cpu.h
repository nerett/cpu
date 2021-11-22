#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../stack/stack.h"

typedef int cpu_operand_t;


/*--------------------------CONST---------------------------------------------*/
const int CPU_VERSION = 0;

const int RAM_SIZE = 100;
const int RAM_ACCESS_TIME = 20;

const int instruction_length[] =
{
	1, //HLT
	1, //START
	2, //PUSH
	1, //POP
	1, //ADD
	1, //SUB
	1, //MUL
	1, //DIV
	1, //OUT
	1 //NONE
};


/*--------------------------ENUM----------------------------------------------*/
enum instruction_type
{
	HLT = 0,
	STRT = 1,
	PUSH = 2,
	POP = 3,
	ADD = 4,
	SUB = 5,
	MUL = 6,
	DIV = 7,
	OUT = 8,
	NONE = 9
};


/*--------------------------STRUCT--------------------------------------------*/
struct CpuCode
{
		cpu_operand_t* machine_code = NULL;
		int N_entities = 0;
		int N_instructions = 0;
};

struct CPU
{
	Stack data_stack;
	cpu_operand_t reg[4] = {};
	cpu_operand_t* ram_ptr = NULL;
	//cpu_operand_t
};

struct BinaryHeader
{
	char header = 0x7f;
	char type[4] = "ELF";
	char name[18] = "SoftwareProcessor";
	int version = 0;
};


/*--------------------------PROTOTYPE-----------------------------------------*/
void execute_cpu( CPU* some_cpu, instruction_type instruction, cpu_operand_t operand = {} );
void execute_cpucode( CPU* some_cpu, CpuCode* some_cpucode );
void cpucode_file_input( CpuCode* some_cpucode, const char* filename );
void free_cpucode( CpuCode* some_cpucode );

void start_cpu( CPU* some_cpu );
void push_cpu( CPU* some_cpu, cpu_operand_t value );
void pop_cpu( CPU* some_cpu );
void add_cpu( CPU* some_cpu );
void sub_cpu( CPU* some_cpu );
void mul_cpu( CPU* some_cpu );
void div_cpu( CPU* some_cpu );
void out_cpu( CPU* some_cpu );
void hlt_cpu( CPU* some_cpu );

#endif //CPU_H_INCLUDED
