#if !defined _COMMAND_ 
#define _COMMAND_

#include "Types.h"
#include "Computer.h"


class Command
{

protected:
	//Computer.
	//Computer *VM;
public:
	virtual int operator()(){ return 0; }
	Command()
	{
		//this->VM = &VM;
		Computer* a;
		
	}
	
};
/*
class CmdSTOP : public Command
{
public:
	CmdSTOP(Computer& VM) : Command(VM){}
	virtual int operator()() { return 0; }
};

class CmdJZ : public Command
{
public:
	CmdJZ(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		return 0;
	}
};

class CmdJNZ : public Command
{
public:
	CmdJNZ(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		return 0;
	}
};

class CmdJE : public Command
{
public:
	CmdJE(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		return 0;
	}
};

class CmdJNE : public Command
{
public:
	CmdJNE(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		return 0;
	}
};

class CmdJA : public Command
{
public:
	CmdJA(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		return 0;
	}
};

class CmdJNA : public Command
{
public:
	CmdJNA(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		return 0;
	}
};

class CmdJAE : public Command
{
public:
	CmdJAE(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		return 0;
	}
};

class CmdJNAE : public Command
{
public:
	CmdJNAE(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		return 0;
	}
};

class CmdJB : public Command
{
public:
	CmdJB(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		return 0;
	}
};
class CmdJNB : public Command
{
public:
	CmdJNB(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		return 0;
	}
};
class CmdJBE : public Command
{
public:
	CmdJBE(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		return 0;
	}
};
class CmdJNBE : public Command
{
public:
	CmdJNBE(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		return 0;
	}
};
class CmdJMPR : public Command
{
public:
	CmdJMPR(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		return 0;
	}
};
class CmdJMP : public Command
{
public:
	CmdJMP(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		return 0;
	}
};




class CmdLDWA : public Command
{
public:
	CmdLDWA(Computer& VM) : Command(VM){}
	virtual int operator()() 
	{
		VM->address = VM->RC.CRaW.aW;
		VM->address %= (64 * 1024);
		for (int i = 0; i < sizeof(Word); ++i)
		{
			VM->registers.RON.ub[VM->RC.CRaW.R1 + i] = VM->memory.b[VM->address + i];
		}
		return 1; 
	}
};

class CmdSTWA : public Command
{
public:
	CmdSTWA(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->address = VM->RC.CRaW.aW;
		VM->address %= (64 * 1024);
		for (int i = 0; i < sizeof(Word); ++i)
		{
			VM->memory.b[VM->address + i] = VM->registers.RON.b[VM->RC.CRaW.R1 + i];
		}
		return 1;
	}
};

class CmdADD : public Command
{
public:
	CmdADD(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->registers.RON.w[VM->RC.CRRR.R1 / 4] =
			VM->registers.RON.w[VM->RC.CRRR.R2 / 4] + VM->registers.RON.w[VM->RC.CRRR.R3 / 4];

		return 1;
	}
};

class CmdSUB : public Command
{
public:
	CmdSUB(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->registers.RON.w[VM->RC.CRRR.R1 / 4] =
			VM->registers.RON.w[VM->RC.CRRR.R2 / 4] - VM->registers.RON.w[VM->RC.CRRR.R3 / 4];

		return 1;
	}
};
class CmdMUL : public Command
{
public:
	CmdMUL(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->registers.RON.w[VM->RC.CRRR.R1 / 4] =
			VM->registers.RON.w[VM->RC.CRRR.R2 / 4] * VM->registers.RON.w[VM->RC.CRRR.R3 / 4];

		return 1;
	}
};

class CmdDIV : public Command
{
public:
	CmdDIV(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->registers.RON.w[VM->RC.CRRR.R1 / 4] =
			VM->registers.RON.w[VM->RC.CRRR.R2 / 4] / VM->registers.RON.w[VM->RC.CRRR.R3 / 4];

		return 1;
	}
};

class CmdMOD : public Command
{
public:
	CmdMOD(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->registers.RON.w[VM->RC.CRRR.R1 / 4] = 
			VM->registers.RON.w[VM->RC.CRRR.R2 / 4] % VM->registers.RON.w[VM->RC.CRRR.R3 / 4];

		return 1;
	}
};

class CmdCMP : public Command
{
public:
	CmdCMP(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		if (VM->registers.RON.w[VM->RC.CRRR.R1 / 4] > VM->registers.RON.w[VM->RC.CRRR.R3 / 4])
			VM->registers.RON.w[VM->RC.CRRR.R2 / 4] = +1;
		else if (VM->registers.RON.w[VM->RC.CRRR.R1 / 4] == VM->registers.RON.w[VM->RC.CRRR.R3 / 4])
			VM->registers.RON.w[VM->RC.CRRR.R2 / 4] = 0;
		else
			VM->registers.RON.w[VM->RC.CRRR.R2 / 4] = -1;

		return 1;
	}
};

class CmdINC : public Command
{
public:
	CmdINC(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		++VM->registers.RON.w[VM->RC.CR.R / 4];
		return 1;
	}
};

class CmdDEC : public Command
{
public:
	CmdDEC(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		--VM->registers.RON.w[VM->RC.CR.R / 4];
		return 1;
	}
};

class CmdABS : public Command
{
public:
	CmdABS(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		if (VM->registers.RON.w[VM->RC.CR.R/4] < 0)
			VM->registers.RON.w[VM->RC.CR.R / 4] = -VM->registers.RON.w[VM->RC.CR.R / 4];
		return 1;
	}
};
class CmdNEG : public Command
{
public:
	CmdNEG(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->registers.RON.w[VM->RC.CR.R / 4] = -VM->registers.RON.w[VM->RC.CR.R / 4];
		return 1;
	}
};

*/
#endif