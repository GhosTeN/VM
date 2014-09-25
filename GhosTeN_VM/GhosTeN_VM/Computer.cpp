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
	//load
	this->instructions.push_back(new CmdLDC(*this));
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

	//16
	//Integer
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
	// ������� ���� ������
	// registers.SP = mKw * 1024;			// �� ��������� ������� �����
	
	clearFlags();
	if (debug) registers.PSW.TF = 1;
	for (int i = 0; i < 64; ++i) memory.w[registers.R[i]] = 0;
	return 0;
}
void Computer::clearFlags()
{
	registers.PSW.CF 
		= registers.PSW.OF 
		= registers.PSW.OV 
		= registers.PSW.UV 
		= registers.PSW.TF
		= registers.PSW.AF
		= registers.PSW.BF
		= registers.PSW.EF
		= registers.PSW.ZF
		= 0;
}
void Computer::Clear()								// ��������� command
{
	for (int i = 0; i < 8; ++i) RC.rc[i] = 0;
}
int Computer::interpreter(bool debug)
{
	int stoping = 1;
	uByte nByte = 0;
	while (stoping)
	{
		Clear(); 
		jumping = false;
		
		for (int i = 0; i < sizeof(Word); ++i)
			RC.rc[i] = memory.b[registers.PSW.IP * 4 + i];

		// �������� �� ������ �����
		if (registers.PSW.TF) Trace();       // ���������� ������
		// ���������� ������� - ��������� ����� �� ���������
		// ��� �������� - ������ � ������� �������
		if (RC.Code < 0xFF)
			stoping = (*instructions[RC.Code])();

		if (!jumping)
			++registers.PSW.IP;					// ��������� PC
	}
	return 0;
}
void Computer::Trace()                   // ����������� �����������
{
	cout << setfill('0');
	cout << setw(5) << dec << registers.PSW.IP << ": ";
	int nByte = 0;
	if (RC.Code < 0xFF)				// �������� ����� ������
		//nByte = Cmd[RC.Code].Length;
		//else                      			// ������� ���������
		//	nByte = ffCmd[RC.FF.Code].Length;
		for (int i = 0; i < nByte; ++i)
			cout << setw(2) << hex << int(RC.rc[i]) << ' ';
	cout << endl;
}