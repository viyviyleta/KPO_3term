#pragma once
#include <cstddef>
namespace FST {

	struct RELATION { //ребро:символ -> вершина графа переходов КА
		char symbol; //символ перехода
		short nnode; //номер смежной вершины
		RELATION(
			char c = 0x00, //символ перехода
			short ns = NULL //новое состояние 
		);
	};

	struct NODE { //вершина графа переходов 
		short n_relation; //кол-во инцидентных ребер
		RELATION  *relations; //инцидентные ребра
		NODE();
		NODE(
			short n, //кол-во инцидентых ребер
			RELATION rel, ... //список ребер
		);
	};
	struct FST { //недетерминированный конечный автомат
		const char* strin;                             // цепочка
		short position;                                //текущая позиция в цепочке
		short nstates;                                 //кол-во состояний автомата
		NODE* nodes;                                   //граф переходов: [0] - начальное состояние, [nstate-1] - конечное
		short* rstates;                                // возможные состояние автомата на данной позиции
		FST(
			const char* s,                             //цепочка
			short ns,                                  //кол-во состояний автомата 
			NODE n, ...                                //список состояний (граф переходов)
		);
	};
	bool execute(                                      //выполнить распознавание цепочки
		FST& fst                                       //недетерминированный КА
	);
}