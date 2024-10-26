#include "stdafx.h"
#include "Parm.h"
#include "Error.h"

namespace Parm
{

	PARM getparm(int argc, wchar_t* argv[])
	{
		PARM result;
		bool isOut = false, isLog = false;

		if (argc < 2) { throw ERROR_THROW(100); }
		for (int i = 0; i < argc; i++)
		{
			/*‘ункци€ wcsstr €вл€етс€ частью стандартной библиотеки C/C++ и используетс€ дл€ поиска первого вхождени€ одной широкой подстроки
			(строки типа wchar_t) в другой широкой строке.
			ќна возвращает указатель на начало найденной подстроки или nullptr, если подстрока не найдена.*/

			if (wcslen(argv[i]) > PARM_MAX_SIZE + 3)
			{
				throw ERROR_THROW(104);
			}
			if (wcsstr(argv[i], PARM_IN) != nullptr)
			{
				/*функци€ wcscpy_s €вл€етс€ частью стандартной библиотеки C/C++ и используетс€ дл€ копировани€ содержимого одной широкой строки
				(строки типа wchar_t) в другую. ѕротитип: errno_t wcscpy_s(wchar_t* dest, size_t destSize, const wchar_t* src);
				ѕараметры:
				dest: ”казатель на целевую строку, в которую будет скопировано содержимое.
				destSize: ћаксимальный размер dest в символах.
				src: ”казатель на строку-источник, которую нужно скопировать.*/
				wcscpy_s(result.in, argv[i] + wcslen(PARM_IN));
			}

			if (wcsstr(argv[i], PARM_OUT) != nullptr)
			{
				isOut = true;
				wcscpy_s(result.out, argv[i] + wcslen(PARM_OUT));
			}

			if (wcsstr(argv[i], PARM_LOG) != nullptr)
			{
				isLog = true;
				wcscpy_s(result.log, argv[i] + wcslen(PARM_LOG));
			}
		}
		if (!isOut)
		{
			wcscpy_s(result.out, result.in);
			wcscat_s(result.out, PARM_OUT_DEFAULT_EXT);
		}
		if (!isLog)
		{
			wcscpy_s(result.log, result.in);
			wcscat_s(result.log, PARM_LOG_DEFAULT_EXT);
		}

		return result;
	}
}