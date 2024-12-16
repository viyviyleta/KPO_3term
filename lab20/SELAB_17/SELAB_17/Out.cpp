#include "Out.h"
#include "stdafx.h"
#pragma warning(disable:4996)

namespace Out {
	OUt getout(wchar_t outfile[]) { // создание и открытие потокового вывода выходного файла
		OUt out;
		out.stream = new ofstream; // создаем новый поток для записи
		out.stream->open(outfile); // открываем поток по переданному названию файла
		if (!out.stream->is_open()) { // если не открылся
			throw ERROR_THROW(113); // вызываем исключение
		}
		wcscpy_s(out.outfile, outfile); // копируем название файла 
		return out;
	}
	void WriteOut(In::iN in, wchar_t outfile[]) { // функция для вывода преобразованного текста в файл
		ofstream fout(outfile);
		fout << in.text;
		fout.close();
	}
	void WriteError(OUt out, Error::ERROr er) { // вывод информации об ошибке
		if (out.stream) { // если открыт поток для записи
			*out.stream << "Ошибка " << er.id << ": " << er.message; // выводим сообщение об ошибке
			if (er.inext.line != -1) { // если имеется информации о месте ошибке, то выводим и эту информацию
				*out.stream << ", строка " << er.inext.line << ", позиция " << er.inext.col << '\n';
			}
			else {
				*out.stream << '\n';
			}
		}
		else { // если поток не открыт, то выводим информацию в консоль
			cout << "Ошибка " << er.id << ": " << er.message << '\n';
			cout << "Строка " << er.inext.line << ", позиция " << er.inext.col << '\n';
		}
	}
	void Close(OUt out) { // закрываем поток
		out.stream->close();
		delete out.stream;
	}
}