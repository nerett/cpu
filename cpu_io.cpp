#include "cpu_io.h"
#include "cpu_logs.h"


/*--------------------------FUNCTION----------------------------------------- */
void cpucode_file_input( CpuCode* some_cpucode, const char* filename )
{
	//printf( "cpucode file input\n" );
	cpulogs_report( "starting cpucode file input", false );

	assert( filename ); //!TODO добавить нормальную проверку


	FILE* cpucode_file = fopen( filename, "rb" );

	BinaryHeader bin_header;
	fread( &bin_header, sizeof( BinaryHeader ), 1, cpucode_file );
	if( strcmp( bin_header.name, BINHEADER_PROGNAME ) )
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
    some_cpucode->N_entities = ( ( ftell( cpucode_file ) - sizeof( BinaryHeader ) ) / sizeof( int ) ); //!TODO новая функция
	fseek( cpucode_file, sizeof( BinaryHeader ), SEEK_SET );

	some_cpucode->machine_code = ( cpu_operand_t* )calloc( some_cpucode->N_entities + 1, sizeof( cpu_operand_t ) ); //смена типа пока не работает в силу неравномерности
	fread( some_cpucode->machine_code, sizeof( int ), some_cpucode->N_entities, cpucode_file );

	some_cpucode->machine_code[some_cpucode->N_entities+1] = -1; //код конца файла / яд

	fclose( cpucode_file );
}


/*--------------------------FUNCTION----------------------------------------- */
void free_cpucode( CpuCode* some_cpucode )
{
	cpulogs_report( "trying to free cpucode", false );

	free( some_cpucode->machine_code);
}


/*--------------------------FUNCTION----------------------------------------- */
char* argv_get_cpucode_filename( int argc, char** argv )
{
	cpulogs_report( "getting cpucode filename from argv", false );

	if( argc < CPUIO_MINIMAL_ARGC )
	{
		return {}; //!TODO возврат кода ошибки
	}

	assert( argv );

	return argv[CPUCODE_FILE_ARGV_POS];
}