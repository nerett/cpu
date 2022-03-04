DEPENDENCIES = https://github.com/nerett/stack.git https://github.com/nerett/htmlogs.git

CC = g++
CFLAGS = -c -fsanitize=address #-Wall -Wextra -g
LDFLAGS = -fsanitize=address #-Wall -Wextra -g
BUILDDIR = Build/
EXECDIR = Debug/

STACKDIR = ../stack/
HTMLOGSDIR = ../htmlogs/

CPUCODEPATH = ../cpucode_builder/cpucode


#------------------------------------BUILDING-----------------------------------------------
all: mkdir main
	$(CC) $(LDFLAGS) $(BUILDDIR)main.o $(BUILDDIR)libcpu.o $(BUILDDIR)libcpu_io.o $(BUILDDIR)libhtmlogs.o $(BUILDDIR)libhtmlogs_templates.o $(BUILDDIR)libcpu_logs.o $(BUILDDIR)libstack.o $(BUILDDIR)libstack_config.o -o $(EXECDIR)cpu
	
mkdir:
	mkdir -p Build Debug
	
main: libhtmlogs libhtmlogs_templates libstack libcpu libcpu_logs
	$(CC) $(CFLAGS) main.cpp -o $(BUILDDIR)main.o


#-------------------------------------libhtmlogs------------------------------------------------
libhtmlogs:
	$(CC) $(CFLAGS) $(HTMLOGSDIR)htmlogs.cpp -o $(BUILDDIR)libhtmlogs.o

libhtmlogs_templates: libhtmlogs
	$(CC) $(CFLAGS) $(HTMLOGSDIR)htmlogs_templates.cpp -o $(BUILDDIR)libhtmlogs_templates.o


#-------------------------------------libstack-----------------------------------------------
libstack: libstack_config
	$(CC) $(CFLAGS) $(STACKDIR)stack.cpp -o $(BUILDDIR)libstack.o
	
libstack_config:
	$(CC) $(CFLAGS) $(STACKDIR)config.cpp -o $(BUILDDIR)libstack_config.o


#--------------------------------------libcpu------------------------------------------------
libcpu: libcpu_io
	$(CC) $(CFLAGS) cpu.cpp -o $(BUILDDIR)libcpu.o

libcpu_io:
	$(CC) $(CFLAGS) cpu_io.cpp -o $(BUILDDIR)libcpu_io.o

libcpu_logs: libcpu libcpu_io libhtmlogs libhtmlogs_templates
	$(CC) $(CFLAGS) cpu_logs.cpp -o $(BUILDDIR)libcpu_logs.o


#-----------------------------INSTALLING DEPENDENCIES----------------------------------------
install-dependencies:
	cd .. && git clone $(DEPENDENCIES)


#------------------------------------RUNNING-------------------------------------------------
run:
	./$(EXECDIR)cpu $(CPUCODEPATH)

rund:
	valgrind ./$(EXECDIR)cpu


#-----------------------------------CLEANING-------------------------------------------------
clean:
	rm -rf $(BUILDDIR) $(EXECDIR)
