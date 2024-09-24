#include "FST.h"
#include <iostream>
#include < string.h  > 
#include <stdarg.h>

namespace FST
{
	RELATION::RELATION(char c, short ns)
	{
		symbol = c;
		nnode = ns;
	};


	NODE::NODE() { // конструктор для узла по умолчанию
		n_relation = 0;                                    // количество связей
		RELATION* relations = nullptr;           
	}
	NODE::NODE(short n, RELATION re1, ...) { // конструктор для узла с параметрами
		n_relation = n; 
		relations = new RELATION[n]; 

		va_list args;
		va_start(args, re1); 
		relations[0] = re1;

		for (int i = 1; i < n; i++) {
			relations[i] = va_arg(args, RELATION); // Получаем следующий RELATION из списка аргументов
		}

		va_end(args);
	}

	FST::FST(const char* s, short ns, NODE n, ...) { // конструктор конечного автомата
		strin = s;                                            // переданная строка
		nstates = ns;                                         // количество состояний
		nodes = new NODE[ns]; 
		
		va_list args;
		va_start(args, n);
		nodes[0] = n;

		for (int k = 1; k < ns; k++) {
			nodes[k] = va_arg(args, NODE); // Получаем следующий NODE из списка аргументов
		}

		va_end(args);
		rstates = new short[nstates]; 
		memset(rstates, 0xff, sizeof(short) * nstates); 
		rstates[0] = 0; // устанавливаем начальное значение
		position = -1; // задаем текущую позицию
	}

	bool step(FST& fst, short*& rstates)
	{
		bool rc = false;

		std::swap(rstates, fst.rstates);

		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
			{
				// Перебираем все состояния перехода
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
				{
					// Если символ совпадает с симвоолом строки
					if (fst.nodes[i].relations[j].symbol == fst.strin[fst.position])
					{
						// Обновляем состояние автомат -> следующая позиция
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;  // Переход произошел успешно
					}
				}
			}
		}
		return rc;
	}
	bool execute(FST& fst)
	{
		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short) * fst.nstates);

		short lstring = strlen(fst.strin);

		bool rc = true;

		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;  
			rc = step(fst, rstates);  
		}

		delete[] rstates;

		// Возвращаем true
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	}

}