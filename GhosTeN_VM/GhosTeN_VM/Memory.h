#pragma  once
#include "Types.h"

const unsigned int mKb = 64;
const unsigned int mKw = mKb / sizeof(Word);

union Memory
	{
		uByte		b[mKb * 1024];	 		// 64 ��������	// 32 K ��������
		uWord		w[mKw * 1024];			// 16 K ����
		Float		f[mKw * 1024];			// 16 K ����
	};
