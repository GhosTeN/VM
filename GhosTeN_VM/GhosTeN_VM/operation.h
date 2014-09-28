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
	UADD = 0x30, USUB, UMUL, UDIV, UMOD, UCMP, UINC, UDEC,
	// целая знаковая
	ADD = 0x40, SUB, MUL, DIV, MOD, CMP, INC, DEC, ABS, NEG,
	
	// плавающая арифметика
	FADD = 0x50, FSUB, FMUL, FDIV, FCMP, FABS, FNEG,
	//вывод
	IIN = 0x70, IOUT, UIN, UOUT,  FIN, FOUT,
};
