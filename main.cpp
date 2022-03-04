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
//#include "../htmlogs/htmlogs.h"
#include "cpu_logs.h"
//#include "config.h"


int main( int argc, char** argv )
{
	remake_log(); //remake stack log
	cpulogs_start( true );

	CpuCode some_cpucode = {};
	CPU Pentium_D = {};

	char* cpucode_filename = argv_get_cpucode_filename( argc, argv );
	cpucode_file_input( &some_cpucode, cpucode_filename );

	execute_cpucode( &Pentium_D, &some_cpucode );

	free_cpucode( &some_cpucode );
	cpulogs_end();
	return 0;
}
