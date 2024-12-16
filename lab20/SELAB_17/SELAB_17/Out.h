#pragma once
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"

using namespace std;

namespace Out {
	struct OUt {
		wchar_t outfile[PARM_MAX_SIZE]; // ��� ��������� �����
		ofstream* stream; // �������� �����
	};

	static const OUt INITOUT{ L"", NULL };
	OUt getout(wchar_t outfile[]); // ��� �������� � �������� ���������� ������ � �������� ����
	void WriteOut(In::iN, wchar_t outfile[]); // ������ ��������� � ��������
	void WriteError(OUt out, Error::ERROr error); // ����� ���������� �� ������
	void Close(OUt out); // �������� ������ ��� ������
}