#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../stack/stack.h"

typedef int cpu_operand_t;


/*--------------------------CONST---------------------------------------------*/
const int CPU_VERSION = 0; ///< This parameter is compared to the same parameter from binary header red from machine code file

const int RAM_SIZE = 100; ///< Number of RAM cells
const int RAM_ACCESS_TIME = 20; ///< Ram access delay (adds realism to the model)

const int instruction_length[] = ///< Number of instruction arguments in machine code + instruction code (N + 1 > 0)
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
enum instruction_type ///< Machine instructions, which are specific actions performed by the CPU when received
//!TODO включить общим файлом или сделать что-то подобное
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


/*--------------------------ENUM----------------------------------------------*/
enum descriptional_argument ///< Special machine code argument that provides additional information about types of instruction operands or is an last argument if numeric data is not expected. Descriptional argument is provided only for long (instruction_length > 1) instructions). Machine code instruction can only have 1 descriptional argument
//тип дополнительного (определительного) аргумента в машинном коде
{
	NARG = 0,
	INT = 1,
	REAL = 2,
	RGAX = 3,
	RGBX = 4,
	RGCX = 5,
	RGDX = 6,
	RAM = 7,
	RAMA = 8,
	RAMB = 9,
	RAMC = 10,
	RAMD = 11
};


/*--------------------------STRUCT--------------------------------------------*/
struct CpuCode ///< Describes machine code that can be loaded from file and executed
{
		cpu_operand_t* machine_code = NULL; //!TODO изменить на int
		int N_entities = 0;
		int N_instructions = 0;
};

struct CPU ///< Describes CPU with its stack, registers and RAM
{
	Stack data_stack;
	cpu_operand_t reg[4] = {};
	cpu_operand_t* ram_ptr = NULL;
	//cpu_operand_t
};

struct BinaryHeader ///< Describes special machine code file header that is responsible for assembler/cpu version compatibility
{
	char header = 0x7f;
	char type[4] = "ELF";
	char name[18] = "SoftwareProcessor";
	int version = 0;
};


/*--------------------------PROTOTYPE-----------------------------------------*/
void execute_cpu( CPU* some_cpu, instruction_type instruction, descriptional_argument descr_arg = NARG, cpu_operand_t operand = {} ); ///< Executes instruction with arguments and operands given on the CPU
void execute_cpucode( CPU* some_cpu, CpuCode* some_cpucode ); ///< Executes machine code sequence on the CPU
void cpucode_file_input( CpuCode* some_cpucode, const char* filename ); ///< Reads machine code from file given and checks its version compatibility
void free_cpucode( CpuCode* some_cpucode ); ///< Frees memory allocated by the cpucode array

void start_cpu( CPU* some_cpu ); ///< Executes STRT instruction on the CPU
void push_cpu( CPU* some_cpu, descriptional_argument descr_arg, cpu_operand_t value ); ///< Executes PUSH instruction with the arguments and operands given on the CPU
void pop_cpu( CPU* some_cpu, descriptional_argument descr_arg ); ///< Executes POP instruction with the arguments given on the CPU
void add_cpu( CPU* some_cpu ); ///< Executes ADD instruction on the CPU
void sub_cpu( CPU* some_cpu ); ///< Executes SUB instruction on the CPU
void mul_cpu( CPU* some_cpu ); ///< Executes MUL instruction on the CPU
void div_cpu( CPU* some_cpu ); ///< Executes DIV instruction on the CPU
void out_cpu( CPU* some_cpu ); ///< Executes OUT instruction on the CPU
void hlt_cpu( CPU* some_cpu );	///< Executes HLT instruction on the CPU

#endif //CPU_H_INCLUDED
