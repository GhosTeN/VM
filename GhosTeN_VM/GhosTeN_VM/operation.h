#pragma once

enum Operations      // Коды операций основной набор
{
	STOP = 0x00,		// СТОП!	есть свободные коды
	LDC = 0x01,			// загрузка константы

	// переходы 16шт:
	JZ = 0x10, JNZ, JE, JNE, JA, JNA, JAE, JNAE, JB, JNB, JBE, JNBE,// условные переходы по регистру
	JMPC, JMPR, JMPRR, JMPO, 										// безусловный
	
	CALL, RETURN,

	// целая беззнаковая
	// целая знаковая
	ADD = 0x40, SUB, MUL, DIV, MOD, CMP, INC, DEC, ABS, NEG,
	
	// плавающая арифметика
	FADD = 0x50, FSUB, FMUL, FDIV, FMOD, FCMP,
	FRND, FSQRT, FEXP, FSIN, FATAN, FLN, FLD1, FLD2, FLDPI, FLDE,
	//вывод
	IIN = 0x70, IOUT, UIN, UOUT,  FIN, FOUT,
};
