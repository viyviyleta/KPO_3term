#pragma once
#define ID_MAXSIZE 5
#define TI_MAXSIZE 4096
#define TI_INT_DEFAULT 0
#define TI_STR_DEFAULT ""
#define TI_NULLIDX 0xffffffff
#define TI_STR_MAXSIZE 255
namespace IT
{
    enum IDDATATYPE { INT = 1, STR = 2 }; // Перечисление для типов данных: INT (целое число) и STR (строка)
    enum IDTYPE { V = 1, F = 2, P = 3, L = 4 }; // Перечисление для типов идентификаторов: V (переменная), F (функция), P (параметр), L (локальная переменная)

    struct Entry // Структура для представления записи в таблице идентификаторов
    {
        int idxfirstLE; // Индекс первой записи в таблице лексем, связанной с этим идентификатором
        std::string id; // Идентификатор (ограниченный по размеру)
        std::string fun; // Название функции, к которой относится идентификатор (ограниченное по размеру)
        IDDATATYPE iddatatype; // Тип данных идентификатора (INT или STR)
        IDTYPE idtype; // Тип идентификатора (переменная, функция, параметр, локальная переменная)
        std::string functionname; // Название функции (ограниченное по размеру)
        char operation[256]; // Операция (например, "+", "-" для параметров функций)
        struct
        {
            int vint;
            std::string vstr;
            int len;

            void setInteger(int value) {
                vint = value;
            }

            void setString(std::string value) {
                vstr = value;
                len = value.length();
            }
        }value;
    };

    struct IdTable
    {
        int maxsize; // Максимальный размер таблицы
        int size; // Текущий размер таблицы
        Entry* table; // Массив записей таблицы идентификаторов
    };

    IdTable Create(int size); // Создать таблицу идентификаторов
    void Add(IdTable& idtable, Entry entry); // Добавить запись в таблицу идентификаторов
    Entry GetEntry(IdTable& idtable, int n); // Получить запись из таблицы идентификаторов по индексу
    int IsId(IdTable& idtable, std::string word, std::string functionName, std::string function); // Проверить, является ли идентификатор частью таблицы
    void Delete(IdTable& idtable); // Удалить таблицу идентификаторов
    int findLexInteger(IdTable& idtable, int word);
    int findLexStr(IdTable& idtable, std::string word);
};

