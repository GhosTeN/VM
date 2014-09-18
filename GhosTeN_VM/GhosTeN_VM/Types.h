#pragma once
#pragma  pack(1)
// ���� 
typedef signed char Byte;
typedef unsigned char uByte;

typedef int Word;
typedef unsigned int uWord;


typedef float Float;


typedef unsigned short Address;
#pragma pack(1)

struct mCN_2            // ��� N - 2 �����
{
	uByte Code; uByte N;
};
struct mCRRR_4          // ��� R R R 
{
	uByte Code; uByte R1; uByte R2; uByte R3;
};
struct mCRA_4
{
	uByte Code; uByte R1; Address addres;
};


// �������������� ����� ������
struct dFCRR_4          // FF ��� R R 
{
	uByte FF; uByte Code; uByte R1; uByte R2;
};