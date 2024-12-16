#pragma once
#include <map>
#define ID_MAXSIZE 6 // ������������ ���������� �������� � ��������������
#define TI_MAXSIZE 4096 // ������������ ���������� ����� � �������
#define TI_INT_DEFAULT 0x00000000 // �������� �� ��������� ��� integer
#define TI_STR_DEFAULT 0x00 // �������� �� ��������� ��� string
#define TI_NULLIDX 0xffffffff // ��� �������� � ������� ���������������
#define TI_STR_MAXSIZE 255 

namespace IT { // ������� ���������������
	enum IDDATATYPE {INT = 1, STR = 2}; // ��� ������ ���������������
	enum IDTYPE {V = 1, F = 2, P = 3, L = 4}; // ��� ���������������: ����������, �������, ��������, �������
	struct Entry		
	{
		int			idxfirstLE;			
		char		id[ID_MAXSIZE];	
		IDDATATYPE	iddatatype;	
		IDTYPE		idtype;			
		string scope_name;
		union
		{
			int		vint;				
			struct
			{
				int len;						
				char str[TI_STR_MAXSIZE - 1];	
			}	vstr[TI_STR_MAXSIZE];			
		} value;	
	};

	struct IdTable { // ��������� ������� ���������������
		int maxsize; // ������� ������ ��������������� < TI_MAXSIZE
		int size; // ������� ������ ������� ��������������� < maxsize
		Entry* table; // ������ ����� � ������� ���������������
	};
	IdTable Create(int size); // ������� ������� ���������������
	void Add(IdTable& idtable, Entry entry); // �������� ������ � ������� ��������������� 
	int search(IdTable& idtable, IT::Entry entry, map<string, string> scop);
	int search(IdTable& idtable, IT::Entry entry);
	Entry GetEntry(IdTable& idtable, int n); // �������� ������ �� ������� ���������������
	void Delete(IdTable& idtable); // ������� ������� ���������������
}