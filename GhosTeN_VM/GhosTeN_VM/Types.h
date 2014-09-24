#pragma  once
#pragma  pack(1)
// ����

typedef char Byte;
typedef unsigned char uByte;
typedef int Word;
typedef unsigned int uWord;
typedef float Float;

typedef unsigned short Address;

union  uCONSTANT
{
	Word w;
	uWord uw;
	Float f;
};

struct mCR_2            // ��� R - 2 �����
{
	uByte Code; uByte R;
};
struct mCRRR_4          // ��� R R R
{
	uByte Code; uByte R1; uByte R2; uByte R3;
};
struct mCRaW_4
{
	uByte Code; uByte R1; Address aW;
};
struct mCCaC_6
{
	uByte Code; Address aC; uCONSTANT Const;
};

