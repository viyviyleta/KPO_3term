#include"LexA.h"
#include"stdafx.h"
#include"In.h"
#include"Error.h"
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <vector>
#include <map>
namespace LexA
{
	LT::LexTable lexTable = LT::Create(LT_MAXSIZE - 1);
	IT::IdTable idTable = IT::Create(TI_MAXSIZE - 1);
	bool stringFlag = false;
	char* str = new char[MAX_LEX_SIZE];
	bool declareFlag = false;

	void Add_LT(int line, char token)
	{
		LT::Entry entry;
		entry.sn = line;
		memset(entry.lexema, '\0', strlen(entry.lexema) - 1);
		entry.lexema[0] = token;
		LT::Add(lexTable, entry);
	}
	char FST()
	{
		FST_INT
			FST_STRING
			FST_FUNC
			FST_DECLARE
			FST_RETURN
			FST_MAIN
			FST_PRINT
			FST_LITERAL
			FST_IDENF
			if (FST::execute(_int))
				return LEX_INTEGER;
		if (FST::execute(_string))
		{
			stringFlag = true;
			return LEX_STRING;
		}
		if (FST::execute(_function))
			return LEX_FUNCTION;
		if (FST::execute(_declare))
			return LEX_DECLARE;
		if (FST::execute(_return))
			return LEX_RETURN;
		if (FST::execute(_main))
		{
			return LEX_MAIN;
		}
		if (FST::execute(_print))
			return LEX_PRINT;
		if (FST::execute(literal_int))
			return LEX_LITERAL;
		if (FST::execute(idenf))
			return LEX_ID;
		return NULL;
 	}
	LEX LexA(Parm::PARm parm, In::iN in)
	{
		LEX lexResult;
		int indexIT;
		setlocale(LC_ALL, "rus");
		LT::Entry cur_lex;
		int bufferIndex = 0;
		cur_lex.sn = 0;
		cur_lex.idxTI = 0;
		cur_lex.lexema[0] = NULL;
		map<string, string> scope;
		scope["global"] = "";
		string cur_scope = "global";
		string prev_scope = "";
		int number_literal = 0;
		bool addedToITFlag = false;
		bool Functionflag = false;
		bool declareFunctionflag = false;
		IT::Entry cur_iden;
		lexTable.size = 0;
		int currentLine = 1;
		std::ofstream LT_file;
		std::ofstream IT_file;
		LT_file.open("LT.txt");
		IT_file.open("IT.txt");
		int pos = 0;
		for (int i = 0; i < in.size; i++)
		{
			if (((in.text[i] >= 'A' && in.text[i] <= 'Z') || (in.text[i] >= 'a' && in.text[i] <= 'z') || (in.text[i] >= '0' && in.text[i] <= '9') || (in.text[i] >= 0xC0 && in.text[i] <= 0xFF) || (in.text[i] >= 0xE0 && in.text[i] <= 0xFF) || in.text[i] == '\'') && in.text[i] != ' ')
			{
				pos++;
				str[bufferIndex] = in.text[i];
				bufferIndex++;
				if (bufferIndex >= MAX_LEX_SIZE)
				{
					throw ERROR_THROW(119);
				}
			}
			else
			{
				str[bufferIndex] = '\0';
				cur_lex.lexema[0] = FST();
				if (cur_lex.lexema[0] == LEX_MAIN)
				{
					cur_lex.idxTI = idTable.size;
					memcpy(cur_iden.id, str, 5);
					cur_iden.id[5] = '\0';
					cur_iden.iddatatype = IT::INT;
					cur_iden.idtype = IT::F;
					cur_iden.value.vint = NULL;
					cur_iden.idxfirstLE = currentLine;
					cur_iden.scope_name = cur_scope;
					indexIT = IT::search(idTable, cur_iden, scope);
					if (indexIT >= 0)
					{
						throw ERROR_THROW_IN(105, currentLine, pos);
					}
					if (indexIT == -1)
					{
						cur_lex.idxTI = idTable.size;
						IT::Add(idTable, cur_iden);
					}
					prev_scope = cur_scope;
					cur_scope = "main";
					scope[cur_scope] = prev_scope;

				}
				if (cur_lex.lexema[0] == LEX_LITERAL)
				{
					cur_lex.idxTI = idTable.size;
					sprintf_s(cur_iden.id, "L%d", number_literal);
					cur_iden.iddatatype = IT::INT;
					cur_iden.idtype = IT::L;
					cur_iden.idxfirstLE = currentLine;
					cur_iden.value.vint = atoi(str);
					cur_iden.scope_name = cur_scope;;
					cur_lex.idxTI = idTable.size;
					IT::Add(idTable, cur_iden);
					number_literal++;
				}
				if (cur_lex.lexema[0] == LEX_ID)
				{
					cur_iden.scope_name = cur_scope;
					cur_lex.idxTI = idTable.size;
					memcpy(cur_iden.id, str, 5);
					cur_iden.id[5] = '\0';
					cur_iden.iddatatype = IT::INT;
					cur_iden.value.vint = NULL;
					cur_iden.idxfirstLE = currentLine;
					cur_iden.idtype = IT::V;
					if (lexTable.table[lexTable.size - 3].lexema[0] == LEX_DECLARE && lexTable.table[lexTable.size - 1].lexema[0] == LEX_FUNCTION) {
						declareFunctionflag = true;
					}
					if (lexTable.table[lexTable.size - 2].lexema[0] == LEX_DECLARE)
					{
						if (lexTable.table[lexTable.size - 1].lexema[0] == LEX_STRING && stringFlag)
						{
							cur_iden.iddatatype = IT::STR;
							strcpy_s(cur_iden.value.vstr->str, "");
							stringFlag = false;
						}
						indexIT = IT::search(idTable, cur_iden);
						if (indexIT >= 0)
						{
							throw ERROR_THROW_IN(105, currentLine, pos);
						}
						if (indexIT == -1)
						{
							cur_lex.idxTI = idTable.size;
							IT::Add(idTable, cur_iden);
							addedToITFlag = true;
						}

					}
					if (lexTable.table[lexTable.size - 1].lexema[0] == LEX_FUNCTION)
					{
						cur_iden.idtype = IT::F;
						Functionflag = true;
						if (lexTable.table[lexTable.size - 2].lexema[0] == LEX_STRING && stringFlag)
						{
							cur_iden.iddatatype = IT::STR;
							strcpy_s(cur_iden.value.vstr->str, "");
							stringFlag = false;
						}
						indexIT = IT::search(idTable, cur_iden);
						if (indexIT >= 0)
						{
							throw ERROR_THROW_IN(105, currentLine, pos);
						}
						if (indexIT == -1)
						{

							cur_lex.idxTI = idTable.size;
							IT::Add(idTable, cur_iden);
							addedToITFlag = true;
						}
					}
					if (lexTable.table[lexTable.size - 2].lexema[0] == LEX_LEFTTHESIS &&
						lexTable.table[lexTable.size - 3].lexema[0] == LEX_ID &&
						lexTable.table[lexTable.size - 3].idxTI == idTable.size - 1 &&
						idTable.table[idTable.size - 1].idtype == IT::F)
					{
						cur_iden.idtype = IT::P;
						if (lexTable.table[lexTable.size - 1].lexema[0] == LEX_STRING && stringFlag)
						{
							cur_iden.iddatatype = IT::STR;
							strcpy_s(cur_iden.value.vstr->str, "");
							stringFlag = false;
						}
						indexIT = IT::search(idTable, cur_iden);
						if (indexIT >= 0)
						{
							throw ERROR_THROW_IN(105, currentLine, pos);
						}
						cur_lex.idxTI = idTable.size;
						IT::Add(idTable, cur_iden);
						addedToITFlag = true;
					}
					if (lexTable.table[lexTable.size - 2].lexema[0] == LEX_COMMA && idTable.table[lexTable.table[lexTable.size - 2].idxTI].idtype == IT::P)
					{
						cur_iden.idtype = IT::P;
						if (lexTable.table[lexTable.size - 1].lexema[0] == LEX_STRING && stringFlag)
						{
							cur_iden.iddatatype = IT::STR;
							strcpy_s(cur_iden.value.vstr->str, "");
							stringFlag = false;
						}
						indexIT = IT::search(idTable, cur_iden);
						if (indexIT >= 0)
						{
							throw ERROR_THROW_IN(105, currentLine, pos);
						}
						IT::Add(idTable, cur_iden);
						addedToITFlag = true;
					}
					if (!addedToITFlag)
					{
						indexIT = IT::search(idTable, cur_iden, scope);
						if (indexIT >= 0)
						{
							for (int i = 0; i < strlen(cur_iden.id); i++)
								cur_lex.idxTI = indexIT;
						}
					}
					std::memset(cur_iden.id, NULL, 5);
					cur_iden.iddatatype = IT::INT;
					cur_iden.value.vint = NULL;
					addedToITFlag = false;
				}

				bufferIndex = 0;
				std::memset(str, NULL, bufferIndex + 1);
			}
			if (cur_lex.lexema[0] != NULL)
			{
				cur_lex.sn = currentLine;
				LT::Add(lexTable, cur_lex);
				cur_lex.lexema[0] = NULL;

			}
			switch (in.text[i])
			{
			case MARK:
				if (str[0] == '\'' && bufferIndex != 1)
				{
					cur_lex.idxTI = idTable.size;
					str[bufferIndex] = '\0';
					cur_lex.lexema[0] = LEX_LITERAL;
					number_literal++;
					sprintf_s(cur_iden.id, "L%d", number_literal);
					cur_iden.iddatatype = IT::STR;
					cur_iden.idtype = IT::L;
					cur_iden.idxfirstLE = currentLine;
					for (int i = 0; i < strlen(str); i++)
					{
						cur_iden.value.vstr->str[i] = str[i];
					}
					cur_iden.value.vstr->str[strlen(str)] = '\0';
					cur_iden.value.vstr->len = strlen(cur_iden.value.vstr->str);
					cur_lex.sn = currentLine;
					cur_iden.scope_name = cur_scope;
					LT::Add(lexTable, cur_lex);
					IT::Add(idTable, cur_iden);
					cur_lex.lexema[0] = NULL;
					break;
				}
				break;
			case NEW_LINE:
				currentLine++;
				pos = 0;
				cur_lex.lexema[0] = NULL;
				break;
			case SEMICOLON:
				cur_lex.lexema[0] = LEX_SEMICOLON;
				cur_lex.sn = currentLine;
				LT::Add(lexTable, cur_lex);
				cur_lex.lexema[0] = NULL;
				if (lexTable.table[lexTable.size - 2].lexema[0] == LEX_BRACELET)
				{
					cur_scope = prev_scope;
					prev_scope = scope[cur_scope];
					Functionflag = false;
				}
				if (declareFunctionflag && lexTable.table[lexTable.size - 2].lexema[0] == RIGHTTHESIS)
				{
					for (int i = idTable.size - 1; i >= 0; i--) {
						if (idTable.table[i].idtype == IT::F) {
							cur_scope = scope[idTable.table[i].id];
							prev_scope = scope[cur_scope];
							declareFunctionflag = false;
							break;
						}
					}
				}
				break;
			case COMMA:
				cur_lex.lexema[0] = LEX_COMMA;
				cur_lex.sn = currentLine;
				LT::Add(lexTable, cur_lex);
				cur_lex.lexema[0] = NULL;
				break;
			case LEFT_BRACE:
				cur_lex.lexema[0] = LEX_LEFTBRACE;
				cur_lex.sn = currentLine;
				LT::Add(lexTable, cur_lex);
				cur_lex.lexema[0] = NULL;
				break;
			case RIGHT_BRACE:
				cur_lex.lexema[0] = LEX_BRACELET;
				cur_lex.sn = currentLine;
				LT::Add(lexTable, cur_lex);
				cur_lex.lexema[0] = NULL;
				break;
			case LEFTTHESIS:
				cur_lex.lexema[0] = LEX_LEFTTHESIS;
				cur_lex.sn = currentLine;
				LT::Add(lexTable, cur_lex);
				cur_lex.lexema[0] = NULL;
				if (declareFunctionflag || Functionflag && lexTable.table[lexTable.size - 3].lexema[0] == LEX_FUNCTION)
				{
					for (int i = idTable.size - 1; i >= 0; i--) {
						if (idTable.table[i].idtype == IT::F) {
							scope[idTable.table[i].id] = cur_scope;
							prev_scope = cur_scope;
							cur_scope = idTable.table[i].id;
							break;
						}
					}
				}
				break;
			case RIGHTTHESIS:
				cur_lex.lexema[0] = LEX_RIGHTTHESIS;
				cur_lex.sn = currentLine;
				LT::Add(lexTable, cur_lex);
				cur_lex.lexema[0] = NULL;
				break;
			case PLUS:
				cur_lex.lexema[0] = LEX_PLUS;
				cur_lex.sn = currentLine;
				LT::Add(lexTable, cur_lex);
				cur_lex.lexema[0] = NULL;
				break;
			case MINUS:
				cur_lex.lexema[0] = LEX_MINUS;
				LT::Add(lexTable, cur_lex);
				cur_lex.lexema[0] = NULL;
				break;
			case STAR:
				cur_lex.lexema[0] = LEX_STAR;
				cur_lex.sn = currentLine;
				LT::Add(lexTable, cur_lex);
				cur_lex.lexema[0] = NULL;
				break;
			case DIRSLASH:
				cur_lex.lexema[0] = LEX_DIRSLASH;
				cur_lex.sn = currentLine;
				LT::Add(lexTable, cur_lex);
				cur_lex.lexema[0] = NULL;
				break;
			case EQUAL:
				cur_lex.lexema[0] = LEX_EQUAL;
				cur_lex.sn = currentLine;
				LT::Add(lexTable, cur_lex);
				cur_lex.lexema[0] = NULL;
				break;
			}
		}
		currentLine = 1;
		LT_file << currentLine;
		LT_file << '\t';
		for (int i = 0; i < lexTable.size; i++)
		{
			cur_lex = LT::GetEntry(lexTable, i);
			if (currentLine != cur_lex.sn)
			{
				currentLine = cur_lex.sn;
				LT_file << '\n';
				LT_file << currentLine;
				LT_file << '\t';
			}
			LT_file << cur_lex.lexema[0];
		}
		LT_file.close();
		IT_file << std::setw(10) << "id"
			<< std::setw(20) << "datatype"
			<< std::setw(20) << "idtype"
			<< std::setw(20) << "Line"
			<< std::setw(20) << "value"
			<< std::setw(20) << "Scope" << std::endl;

		for (int i = 0; i < idTable.size; i++) {
			cur_iden = IT::GetEntry(idTable, i);
			IT_file << std::setw(10) << cur_iden.id;
			if (cur_iden.iddatatype == 1)
				IT_file << std::setw(20) << "INT";
			if (cur_iden.iddatatype == 2)
				IT_file << std::setw(20) << "STR";
			if (cur_iden.idtype == IT::V)
				IT_file << std::setw(20) << "V";
			if (cur_iden.idtype == IT::L)
				IT_file << std::setw(20) << "L";
			if (cur_iden.idtype == IT::F)
				IT_file << std::setw(20) << "F";
			if (cur_iden.idtype == IT::P)
				IT_file << std::setw(20) << "P";
			IT_file << std::setw(20) << cur_iden.idxfirstLE;

			if ((cur_iden.iddatatype == IT::INT) && cur_iden.idtype == IT::L) {
				IT_file << std::setw(20) << cur_iden.value.vint;
			}
			if ((cur_iden.iddatatype == IT::INT  || cur_iden.iddatatype == IT::STR) && cur_iden.idtype != IT::L) {
				IT_file << std::setw(20) << ' ';
			}
			if (cur_iden.iddatatype == IT::STR && cur_iden.idtype == IT::L) {
				IT_file << std::setw(16);
				for (int j = 0; j < strlen(cur_iden.value.vstr->str); j++) {
					IT_file << cur_iden.value.vstr->str[j];
				}
				IT_file << std::setw(20);
			}
			IT_file << std::setw(20);
			IT_file << std::setw(20) << cur_iden.scope_name;
			IT_file << std::endl;
		}
		IT_file.close();
		lexResult.idTable = idTable;
		lexResult.lexTable = lexTable;
		return lexResult;
	}
}