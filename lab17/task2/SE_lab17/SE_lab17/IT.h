#pragma once
#define ID_MAXSIZE 5
#define TI_MAXSIZE 4096
#define TI_INT_DEFAULT 0
#define TI_STR_DEFAULT ""
#define TI_NULLIDX 0xffffffff
#define TI_STR_MAXSIZE 255
namespace IT
{
    enum IDDATATYPE { INT = 1, STR = 2 }; // ������������ ��� ����� ������: INT (����� �����) � STR (������)
    enum IDTYPE { V = 1, F = 2, P = 3, L = 4 }; // ������������ ��� ����� ���������������: V (����������), F (�������), P (��������), L (��������� ����������)

    struct Entry // ��������� ��� ������������� ������ � ������� ���������������
    {
        int idxfirstLE; // ������ ������ ������ � ������� ������, ��������� � ���� ���������������
        std::string id; // ������������� (������������ �� �������)
        std::string fun; // �������� �������, � ������� ��������� ������������� (������������ �� �������)
        IDDATATYPE iddatatype; // ��� ������ �������������� (INT ��� STR)
        IDTYPE idtype; // ��� �������������� (����������, �������, ��������, ��������� ����������)
        std::string functionname; // �������� ������� (������������ �� �������)
        char operation[256]; // �������� (��������, "+", "-" ��� ���������� �������)
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
        int maxsize; // ������������ ������ �������
        int size; // ������� ������ �������
        Entry* table; // ������ ������� ������� ���������������
    };

    IdTable Create(int size); // ������� ������� ���������������
    void Add(IdTable& idtable, Entry entry); // �������� ������ � ������� ���������������
    Entry GetEntry(IdTable& idtable, int n); // �������� ������ �� ������� ��������������� �� �������
    int IsId(IdTable& idtable, std::string word, std::string functionName, std::string function); // ���������, �������� �� ������������� ������ �������
    void Delete(IdTable& idtable); // ������� ������� ���������������
    int findLexInteger(IdTable& idtable, int word);
    int findLexStr(IdTable& idtable, std::string word);
};

