#pragma once
#pragma once
#include "stdafx.h"
namespace FST
{
	struct RELATION // �����: ������ -> ������� ����� ��
	{
		char symbol; // ������ ��������
		short nnode; // ������� �������

		RELATION(
			unsigned char c = 'a', // ������ ��������
			short nn = 0 // ����� ���������
		);
	};


	struct NODE // ������� ����� ���������
	{
		short n_relation; // ���������� ����������� ����
		RELATION* relations;

		NODE();
		NODE(short n, RELATION rel, ...);
	};

	struct FST // ������������������� ��
	{
		std::string string; // ������� (������)
		short position; // ������� ������� � �������
		short nstates; // ���������� ��������� ��������
		NODE* nodes; // ���� ��������� [0] - ���������, [nstate-1] - ��������
		short* rstates; // ��������� ��������� �������� �� ������ �������

		FST(
			std::string s, // ������� (������)
			short ns, // ���������� ��������� ��������
			NODE n, ... // ���� ��������� [0] - ���������, [nstate-1] - ��������
		);
	};

	bool execute(FST& fst);
	void WriteError(Error::ERROR e);

}

