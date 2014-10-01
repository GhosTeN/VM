#pragma  once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unordered_map>
using namespace std;

#include "Registers.h"
#include "Memory.h"
#include "RegisterCommand.h"
#include "operation.h"

#pragma pack(1)

class Command;
class Computer
{
	
	unordered_map<Operations, Command*> instructions;
	void SetConsoleTextColor(Word colorBackground, Word colorForeground);
	void Clear();					// обнуление
	void Trace();					// ~Debug
	void initInstructions();

public:

	
	RegisterCommand RC;				// регистр команды
	Registers registers;
	Memory memory;

	Computer();
	void clearFlags();				// обнуление флагов
	int reset(bool debug);
	int interpreter(bool debug);
	void setIP(Address ip);

	friend class Command;
};
