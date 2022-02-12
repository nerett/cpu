/*! \mainpage CPU
 *
 * This is software CPU model that can execute specific
 * machine code red from the file given.
 * The CPU has registers, stack and RAM and can
 * operate large variety of instructions that can make up
 * big sequences.
 * This project was created during MIPT Ded's course.
 * 
 *
 * by nerett
 * (c) 2021
 */


#include "cpu.h"

int main()
{
	remake_log();

	CpuCode some_cpucode = {};
	CPU Pentium_D = {};
	cpu_operand_t param = {};
	instruction_type the_instruction = {};

	cpucode_file_input( &some_cpucode, "../cpucode_builder/cpucode" );

	execute_cpucode( &Pentium_D, &some_cpucode );

	free_cpucode( &some_cpucode );
	return 0;
}
