#include"Out.h"

namespace Out
{
	OUT GetOut(wchar_t outfile[])
	{
		OUT temp;
		temp.stream = new std::ofstream;
		temp.stream->open(outfile);
		if (!temp.stream->is_open())
		{
			ERROR_THROW(113);
		}
		wcscpy_s(temp.outfile, outfile);
		return temp;
	}

	void WriteText(OUT out, In::IN in)
	{
		*out.stream << in.text;
	}

	void WriteError(OUT out, Error::ERROR error)
	{
		*out.stream << "������: " << error.id << ":" << error.message << std::endl;
		if (error.inext.line != -1)
		{
			*out.stream << "������: " << error.inext.line << " �������: " << error.inext.col << std::endl;
		}
	}

	void Close(OUT out)
	{
		out.stream->close();
		delete out.stream;
	}
}