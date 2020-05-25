#pragma once
#include <string>
using namespace std;
//���� ������
static string types[20] = { "ID", "NUM", "PLUS", "MINUS", "LPAR", "RPAR", "MUL", "DIV", "MORE", "LESS",
						    "APOST", "QUOT", "COMMA", "EQUAL", "MOREEQ", "RES", "FUNCID", "PARID",
							"LOCALID", "STRING" };

enum TokenType {
	ID,		//������������� ���������� 0
	NUM,	//��������� 1
	PLUS,	// + 2
	MINUS,	// - 3
	LPAR,	// ( 4
	RPAR,	// ) 5
	MUL,	// * 6
	DIV,	// / 7
	MORE,	// > 8
	LESS,	// < 9
	APOST,  // ' 10
	QUOT,	// " 11
	COMMA,	// , 12
	EQUAL,	// = 13
	MOREEQ, // >= 14 
	RES,	//����������������� ����� 15
	FUNCID,	//������������� �������
	FUNCPAR,//�������� �������
	LOCALID,//��������� ����������
	STRING	//������ 16
};

class Token {
public:
	string _value;			//��������� ��������
	TokenType _type;		//��� �������
	Token *next, *prev;
	Token *child, *parent;	//��������� �� �������� �������� � �� ��������(���� ������� �������)		
	Token *val;				//������ �� �����, ������� �������� ��������� ��������������(���� �� ������)
	Token() { next = NULL; prev = NULL; child = NULL, parent = NULL, val = NULL, _value = ""; }
};