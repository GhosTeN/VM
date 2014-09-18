#pragma once

enum Operations      // Коды операций основной набор
{
	STOP = 0x01,		// СТОП!!!!	есть свободные коды
	RET = 0x04,		// возврат из подпрограммы
	// переходы: 
	JL = 0x08, JZ, JG, JOD, JLE, JNZ, JGE, JEV,		// условные переходы по регистру
	JMPR = 0x10, JMP, 							// безусловный goto 
	CALLR = 0x18, CALL,								// переход к подпрограмме с возвратом 
	LOOPR = 0x1c, LOOP, 							// цикл
	// загрузки
	LDBA = 0x20, LDSA, LDWA, LDDA, LDB = 0x24, LDS, LDW, LDD,
	STBA = 0x28, STSA, STWA, STDA, STB = 0x2C, STS, STW, STD,
	LDBI = 0x34, LDSI, LDWI,
	CLRB = 0x30, CLRS, CLRW, CLRD,
	// целая арифметика
	ADD = 0x60, ADDU, ADDI, ADDUI,
	SUB = 0x64, SUBU, SUBI, SUBUI,
	MUL = 0x68, MULU, MULI, MULUI,
	DIV = 0x6c, DIVU, DIVI, DIVUI,
	MOD = 0x70, MODU, MODI, MODUI,
	CMP = 0x74, CMPU, CMPI, CMPUI,
	INC = 0x78, INCU, INCI, INCUI,
	DEC = 0x7c, DECU, DECI, DECUI,
	NEG = 0x50, ABS = 0x51,
	// плавающая арифметика
	FADD = 0x80, FSUB, FMUL, FDIV, FMOD = 0x84, FCMP,
	FINT = 0x88, FRND, FSQRT, FEXP, FSIN, FATAN, FLN, FSGN,
	FLD1 = 0x98, FLD2, FLDPI, FLDE,
	// стековые операции - много свободных кодов
	PUSH = 0xc0, PUSHM, POP, POPM,
	STSP = 0xc4, STSPM, FMODS = 0xc6, FMODR,
	FADDS = 0xc8, FSUBS, FMULS, FDIVS,
	FADDR = 0xcc, FSUBR, FMULR, FDIVR,
	// битовые операции - много свободных кодов
	OR = 0xe0, AND, XOR, NOT = 0xe3,
	ORI = 0xec, ANDI, XORI,
	// сдвиги
	SH = 0xb0, SHU, SHI, SHUI,
	// ввод-вывод 
	IN = 0xf0, OUT = 0xf1,
	IIN = 0xF4, IOUT, FIND, FOUTD,
	// загрузки системных регистров
	LDSP = 0x56, LDRI, LDPSW, STPSW,
	// расширенные коды
	bFF = 0xFF

};
// Коды операций пересылки
enum OperationsFF
{
	SWPB = 0x00, SWPS, SWPW, SWPD, 	// обмен регистров
	MOVB = 0x04, MOVS, MOVW, MOVD, 	// копирование регистров
	CBS = 0x08, CSW, CWL,			// расширение знака
	// переводы
	CWF = 0x20, CFW, CLF, CFL,
	CWD = 0x24, CDW, CLD, CDL,
	CFD = 0x30, CDF                     // переводы дробных
};