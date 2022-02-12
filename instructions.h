#ifndef INSTRUCTIONS_H_INCLUDED
#define INSTRUCTIONS_H_INCLUDED


/*--------------------------CONST---------------------------------------------*/
const int instruction_length[] = ///< Number of instruction arguments in machine code + instruction code (N + 1 > 0)
{
	1, //HLT
	1, //START
	2, //PUSH
	1, //POP
	1, //ADD
	1, //SUB
	1, //MUL
	1, //DIV
	1, //OUT
	3, //JUMP
	1 //NONE
};


/*--------------------------ENUM----------------------------------------------*/
enum instruction_type ///< Machine instructions, which are specific actions performed by the CPU when received
//!TODO включить общим файлом или сделать что-то подобное
{
	HLT = 0,
	STRT = 1,
	PUSH = 2,
	POP = 3,
	ADD = 4,
	SUB = 5,
	MUL = 6,
	DIV = 7,
	OUT = 8,
	JUMP = 9,
	NONE = 10
};


/*--------------------------ENUM----------------------------------------------*/
enum descriptional_argument ///< Special machine code argument that provides additional information about types of instruction operands or is an last argument if numeric data is not expected. Descriptional argument is provided only for long (instruction_length > 1) instructions). Machine code instruction can only have 1 descriptional argument
//тип дополнительного (определительного) аргумента в машинном коде
{
	NARG = 0,
	INT = 1,
	REAL = 2,
	RGAX = 3,
	RGBX = 4,
	RGCX = 5,
	RGDX = 6,
	RAM = 7,
	RAMA = 8,
	RAMB = 9,
	RAMC = 10,
	RAMD = 11,
	TRUE = 12,
	ABV = 13,
	NBLW = 14,
	BLW = 15,
	NABV = 16,
	EQL = 17,
	NEQL = 18

};


#endif //INSTRUCTIONS_H_INCLUDED