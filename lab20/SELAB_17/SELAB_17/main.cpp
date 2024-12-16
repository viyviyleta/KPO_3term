#include <iostream>
#include <Windows.h>
#include "stdafx.h"
#include <locale>
#include <cwchar>
#include <TCHAR.h>
using namespace std;
int _tmain(int argc, _TCHAR* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Parm::PARm parm;
	Log::LOG log;
	Out::OUt out;
	try
	{
		parm = Parm::getparm(argc, argv);
		log = Log::INITLOG;
		out = Out::INITOUT;
		out = Out::getout(parm.out);
		log = Log::getlog(parm.log);
		In::iN in_result = In::getin(parm.in);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Out::WriteOut(in_result, out.outfile);
		Log::WriteIn(log, in_result);
		LexA::LEX LEX = LexA::LexA(parm, in_result);

		MFST_TRACE_START				
			MFST::Mfst mfst(LEX.lexTable, GRB::getGreibach());			
		mfst.start();											

		mfst.savededucation();									

		mfst.printrules();

		for (int i = 0; i < LEX.lexTable.size; i++) {
			if (LEX.lexTable.table[i].lexema[0] == LEX_EQUAL) {
				if (PN::PolishNotation(i + 1, LEX.lexTable, LEX.idTable)) {
					cout << LEX.lexTable.table[i].sn << ": польская запись построена\n";
				}
				else {
					cout << LEX.lexTable.table[i].sn << ": польская запись не построена\n";
				}
			}
		}

		LT::WriteInFile(LEX.lexTable);

		Log::Close(log);
		Out::Close(out);
	}
	catch (Error::ERROr e)
	{
		cout << "Ошибка" << e.id << ':' << e.message << endl << endl;
		if (e.inext.line > 0)
		{
			Log::WriteError(log, e);
			Out::WriteError(out, e);
			Log::Close(log);
			Out::Close(out);
		}
	}

	return 0;
}