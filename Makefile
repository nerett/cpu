DEPENDENCIES = https://github.com/nerett/stack.git

CC = g++
CFLAGS = -c #-Wall -Wextra -g
LDFLAGS = #-Wall -Wextra -g
BUILDDIR = Build/
EXECDIR = Debug/

STACKDIR = ../stack/

CPUCODEPATH = ../cpucode_builder/cpucode


#------------------------------------building-----------------------------------------------
all: mkdir main
	$(CC) $(LDFLAGS) $(BUILDDIR)main.o $(BUILDDIR)libcpu.o $(BUILDDIR)libcpu_io.o $(BUILDDIR)libstack.o $(BUILDDIR)libstack_config.o -o $(EXECDIR)cpu
	
mkdir:
	mkdir -p Build Debug
	
main: libcpu libstack
	$(CC) $(CFLAGS) main.cpp -o $(BUILDDIR)main.o

libstack: libstack_config
	$(CC) $(CFLAGS) $(STACKDIR)stack.cpp -o $(BUILDDIR)libstack.o
	
libstack_config:
	$(CC) $(CFLAGS) $(STACKDIR)config.cpp -o $(BUILDDIR)libstack_config.o

libcpu: libcpu_io
	$(CC) $(CFLAGS) cpu.cpp -o $(BUILDDIR)libcpu.o

libcpu_io:
	$(CC) $(CFLAGS) cpu_io.cpp -o $(BUILDDIR)libcpu_io.o


#-----------------------------installing dependencies----------------------------------------
install-dependencies:
	cd .. && git clone $(DEPENDENCIES)$(BUILDDIR)libcpu.o


#------------------------------------running-------------------------------------------------
run:
	./$(EXECDIR)cpu $(CPUCODEPATH)

rund:
	valgrind ./$(EXECDIR)cpu


#-----------------------------------cleaning-------------------------------------------------
clean:
	rm -rf $(BUILDDIR) $(EXECDIR)
