#include "cpu.h"

int main()
{
	/*
	Stack some_stack;
	StackCtor( &some_stack );

	return 0;
	*/
	CPU Pentium_D = {};
	cpu_operand_t param = {};
	instruction_type the_instruction = {};
	printf("%d\n", param);
	remake_log();

	while( true )
	{
		listen_input_cpu( &param, &the_instruction );
		execute_cpu( &Pentium_D, the_instruction, param );
		//stack_dump( &Pentium_D.data_stack, CALLOC_ERROR, __FILE__, __PRETTY_FUNCTION__, __LINE__ );
	}
	return 0;
}
