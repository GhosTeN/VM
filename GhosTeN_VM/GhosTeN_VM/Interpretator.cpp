#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;
#include "Computer.h"


// ��������� - ���������� - �������------------------ -
bool loaderTXT(const char *filename, Computer &VM)
{
	unsigned int loadaddr = 0;			// ����� ��������
	ifstream binary(filename);			// ���� � ����������
	if (binary.is_open()){					// ���� ���� ��������
		string code;							// ��������� ������
		unsigned int bincode = 0;				// ���� �� ������
		Address ip = 0;						// ����� ������� ���������
		istringstream in;						// ������� ����������� ����� � ��������
		getline(binary, code);				// ���� ������ ��������
		if (code[0] != 's')					// ��� ������ �� ��������� �������
		{
			cout << "No load address" << endl; return false;
		}
		else									// ������� ���������� ������
		{
			code = code.substr(1);				// �������� ��� ������ s
			in.str(code); in >> hex >> bincode; // �������� ��������� �����
			//cout << setw(4) << hex << bincode << endl;
			loadaddr = bincode;
		}
		
		getline(binary, code);    			// ���� ����
		while (!binary.eof())
		{
			cout << setfill('0');
			cout << endl;
			if (code[0] != 'e')             // ����� ����� 
			{
				code = code.substr(1);        // �������� ��� ������ k
				in.str(code);	in.clear();	    // ������������� ���������� ������
				while ((in >> hex >> bincode)) // ������ ���������
				{ //cout << setw(2) << hex << bincode << ' '; 
					// ������ � ������
					VM.memory.b[loadaddr] = static_cast<uByte>(bincode);
					++loadaddr;
				} // while
			} // if
			else break;
			getline(binary, code);			// ���� ����
		} // while
		// ��������� ������ ��� ���� ��������� 
		in.clear();  in.str(code.substr(1));  in >> hex >> ip;
		VM.setIP(ip % 0x10000);  return true;
	}
	else
	{
		cout << filename << " - not open!" << endl;		// ���� �� ��������!
		return false;
	}
} // loader

int main(int argc, char *argv[])
{
	bool debug = false;
	if (argc > 1)
	{
		Computer VM;
		VM.reset(true);
#if defined DEBUG
		string nameLog = getNameLog(argv[1]);
		ofstream logfile(nameLog.c_str());
#endif
		bool yes = false;
		yes = loaderTXT(argv[1], VM);

		if (yes) VM.interpreter(debug);
		else cout << argv[1] << " - not run!" << endl;
#if defined DEBUG	 
		logfile.close();
#endif
	}
	else cout << "No file in command line!" << endl;
	system("pause");
}