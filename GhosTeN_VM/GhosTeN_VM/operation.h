#pragma once

enum Operations      // Коды операций основной набор
{
	STOP = 0x01,		// СТОП!!!!	есть свободные коды
	// переходы:
	JZ = 0x10, JNZ, JE, JNE, JA, JNA, JAE, JNAE, JB, JNB, JBE, JNBE,// условные переходы по регистру
	JMPR, JMP, 										// безусловный
	// загрузки
	LDWA = 0x20, LDUWA, LDFA,
	// выгрузка
	STW = 0x30, STUW, STF,
	// целая арифметика
	ADD = 0x40, SUB, MUL, DIV, MOD, CMP, INC, DEC, NEG, ABS,
	// плавающая арифметика
	FADD = 0x50, FSUB, FMUL, FDIV, FMOD, FCMP, FINT,
	FRND = 0x60, FSQRT, FEXP, FSIN, FATAN, FLN, FSGN, FLD1, FLD2, FLDPI, FLDE,
	//вывод
	IIN = 0x70, IOUT, FIND, FOUTD,
};
// Коды операций пересылки
enum OperationsFF
{
	SWPB = 0x00, 	// обмен регистров
	MOVB = 0x04, 	// копирование регистров
};