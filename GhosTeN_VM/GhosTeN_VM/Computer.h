#pragma  once
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#include "Registers.h"
#include "Memory.h"
#include "RegisterCommand.h"
#include <vector>
#pragma pack(1)

class Command;
class Computer
{
	vector<Command*> instructions;

	bool jumping;
	void Clear();					// обнуление
	void Trace();					// ~Debug
	void initInstructions();

	//void setPSW();

public:
	uCONSTANT constanst[256];
	
	Address address;				// адрес аргумента из команд загрузки-выгрузки
	RegisterCommand RC;				// регистр команды
	Registers registers;
	Memory memory;

	Computer();
	int reset(bool debug);
	int interpreter(bool debug);
	void setIP(Address ip);

	friend class Command;
};
