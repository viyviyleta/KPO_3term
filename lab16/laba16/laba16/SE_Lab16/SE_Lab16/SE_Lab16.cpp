#include "FST.h"
#include <tchar.h>
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	FST::FST fst1(			// ������������������ �������� ������� (a+b)*aba
		(char*)"aabbabaaba",					// ������� ��� �������������
		4,										// ���������� ��������
		FST::NODE(3, FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('a', 1)),	// ��������� 0 (���������)
		FST::NODE(1, FST::RELATION('b', 2)),												// ��������� 1
		FST::NODE(1, FST::RELATION('a', 3)),												// ��������� 2
		FST::NODE()																			// ��������� 3 (��������)
	);
	if (FST::execute(fst1))
		cout << "������� " << fst1.strin << " ����������" << endl;
	else
		cout << "������� " << fst1.strin << " �� ����������" << endl;


	FST::FST fst2(
		(char*)"aaabbbabba",
		4,
		FST::NODE(3, FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('a', 1)),	// ��������� 0 (���������)
		FST::NODE(1, FST::RELATION('b', 2)),												// ��������� 1
		FST::NODE(1, FST::RELATION('a', 3)),												// ��������� 2
		FST::NODE()
	);
	if (FST::execute(fst2))
		cout << "������� " << fst2.strin << " ����������" << endl;
	else
		cout << "������� " << fst2.strin << " �� ����������" << endl;

	FST::FST fst3( 	// ������������������� �������� ������� a(b)+ ((c+d+e))+ b+ f
		(char*)"abbcccdbf",
		7,
		FST::NODE(1, FST::RELATION('a', 1)),
		FST::NODE(2, FST::RELATION('b', 1), FST::RELATION('b', 2)),
		FST::NODE(3, FST::RELATION('c', 3), FST::RELATION('d', 3), FST::RELATION('e', 3)),
		FST::NODE(6, FST::RELATION('c', 3), FST::RELATION('d', 3), FST::RELATION('e', 3), FST::RELATION('c', 4), FST::RELATION('d', 4), FST::RELATION('e', 4)),
		FST::NODE(2, FST::RELATION('b', 4), FST::RELATION('b', 5)),
		FST::NODE(1, FST::RELATION('f', 6)),
		FST::NODE()
	);

	if (FST::execute(fst3))
		cout << "������� " << fst3.strin << " ����������" << endl;
	else
		cout << "������� " << fst3.strin << " �� ����������" << endl;

	FST::FST fst4(
		(char*)"abcccdeebf",
		7,
		FST::NODE(1, FST::RELATION('a', 1)),
		FST::NODE(2, FST::RELATION('b', 1), FST::RELATION('b', 2)),
		FST::NODE(3, FST::RELATION('c', 3), FST::RELATION('d', 3), FST::RELATION('e', 3)),
		FST::NODE(6, FST::RELATION('c', 3), FST::RELATION('d', 3), FST::RELATION('e', 3), FST::RELATION('c', 4), FST::RELATION('d', 4), FST::RELATION('e', 4)),
		FST::NODE(2, FST::RELATION('b', 4), FST::RELATION('b', 5)),
		FST::NODE(1, FST::RELATION('f', 6)),
		FST::NODE()
	);
	if (FST::execute(fst4))
		cout << "������� " << fst4.strin << " ����������" << endl;
	else
		cout << "������� " << fst4.strin << " �� ����������" << endl;

	FST::FST fst5(
		(char*)"abbdeebf",
		7,
		FST::NODE(1, FST::RELATION('a', 1)),
		FST::NODE(2, FST::RELATION('b', 1), FST::RELATION('b', 2)),
		FST::NODE(3, FST::RELATION('c', 3), FST::RELATION('d', 3), FST::RELATION('e', 3)),
		FST::NODE(6, FST::RELATION('c', 3), FST::RELATION('d', 3), FST::RELATION('e', 3), FST::RELATION('c', 4), FST::RELATION('d', 4), FST::RELATION('e', 4)),
		FST::NODE(2, FST::RELATION('b', 4), FST::RELATION('b', 5)),
		FST::NODE(1, FST::RELATION('f', 6)),
		FST::NODE()
	);
	if (FST::execute(fst5))
		cout << "������� " << fst5.strin << " ����������" << endl;
	else
		cout << "������� " << fst5.strin << " �� ����������" << endl;

	FST::FST fst6(
		(char*)"abcebf",
		7,
		FST::NODE(1, FST::RELATION('a', 1)),
		FST::NODE(2, FST::RELATION('b', 1), FST::RELATION('b', 2)),
		FST::NODE(3, FST::RELATION('c', 3), FST::RELATION('d', 3), FST::RELATION('e', 3)),
		FST::NODE(6, FST::RELATION('c', 3), FST::RELATION('d', 3), FST::RELATION('e', 3), FST::RELATION('c', 4), FST::RELATION('d', 4), FST::RELATION('e', 4)),
		FST::NODE(2, FST::RELATION('b', 4), FST::RELATION('b', 5)),
		FST::NODE(1, FST::RELATION('f', 6)),
		FST::NODE()
	);
	if (FST::execute(fst6))
		cout << "������� " << fst6.strin << " ����������" << endl;
	else
		cout << "������� " << fst6.strin << " �� ����������" << endl;

	FST::FST fst7(
		(char*)"abbbbcccdbf",
		7,
		FST::NODE(1, FST::RELATION('a', 1)),
		FST::NODE(2, FST::RELATION('b', 1), FST::RELATION('b', 2)),
		FST::NODE(3, FST::RELATION('c', 3), FST::RELATION('d', 3), FST::RELATION('e', 3)),
		FST::NODE(6, FST::RELATION('c', 3), FST::RELATION('d', 3), FST::RELATION('e', 3), FST::RELATION('c', 4), FST::RELATION('d', 4), FST::RELATION('e', 4)),
		FST::NODE(2, FST::RELATION('b', 4), FST::RELATION('b', 5)),
		FST::NODE(1, FST::RELATION('f', 6)),
		FST::NODE()
	);
	if (FST::execute(fst7))
		cout << "������� " << fst7.strin << " ����������" << endl;
	else
		cout << "������� " << fst7.strin << " �� ����������" << endl;

	FST::FST fst8(
		(char*)"abf",
		7,
		FST::NODE(1, FST::RELATION('a', 1)),
		FST::NODE(2, FST::RELATION('b', 1), FST::RELATION('b', 2)),
		FST::NODE(3, FST::RELATION('c', 3), FST::RELATION('d', 3), FST::RELATION('e', 3)),
		FST::NODE(6, FST::RELATION('c', 3), FST::RELATION('c', 4), FST::RELATION('d', 3), FST::RELATION('d', 4), FST::RELATION('e', 3), FST::RELATION('e', 4)),
		FST::NODE(2, FST::RELATION('b', 4), FST::RELATION('b', 5)),
		FST::NODE(1, FST::RELATION('f', 6)),
		FST::NODE()
	);
	if (FST::execute(fst8))
		cout << "������� " << fst8.strin << " ����������" << endl;
	else
		cout << "������� " << fst8.strin << " �� ����������" << endl;

	FST::FST fst9(
		(char*)"abcdef",
		7,
		FST::NODE(1, FST::RELATION('a', 1)),
		FST::NODE(2, FST::RELATION('b', 1), FST::RELATION('b', 2)),
		FST::NODE(3, FST::RELATION('c', 3), FST::RELATION('d', 3), FST::RELATION('e', 3)),
		FST::NODE(6, FST::RELATION('c', 3), FST::RELATION('c', 4), FST::RELATION('d', 3), FST::RELATION('d', 4), FST::RELATION('e', 3), FST::RELATION('e', 4)),
		FST::NODE(2, FST::RELATION('b', 4), FST::RELATION('b', 5)),
		FST::NODE(1, FST::RELATION('f', 6)),
		FST::NODE()
	);
	if (FST::execute(fst9))
		cout << "������� " << fst9.strin << " ����������" << endl;
	else
		cout << "������� " << fst9.strin << " �� ����������" << endl;
}