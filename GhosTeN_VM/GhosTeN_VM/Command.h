#pragma once
#include <iostream>
#include "Types.h"
#include "Computer.h"

class Command
{
protected:
	Computer* VM;
public:
	int size = 2;
	Command(Computer& VMM)
	{
		this->VM = &VMM;
	}
	virtual int operator()(){ return 0; }
};

class CmdLDC : public Command
{
public:

	CmdLDC(Computer& VM) : Command(VM){ size = 4; }
	virtual int operator()()
	{
		VM->registers.R[VM->RC.CRaC.R] = VM->RC.CRaC.aC;
		//VM->constanst[VM->RC.CCaC.aC] = VM->RC.CCaC.Const;

		return 1;
	}
};
class CmdSTOP : public Command
{
public:

	CmdSTOP(Computer& VM) : Command(VM){ size = 2; }
	virtual int operator()() { return 0; }
};

#pragma region J
class CmdJZ : public Command
{
public:
	CmdJZ(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		//если не ноль, то пропускаем команду
		if (VM->registers.PSW.ZF == 0)
		{
			++VM->registers.PSW.IP;
		}
		return 1;
	}
};
class CmdJNZ : public Command
{
public:
	CmdJNZ(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		if (VM->registers.PSW.ZF == 1)
		{
			++VM->registers.PSW.IP;
		}
		return 1;
	}
};
class CmdJE : public Command
{
public:
	CmdJE(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		if (VM->registers.PSW.EF == 0)
		{
			++VM->registers.PSW.IP;
		}
		return 1;
	}
};
class CmdJNE : public Command
{
public:
	CmdJNE(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		if (VM->registers.PSW.EF == 1)
		{
			++VM->registers.PSW.IP;
		}
		return 1;
	}
};
class CmdJA : public Command
{
public:
	CmdJA(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		if (VM->registers.PSW.AF == 0)
		{
			++VM->registers.PSW.IP;
		}
		return 1;
	}
};
class CmdJNA : public Command
{
public:
	CmdJNA(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		if (VM->registers.PSW.AF == 1)
		{
			++VM->registers.PSW.IP;
		}
		return 1;
	}
};
class CmdJAE : public Command
{
public:
	CmdJAE(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		if (VM->registers.PSW.AF == 0 && VM->registers.PSW.EF == 0)
		{
			++VM->registers.PSW.IP;
		}
		return 1;
	}
};

class CmdJNAE : public Command
{
public:
	CmdJNAE(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		if (VM->registers.PSW.AF == 1 || VM->registers.PSW.EF == 1)
		{
			++VM->registers.PSW.IP;
		}
		return 1;
	}
};
class CmdJB : public Command
{
public:
	CmdJB(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		if (VM->registers.PSW.BF == 0)
		{
			++VM->registers.PSW.IP;
		}
		return 1;
	}
};
class CmdJNB : public Command
{
public:
	CmdJNB(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		if (VM->registers.PSW.BF == 1)
		{
			++VM->registers.PSW.IP;
		}
		return 1;
	}
};
class CmdJBE : public Command
{
public:
	CmdJBE(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		if (VM->registers.PSW.BF == 0 && VM->registers.PSW.EF == 0)
		{
			++VM->registers.PSW.IP;
		}
		return 1;
	}
};
class CmdJNBE : public Command
{
public:
	CmdJNBE(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		if (VM->registers.PSW.BF == 1 || VM->registers.PSW.EF == 1)
		{
			++VM->registers.PSW.IP;
		}
		return 1;
	}
};
class CmdJMPC : public Command
{
public:
	CmdJMPC(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->setIP(VM->RC.CaC.aC);
		return 1;
	}
};
class CmdJMPR : public Command
{
public:
	CmdJMPR(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->setIP(VM->memory.w[VM->registers.R[VM->RC.CR.R]]);
		return 1;
	}
};
class CmdJMPRR : public Command
{
public:
	CmdJMPRR(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->setIP(VM->memory.w[VM->registers.R[VM->RC.CRR.R1]] + VM->memory.w[VM->registers.R[VM->RC.CRR.R2]]);
		return 1;
	}
};
class CmdJMPO : public Command
{
public:
	CmdJMPO(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->registers.PSW.IP += VM->RC.CaC.aC;
		return 1;
	}
};
class CmdCALL : public Command
{
public:
	CmdCALL(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->memory.w[VM->registers.R[VM->RC.CRaC.R]] = VM->registers.PSW.IP;
		VM->setIP(VM->RC.CRaC.aC);
		return 1;
	}
};
class CmdRETURN : public Command
{
public:
	CmdRETURN(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->setIP(VM->memory.w[VM->registers.R[VM->registers.PSW.RR]]);
		return 1;
	}
};
#pragma  endregion

