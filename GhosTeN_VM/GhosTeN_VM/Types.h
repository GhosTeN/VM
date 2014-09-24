#pragma  once
#pragma  pack(1)
// типы

typedef char Byte;
typedef unsigned char uByte;

typedef int Word;
typedef unsigned int uWord;

typedef float Float;

typedef unsigned short Address;

struct mCR_2            // КОП R - 2 байта
{
	uByte Code; uByte R;
};
struct mCRRR_4          // КОП R R R
{
	uByte Code; uByte R1; uByte R2; uByte R3;
};
struct mCRaW_4
{
	uByte Code; uByte R1; Address aW;
};
