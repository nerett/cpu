#include "cpu.h"

int main()
{
	/*
	Stack some_stack;
	StackCtor( &some_stack );

	return 0;
	*/
	remake_log();

	CpuCode some_cpucode = {};
	CPU Pentium_D = {};
	cpu_operand_t param = {};
	instruction_type the_instruction = {};

	cpucode_file_input( &some_cpucode, "../cpucode_builder/code.txt" );

	printf("RED CPUCODE: \n" );
	for( int i = 0; i < some_cpucode.N_entities; i ++ )
	{
		printf("%d\n", some_cpucode.machine_code[i] );
	}

	execute_cpucode( &Pentium_D, &some_cpucode );

	free_cpucode( &some_cpucode );
	return 0;
}
