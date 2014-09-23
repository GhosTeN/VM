#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;
#include "Computer.h"


// загрузчик - текстового - формата------------------ -
bool loaderTXT(const char *filename, Computer &VM)
{
	unsigned int loadaddr = 0;			// адрес загрузки
	ifstream binary(filename);			// файл с программой
	if (binary.is_open()){					// если файл открылся
		string code;							// введенная строка
		unsigned int bincode = 0;				// байт из строки
		Address ip = 0;						// адрес запуска программы
		istringstream in;						// перевод символьного байта в числовой
		getline(binary, code);				// ввод адреса загрузки
		if (code[0] != 's')					// нет записи со стартовым адресом
		{
			cout << "No load address" << endl; return false;
		}
		else									// перевод стартового адреса
		{
			code = code.substr(1);				// отрезали тип записи s
			in.str(code); in >> hex >> bincode; // перевели стартовый адрес
			//cout << setw(4) << hex << bincode << endl;
			loadaddr = bincode;
		}
		
		getline(binary, code);    			// ввод кода
		while (!binary.eof())
		{
			cout << setfill('0');
			cout << endl;
			if (code[0] != 'e')             // Конец кодов 
			{
				code = code.substr(1);        // отрезали тип записи k
				in.str(code);	in.clear();	    // инициализация строкового потока
				while ((in >> hex >> bincode)) // чтение побайтное
				{ //cout << setw(2) << hex << bincode << ' '; 
					// запись в память
					VM.memory.b[loadaddr] = static_cast<uByte>(bincode);
					++loadaddr;
				} // while
			} // if
			else break;
			getline(binary, code);			// ввод кода
		} // while
		// последняя строка уже была прочитана 
		in.clear();  in.str(code.substr(1));  in >> hex >> ip;
		VM.setIP(ip % 0x10000);  return true;
	}
	else
	{
		cout << filename << " - not open!" << endl;		// файл не открылся!
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