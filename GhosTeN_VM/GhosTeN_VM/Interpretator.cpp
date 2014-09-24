#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
#include "Computer.h"

// ��������� - ���������� - �������------------------ -
bool loaderTXT(const char *filename, Computer &VM)
{
	uWord loadaddr = 0;			// ����� ��������
	ifstream binary(filename);			// ���� � ����������
	if (binary.is_open()){					// ���� ���� ��������
		uWord startIndex = 0;
		uWord currentIndex = 0;
		string code;							// ��������� ������
		uWord bincode = 0;				// ���� �� ������
		Address ip = 0;						// ����� ������� ���������
		istringstream in;						// ������� ����������� ����� � ��������
		getline(binary, code);				// ���� ������ ��������
		in.str(code); in >> hex >> startIndex; // �������� ��������� �����

		/*if (code[0] != 's')					// ��� ������ �� ��������� �������
		{
		cout << "No load address" << endl; return false;
		}
		else									// ������� ���������� ������
		{
		code = code.substr(1);				// �������� ��� ������ s

		//cout << setw(4) << hex << bincode << endl;
		loadaddr = bincode;
		}*/

		getline(binary, code);    			// ���� ����
		while (!binary.eof())
		{
			cout << setfill('0');
			cout << endl;
			if (startIndex == currentIndex)
				VM.setIP(loadaddr);

			in.str(code);
			in.clear();	    // ������������� ���������� ������
			while ((in >> hex >> bincode)) // ������ ���������
			{ //cout << setw(2) << hex << bincode << ' ';
				// ������ � ������
				vector<unsigned char> arrayOfByte(4);
				for (int i = 0; i < 4; i++)
					arrayOfByte[3 - i] = (bincode >> (i * 8));

				for (int i = 0; i < 4; ++i)
				{
					VM.memory.b[loadaddr] = static_cast<uByte>(arrayOfByte[i]);
					++loadaddr;
				}
			}

			getline(binary, code);			// ���� ����
			++currentIndex;
		} // while
		// ��������� ������ ��� ���� ���������
		in.clear();  in.str(code.substr(1));  in >> hex >> ip;
		return true;
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

		if (yes)
			VM.interpreter(debug);
		else cout << argv[1] << " - not run!" << endl;
#if defined DEBUG
		logfile.close();
#endif
	}
	else cout << "No file in command line!" << endl;
	system("pause");
}