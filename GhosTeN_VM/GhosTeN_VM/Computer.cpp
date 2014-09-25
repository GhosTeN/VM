#include "Computer.h"
#include "Command.h"

Computer::Computer()
{
	Clear();
	initInstructions();
}
void Computer::initInstructions()
{
	instructions.insert(std::make_pair<Operations, Command*>(STOP, new CmdSTOP(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(LDC, new CmdLDC(*this)));

#pragma region J
	instructions.insert(std::make_pair<Operations, Command*>(JZ, new CmdJZ(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(JNZ, new CmdJNZ(*this)));

	instructions.insert(std::make_pair<Operations, Command*>(JE, new CmdJE(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(JNE, new CmdJNE(*this)));

	instructions.insert(std::make_pair<Operations, Command*>(JA, new CmdJA(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(JNA, new CmdJNA(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(JAE, new CmdJAE(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(JNAE, new CmdJNAE(*this)));

	instructions.insert(std::make_pair<Operations, Command*>(JB, new CmdJB(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(JNB, new CmdJNB(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(JBE, new CmdJBE(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(JNBE, new CmdJNBE(*this)));

	instructions.insert(std::make_pair<Operations, Command*>(JMPC, new CmdJMPC(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(JMPR, new CmdJMPR(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(JMPRR, new CmdJMPRR(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(JMPO, new CmdJMPO(*this)));
#pragma endregion

	instructions.insert(std::make_pair<Operations, Command*>(CALL, new CmdCALL(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(RETURN, new CmdRETURN(*this)));

#pragma region unsigned integer
#pragma endregion

#pragma region integer
	instructions.insert(std::make_pair<Operations, Command*>(ADD, new CmdADD(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(SUB, new CmdSUB(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(MUL, new CmdMUL(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(DIV, new CmdDIV(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(MOD, new CmdMOD(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(CMP, new CmdCMP(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(INC, new CmdINC(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(DEC, new CmdDEC(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(NEG, new CmdNEG(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(ABS, new CmdABS(*this)));
#pragma endregion

#pragma region float
#pragma endregion
	
#pragma region IO
	instructions.insert(std::make_pair<Operations, Command*>(IIN, new CmdIIN(*this)));

	
	instructions.insert(std::make_pair<Operations, Command*>(IOUT, new CmdIOUT(*this)));
#pragma endregion


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
		= registers.PSW.TF
		= registers.PSW.AF
		= registers.PSW.BF
		= registers.PSW.EF
		= registers.PSW.ZF
		= registers.PSW.RR
		= 0;
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
		Clear(); 
		jumping = false;
		
		for (int i = 0; i < sizeof(Word); ++i)
			RC.rc[i] = memory.b[registers.PSW.IP * 4 + i];

		// добираем из памяти байты
		if (registers.PSW.TF) Trace();       // отладочная выдача
		// выполнение команды - косвенный вызов по указателю
		// код операции - индекс в массиве адресов
		Operations code = static_cast<Operations>(RC.Code);
		if (RC.Code < 0xFF)
			stoping = (*instructions[code])();
		
		if (!jumping)
			++registers.PSW.IP;					// изменение PC
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