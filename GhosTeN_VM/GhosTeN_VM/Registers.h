#pragma  once
#pragma  pack(1)
#include "Types.h"

class Registers
{
public:

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
		unsigned int RR : 8;					// ������ �������� ��������
	} PSW;
};
