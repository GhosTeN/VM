#pragma  once
#include "Types.h"

union RegisterCommand                // ������� ������
{
	uByte rc[4];
	mCR_2 CR;
	uByte Code;
	mCRRR_4 CRRR;
	mCRaC_4 CRaC;
};