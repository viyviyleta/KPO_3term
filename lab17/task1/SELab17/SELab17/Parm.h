#pragma once
#define PARM_IN L"-in:" // Параметр для имени файла ввода
#define PARM_OUT L"-out:" // Параметр для имени файла вывода
#define PARM_LOG L"-log:" // Параметр для имени файла журнала
#define PARM_MAX_SIZE 300 // Максимальная длина строки параметра командной строки
#define PARM_OUT_DEFAULT_EXT L".out" // Расширение файла вывода по умолчанию
#define PARM_LOG_DEFAULT_EXT L".log" // Расширение файла журнала по умолчанию

namespace Parm
{
    struct PARM
    {
        wchar_t in[PARM_MAX_SIZE]; // Имя файла ввода
        wchar_t out[PARM_MAX_SIZE]; // Имя файла вывода
        wchar_t log[PARM_MAX_SIZE]; // Имя файла журнала
    };

    PARM getparm(int argc, wchar_t* argv[]); // Получение структуры PARM из параметров командной строки
};


