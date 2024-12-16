#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"
using namespace std;

namespace Log { // ������ � ����������
	struct LOG { // ��������
		wchar_t logfile[PARM_MAX_SIZE]; // ��� ����� ���������
		ofstream* stream; // �������� �����
	};

	static const LOG INITLOG{ L"", NULL };
	LOG getlog(wchar_t logfile[]); // ��� �������� � �������� ���������� ������ ���������
	void WriteLine(LOG log, char* c, ...); // ������ ������ � ��������
	void WriteLine(LOG log, wchar_t* c, ...); // ������ ������ � ��������
	void WriteLog(LOG log); // ������ ��������� � ��������
	void WriteParm(LOG log, Parm::PARm parm); // ������ ���������� � ������� ����������
	void WriteIn(LOG log, In::iN in); // ������ � ���������� �����
	void WriteError(LOG log, Error::ERROr error); // ����� ���������� �� ������
	void Close(LOG log); // �������� ������ ��� ������
}