#pragma region INTEGER
class CmdADD : public Command
{
public:
	CmdADD(Computer& VM) : Command(VM){ size = 4; }
	virtual int operator()()
	{
		VM->memory.w[VM->registers.R[VM->RC.CRRR.R1]] =
			VM->memory.w[VM->registers.R[VM->RC.CRRR.R2]] + VM->memory.w[VM->registers.R[VM->RC.CRRR.R3]];

		return 1;
	}
};
class CmdSUB : public Command
{
public:
	CmdSUB(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->memory.w[VM->registers.R[VM->RC.CRRR.R1]] =
			VM->memory.w[VM->registers.R[VM->RC.CRRR.R2]] - VM->memory.w[VM->registers.R[VM->RC.CRRR.R3]];

		return 1;
	}
};
class CmdMUL : public Command
{
public:
	CmdMUL(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->memory.w[VM->registers.R[VM->RC.CRRR.R1]] =
			VM->memory.w[VM->registers.R[VM->RC.CRRR.R2]] * VM->memory.w[VM->registers.R[VM->RC.CRRR.R3]];

		return 1;
	}
};
class CmdDIV : public Command
{
public:
	CmdDIV(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->memory.w[VM->registers.R[VM->RC.CRRR.R1]] =
			VM->memory.w[VM->registers.R[VM->RC.CRRR.R2]] / VM->memory.w[VM->registers.R[VM->RC.CRRR.R3]];

		return 1;
	}
};
class CmdMOD : public Command
{
public:
	CmdMOD(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->memory.w[VM->registers.R[VM->RC.CRRR.R1]] =
			VM->memory.w[VM->registers.R[VM->RC.CRRR.R2]] % VM->memory.w[VM->registers.R[VM->RC.CRRR.R3]];

		return 1;
	}
};
class CmdCMP : public Command
{
public:
	CmdCMP(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->clearFlags();
		if (VM->memory.w[VM->registers.R[VM->RC.CRRR.R2]] > VM->memory.w[VM->registers.R[VM->RC.CRRR.R3]])
			VM->registers.PSW.AF = 1;
		else if (VM->memory.w[VM->registers.R[VM->RC.CRRR.R2]] < VM->memory.w[VM->registers.R[VM->RC.CRRR.R3]])
			VM->registers.PSW.BF = 1;
		else
			VM->registers.PSW.EF = 1;

		if (VM->memory.w[VM->registers.R[VM->RC.CRRR.R2]] == 0)
			VM->registers.PSW.ZF = 1;

		return 1;
	}
};
class CmdINC : public Command
{
public:
	CmdINC(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		++VM->memory.w[VM->registers.R[VM->RC.CR.R]];
		return 1;
	}
};
class CmdDEC : public Command
{
public:
	CmdDEC(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		--VM->memory.w[VM->registers.R[VM->RC.CR.R]];
		return 1;
	}
};
class CmdABS : public Command
{
public:
	CmdABS(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		if (VM->memory.w[VM->registers.R[VM->RC.CR.R]] < 0)
			VM->memory.w[VM->registers.R[VM->RC.CR.R]] = -VM->memory.w[VM->registers.R[VM->RC.CR.R]];
		return 1;
	}
};
class CmdNEG : public Command
{
public:
	CmdNEG(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->memory.w[VM->registers.R[VM->RC.CR.R]] = -VM->memory.w[VM->registers.R[VM->RC.CR.R]];
		return 1;
	}
};
class CmdIOUT : public Command
{
public:
	CmdIOUT(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		std::cout << VM->memory.w[VM->registers.R[VM->RC.CR.R]];
		return 1;
	}
};
class CmdIIN : public Command
{
public:
	CmdIIN(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		std::cin >> VM->memory.w[VM->registers.R[VM->RC.CR.R]];
		return 1;
	}
};
#pragma endregion
