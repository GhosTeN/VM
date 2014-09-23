
#pragma  once
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


#include "Registers.h"
#include "Memory.h"
#include "RegisterCommand.h"

#include "Command.h"
#include <vector>
#pragma pack(1)



class Computer
{
	vector<Command*> instructions;
	
	
	bool jumping;
	void Clear();					// ���������
	void Trace();					// ~Debug
	

	//void setPSW();						


public:
	
	Address address;				// ����� ��������� �� ������ ��������-��������
	RegisterCommand RC;				// ������� �������
	Registers registers;
	Memory memory;
	
	Computer();
	int reset(bool debug);
	int interpreter(bool debug);
	void setIP(Address ip) { registers.PSW.IP = ip; return; }

	
};
