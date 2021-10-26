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
