#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack_stable/stack.h"

typedef int cpu_operand_t;

enum instruction_type
{
	HLT = 0,
	START = 1,
	PUSH = 2,
	POP = 3,
	ADD = 4,
	SUB = 5,
	MUL = 6,
	DIV = 7,
	OUT = 8,
	NONE = 9
};

struct CPUInstruction
{
	instruction_type type = NONE;
	cpu_operand_t param;
};

struct CPU
{
	Stack data_stack;
	//cpu_operand_t
};

instruction_type listen_input_cpu( cpu_operand_t* operand, instruction_type* instruction = NULL );
void execute_cpu( CPU* some_cpu, instruction_type instruction, cpu_operand_t operand = {} );

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
