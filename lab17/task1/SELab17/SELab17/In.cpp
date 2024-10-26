#include "stdafx.h"
using namespace std;

namespace In
{
    // Функция удаления лишних пробелов 
    void removeExtraSpacesAndAddLineInfo(std::string& input, int& removedSpacesCount, int lineNumber, std::vector<std::string>& processedTokens, int& totalChars)
    {
        bool insideQuotes = false;
        std::string currentToken = "";  // Для накопления текущей лексемы
        totalChars += input.length();   // Считаем все символы в строке

        for (size_t i = 0; i < input.length(); ++i)
        {
            if (input[i] == '\'')
            {
                insideQuotes = !insideQuotes;
            }

            // Если символ не является пробелом или кавычкой — добавляем в текущую лексему
            if (!std::isspace(input[i]) || insideQuotes)
            {
                currentToken += input[i];
            }

            // Если встретили пробел вне кавычек — обрабатываем лексему
            if (!insideQuotes && std::isspace(input[i]))
            {
                if (!currentToken.empty())
                {
                    // Добавляем лексему с номером строки
                    processedTokens.push_back(currentToken + "|" + std::to_string(lineNumber));
                    currentToken.clear();
                }

                removedSpacesCount++; // Увеличиваем счетчик удаленных пробелов
            }
        }

        // Добавляем оставшуюся лексему после последнего пробела
        if (!currentToken.empty())
        {
            processedTokens.push_back(currentToken + "|" + std::to_string(lineNumber));
        }
    }

    // Функция удаления пробелов вокруг операторов
    void removeSpacesAroundOperators(std::string& input, int& removedSpacesCount, int lineNumber, std::vector<std::string>& processedTokens)
    {
        const std::string operators = ";,}{()=+-/*";
        std::string currentToken = ""; // Для накопления текущей лексемы

        for (size_t i = 0; i < input.length(); ++i)
        {
            if (operators.find(input[i]) != std::string::npos)
            {
                // Обрабатываем текущую лексему перед оператором
                if (!currentToken.empty())
                {
                    processedTokens.push_back(currentToken + "|" + std::to_string(lineNumber));
                    currentToken.clear();
                }

                // Добавляем оператор как отдельную лексему
                std::string operatorToken(1, input[i]);
                processedTokens.push_back(operatorToken + "|" + std::to_string(lineNumber));

                // Удаляем пробелы после оператора
                while (i + 1 < input.length() && std::isspace(input[i + 1]))
                {
                    input.erase(i + 1, 1);
                    removedSpacesCount++;
                }
            }
            else
            {
                // Продолжаем собирать лексему
                currentToken += input[i];
            }
        }

        // Обрабатываем последнюю лексему, если есть
        if (!currentToken.empty())
        {
            processedTokens.push_back(currentToken + "|" + std::to_string(lineNumber));
        }
    }

    // Основная функция обработки файла
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
        int removedSpacesCount = 0; // Счетчик удаленных пробелов
        int totalChars = 0;         // Счетчик всех символов
        std::string currentLine;
        std::string buffer;

        std::vector<std::string> processedTokens; // Лексемы с добавленным номером строки

        while (std::getline(fin, buffer))
        {
            resultIn.lines++; // Увеличиваем количество строк

            // Удаляем лишние пробелы и пробелы вокруг операторов
            removeExtraSpacesAndAddLineInfo(buffer, removedSpacesCount, resultIn.lines, processedTokens, totalChars);
            removeSpacesAroundOperators(buffer, removedSpacesCount, resultIn.lines, processedTokens);
        }

        fin.close();

       

        // Выводим обработанные лексемы с номерами строк
        for (const auto& token : processedTokens)
        {
            cout << token << endl;
        }

        cout << "Spaces Count: ";
        // Выводим количество удаленных пробелов
        cout <<removedSpacesCount << endl;

        // Выводим количество строк
        cout << "String Count: " << resultIn.lines << endl;

        // Выводим количество символов
        cout << "Symbols Count: " << totalChars << endl;

        return resultIn;
    }


}
