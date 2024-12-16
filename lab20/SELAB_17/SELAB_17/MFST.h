#pragma once
#include <iomanip>
#include "stdafx.h"


#define MFST_DIAGN_MAXSIZE  2 * ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3

class MFSTSTSTACK : public std::stack<short> { // стек автомата
public:
	using std::stack<short>::c;
};

static int FST_TRACE_n = -1;
static char rbuf[205], sbuf[205], lbuf[1024];



#define MFST_TRACE_START std::cout<< std::setw(4)<<std::left<<"Шаг"<<":"\
								  << std::setw(20)<<std::left<<" Правило"\
								  << std::setw(30)<<std::left<<" Входная лента"\
								  << std::setw(20)<<std::left<<" Стек"\
								  << std::endl;

#define MFST_TRACE1		 std::cout<< std::setw(4)<<std::left<<++FST_TRACE_n<<": "\
								  << std::setw(20)<<std::left<<rule.getCRule(rbuf,nrulechain)\
								  << std::setw(30)<<std::left<<getCLenta(lbuf,lenta_position)\
								  << std::setw(20)<<std::left<<getCSt(sbuf)\
								  << std::endl;

#define MFST_TRACE2		 std::cout<< std::setw(4)<<std::left<<FST_TRACE_n<<": "\
								  << std::setw(20)<<std::left<<" "\
								  << std::setw(30)<<std::left<<getCLenta(lbuf,lenta_position)\
								  << std::setw(20)<<std::left<<getCSt(sbuf)\
								  << std::endl;

#define MFST_TRACE3		 std::cout<< std::setw(4)<<std::left<<++FST_TRACE_n<<": "\
								  << std::setw(20)<<std::left<<" "\
								  << std::setw(30)<<std::left<<getCLenta(lbuf,lenta_position)\
								  << std::setw(20)<<std::left<<getCSt(sbuf)\
								  << std::endl;

#define MFST_TRACE4(c)		std::cout<<std::setw(4)<<std::left << ++FST_TRACE_n << ": "<<std::setw(20)<< std::left <<c<<std::endl;
#define MFST_TRACE5(c)		std::cout<<std::setw(4)<<std::left << FST_TRACE_n << ": "<<std::setw(20)<< std::left <<c<<std::endl;
#define MFST_TRACE6(c,k)	std::cout<<std::setw(4)<<std::left << FST_TRACE_n << ": "<<std::setw(20)<< std::left << c << k <<std::endl;
#define MFST_TRACE7			std::cout<<std::setw(4)<<std::left << state.lenta_position << ": "\
							<<std::setw(20)<< std::left << rule.getCRule(rbuf,state.nrulechain)\
							<<std::endl;



namespace MFST { 
	struct MfstState {// состояние автомата
		short lenta_position; // позиция на ленте
		short nrule; // номер текущего правила
		short nrulechain; // номер текущей цепочки
		MFSTSTSTACK st; // стек автомата
		MfstState();
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain);
		MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain);
	};

	class MFSTSTATE : public std::stack<MfstState> {
	public:
		using std::stack<MfstState>::c;
	};

	struct Mfst { // структура магазинного автомата
		enum RC_STEP { // код возврата функции step 
			NS_OK, // найдено правило и цепочка
			NS_NORULE, // не найдено правило грамматики
			NS_NORULECHAIN, // не найдена подходящая цепочка
			NS_ERROR, // неизвестный нетерминальный символ
			TS_OK, // текущий символ ленты == вершине стека, продвинулась лента
			TS_NOK, // текущий символ ленты != вершине стека, восстановлено состояние
			LENTA_END, // тек. позиция ленты >= lenta_size
			SURPRISE // неожиданный код возврата
		};

		struct MfstDiagnosis { // диагностика
			short lenta_position; // позиция на ленте
			RC_STEP rc_step; // код завершения шага
			short nrule; // номер правила
			short nrule_chain; // номер цепочки правила
			MfstDiagnosis();
			MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain);
		} diagnosis[MFST_DIAGN_NUMBER];

		GRBALPHABET* lenta; // перекодированная лента
		short lenta_position; // тек.позиция на ленте
		short nrule; // номер текущего правила
		short nrulechain; // номер текущей цепочки в тек.правиле
		short lenta_size; // размер ленты
		GRB::Greibach grebach; // грамматика Грейбах
		LT::LexTable lex; // таблица лексем
		MFSTSTSTACK st; // стек автомата
		MFSTSTATE storestate; // стек для сохранения состояний
		Mfst();
		Mfst(LT::LexTable& plex, GRB::Greibach pgreibach);
		char* getCSt(char* buf); // получить содержимое стека
		char* getCLenta(char* buf, short pos, short n = 25); // лента: n символов с pos
		char* getDiagnosis(short n, char* buf); // получить n-ую строку диагностики
		bool savestate(); // сохранить состояние автомата
		bool reststate(); // восстановить состояние автомата
		bool push_chain(GRB::Rule::Chain chain); // поместить цепочку правил в стек
		RC_STEP step(); // выполнить шаг автомата
		bool start(); // запустить автомат
		bool savediagnosis(RC_STEP pprc_step); // сохранить диагностическое сообщение
		void printrules(); // вывести правила

		struct Deducation { // вывод
			short size; // кол-во шагов в выводе
			short* nrules; // номер правила грамматики
			short* nrulechains; // номер цепочек правил грамматики
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		} deducation;
		bool savededucation(); // сохранить дерево вывода
	};
}
