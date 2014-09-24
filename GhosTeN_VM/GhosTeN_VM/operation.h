#pragma once

enum Operations      // ���� �������� �������� �����
{
	STOP = 0x01,		// ����!!!!	���� ��������� ����
	// ��������:
	JZ = 0x10, JNZ, JE, JNE, JA, JNA, JAE, JNAE, JB, JNB, JBE, JNBE,// �������� �������� �� ��������
	JMPR, JMP, 										// �����������
	// ��������
	LDWA = 0x20, LDUWA, LDFA,
	// ��������
	STW = 0x30, STUW, STF,
	// ����� ����������
	ADD = 0x40, SUB, MUL, DIV, MOD, CMP, INC, DEC, NEG, ABS,
	// ��������� ����������
	FADD = 0x50, FSUB, FMUL, FDIV, FMOD, FCMP, FINT,
	FRND = 0x60, FSQRT, FEXP, FSIN, FATAN, FLN, FSGN, FLD1, FLD2, FLDPI, FLDE,
	//�����
	IIN = 0x70, IOUT, FIND, FOUTD,
};
// ���� �������� ���������
enum OperationsFF
{
	SWPB = 0x00, 	// ����� ���������
	MOVB = 0x04, 	// ����������� ���������
};