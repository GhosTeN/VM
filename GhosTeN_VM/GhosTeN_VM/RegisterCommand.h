#pragma  once
#include "Types.h"

union RegisterCommand                // регистр команд
{
	uByte rc[8];
	uByte Code;
	struct ff { uByte FF; uByte Code; } FF;
	mCN_2   CN;
	mCRRR_4 CRRR;
	mCRA_4 CRA;
	dFCRR_4 FCRR;
};