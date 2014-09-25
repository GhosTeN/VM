#pragma  once
#include "Types.h"

union RegisterCommand                // регистр команд
{
	uByte rc[4];
	uByte Code;
	mCR_2 CR;
	mCaC_3 CaC;
	mCRR_3 CRR;
	mCRRR_4 CRRR;
	mCRaC_4 CRaC;
};