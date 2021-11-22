#include "cpu.h"


/*--------------------------FUNCTION----------------------------------------- */
void cpucode_file_input( CpuCode* some_cpucode, const char* filename )
{
	assert( filename );


	FILE* cpucode_file = fopen( filename, "rb" );

	BinaryHeader bin_header;
	fread( &bin_header, sizeof( BinaryHeader ), 1, cpucode_file );
	if( strcmp( bin_header.name, "SoftwareProcessor" ) != 0 )
	{
		printf( "Invalid executable file!\n" );
		return;
	}
	if( bin_header.version > CPU_VERSION )
	{
		printf( "The version of the cpucode commands is too new for this CPU!\n" );
		return;
	}

	fseek( cpucode_file, 0L, SEEK_END ); //определение размера файла
    some_cpucode->N_entities = ( ( ftell( cpucode_file ) - sizeof( BinaryHeader ) )/ sizeof( int ) ); //новая функция
	fseek( cpucode_file, sizeof( BinaryHeader ), SEEK_SET );

	some_cpucode->machine_code = ( cpu_operand_t* )calloc( some_cpucode->N_entities + 1, sizeof( cpu_operand_t ) ); //смена типа пока не работает в силу неравномерности
	fread( some_cpucode->machine_code, sizeof( int ), some_cpucode->N_entities, cpucode_file );

	some_cpucode->machine_code[some_cpucode->N_entities+1] = -1;

	fclose( cpucode_file );
}


/*--------------------------FUNCTION----------------------------------------- */
void execute_cpucode( CPU* some_cpu, CpuCode* some_cpucode )
{
	assert( some_cpu );
	assert( some_cpucode );

	instruction_type current_instruction = NONE;
	cpu_operand_t param = 0;
	for( int i = 0; i < some_cpucode->N_entities; i++ )
	{
		current_instruction = ( instruction_type )some_cpucode->machine_code[i];
		if( instruction_length[current_instruction] == 2 )
		{
			i++;
			param = some_cpucode->machine_code[i];
		}
		execute_cpu( some_cpu, current_instruction, param );
	}
}


/*--------------------------FUNCTION----------------------------------------- */
void free_cpucode( CpuCode* some_cpucode )
{
	free( some_cpucode->machine_code);
}


/*--------------------------FUNCTION----------------------------------------- */
void execute_cpu( CPU* some_cpu, instruction_type instruction, cpu_operand_t operand )
{
	switch( instruction )
	{
		case HLT: hlt_cpu( some_cpu ); break;
		case STRT: start_cpu( some_cpu ); break;
		case PUSH: push_cpu( some_cpu, operand ); break;
		case POP: pop_cpu( some_cpu ); break;
		case ADD: add_cpu( some_cpu ); break;
		case SUB: sub_cpu( some_cpu ); break;
		case MUL: mul_cpu( some_cpu ); break;
		case DIV: div_cpu( some_cpu ); break;
		case OUT: out_cpu( some_cpu ); break;
		case NONE: break; //в принципе, лишнее
		default: break;
	}
}


/*--------------------------FUNCTION----------------------------------------- */
void start_cpu( CPU* some_cpu )
{
	printf( "[SYSTEM] CPU started\n" );
	StackCtor( &some_cpu->data_stack, int_array_dump );
	some_cpu->ram_ptr = ( cpu_operand_t* )calloc( RAM_SIZE, sizeof( cpu_operand_t ) );
}


/*--------------------------FUNCTION----------------------------------------- */
void push_cpu( CPU* some_cpu, cpu_operand_t value )
{
	printf( "[SYSTEM] CPU push\n" );
	//printf("value=%d\n", value );
	stack_push( &some_cpu->data_stack, value );
stack_dump( &some_cpu->data_stack, CALLOC_ERROR, __FILE__, __PRETTY_FUNCTION__, __LINE__  );
}


/*--------------------------FUNCTION----------------------------------------- */
void pop_cpu( CPU* some_cpu )
{
	printf( "[SYSTEM] CPU pop\n" );
	stack_pop( &some_cpu->data_stack );
}


/*--------------------------FUNCTION----------------------------------------- */
void add_cpu( CPU* some_cpu )
{
	printf( "[SYSTEM] CPU add\n" );
	cpu_operand_t value_1 = stack_pop( &some_cpu->data_stack );
	cpu_operand_t value_2 = stack_pop( &some_cpu->data_stack );
	stack_push( &some_cpu->data_stack, value_1 + value_2 );
}


/*--------------------------FUNCTION----------------------------------------- */
void sub_cpu( CPU* some_cpu )
{
	printf( "[SYSTEM] CPU sub\n" );
	cpu_operand_t value_1 = stack_pop( &some_cpu->data_stack );
	cpu_operand_t value_2 = stack_pop( &some_cpu->data_stack );
	stack_push( &some_cpu->data_stack, value_1 - value_2 );
}


/*--------------------------FUNCTION----------------------------------------- */
void mul_cpu( CPU* some_cpu )
{
	printf( "[SYSTEM] CPU mul\n" );
	cpu_operand_t value_1 = stack_pop( &some_cpu->data_stack );
	cpu_operand_t value_2 = stack_pop( &some_cpu->data_stack );
	stack_push( &some_cpu->data_stack, value_1 * value_2 );
}


/*--------------------------FUNCTION----------------------------------------- */
void div_cpu( CPU* some_cpu )
{
	printf( "[SYSTEM] CPU div\n" );
	cpu_operand_t value_1 = stack_pop( &some_cpu->data_stack );
	cpu_operand_t value_2 = stack_pop( &some_cpu->data_stack );
	stack_push( &some_cpu->data_stack, value_1 / value_2 );
}


/*--------------------------FUNCTION----------------------------------------- */
void out_cpu( CPU* some_cpu )
{
	printf( "[SYSTEM] CPU out\n" );
	cpu_operand_t value = stack_pop( &some_cpu->data_stack );
	printf("%d\n", value );
}


/*--------------------------FUNCTION----------------------------------------- */
void hlt_cpu( CPU* some_cpu )
{
	printf( "[SYSTEM] CPU hlt\n" );
	StackDtor( &some_cpu->data_stack );
	free( some_cpu->ram_ptr );
}
