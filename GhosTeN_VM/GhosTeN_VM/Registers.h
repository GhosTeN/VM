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
		Word		w[128];  uWord		uw[128]; 	// четырех байтовые
		Float		f[128];
	} RON;*/
>>>>>>> origin/master

	Address R[256];

	struct sPSW
	{
		unsigned int CF : 1;					// переполнение беззнаковое целое
		unsigned int OF : 1;					// переполнение знаковое целое
		unsigned int OV : 1;					// переполнение плавающей арифметики
		unsigned int TF : 1;					// флаг трассировки
		unsigned int AF : 1;					// флаг больше
		unsigned int BF : 1;					// флаг меньше
		unsigned int EF : 1;					// флаг равно
		unsigned int ZF : 1;					// флаг нуля
		unsigned int IP : 16;
<<<<<<< HEAD
		unsigned int RR : 8;					// индекс регистра возврата
=======
		unsigned int : 7;						// пока не используется
>>>>>>> origin/master
	} PSW;
};
