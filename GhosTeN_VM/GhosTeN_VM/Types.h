#pragma once
#pragma  pack(1)
// типы 
typedef signed char Byte;
typedef unsigned char uByte;

typedef int Word;
typedef unsigned int uWord;


typedef float Float;


typedef unsigned short Address;
#pragma pack(1)

struct mCN_2            // КОП N - 2 байта
{
	uByte Code; uByte N;
};
struct mCRRR_4          // КОП R R R 
{
	uByte Code; uByte R1; uByte R2; uByte R3;
};
struct mCRA_4
{
	uByte Code; uByte R1; Address addres;
};


// Дополнительный набор команд
struct dFCRR_4          // FF КОП R R 
{
	uByte FF; uByte Code; uByte R1; uByte R2;
};