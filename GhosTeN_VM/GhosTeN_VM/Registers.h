#pragma  once
#pragma  pack(1)
#include "Types.h"

class Registers
{
public:
<<<<<<< HEAD
=======
	/*union uRON
	{
		Byte		b[512];  uByte	    ub[512];
		Word		w[128];  uWord		uw[128]; 	// ������� ��������
		Float		f[128];
	} RON;*/
>>>>>>> origin/master

	Address R[256];

	struct sPSW
	{
		unsigned int CF : 1;					// ������������ ����������� �����
		unsigned int OF : 1;					// ������������ �������� �����
		unsigned int OV : 1;					// ������������ ��������� ����������
		unsigned int TF : 1;					// ���� �����������
		unsigned int AF : 1;					// ���� ������
		unsigned int BF : 1;					// ���� ������
		unsigned int EF : 1;					// ���� �����
		unsigned int ZF : 1;					// ���� ����
		unsigned int IP : 16;
<<<<<<< HEAD
		unsigned int RR : 8;					// ������ �������� ��������
=======
		unsigned int : 7;						// ���� �� ������������
>>>>>>> origin/master
	} PSW;
};
