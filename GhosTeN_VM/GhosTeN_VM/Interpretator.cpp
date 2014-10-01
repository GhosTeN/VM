#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
#include "Computer.h"

// загрузчик - текстового - формата------------------ -
bool loaderTXT(const char *filename, Computer &VM)
{
	uWord loadaddr = 0;			// адрес загрузки
	uWord indexByte = 0;
	ifstream binary(filename);			// файл с программой
	if (binary.is_open()){					// если файл открылс€
		uWord startIndex = 0;
		uWord currentIndex = 0;
		string code;							// введенна€ строка
		uWord bincode = 0;				// байт из строки
		Address ip = 0;						// адрес запуска программы
		istringstream in;						// перевод символьного байта в числовой
		getline(binary, code);				// ввод адреса загрузки
		in.str(code); in >> hex >> startIndex; // перевели стартовый адрес

		getline(binary, code);    			// ввод кода
		while (!binary.eof())
		{
			cout << setfill('0');
			cout << endl;
			if (startIndex == currentIndex)
				VM.setIP(loadaddr);

			in.str(code);
			in.clear();	    // инициализаци€ строкового потока
			
			while ((in >> hex >> bincode)) // чтение побайтное
			{
				// запись в пам€ть
					VM.memory.b[indexByte] = static_cast<uByte>(bincode);
					++indexByte;
			}
			//добор
			while ((indexByte % 4) != 0)
			{
				bincode = 0;
				VM.memory.b[indexByte] = static_cast<uByte>(bincode);
				++indexByte;
			}
			++loadaddr;
			getline(binary, code);			// ввод кода
			++currentIndex;
		} // while
		// последн€€ строка уже была прочитана
		in.clear();  in.str(code.substr(1));  in >> hex >> ip;
		return true;
	}
	else
	{
		cout << filename << " - not open!" << endl;		// файл не открылс€!
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