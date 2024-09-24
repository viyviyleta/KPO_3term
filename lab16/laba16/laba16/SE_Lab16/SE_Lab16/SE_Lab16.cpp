#include "FST.h"
#include <tchar.h>
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	FST::FST fst1(			// недетермнированный конечный автомат (a+b)*aba
		(char*)"aabbabaaba",					// цепочка для распознования
		4,										// количество состяний
		FST::NODE(3, FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('a', 1)),	// состояние 0 (начальное)
		FST::NODE(1, FST::RELATION('b', 2)),												// состояние 1
		FST::NODE(1, FST::RELATION('a', 3)),												// состояние 2
		FST::NODE()																			// состояние 3 (конечное)
	);
	if (FST::execute(fst1))
		cout << "Цепочка " << fst1.strin << " распознана" << endl;
	else
		cout << "Цепочка " << fst1.strin << " не распознана" << endl;


	FST::FST fst2(
		(char*)"aaabbbabba",
		4,
		FST::NODE(3, FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('a', 1)),	// состояние 0 (начальное)
		FST::NODE(1, FST::RELATION('b', 2)),												// состояние 1
		FST::NODE(1, FST::RELATION('a', 3)),												// состояние 2
		FST::NODE()
	);
	if (FST::execute(fst2))
		cout << "Цепочка " << fst2.strin << " распознана" << endl;
	else
		cout << "Цепочка " << fst2.strin << " не распознана" << endl;

	FST::FST fst3( 	// недетерминированный конечный автомат a(b)+ ((c+d+e))+ b+ f
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
		cout << "Цепочка " << fst3.strin << " распознана" << endl;
	else
		cout << "Цепочка " << fst3.strin << " не распознана" << endl;

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
		cout << "Цепочка " << fst4.strin << " распознана" << endl;
	else
		cout << "Цепочка " << fst4.strin << " не распознана" << endl;

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
		cout << "Цепочка " << fst5.strin << " распознана" << endl;
	else
		cout << "Цепочка " << fst5.strin << " не распознана" << endl;

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
		cout << "Цепочка " << fst6.strin << " распознана" << endl;
	else
		cout << "Цепочка " << fst6.strin << " не распознана" << endl;

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
		cout << "Цепочка " << fst7.strin << " распознана" << endl;
	else
		cout << "Цепочка " << fst7.strin << " не распознана" << endl;

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
		cout << "Цепочка " << fst8.strin << " распознана" << endl;
	else
		cout << "Цепочка " << fst8.strin << " не распознана" << endl;

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
		cout << "Цепочка " << fst9.strin << " распознана" << endl;
	else
		cout << "Цепочка " << fst9.strin << " не распознана" << endl;
}