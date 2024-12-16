#include "Log.h"
#include "stdafx.h"
#include <time.h>
#pragma warning(disable:4996)

namespace Log {
	LOG getlog(wchar_t logfile[]) { // �������� � �������� ���������� ������ ���������
		LOG log;
		log.stream = new ofstream; // ������� ����� ����� ��� ������
		log.stream->open(logfile); // ��������� ����� �� ����������� �������� �����
		if (!log.stream->is_open()) { // ���� �� ��������
			throw ERROR_THROW(112); // �������� ����������
		}
		wcscpy_s(log.logfile, logfile); // �������� �������� ����� 
		return log;
	}
	void WriteLine(LOG log, char* c, ...) { // ������������ ��� ������ ������ � ��������
		char** p = &c; // ������� ��������� ��� ��������� ������������ ����� �����
		int j = 0; // �������
		while (p[j] != "") { // ���� �� ����������� ������ ������
			*log.stream << p[j++]; // ���������� ������� � log � ��������� �� ��������� 
		}
	}
	void WriteLine(LOG log, wchar_t* c, ...) { // ����, ��� � ���������� �������, ��, ���� ��������� wchar_t*
		wchar_t** p = &c;
		char buf[50];
		int j = 0;
		while (p[j] != L"") {
			wcstombs(buf, p[j++], 50); // �������������� wchar_t* � char*
			*log.stream << buf;
		}
	}
	void WriteLog(LOG log) { // ������� ��� ������ ��������� � log
		char buf[50]; // �������� ����������
		time_t curtime; // ���������� ��� �������
		curtime = time(NULL); // ������� �����
		tm localtime; // ��������� ��� �������
		localtime_s(&localtime, &curtime); // ����� � time_t ���������� � ��������� tm
		strftime(buf, 50, "%Y.%m.%d %H:%M:%S", &localtime); // ����������� ���� � ����� � ������ �� ��������� �������
		*log.stream << "---- �������� ---- " << buf << " ----------" << '\n';
	}
	void WriteParm(LOG log, Parm::PARm parm) { // ������� ��� ������ ���������� � �������� ����������
		*log.stream << "---- ��������� ----" << '\n';
		char buf[PARM_MAX_SIZE]; // �������� ����������
		wcstombs(buf, parm.log, PARM_MAX_SIZE);  // �������������� wchar_t* � char*
		*log.stream << "-log: " << buf << '\n'; // ���������� ��� log
		wcstombs(buf, parm.out, PARM_MAX_SIZE); // �������������� wchar_t* � char*
		*log.stream << "-out: " << buf << '\n'; // ���������� ��� out
		wcstombs(buf, parm.in, PARM_MAX_SIZE); // �������������� wchar_t* � char*
		*log.stream << "-in: " << buf << '\n'; // ���������� ��� in
	}
	void WriteIn(LOG log, In::iN in) { // ����� ���������� � ������ � �����
		*log.stream << "---- �������� ������ ----" << '\n';
		*log.stream << "���������� ��������: " << in.size << '\n';
		*log.stream << "���������������    :" << in.ignore << '\n';
		*log.stream << "���������� �����   :" << in.lines << '\n';
	}
	void WriteError(LOG log, Error::ERROr er) { // ����� ���������� �� ������
		if (log.stream) { // ���� ������ ����� ��� ������
			*log.stream << "������ " << er.id << ": " << er.message; // ������� ��������� �� ������
			if (er.inext.line != -1) { // ���� ������� ���������� � ����� ������, �� ������� � ��� ����������
				*log.stream << ", ������ " << er.inext.line << ", ������� " << er.inext.col << '\n';
			}
			else {
				*log.stream << '\n';
			}
		}
		else { // ���� ����� �� ������, �� ������� ���������� � �������
			cout << "������ " << er.id << ": " << er.message << '\n';
			cout << "������ " << er.inext.line << ", ������� " << er.inext.col << '\n';
		}
	}
	void Close(LOG log) { // ��������� �����
		log.stream->close();
		delete log.stream;
	}
}