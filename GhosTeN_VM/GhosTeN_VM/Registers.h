#if !defined _REGISTERS_ 
#define _REGISTERS_
#include "Types.h"

class Registers
{
public:
	union uRON
	{
		Byte		b[512];  uByte	    ub[512];
		Word		w[128];  uWord		uw[128]; 	// ������� ��������
		Address	    a[256];  Float		f[128];		
	} RON;

	struct sPSW
	{
		unsigned int CF : 1;					// ������������ ����������� ����� 
		unsigned int OF : 1;					// ������������ �������� �����	
		unsigned int OV : 1;					// ������������ ��������� ����������
		unsigned int UV : 1;					// ���������������� ��������� ����������
		unsigned int TF : 1;					// ���� �����������
		unsigned int IP : 16;
		unsigned int : 11;						// ���� �� ������������ 
	} PSW;
};
#endif

