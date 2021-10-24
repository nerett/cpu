#include "cpu.h"

int main()
{
	CPU Pentium_D = {};
	cpu_operand_t param = {};
	remake_log();

	while( true )
	{
		execute_cpu( &Pentium_D, listen_input_cpu( &param ), param );
		//stack_dump( &Pentium_D.data_stack, NO_ELEMENTS_TO_POP );
	}
	return 0;
}
