#include "stdafx.h"

namespace IT
{
    // ������� ����� ������� ��������������� ��������� �������
    IdTable Create(int size)
    {
        if (size >= TI_MAXSIZE)
        {
            throw ERROR_THROW(3); // ������� ������ � ����� 3, ���� ������ ������� ������� �������
        }

        IdTable idtable;
        idtable.maxsize = size; // ���������� ������������ ������ �������
        idtable.size = 0; // ���������� ������� ������ �������
        idtable.table = new Entry[size]; // �������� ������ ��� �������

        return idtable; // ������� ��������� �������
    }

    // �������� ������ (Entry) � ������� ���������������
    void Add(IdTable& idtable, Entry entry)
    {
        if (idtable.size >= idtable.maxsize)
        {
            throw ERROR_THROW(106); // ������� ������ � ����� 106, ���� ������� ���������
        }

        idtable.table[idtable.size] = entry; // �������� ������ � �������
        idtable.size++; // ��������� ������� ������ �������
    }

    // �������� ������ (Entry) �� ������� ��������������� �� �������
    Entry GetEntry(IdTable& idtable, int n)
    {
        if (n < 0 || n >= idtable.size)
        {
            throw ERROR_THROW(15); // ������� ������ � ����� 15, ���� ������ ������� �� ������� �������
        }
        return idtable.table[n]; // ������� ������ �� ���������� �������
    }

    // ������� ������� ��������������� � ���������� ������
    void Delete(IdTable& idtable)
    {
        delete[] idtable.table; // ���������� ������, ������� ��������
        idtable.size = 0; // ���������� ������� ������ � ������������ ������ ������� � ����
        idtable.maxsize = 0;
    }

    // ����� �������������� � ������� � �������� ������ � ���������� �������
    int IsId(IdTable& idtable, std::string id, std::string functionName, std::string function)
    {
        for (int n = idtable.size; n >= 0; n--)
        {
            if (idtable.table[n].id == id && (idtable.table[n].fun == function || idtable.table[n].functionname == functionName))
            {
                return n; // ������� ������, ���� ������������� ������ � ��������� �������
            }
        }
        return TI_NULLIDX; // ������� ����������� ��������, ���� ������������� �� ������
    }

    // ����� �������������� �������� � ������� ���������������
    int findLexInteger(IdTable& idtable, int word)
    {
        for (int n = idtable.size; n >= 0; n--)
        {
            if (idtable.table[n].value.vint == word)
            {
                return n; // ������� ������, ���� ������������� �������� �������
            }
        }
        return TI_NULLIDX; // ������� ����������� ��������, ���� ������������� �������� �� �������
    }

    // ����� ���������� �������� � ������� ���������������
    int findLexStr(IdTable& idtable, std::string word)
    {
        for (int n = idtable.size; n >= 0; n--)
        {
            if (idtable.table[n].value.vstr == word)
            {
                return n; // ������� ������, ���� ��������� �������� �������
            }
        }
        return TI_NULLIDX; // ������� ����������� ��������, ���� ��������� �������� �� �������
    }
};
