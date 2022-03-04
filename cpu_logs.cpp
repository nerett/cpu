#include "cpu_logs.h"
#include "../htmlogs/htmlogs_templates.h"
//#include "config.h"


/*--------------------------CONST---------------------------------------------*/
HTMLog CPU_LOG = {}; //дефолтный лог
const char CPU_LOG_FILENAME[] = "cpu_log.html";


/*--------------------------FUNCTION----------------------------------------- */
void cpulogs_construct_log( HTMLog* some_log, const char* log_filename, const char* birthpoint_filename, const char* birthpoint_function, const int birthpoint_line, bool remake_log )
{
	HTMLogCtor( some_log, log_filename );

	if( remake_log )
	{
		htmlogs_remake_log( some_log );
	}

	htmlogs_print_msg_EVENT( some_log, "CPULOGS", "log started", birthpoint_filename, birthpoint_function, birthpoint_line );
	htmlogs_logfile_close( some_log );
}


/*--------------------------FUNCTION----------------------------------------- */
void cpulogs_destruct_log( HTMLog* some_log, const char* deathpoint_filename, const char* deathpoint_function, const int deathpoint_line )
{
	htmlogs_print_msg_EVENT( some_log, "CPULOGS", "log ended", deathpoint_filename, deathpoint_function, deathpoint_line );
	HTMLogDtor( some_log );
}


/*--------------------------FUNCTION----------------------------------------- */
void cpulogs_event_output( HTMLog* some_log, const int error_code, const char* message, const char* msg_filename, const char* msg_function, const int msg_line, bool dump_values, CPU* some_cpu )
{
printf( "cpulogs_event_output\n" );
	htmlogs_print_msg_EVENT( some_log, "SYSTEM", message, msg_filename, msg_function, msg_line ); //!TODO дать возможность изменять тип события

	if( dump_values )
	{
		cpulogs_dump_values( some_log, some_cpu );
	}

	htmlogs_logfile_close( some_log );
}


/*--------------------------FUNCTION----------------------------------------- */
static void cpulogs_dump_values( HTMLog* some_log, CPU* some_cpu )
{
	return;
}


/*--------------------------FUNCTION----------------------------------------- */
void cpulogs_construct_log_default( const char* birthpoint_filename, const char* birthpoint_function, const int birthpoint_line, bool remake_log )
{
	cpulogs_construct_log( &CPU_LOG, CPU_LOG_FILENAME, birthpoint_filename, birthpoint_function, birthpoint_line, remake_log );
}


/*--------------------------FUNCTION----------------------------------------- */
void cpulogs_destruct_log_default( const char* deathpoint_filename, const char* deathpoint_function, const int deathpoint_line )
{
	cpulogs_destruct_log( &CPU_LOG, deathpoint_filename, deathpoint_function, deathpoint_line );
}


/*--------------------------FUNCTION----------------------------------------- */
void cpulogs_event_output_default( const int error_code, const char* message, const char* msg_filename, const char* msg_function, const int msg_line, bool dump_values, CPU* some_cpu )
{
printf( "cpulogs_event_output_default\n" );
	cpulogs_event_output( &CPU_LOG, error_code, message, msg_filename, msg_function, msg_line, dump_values, some_cpu );
}
