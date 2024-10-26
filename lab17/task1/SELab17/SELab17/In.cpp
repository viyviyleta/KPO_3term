#include "stdafx.h"
using namespace std;

namespace In
{
    // ������� �������� ������ �������� 
    void removeExtraSpacesAndAddLineInfo(std::string& input, int& removedSpacesCount, int lineNumber, std::vector<std::string>& processedTokens, int& totalChars)
    {
        bool insideQuotes = false;
        std::string currentToken = "";  // ��� ���������� ������� �������
        totalChars += input.length();   // ������� ��� ������� � ������

        for (size_t i = 0; i < input.length(); ++i)
        {
            if (input[i] == '\'')
            {
                insideQuotes = !insideQuotes;
            }

            // ���� ������ �� �������� �������� ��� �������� � ��������� � ������� �������
            if (!std::isspace(input[i]) || insideQuotes)
            {
                currentToken += input[i];
            }

            // ���� ��������� ������ ��� ������� � ������������ �������
            if (!insideQuotes && std::isspace(input[i]))
            {
                if (!currentToken.empty())
                {
                    // ��������� ������� � ������� ������
                    processedTokens.push_back(currentToken + "|" + std::to_string(lineNumber));
                    currentToken.clear();
                }

                removedSpacesCount++; // ����������� ������� ��������� ��������
            }
        }

        // ��������� ���������� ������� ����� ���������� �������
        if (!currentToken.empty())
        {
            processedTokens.push_back(currentToken + "|" + std::to_string(lineNumber));
        }
    }

    // ������� �������� �������� ������ ����������
    void removeSpacesAroundOperators(std::string& input, int& removedSpacesCount, int lineNumber, std::vector<std::string>& processedTokens)
    {
        const std::string operators = ";,}{()=+-/*";
        std::string currentToken = ""; // ��� ���������� ������� �������

        for (size_t i = 0; i < input.length(); ++i)
        {
            if (operators.find(input[i]) != std::string::npos)
            {
                // ������������ ������� ������� ����� ����������
                if (!currentToken.empty())
                {
                    processedTokens.push_back(currentToken + "|" + std::to_string(lineNumber));
                    currentToken.clear();
                }

                // ��������� �������� ��� ��������� �������
                std::string operatorToken(1, input[i]);
                processedTokens.push_back(operatorToken + "|" + std::to_string(lineNumber));

                // ������� ������� ����� ���������
                while (i + 1 < input.length() && std::isspace(input[i + 1]))
                {
                    input.erase(i + 1, 1);
                    removedSpacesCount++;
                }
            }
            else
            {
                // ���������� �������� �������
                currentToken += input[i];
            }
        }

        // ������������ ��������� �������, ���� ����
        if (!currentToken.empty())
        {
            processedTokens.push_back(currentToken + "|" + std::to_string(lineNumber));
        }
    }

    // �������� ������� ��������� �����
    IN getin(wchar_t infile[])
    {
        ifstream fin;
        char* outFile = new char[wcslen(infile) + 1];
        wcstombs_s(NULL, outFile, wcslen(infile) + 1, infile, wcslen(infile) + 1);
        fin.open(infile);
        if (fin.bad())
        {
            throw ERROR_THROW(116);
        }
        if (!fin.is_open())
        {
            throw ERROR_THROW(110);
        }

        IN resultIn;
        resultIn.size = 0;
        resultIn.lines = 0;
        int removedSpacesCount = 0; // ������� ��������� ��������
        int totalChars = 0;         // ������� ���� ��������
        std::string currentLine;
        std::string buffer;

        std::vector<std::string> processedTokens; // ������� � ����������� ������� ������

        while (std::getline(fin, buffer))
        {
            resultIn.lines++; // ����������� ���������� �����

            // ������� ������ ������� � ������� ������ ����������
            removeExtraSpacesAndAddLineInfo(buffer, removedSpacesCount, resultIn.lines, processedTokens, totalChars);
            removeSpacesAroundOperators(buffer, removedSpacesCount, resultIn.lines, processedTokens);
        }

        fin.close();

       

        // ������� ������������ ������� � �������� �����
        for (const auto& token : processedTokens)
        {
            cout << token << endl;
        }

        cout << "Spaces Count: ";
        // ������� ���������� ��������� ��������
        cout <<removedSpacesCount << endl;

        // ������� ���������� �����
        cout << "String Count: " << resultIn.lines << endl;

        // ������� ���������� ��������
        cout << "Symbols Count: " << totalChars << endl;

        return resultIn;
    }


}
