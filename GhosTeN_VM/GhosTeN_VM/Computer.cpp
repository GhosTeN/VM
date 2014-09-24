#include "Computer.h"
#include "Command.h"

Computer::Computer()
{
	Clear();
	initInstructions();
}
void Computer::initInstructions()
{
#pragma  region instructions
	//stop
	this->instructions.push_back(new CmdSTOP(*this));
	//jumps
	this->instructions.push_back(new CmdJZ(*this));
	this->instructions.push_back(new CmdJNZ(*this));
	this->instructions.push_back(new CmdJE(*this));
	this->instructions.push_back(new CmdJNE(*this));
	this->instructions.push_back(new CmdJA(*this));
	this->instructions.push_back(new CmdJNA(*this));
	this->instructions.push_back(new CmdJAE(*this));
	this->instructions.push_back(new CmdJNAE(*this));
	this->instructions.push_back(new CmdJB(*this));
	this->instructions.push_back(new CmdJNB(*this));
	this->instructions.push_back(new CmdJBE(*this));
	this->instructions.push_back(new CmdJNBE(*this));
	this->instructions.push_back(new CmdJMPR(*this));
	this->instructions.push_back(new CmdJMP(*this));

	//Integer
	this->instructions.push_back(new CmdLDWA(*this));
	this->instructions.push_back(new CmdSTWA(*this));
	this->instructions.push_back(new CmdADD(*this));
	this->instructions.push_back(new CmdSUB(*this));
	this->instructions.push_back(new CmdMUL(*this));
	this->instructions.push_back(new CmdDIV(*this));
	this->instructions.push_back(new CmdMOD(*this));
	this->instructions.push_back(new CmdCMP(*this));
	this->instructions.push_back(new CmdINC(*this));
	this->instructions.push_back(new CmdDEC(*this));
	this->instructions.push_back(new CmdNEG(*this));
	this->instructions.push_back(new CmdABS(*this));

#pragma  endregion
}
void Computer::setIP(Address ip)
{
	registers.PSW.IP = ip;
}
int Computer::reset(bool debug)
{
	registers.PSW.IP = 0;
	// считаем стек словах
	// registers.SP = mKw * 1024;			// за последним адресом слова
	registers.PSW.CF = registers.PSW.OF = registers.PSW.OV = registers.PSW.UV = 0;
	if (debug) registers.PSW.TF = 1; else registers.PSW.TF = 0;
	for (int i = 0; i < 64; ++i) registers.RON.w[i] = 0;
	return 0;
}
void Computer::Clear()								// обнуление command
{
	for (int i = 0; i < 8; ++i) RC.rc[i] = 0;
}
int Computer::interpreter(bool debug)
{
	int stoping = 1;
	uByte nByte = 0;
	while (stoping)
	{
		Clear(); jumping = false;
		//if (registers.PSW.IP & 0x00000001u) throw "error!";
		// выборка 2 байтов
		RC.rc[0] = memory.b[registers.PSW.IP];
		RC.rc[1] = memory.b[registers.PSW.IP + 1];
		nByte = (*instructions[RC.Code]).size;
		// добираем из памяти байты
		for (int i = 2; i < nByte; ++i) 
			RC.rc[i] = memory.b[registers.PSW.IP + i];
		if (registers.PSW.TF) Trace();       // отладочная выдача
		// выполнение команды - косвенный вызов по указателю
		// код операции - индекс в массиве адресов
		if (RC.Code < 0xFF)
			stoping = (*instructions[RC.Code])();
		//else                stoping = ffCmd[RC.FF.Code].function(*this);
		// если не команда перехода
		if (!jumping)
			registers.PSW.IP += nByte;					// изменение PC
	}
	return 0;
}
void Computer::Trace()                   // трассировка покомандная
{
	cout << setfill('0');
	cout << setw(5) << dec << registers.PSW.IP << ": ";
	int nByte = 0;
	if (RC.Code < 0xFF)				// основной набор команд
		//nByte = Cmd[RC.Code].Length;
		//else                      			// команды пересылки
		//	nByte = ffCmd[RC.FF.Code].Length;
		for (int i = 0; i < nByte; ++i)
			cout << setw(2) << hex << int(RC.rc[i]) << ' ';
	cout << endl;
}