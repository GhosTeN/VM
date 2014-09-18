#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


#include "Registers.h"
#include "Memory.h"
#include "RegisterCommand.h"
#pragma pack(1)



class Computer
{
	typedef int(*cmd)(Computer &VM);
	struct command
	{
		uByte Length;									// ����� �������					
		cmd function;									// ����������� �������
		command(uByte l, cmd f) :Length(l), function(f){};
		command() :Length(), function(){};
	};

	command   Cmd[256];				// �������� ����� ������			
	command ffCmd[256];
	RegisterCommand RC;				// ������� �������
	address Address;					// ����� ��������� �� ������ ��������-��������
	bool jumping;
	void Clear();						// ���������
	void Trace();						//
	//void setPSW();						


public:
	Registers registers;
	Memory memory;
	
	Computer();
	int reset(bool debug);
	int interpreter(bool debug);
	void setIP(address ip) { registers.PSW.IP = ip; return; }
	friend class Command;

	
};
