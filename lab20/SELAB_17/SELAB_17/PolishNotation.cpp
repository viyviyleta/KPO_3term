#include "PolishNotation.h"
#include <queue>
#include <stack>

namespace PN {


	int getPriority(LT::Entry cur_lex)
	{
		switch (cur_lex.lexema[0])
		{
		case LEX_STAR:
			return 3;
		case LEX_DIRSLASH:
			return 3;
		case LEX_PLUS:
			return 2;
		case LEX_MINUS:
			return 2;
		case LEX_COMMA:
			return 1;
		case LEX_LEFTTHESIS:
			return 0;
		case LEX_RIGHTTHESIS:
			return 0;
		default:
			return -1;
		}
	}




	bool Rpn(LT::LexTable lextable, IT::IdTable idtable, int curPos)
	{
		queue<LT::Entry> q; // для хранения выходных лексем
		stack<LT::Entry> s; // для хранения операторов и скобок
		LT::Entry bottom = { '@', LT_TI_NULLIDX, LT_TI_NULLIDX };
		int curpos = curPos; // текущая позиция
		int kolLex = 0; // количество обработанных лексем
		for (curPos; lextable.table[curPos].lexema[0] != LEX_SEMICOLON; curPos++, kolLex++)
		{
			switch (lextable.table[curPos].lexema[0])
			{
			case LEX_ID:
			{
				if (idtable.table[lextable.table[curPos].idxTI].idtype == IT::IDTYPE::F)
				{
					s.push(lextable.table[curPos]); // идентификатор функции помещаем в стек
					continue;
				}
				q.push(lextable.table[curPos]); // помещаем идентификатор в очередь
				continue;
			}
			case LEX_LITERAL:
			{
				q.push(lextable.table[curPos]);// помещаем литерал в очередь
				continue;
			}
			case LEX_LEFTTHESIS:
			{
				s.push(lextable.table[curPos]); // открывающуюся скобку помещаем в стек
				continue;
			}
			case LEX_RIGHTTHESIS: 
			{
				if (!s.empty()) // если стек не пуст
				{
					while (s.top().lexema[0] != LEX_LEFTTHESIS) // пока не встретим открывающуюся скобку
					{
						q.push(s.top()); // помещаем в очередь текущую лексему из стека
						s.pop(); // удаляем элемент с вершины стека
					}
					s.pop(); // удаляем открывающуюся скобку
				}
				else {
					return false;
				}
				continue;
			}
			case LEX_STAR: {
				if (!s.empty()) // если стек не пуст
				{
					// пока приоритет текущего оператора меньше приоритета оператора на вершине или если на вершине стека идентификатор функции
					while (getPriority(lextable.table[curPos]) <= getPriority(s.top()) || idtable.table[s.top().idxTI].idtype == IT::IDTYPE::F)
					{
						q.push(s.top()); // помещаем элемент с вершины стека в очередь
						s.pop(); // удаляем элемент с вершины стека
						if (s.empty()) // если стек стал пустым, то мы выходим с цикла проверки приоритетов
							break;
					}
				}
				s.push(lextable.table[curPos]); // добавляем текущую операцию
				continue;
			}
			case LEX_DIRSLASH: {
				if (!s.empty()) // если стек не пуст
				{
					// пока приоритет текущего оператора меньше приоритета оператора на вершине или если на вершине стека идентификатор функции
					while (getPriority(lextable.table[curPos]) <= getPriority(s.top()) || idtable.table[s.top().idxTI].idtype == IT::IDTYPE::F)
					{
						q.push(s.top());// помещаем элемент с вершины стека в очередь
						s.pop();// удаляем элемент с вершины стека
						if (s.empty()) // если стек стал пустым, то мы выходим с цикла проверки приоритетов
							break;
					}
				}
				s.push(lextable.table[curPos]); // добавляем текущую операцию
				continue;
			}
			case LEX_PLUS: {
				if (!s.empty()) // если стек не пуст
				{
					// пока приоритет текущего оператора меньше приоритета оператора на вершине или если на вершине стека идентификатор функции
					while (getPriority(lextable.table[curPos]) <= getPriority(s.top()) || idtable.table[s.top().idxTI].idtype == IT::IDTYPE::F)
					{
						q.push(s.top());// помещаем элемент с вершины стека в очередь
						s.pop();// удаляем элемент с вершины стека
						if (s.empty()) // если стек стал пустым, то мы выходим с цикла проверки приоритетов
							break;
					}
				}
				s.push(lextable.table[curPos]); // добавляем текущую операцию
				continue;
			}
			case LEX_MINUS: {
				if (!s.empty()) // если стек не пуст
				{
					// пока приоритет текущего оператора меньше приоритета оператора на вершине или если на вершине стека идентификатор функции
					while (getPriority(lextable.table[curPos]) <= getPriority(s.top()) || idtable.table[s.top().idxTI].idtype == IT::IDTYPE::F)
					{
						q.push(s.top());// помещаем элемент с вершины стека в очередь
						s.pop();// удаляем элемент с вершины стека
						if (s.empty()) // если стек стал пустым, то мы выходим с цикла проверки приоритетов
							break;
					}
				}
				s.push(lextable.table[curPos]); // добавляем текущую операцию
				continue;
			}
			case LEX_COMMA: { // если запятая
				// пока не встретилась открывающаяся скобка в стеке
				while (s.top().lexema[0] != LEX_LEFTTHESIS && !s.empty())
				{
					q.push(s.top()); // помещаем элемент с вершины стека в очередь
					s.pop(); // удаляем элемент с вершины стека
				}
				if (s.empty()) {
					return false;
				}
				continue;
			}
			default:
				continue;
			}
		}
		// после прохождения всех лексем, пока стек не пуст, то
		while (!s.empty())
		{
			q.push(s.top()); // помещаем элемент с вершины стека в очередь
			s.pop();// удаляем элемент с вершины стека
		}

		// проходимся по всем полученным лексемам
		for (int i = 0; i < kolLex; i++)
		{
			if (!q.empty()) // если очередь не пуста
			{
				switch (q.front().lexema[0]) // проверяем верхнюю лексему
				{
				case LEX_ID:
					// проверяем, что полученный идентификатор находится в пределах от стартовой позиции до конца выражения
					if (curpos <= idtable.table[q.front().idxTI].idxfirstLE && idtable.table[q.front().idxTI].idxfirstLE < curpos + kolLex)
					{
						lextable.table[curpos + i] = q.front(); // тогда помещаем в таблицу лексем текущий идентификатор на позицию curpos + i
						idtable.table[q.front().idxTI].idxfirstLE = curpos + i; // также обновляем информацию в таблице идентификаторов
						q.pop(); // удаляем элемент с вершины очереди
					}
					else
					{
						lextable.table[curpos + i] = q.front(); // в противном случае просто помещаем в таблицу лексем на новую позицию
						q.pop();// удаляем элемент с вершины очереди
					}
					continue;
				case LEX_LITERAL:
					lextable.table[curpos + i] = q.front(); // тогда помещаем в таблицу лексем текущий идентификатор на позицию curpos + i
					idtable.table[q.front().idxTI].idxfirstLE = curpos + i; // также обновляем информацию в таблице идентификаторов
					q.pop(); // удаляем элемент с вершины очереди
					continue;
				default: // если это не идентификатор и не литерал, то просто помещаем его в таблицу лексем
					lextable.table[curpos + i] = q.front();
					q.pop();
					continue;
				}
			}
			// если очередь пуста, но мы не прошли количество лексем, которые были обработаны до этого, значит записываем пустые лексемы
			else
			{
				lextable.table[curpos + i] = bottom;
			}
		}
		return true;
	}
	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idTable) {
		return Rpn(lextable, idTable, lextable_pos);
	}
}