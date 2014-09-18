#include "Computer.h"
Computer::Computer()
{
	
}
int Computer::reset(bool debug)
{
	registers.PSW.IP = registers.RI = 0;
	// ������� ���� ������
	// registers.SP = mKw * 1024;			// �� ��������� ������� �����			
	registers.PSW.CF = registers.PSW.OF = registers.PSW.OV = registers.PSW.UV = 0;
	if (debug) registers.PSW.TF = 1; else registers.PSW.TF = 0;
	for (int i = 0; i < 64; ++i) registers.RON.w[i] = 0;
	return 0;
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
		Clear(); jumping = false;
		if (registers.PSW.IP & 0x00000001u) throw "error!";
		// ������� 2 ������
		RC.rc[0] = memory.b[registers.PSW.IP]; RC.rc[1] = memory.b[registers.PSW.IP + 1];
		// ���������� ����� �������
		if (RC.Code < 0xFF)				// �������� ����� ������
		{
			nByte = Cmd[RC.Code].Length;
		}
		else            			// ������� ���������
		{
			nByte = ffCmd[RC.FF.Code].Length;
		}
		// �������� �� ������ �����
		for (int i = 2; i < nByte; ++i) RC.rc[i] = memory.b[registers.PSW.IP + i];
		if (registers.PSW.TF) Trace();       // ���������� ������
		// ���������� ������� - ��������� ����� �� ���������
		// ��� �������� - ������ � ������� �������
		if (RC.Code < 0xFF)	stoping = Cmd[RC.Code].function(*this);
		else                stoping = ffCmd[RC.FF.Code].function(*this);
		// ���� �� ������� ��������
		if (!jumping) registers.PSW.IP += nByte;					// ��������� PC
	}
	return 0;
}
void Computer::Trace()                   // ����������� �����������
{
	cout << setfill('0');
	cout << setw(5) << dec << registers.PSW.IP << ": ";
	int nByte = 0;
	if (RC.Code < 0xFF)				// �������� ����� ������
		nByte = Cmd[RC.Code].Length;
	else                      			// ������� ���������
		nByte = ffCmd[RC.FF.Code].Length;
	for (int i = 0; i < nByte; ++i)
		cout << setw(2) << hex << int(RC.rc[i]) << ' ';
	cout << endl;
}