#ifndef CPU_LOGS_H_INCLUDED
#define CPU_LOGS_H_INCLUDED


#include "../htmlogs/htmlogs.h"
#include "cpu.h"


/*--------------------------MACRO---------------------------------------------*/
//dump_values, some_cpu
#define cpulogs_report( report_message, ... ) do {                                                                  \
		cpulogs_event_output_default( 0, report_message, __FILE__, __PRETTY_FUNCTION__, __LINE__, __VA_ARGS__ );    \
	} while(0)

#define cpulogs_start( remake_log ) do {                                                                            \
		cpulogs_construct_log_default( __FILE__, __PRETTY_FUNCTION__, __LINE__, remake_log );                       \
	} while(0)

#define cpulogs_end() do {                                                                                          \
		cpulogs_destruct_log_default( __FILE__, __PRETTY_FUNCTION__, __LINE__ );                                    \
	} while(0)


/*--------------------------PROTOTYPE-----------------------------------------*/
static void cpulogs_construct_log( HTMLog* some_log, const char* log_filename, const char* birthpoint_filename, const char* birthpoint_function, const int birthpoint_line, bool remake_log = false );
static void cpulogs_destruct_log( HTMLog* some_log, const char* deathpoint_filename, const char* deathpoint_function, const int deathpoint_line );
static void cpulogs_event_output( HTMLog* some_log, const int error_code, const char* message, const char* msg_filename, const char* msg_function, const int msg_line, bool dump_values = false, CPU* some_cpu = NULL );

static void cpulogs_dump_values( HTMLog* some_log, CPU* some_cpu );

void cpulogs_construct_log_default( const char* birthpoint_filename, const char* birthpoint_function, const int birthpoint_line, bool remake_log = false );
void cpulogs_destruct_log_default( const char* deathpoint_filename, const char* deathpoint_function, const int deathpoint_line );
void cpulogs_event_output_default( const int error_code, const char* message, const char* msg_filename, const char* msg_function, const int msg_line, bool dump_values = false, CPU* some_cpu = NULL );


#endif //CPU_LOGS_H_INCLUDED