#include "Out.h"
#include "stdafx.h"
#pragma warning(disable:4996)

namespace Out {
	OUt getout(wchar_t outfile[]) { // �������� � �������� ���������� ������ ��������� �����
		OUt out;
		out.stream = new ofstream; // ������� ����� ����� ��� ������
		out.stream->open(outfile); // ��������� ����� �� ����������� �������� �����
		if (!out.stream->is_open()) { // ���� �� ��������
			throw ERROR_THROW(113); // �������� ����������
		}
		wcscpy_s(out.outfile, outfile); // �������� �������� ����� 
		return out;
	}
	void WriteOut(In::iN in, wchar_t outfile[]) { // ������� ��� ������ ���������������� ������ � ����
		ofstream fout(outfile);
		fout << in.text;
		fout.close();
	}
	void WriteError(OUt out, Error::ERROr er) { // ����� ���������� �� ������
		if (out.stream) { // ���� ������ ����� ��� ������
			*out.stream << "������ " << er.id << ": " << er.message; // ������� ��������� �� ������
			if (er.inext.line != -1) { // ���� ������� ���������� � ����� ������, �� ������� � ��� ����������
				*out.stream << ", ������ " << er.inext.line << ", ������� " << er.inext.col << '\n';
			}
			else {
				*out.stream << '\n';
			}
		}
		else { // ���� ����� �� ������, �� ������� ���������� � �������
			cout << "������ " << er.id << ": " << er.message << '\n';
			cout << "������ " << er.inext.line << ", ������� " << er.inext.col << '\n';
		}
	}
	void Close(OUt out) { // ��������� �����
		out.stream->close();
		delete out.stream;
	}
}