#ifndef CPU_IO_H_INCLUDED
#define CPU_IO_H_INCLUDED


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef int cpu_operand_t;


/*--------------------------CONST---------------------------------------------*/
const int CPU_VERSION = 4; ///< This parameter is compared to the same parameter from binary header red from machine code file

const size_t CPUIO_MINIMAL_ARGC = 2;
const size_t CPUCODE_FILE_ARGV_POS = 1;

const size_t BINHEADER_FILETYPE_LENGTH = 4;
const size_t BINHEADER_PROGNAME_LENGTH = 18;

const char BINHEADER_HEADER = 0x7f;
const char BINHEADER_FILETYPE[BINHEADER_FILETYPE_LENGTH] = "ELF";
const char BINHEADER_PROGNAME[BINHEADER_PROGNAME_LENGTH] = "SoftwareProcessor";


/*--------------------------STRUCT--------------------------------------------*/
struct CpuCode ///< Describes machine code that can be loaded from file and executed
{
		cpu_operand_t* machine_code = NULL; //!TODO изменить на int
		int N_entities = 0;
		int N_instructions = 0;
};


struct BinaryHeader ///< Describes special machine code file header that is responsible for assembler/cpu version compatibility
{
	char header = {}; //0x7f
	char type[BINHEADER_FILETYPE_LENGTH] = {}; //"ELF"
	char name[BINHEADER_PROGNAME_LENGTH] = {}; //"SoftwareProcessor"; //!TODO убрать magic number
	int version = {};
};


/*--------------------------PROTOTYPE-----------------------------------------*/
void cpucode_file_input( CpuCode* some_cpucode, const char* filename ); ///< Reads machine code from file given and checks its version compatibility
void free_cpucode( CpuCode* some_cpucode ); ///< Frees memory allocated by the cpucode array

char* argv_get_cpucode_filename( int argc, char** argv );


#endif //CPU_IO_H_INCLUDED