#pragma once
#define LEXEMA_FIXSIZE 1	// ������������� ������ �������
#define LT_MAXSIZE 4096		// ������������ ������ ������� ������
#define LT_TI_NULLIDX 0xffffffff	// ��� ������ � ������� ���������������
#define LEX_INTEGER		't'	// ������� ��� ����� �����
#define LEX_STRING		't'	// ������� ��� �����
#define LEX_LITERAL		'l'	// ������� ��� ���������
#define LEX_ID			'i'	// ������� ��� ���������������
#define LEX_FUNCTION	'f'	// ������� ��� �������
#define LEX_MAINFUNC	'm'	// ������� ��� ������� �������
#define LEX_DECLARE		'd'	// ������� ��� ����������
#define LEX_RETURN		'r'	// �������� ����� return
#define LEX_PRINT		'p'	// �������� ����� print
#define LEX_SEMICOLON	';'	// ;
#define LEX_COMMA		','	// ,
#define LEX_LEFTBRACE	'{'	// {
#define LEX_RIGHTBRACE	'}'	// }
#define LEX_LEFTHESIS	'('	// (
#define LEX_RIGHTHESIS	')'	// )
#define LEX_PLUS		'v'	// +
#define LEX_MINUS		'v'	// -
#define LEX_STAR		'v'	// *
#define LEX_DIRSLASH	'v'	// /
#define LEX_RAV			'='	// =
#define LIB_FUNCTION1 "substr"
#define LIB_FUNCTION2 "strlen"


namespace LT	// ������������ ���� ��� ������� ������
{
	struct Entry	// ��������� ��� ������������� ������ � ������� ������
	{
		unsigned char lexema;	/// �������
		int sn;			/// ����� ������ � �������� ����
		int idxTI;		/// ������ � ������� ��������������� ��� LT_TI_NULLIDX
		std::string comm{};
	};

	struct LexTable		// ��������� ��� ������� ������
	{
		int maxsize;	/// ������������ ������ ������� < LT_MAXSIZE
		int size;		/// ������� ������ ������� < maxsize
		Entry* table;	/// ������ ������� ������� ������
	};

	LexTable Create( // ������� ������� ������
		int size	/// ������ ������� ������ < LT_MAXSIZE
	);
	void Add(				// �������� ������ � ������� ������
		LexTable& lextable, /// ������ �� ������� ������
		Entry entry			/// ������ ��� ����������
	);

	Entry GetEntry(			// �������� ������ �� ������� ������ �� �������
		LexTable& lextable,	/// ������ �� ������� ������
		int n				/// ������ ������
	);

	void Delete(LexTable& lextable); // ������� ������� ������ (���������� ������)
};
