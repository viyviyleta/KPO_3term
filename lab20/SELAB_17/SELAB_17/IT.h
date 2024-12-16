#pragma once
#include <map>
#define ID_MAXSIZE 6 // максимальное количество символов в идентификаторе
#define TI_MAXSIZE 4096 // максимальное количество строк в таблице
#define TI_INT_DEFAULT 0x00000000 // значение по умолчанию дл€ integer
#define TI_STR_DEFAULT 0x00 // значение по умолчанию дл€ string
#define TI_NULLIDX 0xffffffff // нет элемента в таблице идентификаторов
#define TI_STR_MAXSIZE 255 

namespace IT { // таблица идентификаторов
	enum IDDATATYPE {INT = 1, STR = 2}; // тип данных идентификаторов
	enum IDTYPE {V = 1, F = 2, P = 3, L = 4}; // тип идентификаторов: переменна€, функци€, параметр, литерал
	struct Entry		
	{
		int			idxfirstLE;			
		char		id[ID_MAXSIZE];	
		IDDATATYPE	iddatatype;	
		IDTYPE		idtype;			
		string scope_name;
		union
		{
			int		vint;				
			struct
			{
				int len;						
				char str[TI_STR_MAXSIZE - 1];	
			}	vstr[TI_STR_MAXSIZE];			
		} value;	
	};

	struct IdTable { // экземпл€р таблицы идентификаторов
		int maxsize; // емкость таблиц идентификаторов < TI_MAXSIZE
		int size; // текущий размер таблицы идентификаторов < maxsize
		Entry* table; // массив строк в таблице идентификаторов
	};
	IdTable Create(int size); // создать таблицу идентификаторов
	void Add(IdTable& idtable, Entry entry); // добавить строку в таблицу идентификаторов 
	int search(IdTable& idtable, IT::Entry entry, map<string, string> scop);
	int search(IdTable& idtable, IT::Entry entry);
	Entry GetEntry(IdTable& idtable, int n); // получить строку из таблицы идентификаторов
	void Delete(IdTable& idtable); // удалить таблицу идентификаторов
}