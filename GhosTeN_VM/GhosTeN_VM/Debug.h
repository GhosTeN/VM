#pragma  once
#include <iostream>
#include <iomanip>
using namespace std;

#include "Types.h"
#include "Memory.h"
#include "Registers.h"

class Debug
{
private:
	Memory* memory;
	uWord memory_size;
	Registers* registers;
public:
	Debug(Memory* memory, Registers* registers)
	{
		this->memory = memory;
		this->registers = registers;
		memory_size = sizeof(memory->uw) / 4 - 1 ;
	}
	
	void printIP()
	{
		cout << "[startIP:" << 16383 << "] [endIP:" << 16383 << "] [allIP:" << memory_size << "] [selectedIP:" << registers->PSW.IP << "]" << endl;
	}
	void printFlugs()
	{
		cout << "CF:" << registers->PSW.CF 
			<< " OF:" << registers->PSW.OF
			<< " OV:" << registers->PSW.OV
			<< " TF:" << registers->PSW.TF
			<< " AF:" << registers->PSW.AF
			<< " BF:" << registers->PSW.BF
			<< " EF:" << registers->PSW.EF
			<< " ZF:" << registers->PSW.ZF
			<< " IP:" << registers->PSW.IP
			<< " RR:" << registers->PSW.RR
			<< endl;
	}
	void printMemoryint()
	{
		Address IP = 0;
		for (int i = 0; i < 30; ++i)
		{
			for (int j = 0; j < 7; ++j)
			{
				cout << memory->w[IP] << "|";
				++IP;
			}
			cout << endl;
		}
	}
	void printMemoryByte()
	{
		Address IP = 0;
		for (int i = 0; i < 20; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				cout << "[";
				for (int k = 0; k < 3; ++k)
				{
					cout << setfill('0') << setw(2) << hex << (int)memory->b[IP * 4 + k] << " ";
				}
				cout << setfill('0') << setw(2) << hex << (int)memory->b[IP * 4 + 3] << "] ";
				++IP;
			}
			cout << endl;
		}
	}
	//void setCurrentIP(Address IP);
};