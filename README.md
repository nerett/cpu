# CPU
This project is an implementation of software cpu model, that consists of registers, RAM and stack and can execute compiled specific assembler code (specific machine code) with its built-in instructions. It automatically checks whether this code is supported or not.

## Usage
If you've already built and added `cpu` to `$PATH`, run `cpu <path-to-machine-code>` to execute a file with the machine code supported. Otherwise build the project and execute with `./Debug/cpu` or `make run` (from project root directory).

## Building from source
Download this repository with

```
git clone https://github.com/nerett/cpu.git
```

Download dependencies with

```
cd cpu/
make install-dependencies
```

...or download the repositiries required manually.

Build the project

```
make
```

Run Software CPU with (machine code file path is set to default)

```
make run
```

or use `make rund` instead to run with `valgrind`.
You can also run this binary with

```
./Debug/cpu <path-to-machine-code>
```

To totally rebuild the project run

```
make clean
make
```

## Documentation
https://nerett.github.io/cpu/

## About project
This programm was written during MIPT **Ded's** cource.
