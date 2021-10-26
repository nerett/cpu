#include "cpu.h"

instruction_type listen_input_cpu( cpu_operand_t* operand, instruction_type* instruction )
{
	char* input_line = NULL;
	int input_operand = 0;
	instruction_type input_instruction = NONE;

	scanf("%ms[a-z]", &input_line );
	if( !strcmp( input_line, "push" ) )
	{
		scanf( "%d", &input_operand );
	}
//printf("[SYSTEM] red value = \"%s\"\n", input_line );
//printf("[SYSTEM] input_operand = \"%d\"\n", input_operand );

	*operand = input_operand;
	printf("operand=%d\n", *operand );
	if( !strcmp( input_line, "start" ) ) input_instruction = START;
	else if( !strcmp( input_line, "push" ) ) input_instruction = PUSH;
	else if( !strcmp( input_line, "pop" ) ) input_instruction = POP;
	else if( !strcmp( input_line, "add" ) ) input_instruction = ADD;
	else if( !strcmp( input_line, "sub" ) ) input_instruction = SUB;
	else if( !strcmp( input_line, "mul" ) ) input_instruction = MUL;
	else if( !strcmp( input_line, "div" ) ) input_instruction = DIV;
	else if( !strcmp( input_line, "out" ) ) input_instruction = OUT;
	else if( !strcmp( input_line, "hlt" ) ) input_instruction = HLT;
	//else input_instruction = NONE;


/*
	switch( input_line )
	{
		case "start": input_instruction = START; break;
		case "push": input_instruction = PUSH; break;
		case "pop": input_instruction = POP; break;
		case "add": input_instruction = ADD; break;
		case "sub": input_instruction = SUB; break;
		case "mul": input_instruction = MUL; break;
		case "div": input_instruction = DIV; break;
		case "out": input_instruction = OUT; break;
		case "hlt": input_instruction = HLT; break;
		default: input_instruction = NONE;
	}
*/
	free( input_line );

	if( instruction )
	{
		*instruction = input_instruction;
	}
	return input_instruction;
}



void cpucode_file_input( CpuCode* some_cpucode, const char* filename )
{
	assert( filename );
	FILE* cpucode_file = fopen( filename, "r" );

	fseek( cpucode_file, 0L, SEEK_END ); //определение размера файла
    size_t N_symbols = ftell( cpucode_file );
	fseek( cpucode_file, 0L, SEEK_SET );

	char* cpucode_char = ( char* )calloc( N_symbols, sizeof( char ) );
	fread( cpucode_char, sizeof( char ), N_symbols, cpucode_file );
printf("RED SEQUENCE = %s\n", cpucode_char );
/*
printf("char_cpucode = %s\n", cpucode_char );
int test1, test2, test3, test4;
sscanf( cpucode_char, "%d", &test1 );
sscanf( cpucode_char, "%d", &test2 );
sscanf( cpucode_char, "%d", &test3 );
sscanf( cpucode_char, "%d", &test4 );
printf("sscanf_test: %d %d %d %d\n", test1, test2, test3, test4 );
*/

	for( int i = 0; i < N_symbols; i++ )
	{
		if( cpucode_char[i] == ' ' || cpucode_char[i] == '\n' )
		{
			some_cpucode->N_entities++;
		}
	}
printf("N_values = %d\n", some_cpucode->N_entities );

	some_cpucode->machine_code = ( cpu_operand_t* )calloc( some_cpucode->N_entities + 1, sizeof( cpu_operand_t ) ); //смена типа пока не работает в силу неравномерности
	for( int i = 0; i < some_cpucode->N_entities - 1; i++ ) // -1 или нет
	{
		int ret = sscanf( cpucode_char, "%d", &some_cpucode->machine_code[i] );
		//printf("Sscanf ret value: %d\n", ret);
	}

	some_cpucode->machine_code[some_cpucode->N_entities+1] = -1;

	fclose( cpucode_file );
	free( cpucode_char );
}



void execute_cpucode( CPU* some_cpu, CpuCode* some_cpucode )
{
	assert( some_cpu );
	assert( some_cpucode );
/*
	int i = 0;
	instruction_type current_instruction = NONE;
	cpu_operand_t param = 0;
	while( some_cpucode[i] >= 0 )
	{
		current_instruction = ( instruction_type )some_cpucode[i];
		if( instruction_lenght[current_instruction] == 2 )
		{
			i++;
			param = some_cpucode[i];
		}
		execute_cpu( some_cpu, current_instruction, param );
		i++;
	}
*/
}



void free_cpucode( CpuCode* some_cpucode )
{
	free( some_cpucode->machine_code);
}



void execute_cpu( CPU* some_cpu, instruction_type instruction, cpu_operand_t operand )
{
	switch( instruction )
	{
		case HLT: hlt_cpu( some_cpu ); break;
		case START: start_cpu( some_cpu ); break;
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



void start_cpu( CPU* some_cpu )
{
printf( "[SYSTEM] CPU started\n" );
	StackCtor( &some_cpu->data_stack, int_array_dump );
}



void push_cpu( CPU* some_cpu, cpu_operand_t value )
{
printf( "[SYSTEM] CPU push\n" );
printf("value=%d\n", value );
	stack_push( &some_cpu->data_stack, value );
}



void pop_cpu( CPU* some_cpu )
{
printf( "[SYSTEM] CPU pop\n" );
	stack_pop( &some_cpu->data_stack );
}



void add_cpu( CPU* some_cpu )
{
printf( "[SYSTEM] CPU add\n" );
	cpu_operand_t value_1 = stack_pop( &some_cpu->data_stack );
	cpu_operand_t value_2 = stack_pop( &some_cpu->data_stack );
	stack_push( &some_cpu->data_stack, value_1 + value_2 );
}



void sub_cpu( CPU* some_cpu )
{
printf( "[SYSTEM] CPU sub\n" );
	cpu_operand_t value_1 = stack_pop( &some_cpu->data_stack );
	cpu_operand_t value_2 = stack_pop( &some_cpu->data_stack );
	stack_push( &some_cpu->data_stack, value_1 - value_2 );
}



void mul_cpu( CPU* some_cpu )
{
printf( "[SYSTEM] CPU mul\n" );
	cpu_operand_t value_1 = stack_pop( &some_cpu->data_stack );
	cpu_operand_t value_2 = stack_pop( &some_cpu->data_stack );
	stack_push( &some_cpu->data_stack, value_1 * value_2 );
}



void div_cpu( CPU* some_cpu )
{
printf( "[SYSTEM] CPU div\n" );
	cpu_operand_t value_1 = stack_pop( &some_cpu->data_stack );
	cpu_operand_t value_2 = stack_pop( &some_cpu->data_stack );
	stack_push( &some_cpu->data_stack, value_1 / value_2 );
}



void out_cpu( CPU* some_cpu )
{
printf( "[SYSTEM] CPU out\n" );
	cpu_operand_t value = stack_pop( &some_cpu->data_stack );
	printf("%d\n", value );
}



void hlt_cpu( CPU* some_cpu )
{
printf( "[SYSTEM] CPU hlt\n" );
	StackDtor( &some_cpu->data_stack );
}
