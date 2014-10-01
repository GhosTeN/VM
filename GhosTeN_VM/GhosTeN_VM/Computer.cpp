#include "Computer.h"
#include "Command.h"
#include "Debug.h"
#include <Windows.h>
Computer::Computer()
{
	Clear();
	initInstructions();
}
void Computer::SetConsoleTextColor(Word colorBackground, Word colorForeground)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (Word)((colorForeground << 4) | colorBackground));
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
	instructions.insert(std::make_pair<Operations, Command*>(UADD, new CmdUADD(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(USUB, new CmdUSUB(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(UMUL, new CmdUMUL(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(UDIV, new CmdUDIV(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(UMOD, new CmdUMOD(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(UCMP, new CmdUCMP(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(UINC, new CmdUINC(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(UDEC, new CmdUDEC(*this)));
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
	instructions.insert(std::make_pair<Operations, Command*>(FADD, new CmdFADD(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(FSUB, new CmdFSUB(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(FMUL, new CmdFMUL(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(FDIV, new CmdFDIV(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(FCMP, new CmdFCMP(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(FNEG, new CmdFNEG(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(FABS, new CmdFABS(*this)));
#pragma endregion
	
#pragma region IO
	instructions.insert(std::make_pair<Operations, Command*>(IIN, new CmdIIN(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(UIN, new CmdUIN(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(FIN, new CmdFIN(*this)));

	
	instructions.insert(std::make_pair<Operations, Command*>(IOUT, new CmdIOUT(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(UOUT, new CmdUOUT(*this)));
	instructions.insert(std::make_pair<Operations, Command*>(FOUT, new CmdFOUT(*this)));
#pragma endregion



}
void Computer::setIP(Address ip)
{
	registers.PSW.IP = ip;
}
int Computer::reset(bool debug)
{
	registers.PSW.IP = 0;
	
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
		= registers.PSW.AF
		= registers.PSW.BF
		= registers.PSW.EF
		= registers.PSW.ZF
		= registers.PSW.RR
		= 0;
}
void Computer::Clear()								// обнуление command
{
	for (int i = 0; i < 4; ++i) RC.rc[i] = 0;
}

int Computer::interpreter(bool debug)
{
	Debug d(&memory, &registers);
	int STATE = 1;
	uByte nByte = 0;
	while (STATE)
	{
		Clear(); 
		
		COORD coord;
		coord.X = 0;
		coord.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

		// читаем слово
		for (int i = 0; i < sizeof(Word); ++i)
			RC.rc[i] = memory.b[registers.PSW.IP * 4 + i];

		if (registers.PSW.TF) Trace();
		Operations code = static_cast<Operations>(RC.Code);
		d.printIP();
		d.printFlugs();
		cout << endl;
		d.printMemoryByte();
		if (instructions.find(code) != instructions.end())
		{
			STATE = (*instructions[code])();


			if (STATE != 2)
				++registers.PSW.IP;					// изменение IP
		}
		else
		{
			SetConsoleTextColor(15, 12);
			cerr << "IP: " << registers.PSW.IP << "  [ ERORR: Unknown command code: 0x" << code  << " ]"<< endl;
			STATE = 0;
			SetConsoleTextColor(7, 0);
		}
		
	}
	return 0;
}
void Computer::Trace()                   // трассировка покомандная
{
	Operations code = static_cast<Operations>(RC.Code);
	/*cout << "IP: " << setfill('0') << setw(5) << registers.PSW.IP << " ";
		switch (code)
		{
		case IIN:
			cout << "\t IIN: ";
			break;
		case IOUT:
			cout << "\t IOUT: ";
			break;
		case UIN:
			cout << "\t UIN: ";
			break;
		case UOUT:
			cout << "\t UOUT: ";
			break;
		case FIN:
			cout << "\t FIN: ";
			break;
		case FOUT:
			cout << "\t FOUT: ";
			break;
		default: cout << endl;
			break;
		}*/
}

