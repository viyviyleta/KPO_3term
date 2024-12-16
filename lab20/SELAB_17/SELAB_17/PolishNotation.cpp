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
		queue<LT::Entry> q; // ��� �������� �������� ������
		stack<LT::Entry> s; // ��� �������� ���������� � ������
		LT::Entry bottom = { '@', LT_TI_NULLIDX, LT_TI_NULLIDX };
		int curpos = curPos; // ������� �������
		int kolLex = 0; // ���������� ������������ ������
		for (curPos; lextable.table[curPos].lexema[0] != LEX_SEMICOLON; curPos++, kolLex++)
		{
			switch (lextable.table[curPos].lexema[0])
			{
			case LEX_ID:
			{
				if (idtable.table[lextable.table[curPos].idxTI].idtype == IT::IDTYPE::F)
				{
					s.push(lextable.table[curPos]); // ������������� ������� �������� � ����
					continue;
				}
				q.push(lextable.table[curPos]); // �������� ������������� � �������
				continue;
			}
			case LEX_LITERAL:
			{
				q.push(lextable.table[curPos]);// �������� ������� � �������
				continue;
			}
			case LEX_LEFTTHESIS:
			{
				s.push(lextable.table[curPos]); // ������������� ������ �������� � ����
				continue;
			}
			case LEX_RIGHTTHESIS: 
			{
				if (!s.empty()) // ���� ���� �� ����
				{
					while (s.top().lexema[0] != LEX_LEFTTHESIS) // ���� �� �������� ������������� ������
					{
						q.push(s.top()); // �������� � ������� ������� ������� �� �����
						s.pop(); // ������� ������� � ������� �����
					}
					s.pop(); // ������� ������������� ������
				}
				else {
					return false;
				}
				continue;
			}
			case LEX_STAR: {
				if (!s.empty()) // ���� ���� �� ����
				{
					// ���� ��������� �������� ��������� ������ ���������� ��������� �� ������� ��� ���� �� ������� ����� ������������� �������
					while (getPriority(lextable.table[curPos]) <= getPriority(s.top()) || idtable.table[s.top().idxTI].idtype == IT::IDTYPE::F)
					{
						q.push(s.top()); // �������� ������� � ������� ����� � �������
						s.pop(); // ������� ������� � ������� �����
						if (s.empty()) // ���� ���� ���� ������, �� �� ������� � ����� �������� �����������
							break;
					}
				}
				s.push(lextable.table[curPos]); // ��������� ������� ��������
				continue;
			}
			case LEX_DIRSLASH: {
				if (!s.empty()) // ���� ���� �� ����
				{
					// ���� ��������� �������� ��������� ������ ���������� ��������� �� ������� ��� ���� �� ������� ����� ������������� �������
					while (getPriority(lextable.table[curPos]) <= getPriority(s.top()) || idtable.table[s.top().idxTI].idtype == IT::IDTYPE::F)
					{
						q.push(s.top());// �������� ������� � ������� ����� � �������
						s.pop();// ������� ������� � ������� �����
						if (s.empty()) // ���� ���� ���� ������, �� �� ������� � ����� �������� �����������
							break;
					}
				}
				s.push(lextable.table[curPos]); // ��������� ������� ��������
				continue;
			}
			case LEX_PLUS: {
				if (!s.empty()) // ���� ���� �� ����
				{
					// ���� ��������� �������� ��������� ������ ���������� ��������� �� ������� ��� ���� �� ������� ����� ������������� �������
					while (getPriority(lextable.table[curPos]) <= getPriority(s.top()) || idtable.table[s.top().idxTI].idtype == IT::IDTYPE::F)
					{
						q.push(s.top());// �������� ������� � ������� ����� � �������
						s.pop();// ������� ������� � ������� �����
						if (s.empty()) // ���� ���� ���� ������, �� �� ������� � ����� �������� �����������
							break;
					}
				}
				s.push(lextable.table[curPos]); // ��������� ������� ��������
				continue;
			}
			case LEX_MINUS: {
				if (!s.empty()) // ���� ���� �� ����
				{
					// ���� ��������� �������� ��������� ������ ���������� ��������� �� ������� ��� ���� �� ������� ����� ������������� �������
					while (getPriority(lextable.table[curPos]) <= getPriority(s.top()) || idtable.table[s.top().idxTI].idtype == IT::IDTYPE::F)
					{
						q.push(s.top());// �������� ������� � ������� ����� � �������
						s.pop();// ������� ������� � ������� �����
						if (s.empty()) // ���� ���� ���� ������, �� �� ������� � ����� �������� �����������
							break;
					}
				}
				s.push(lextable.table[curPos]); // ��������� ������� ��������
				continue;
			}
			case LEX_COMMA: { // ���� �������
				// ���� �� ����������� ������������� ������ � �����
				while (s.top().lexema[0] != LEX_LEFTTHESIS && !s.empty())
				{
					q.push(s.top()); // �������� ������� � ������� ����� � �������
					s.pop(); // ������� ������� � ������� �����
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
		// ����� ����������� ���� ������, ���� ���� �� ����, ��
		while (!s.empty())
		{
			q.push(s.top()); // �������� ������� � ������� ����� � �������
			s.pop();// ������� ������� � ������� �����
		}

		// ���������� �� ���� ���������� ��������
		for (int i = 0; i < kolLex; i++)
		{
			if (!q.empty()) // ���� ������� �� �����
			{
				switch (q.front().lexema[0]) // ��������� ������� �������
				{
				case LEX_ID:
					// ���������, ��� ���������� ������������� ��������� � �������� �� ��������� ������� �� ����� ���������
					if (curpos <= idtable.table[q.front().idxTI].idxfirstLE && idtable.table[q.front().idxTI].idxfirstLE < curpos + kolLex)
					{
						lextable.table[curpos + i] = q.front(); // ����� �������� � ������� ������ ������� ������������� �� ������� curpos + i
						idtable.table[q.front().idxTI].idxfirstLE = curpos + i; // ����� ��������� ���������� � ������� ���������������
						q.pop(); // ������� ������� � ������� �������
					}
					else
					{
						lextable.table[curpos + i] = q.front(); // � ��������� ������ ������ �������� � ������� ������ �� ����� �������
						q.pop();// ������� ������� � ������� �������
					}
					continue;
				case LEX_LITERAL:
					lextable.table[curpos + i] = q.front(); // ����� �������� � ������� ������ ������� ������������� �� ������� curpos + i
					idtable.table[q.front().idxTI].idxfirstLE = curpos + i; // ����� ��������� ���������� � ������� ���������������
					q.pop(); // ������� ������� � ������� �������
					continue;
				default: // ���� ��� �� ������������� � �� �������, �� ������ �������� ��� � ������� ������
					lextable.table[curpos + i] = q.front();
					q.pop();
					continue;
				}
			}
			// ���� ������� �����, �� �� �� ������ ���������� ������, ������� ���� ���������� �� �����, ������ ���������� ������ �������
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