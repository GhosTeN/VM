#pragma  once
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#include "Registers.h"
#include "Memory.h"
#include "RegisterCommand.h"
#include "operation.h"
#include <vector>
#include <unordered_map>
#pragma pack(1)

class Command;
class Computer
{
	unordered_map<Operations, Command*> instructions;
	bool jumping;
	
	void Clear();					// обнуление
	void Trace();					// ~Debug
	void initInstructions();

	//void setPSW();

public:
<<<<<<< HEAD
=======
	
>>>>>>> origin/master
	
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
