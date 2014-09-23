#pragma  once
#include "Types.h"

union RegisterCommand                // регистр команд
{
	uByte rc[8];
	mCR_2 CR;
	uByte Code;
	mCRRR_4 CRRR;
	mCRaW_4 CRaW;
};