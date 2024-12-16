#pragma once
#include "Error.h"
#define GRB_ERROR_SERIES 600
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)
typedef short GRBALPHABET; // ������ �������� ����������
namespace GRB {
	struct Rule { // ��������� ������� � ���������� �������
		GRBALPHABET nn; // �������������� ������(����� ������ ������)
		int iderror; // ������������� ���������������� ���������
		short size; // ���������� ������� - ������ ������ �������
		struct Chain { // ��������� �������
			short size; // ����� �������
			GRBALPHABET* nt; // ������� ��������
			Chain() { this->size = 0; this->nt = 0;}
			Chain(short size, GRBALPHABET s, ...);
			char* getCChain(char* b); // �������� ������ ������� �������
			static GRBALPHABET T(char t) { return GRBALPHABET(t);}; // ��������
			static GRBALPHABET N(char n) { return -GRBALPHABET(n);}; // ����������
			static bool isT(GRBALPHABET s) { return s > 0; }
			static bool isN(GRBALPHABET s) { return !isT(s); }
			static char alphabet_to_char(GRBALPHABET s) { return isT(s) ? char(s) : char(-s); }; // �������������� � char 
		} *chains;
		Rule() { this->nn = 0x00; this->size = 0; }
		Rule(GRBALPHABET pnn, int iderror, short psize, Chain c, ...);
		char* getCRule(char* b, short nchain); // �������� ������� � ���� N-> �������
		short getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j); // �������� ��������� �������
	};

	struct Greibach { // ���������� �������
		short size; // ���������� ������
		GRBALPHABET startN; // ��������� ������
		GRBALPHABET stbottomT; // ��� �����
		Rule* rules; // ��������� ������
		Greibach() { this->size = 0; this->startN = 0; this->stbottomT = 0; this->rules = 0; };
		Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...);
		short getRule(GRBALPHABET pnn, Rule& prule); 
		Rule getRule(short n);// �������� ������� �� ������
	};
	Greibach getGreibach(); // �������� ����������
}