CC = g++
CFLAGS = -c #-Wall -Wextra -g
LDFLAGS = #-Wall -Wextra -g
BUILDDIR = Build/
EXECDIR = Debug/

STACKDIR = ../stack/

all: mkdir main
	$(CC) $(LDFLAGS) $(BUILDDIR)main.o $(BUILDDIR)libcpu.o $(BUILDDIR)libstack.o $(BUILDDIR)libstack_config.o -o $(EXECDIR)cpu
	
mkdir:
	mkdir -p Build Debug
	
main: libcpu libstack
	$(CC) $(CFLAGS) main.cpp -o $(BUILDDIR)main.o

libstack: libstack_config
	$(CC) $(CFLAGS) $(STACKDIR)stack.cpp -o $(BUILDDIR)libstack.o
	
libstack_config:
	$(CC) $(CFLAGS) $(STACKDIR)config.cpp -o $(BUILDDIR)libstack_config.o

libcpu:
	$(CC) $(CFLAGS) cpu.cpp -o $(BUILDDIR)libcpu.o
	
	
run:
	./$(EXECDIR)cpu

rund:
	valgrind ./$(EXECDIR)cpu
	
clean:
	rm -rf $(BUILDDIR) $(EXECDIR)
