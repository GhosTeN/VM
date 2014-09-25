#pragma once

enum Operations      // ���� �������� �������� �����
{
	STOP = 0x00,		// ����!	���� ��������� ����
	LDC = 0x01,			// �������� ���������

	// �������� 16��:
	JZ = 0x10, JNZ, JE, JNE, JA, JNA, JAE, JNAE, JB, JNB, JBE, JNBE,// �������� �������� �� ��������
	JMPC, JMPR, JMPRR, JMPO, 										// �����������
	
	CALL, RETURN,

	// ����� �����������
	// ����� ��������
	ADD = 0x40, SUB, MUL, DIV, MOD, CMP, INC, DEC, ABS, NEG,
	
	// ��������� ����������
	FADD = 0x50, FSUB, FMUL, FDIV, FMOD, FCMP,
	FRND, FSQRT, FEXP, FSIN, FATAN, FLN, FLD1, FLD2, FLDPI, FLDE,
	//�����
	IIN = 0x70, IOUT, UIN, UOUT,  FIN, FOUT,
};
