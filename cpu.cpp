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
	descriptional_argument descr_arg = NARG;

	int i = 0;
	while( i < some_cpucode->N_entities )
	{
		current_instruction = NONE;
		param = 0;
		descr_arg = NARG;


		current_instruction = ( instruction_type )some_cpucode->machine_code[i];
		i++;

		if( instruction_length[current_instruction] > 1 )
		{
			descr_arg = ( descriptional_argument )some_cpucode->machine_code[i];
			i++;

			if( instruction_length[current_instruction] > 2 )
			{
				param = some_cpucode->machine_code[i];
				i++;
			}
		}
		execute_cpu( some_cpu, current_instruction, descr_arg, param );
	}
}


/*--------------------------FUNCTION----------------------------------------- */
void free_cpucode( CpuCode* some_cpucode )
{
	free( some_cpucode->machine_code);
}


/*--------------------------FUNCTION----------------------------------------- */
void execute_cpu( CPU* some_cpu, instruction_type instruction, descriptional_argument descr_arg, cpu_operand_t operand )
{
	switch( instruction )
	{
		case HLT:  hlt_cpu( some_cpu );                      break;
		case STRT: start_cpu( some_cpu );                    break;
		case PUSH: push_cpu( some_cpu, descr_arg, operand ); break;
		case POP:  pop_cpu( some_cpu, descr_arg );           break;
		case ADD:  add_cpu( some_cpu );                      break;
		case SUB:  sub_cpu( some_cpu );                      break;
		case MUL:  mul_cpu( some_cpu );                      break;
		case DIV:  div_cpu( some_cpu );                      break;
		case OUT:  out_cpu( some_cpu );                      break;
		case NONE:                                           break; //в принципе, лишнее, но можно сделать проверку
		default:                                             break;
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
void push_cpu( CPU* some_cpu, descriptional_argument descr_arg, cpu_operand_t value )
{
	printf( "[SYSTEM] CPU push\n" );
	//printf("value=%d\n", value );

	switch( descr_arg )
	{
		case INT:  stack_push( &some_cpu->data_stack, value );                               break;
		case REAL: printf( "REAL DOESN'T WORK\n" );                                          break; //!TODO добавить полноценную поддержку
		case RGAX: stack_push( &some_cpu->data_stack, some_cpu->reg[0] );                    break;
		case RGBX: stack_push( &some_cpu->data_stack, some_cpu->reg[1] );                    break;
		case RGCX: stack_push( &some_cpu->data_stack, some_cpu->reg[2] );                    break;
		case RGDX: stack_push( &some_cpu->data_stack, some_cpu->reg[3] );                    break;
		case RAM:  stack_push( &some_cpu->data_stack, some_cpu->ram_ptr[value] );            break;
		case RAMA: stack_push( &some_cpu->data_stack, some_cpu->ram_ptr[some_cpu->reg[0]] ); break; //DSL'а нет, но вы держитесь
		case RAMB: stack_push( &some_cpu->data_stack, some_cpu->ram_ptr[some_cpu->reg[1]] ); break;
		case RAMC: stack_push( &some_cpu->data_stack, some_cpu->ram_ptr[some_cpu->reg[2]] ); break;
		case RAMD: stack_push( &some_cpu->data_stack, some_cpu->ram_ptr[some_cpu->reg[3]] ); break;
		case NARG: printf( "NARG!!!" );                                                      break;
	}


stack_dump( &some_cpu->data_stack, CALLOC_ERROR, __FILE__, __PRETTY_FUNCTION__, __LINE__  );
}


/*--------------------------FUNCTION----------------------------------------- */
void pop_cpu( CPU* some_cpu, descriptional_argument descr_arg )
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
