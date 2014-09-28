#pragma once
#include <iostream>
#include <cmath>
#include "Types.h"
#include "Computer.h"

class Command
{
protected:
	Computer* VM;
public:
	Command(Computer& VMM)
	{
		this->VM = &VMM;
	}
	virtual int operator()(){ return 0; }
};

class CmdLDC : public Command
{
public:

	CmdLDC(Computer& VM) : Command(VM){}

	virtual int operator()()
	{
		VM->registers.R[VM->RC.CRaC.R] = VM->RC.CRaC.aC;
		return 1;
	}
};
class CmdSTOP : public Command
{
public:

	CmdSTOP(Computer& VM) : Command(VM){  }
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
		if (VM->registers.PSW.ZF != 1)
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
		return 2;
	}
};
class CmdJMPR : public Command
{
public:
	CmdJMPR(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->setIP(VM->memory.w[VM->registers.R[VM->RC.CR.R]]);
		return 2;
	}
};
class CmdJMPRR : public Command
{
public:
	CmdJMPRR(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->setIP(VM->memory.w[VM->registers.R[VM->RC.CRR.R1]] + VM->memory.w[VM->registers.R[VM->RC.CRR.R2]]);
		return 2;
	}
};

class CmdJMPO : public Command
{
public:
	CmdJMPO(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		int sdivg = VM->RC.CRaC.aC;
		if (VM->RC.CRaC.R > 0)
			VM->registers.PSW.IP += sdivg;
		else
			VM->registers.PSW.IP -= sdivg;
		return 2;
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
		return 2;
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

#pragma region UNSIGNED INTEGER
class CmdUADD : public Command
{
public:
	CmdUADD(Computer& VM) : Command(VM){  }
	virtual int operator()()
	{
		VM->memory.uw[VM->registers.R[VM->RC.CRRR.R1]] =
			VM->memory.uw[VM->registers.R[VM->RC.CRRR.R2]] + VM->memory.uw[VM->registers.R[VM->RC.CRRR.R3]];
		return 1;
	}
};
class CmdUSUB : public Command
{
public:
	CmdUSUB(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->memory.uw[VM->registers.R[VM->RC.CRRR.R1]] =
			VM->memory.uw[VM->registers.R[VM->RC.CRRR.R2]] - VM->memory.uw[VM->registers.R[VM->RC.CRRR.R3]];

		return 1;
	}
};
class CmdUMUL : public Command
{
public:
	CmdUMUL(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->memory.uw[VM->registers.R[VM->RC.CRRR.R1]] =
			VM->memory.uw[VM->registers.R[VM->RC.CRRR.R2]] * VM->memory.uw[VM->registers.R[VM->RC.CRRR.R3]];

		return 1;
	}
};
class CmdUDIV : public Command
{
public:
	CmdUDIV(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->memory.uw[VM->registers.R[VM->RC.CRRR.R1]] =
			VM->memory.uw[VM->registers.R[VM->RC.CRRR.R2]] / VM->memory.uw[VM->registers.R[VM->RC.CRRR.R3]];

		return 1;
	}
};
class CmdUMOD : public Command
{
public:
	CmdUMOD(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->memory.uw[VM->registers.R[VM->RC.CRRR.R1]] =
			VM->memory.uw[VM->registers.R[VM->RC.CRRR.R2]] % VM->memory.uw[VM->registers.R[VM->RC.CRRR.R3]];

		return 1;
	}
};
class CmdUCMP : public Command
{
public:
	CmdUCMP(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->clearFlags();
		if (VM->memory.uw[VM->registers.R[VM->RC.CRR.R1]] > VM->memory.uw[VM->registers.R[VM->RC.CRR.R1]])
			VM->registers.PSW.AF = 1;
		else if (VM->memory.uw[VM->registers.R[VM->RC.CRR.R1]] < VM->memory.uw[VM->registers.R[VM->RC.CRR.R2]])
			VM->registers.PSW.BF = 1;
		else
			VM->registers.PSW.EF = 1;

		if (VM->memory.uw[VM->registers.R[VM->RC.CRR.R1]] == 0)
			VM->registers.PSW.ZF = 1;

		return 1;
	}
};
class CmdUINC : public Command
{
public:
	CmdUINC(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		++VM->memory.uw[VM->registers.R[VM->RC.CR.R]];
		return 1;
	}
};
class CmdUDEC : public Command
{
public:
	CmdUDEC(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		--VM->memory.uw[VM->registers.R[VM->RC.CR.R]];
		return 1;
	}
};
class CmdUOUT : public Command
{
public:
	CmdUOUT(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		std::cout << dec << VM->memory.uw[VM->registers.R[VM->RC.CR.R]];
		return 1;
	}
};
class CmdUIN : public Command
{
public:
	CmdUIN(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		std::cin >> VM->memory.uw[VM->registers.R[VM->RC.CR.R]];

		return 1;
	}
};
#pragma endregion

#pragma region INTEGER
class CmdADD : public Command
{
public:
	CmdADD(Computer& VM) : Command(VM){  }
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
		if (VM->memory.w[VM->registers.R[VM->RC.CRR.R1]] > VM->memory.w[VM->registers.R[VM->RC.CRR.R1]])
			VM->registers.PSW.AF = 1;
		else if (VM->memory.w[VM->registers.R[VM->RC.CRR.R1]] < VM->memory.w[VM->registers.R[VM->RC.CRR.R2]])
			VM->registers.PSW.BF = 1;
		else
			VM->registers.PSW.EF = 1;

		if (VM->memory.w[VM->registers.R[VM->RC.CRR.R1]] == 0)
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
		std::cout << dec << VM->memory.w[VM->registers.R[VM->RC.CR.R]];
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

#pragma region FLOAT
class CmdFADD : public Command
{
public:
	CmdFADD(Computer& VM) : Command(VM){  }
	virtual int operator()()
	{
		VM->memory.f[VM->registers.R[VM->RC.CRRR.R1]] =
			VM->memory.f[VM->registers.R[VM->RC.CRRR.R2]] + VM->memory.f[VM->registers.R[VM->RC.CRRR.R3]];
		return 1;
	}
};
class CmdFSUB : public Command
{
public:
	CmdFSUB(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->memory.f[VM->registers.R[VM->RC.CRRR.R1]] =
			VM->memory.f[VM->registers.R[VM->RC.CRRR.R2]] - VM->memory.f[VM->registers.R[VM->RC.CRRR.R3]];

		return 1;
	}
};
class CmdFMUL : public Command
{
public:
	CmdFMUL(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->memory.f[VM->registers.R[VM->RC.CRRR.R1]] =
			VM->memory.f[VM->registers.R[VM->RC.CRRR.R2]] * VM->memory.f[VM->registers.R[VM->RC.CRRR.R3]];

		return 1;
	}
};
class CmdFDIV : public Command
{
public:
	CmdFDIV(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->memory.f[VM->registers.R[VM->RC.CRRR.R1]] =
			VM->memory.f[VM->registers.R[VM->RC.CRRR.R2]] / VM->memory.f[VM->registers.R[VM->RC.CRRR.R3]];

		return 1;
	}
};

class CmdFCMP : public Command
{
public:
	CmdFCMP(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->clearFlags();
		if (VM->memory.f[VM->registers.R[VM->RC.CRR.R1]] > VM->memory.f[VM->registers.R[VM->RC.CRR.R1]])
			VM->registers.PSW.AF = 1;
		else if (VM->memory.f[VM->registers.R[VM->RC.CRR.R1]] < VM->memory.f[VM->registers.R[VM->RC.CRR.R2]])
			VM->registers.PSW.BF = 1;
		else if (fabs(VM->memory.f[VM->registers.R[VM->RC.CRR.R1]] - VM->memory.f[VM->registers.R[VM->RC.CRR.R2]]) < 0.0000001)
			VM->registers.PSW.EF = 1;

		if (VM->memory.f[VM->registers.R[VM->RC.CRR.R1]] < 0.0000001)
			VM->registers.PSW.ZF = 1;

		return 1;
	}
};

class CmdFABS : public Command
{
public:
	CmdFABS(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		if (VM->memory.f[VM->registers.R[VM->RC.CR.R]] < 0)
			VM->memory.f[VM->registers.R[VM->RC.CR.R]] = -VM->memory.f[VM->registers.R[VM->RC.CR.R]];

		return 1;
	}
};
class CmdFNEG : public Command
{
public:
	CmdFNEG(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		VM->memory.f[VM->registers.R[VM->RC.CR.R]] = -VM->memory.f[VM->registers.R[VM->RC.CR.R]];
		return 1;
	}
};


class CmdFOUT : public Command
{
public:
	CmdFOUT(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		std::cout << dec << VM->memory.f[VM->registers.R[VM->RC.CR.R]];
		return 1;
	}
};
class CmdFIN : public Command
{
public:
	CmdFIN(Computer& VM) : Command(VM){}
	virtual int operator()()
	{
		std::cin >> VM->memory.f[VM->registers.R[VM->RC.CR.R]];

		return 1;
	}
};
#pragma endregion
