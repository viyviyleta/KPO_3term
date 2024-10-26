#include "stdafx.h"

namespace IT
{
    // Создать новую таблицу идентификаторов заданного размера
    IdTable Create(int size)
    {
        if (size >= TI_MAXSIZE)
        {
            throw ERROR_THROW(3); // Вызвать ошибку с кодом 3, если размер таблицы слишком большой
        }

        IdTable idtable;
        idtable.maxsize = size; // Установить максимальный размер таблицы
        idtable.size = 0; // Установить текущий размер таблицы
        idtable.table = new Entry[size]; // Выделить память под таблицу

        return idtable; // Вернуть созданную таблицу
    }

    // Добавить запись (Entry) в таблицу идентификаторов
    void Add(IdTable& idtable, Entry entry)
    {
        if (idtable.size >= idtable.maxsize)
        {
            throw ERROR_THROW(106); // Вызвать ошибку с кодом 106, если таблица заполнена
        }

        idtable.table[idtable.size] = entry; // Добавить запись в таблицу
        idtable.size++; // Увеличить текущий размер таблицы
    }

    // Получить запись (Entry) из таблицы идентификаторов по индексу
    Entry GetEntry(IdTable& idtable, int n)
    {
        if (n < 0 || n >= idtable.size)
        {
            throw ERROR_THROW(15); // Вызвать ошибку с кодом 15, если индекс выходит за пределы таблицы
        }
        return idtable.table[n]; // Вернуть запись по указанному индексу
    }

    // Удалить таблицу идентификаторов и освободить память
    void Delete(IdTable& idtable)
    {
        delete[] idtable.table; // Освободить память, занятую таблицей
        idtable.size = 0; // Установить текущий размер и максимальный размер таблицы в ноль
        idtable.maxsize = 0;
    }

    // Поиск идентификатора в таблице с заданным именем и контекстом функции
    int IsId(IdTable& idtable, std::string id, std::string functionName, std::string function)
    {
        for (int n = idtable.size; n >= 0; n--)
        {
            if (idtable.table[n].id == id && (idtable.table[n].fun == function || idtable.table[n].functionname == functionName))
            {
                return n; // Вернуть индекс, если идентификатор найден в контексте функции
            }
        }
        return TI_NULLIDX; // Вернуть специальное значение, если идентификатор не найден
    }

    // Поиск целочисленного значения в таблице идентификаторов
    int findLexInteger(IdTable& idtable, int word)
    {
        for (int n = idtable.size; n >= 0; n--)
        {
            if (idtable.table[n].value.vint == word)
            {
                return n; // Вернуть индекс, если целочисленное значение найдено
            }
        }
        return TI_NULLIDX; // Вернуть специальное значение, если целочисленное значение не найдено
    }

    // Поиск строкового значения в таблице идентификаторов
    int findLexStr(IdTable& idtable, std::string word)
    {
        for (int n = idtable.size; n >= 0; n--)
        {
            if (idtable.table[n].value.vstr == word)
            {
                return n; // Вернуть индекс, если строковое значение найдено
            }
        }
        return TI_NULLIDX; // Вернуть специальное значение, если строковое значение не найдено
    }
};
