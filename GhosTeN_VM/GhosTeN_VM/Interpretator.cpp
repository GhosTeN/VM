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
	uWord indexByte = 0;
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
			{
				// ������ � ������
					VM.memory.b[indexByte] = static_cast<uByte>(bincode);
					++indexByte;
			}
			//�����
			while ((indexByte % 4) != 0)
			{
				bincode = 0;
				VM.memory.b[indexByte] = static_cast<uByte>(bincode);
				++indexByte;
			}
			++loadaddr;
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