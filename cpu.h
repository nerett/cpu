#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED


#include "../stack/stack.h"
#include "instructions.h"
#include "cpu_io.h"


/*--------------------------CONST---------------------------------------------*/
const int RAM_SIZE = 100; ///< Number of RAM cells
const size_t RAM_ACCESS_TIME = 20; ///< Ram access delay (adds realism to the model)
const size_t N_REGISTERS = 4;


/*--------------------------STRUCT--------------------------------------------*/
struct CPU ///< Describes CPU with its stack, registers and RAM
{
	Stack data_stack;
	Stack return_stack;

	int ip = 0;

	cpu_operand_t reg[N_REGISTERS] = {};
	cpu_operand_t* ram_ptr = NULL;
	//cpu_operand_t
};


/*--------------------------PROTOTYPE-----------------------------------------*/
void execute_cpucode( CPU* some_cpu, CpuCode* some_cpucode, int start_position = 0 ); ///< Executes machine code sequence on the CPU
void execute_cpu( CPU* some_cpu, instruction_type instruction, descriptional_argument descr_arg = NARG, cpu_operand_t operand = {} ); ///< Executes instruction with arguments and operands given on the CPU

void set_ip_default_instruction_length( CPU* some_cpu, instruction_type instruction );

void start_cpu( CPU* some_cpu ); ///< Executes STRT instruction on the CPU
void push_cpu( CPU* some_cpu, descriptional_argument descr_arg, cpu_operand_t operand ); ///< Executes PUSH instruction with the arguments and operands given on the CPU
void pop_cpu( CPU* some_cpu, descriptional_argument descr_arg, cpu_operand_t operand ); ///< Executes POP instruction with the arguments given on the CPU
void add_cpu( CPU* some_cpu ); ///< Executes ADD instruction on the CPU
void sub_cpu( CPU* some_cpu ); ///< Executes SUB instruction on the CPU
void mul_cpu( CPU* some_cpu ); ///< Executes MUL instruction on the CPU
void div_cpu( CPU* some_cpu ); ///< Executes DIV instruction on the CPU
void out_cpu( CPU* some_cpu ); ///< Executes OUT instruction on the CPU
void hlt_cpu( CPU* some_cpu ); ///< Executes HLT instruction on the CPU
void jump_cpu( CPU* some_cpu, descriptional_argument descr_arg, int jump_position );
void ret_cpu( CPU* some_cpu );


#endif //CPU_H_INCLUDED
