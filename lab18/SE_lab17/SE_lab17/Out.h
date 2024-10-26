#pragma once
#include<fstream>
#include"In.h"
#include"Parm.h"
#include"Error.h"

namespace Out
{
	struct OUT
	{
		wchar_t outfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};
	static const OUT INITOUT{ L"", NULL };
	OUT GetOut(wchar_t outfile[]);
	void WriteText(OUT out, In::IN in);
	void WriteError(OUT out, Error::ERROR error);
	void WriteLine(OUT out, char* c, ...);
	void Close(OUT out);
}