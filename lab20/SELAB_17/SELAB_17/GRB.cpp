#include "GRB.h"
#include"Rules.h"
#include "string.h"

namespace GRB {
	Rule::Chain::Chain(short psize, GRBALPHABET s, ...) {
		this->nt = new GRBALPHABET[this->size = psize];
		int* p = (int*)&s;
		for (short i = 0; i < psize; ++i) this->nt[i] = (GRBALPHABET)p[i];
	};

	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...) {
		this->nn = pnn;
		this->iderror = piderror;
		this->chains = new Chain[size = psize];
		Chain* p = &c;
		for (int i = 0; i < size; i++) this->chains[i] = p[i];
	};

	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...) {
		this->startN = pstartN;
		this->stbottomT = pstbottom;
		this->rules = new Rule[this->size = psize];
		Rule* p = &r;
		for (int i = 0; i < size; i++) this->rules[i] = p[i];
	}

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule) {
		short rc = -1;
		short k = 0;
		while (k < this->size && rules[k].nn != pnn) k++;
		if (k < this->size) prule = rules[rc = k];
		return rc;
	}

	Rule Greibach::getRule(short n) {
		Rule rc;
		if (n < this->size) rc = rules[n];
		return rc;
	};

	char* Rule::getCRule(char* b, short nchain) {
		char bchain[200];
		b[0] = Chain::alphabet_to_char(this->nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		this->chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	}

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j) {
		short rc = -1;
		while (j < this->size && this->chains[j].nt[0] != t) ++j;
		rc = (j < this->size ? j : -1);
		if (rc >= 0) pchain = chains[rc];
		return rc;
	};

	char* Rule::Chain::getCChain(char* b) {
		for (int i = 0; i < this->size; i++) b[i] = Chain::alphabet_to_char(this->nt[i]);
		b[this->size] = '\0';
		return b;
	};

	Greibach getGreibach() {
		return greibach;
	}
}