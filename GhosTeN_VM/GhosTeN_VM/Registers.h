#pragma  once
#include "Types.h"

class Registers
{
public:
	union uRON
	{
		Word		w[128];  uWord		uw[128]; 	// четырехбайтовые
		Address	    a[256];  Float		f[128];		
	} RON;

	struct sPSW
	{
		unsigned int CF : 1;					// переполнение беззнаковое целое 
		unsigned int OF : 1;					// переполнение знаковое целое	
		unsigned int OV : 1;					// переполнение плавающей арифметики
		unsigned int UV : 1;					// антипереполнение плавающей арифметики
		unsigned int TF : 1;					// флаг трассировки
		unsigned int IP : 16;
		unsigned int : 11;						// пока не используется 
	} PSW;
};


