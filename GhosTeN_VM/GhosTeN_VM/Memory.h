#pragma  once
#include "Types.h"

const unsigned int mKb = 64;
const unsigned int mKw = mKb / sizeof(Word);

union Memory
	{
		uByte		b[mKb * 1024];	 		// 64 ��������	// 32 K ��������
		Word		w[mKw * 1024];			// 16 � ����
		Float		f[mKw * 1024];			// 16 K ����
	};

