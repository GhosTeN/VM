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
		uByte Length;									// длина команды					
		cmd function;									// исполн€юща€ функци€
		command(uByte l, cmd f) :Length(l), function(f){};
		command() :Length(), function(){};
	};

	command   Cmd[256];				// основной набор команд			
	command ffCmd[256];
	RegisterCommand RC;				// регистр команды
	address Address;					// адрес аргумента из команд загрузки-выгрузки
	bool jumping;
	void Clear();						// обнуление
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
