#pragma once
#pragma once
#include "stdafx.h"
namespace FST
{
	struct RELATION // Ребро: символ -> вершина графа КА
	{
		char symbol; // Символ перехода
		short nnode; // Смежная вершина

		RELATION(
			unsigned char c = 'a', // Символ перехода
			short nn = 0 // Новое состояние
		);
	};


	struct NODE // Вершина графа переходов
	{
		short n_relation; // Количество инцидентных рёбер
		RELATION* relations;

		NODE();
		NODE(short n, RELATION rel, ...);
	};

	struct FST // Недетерминированный КА
	{
		std::string string; // Цепочка (строка)
		short position; // Текущая позиция в цепочке
		short nstates; // Количество состояний автомата
		NODE* nodes; // Граф переходов [0] - начальное, [nstate-1] - конечное
		short* rstates; // Возможные состояния автомата на данной позиции

		FST(
			std::string s, // Цепочка (строка)
			short ns, // Количество состояний автомата
			NODE n, ... // Граф переходов [0] - начальное, [nstate-1] - конечное
		);
	};

	bool execute(FST& fst);
	void WriteError(Error::ERROR e);

}

