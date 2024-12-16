#pragma once
#include "Error.h"
#define GRB_ERROR_SERIES 600
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)
typedef short GRBALPHABET; // символ алфавита грамматики
namespace GRB {
	struct Rule { // структура правила в грамматике Грейбах
		GRBALPHABET nn; // нетерминальный символ(самый первый символ)
		int iderror; // идентификатор диагностического сообщения
		short size; // количество цепочек - правых частей правила
		struct Chain { // структура цепочки
			short size; // длина цепочки
			GRBALPHABET* nt; // цепочка символов
			Chain() { this->size = 0; this->nt = 0;}
			Chain(short size, GRBALPHABET s, ...);
			char* getCChain(char* b); // получить правую сторону правила
			static GRBALPHABET T(char t) { return GRBALPHABET(t);}; // терминал
			static GRBALPHABET N(char n) { return -GRBALPHABET(n);}; // нетерминал
			static bool isT(GRBALPHABET s) { return s > 0; }
			static bool isN(GRBALPHABET s) { return !isT(s); }
			static char alphabet_to_char(GRBALPHABET s) { return isT(s) ? char(s) : char(-s); }; // преобразование к char 
		} *chains;
		Rule() { this->nn = 0x00; this->size = 0; }
		Rule(GRBALPHABET pnn, int iderror, short psize, Chain c, ...);
		char* getCRule(char* b, short nchain); // получить правило в виде N-> цепочка
		short getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j); // получить следующую цепочку
	};

	struct Greibach { // грамматика Грейбах
		short size; // количество правил
		GRBALPHABET startN; // стартовый символ
		GRBALPHABET stbottomT; // дно стека
		Rule* rules; // множество правил
		Greibach() { this->size = 0; this->startN = 0; this->stbottomT = 0; this->rules = 0; };
		Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...);
		short getRule(GRBALPHABET pnn, Rule& prule); 
		Rule getRule(short n);// получить правило по номеру
	};
	Greibach getGreibach(); // получить грамматику
}