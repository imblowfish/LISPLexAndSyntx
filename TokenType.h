#pragma once
#include <string>
using namespace std;
//типы лексем
static string types[20] = { "ID", "NUM", "PLUS", "MINUS", "LPAR", "RPAR", "MUL", "DIV", "MORE", "LESS",
						    "APOST", "QUOT", "COMMA", "EQUAL", "MOREEQ", "RES", "FUNCID", "PARID",
							"LOCALID", "STRING" };

enum TokenType {
	ID,		//идентификатор переменной 0
	NUM,	//константа 1
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
	RES,	//зарезервированные слова 15
	FUNCID,	//идентификатор функции
	FUNCPAR,//параметр функции
	LOCALID,//локальная переменная
	STRING	//строка 16
};

class Token {
public:
	string _value;			//строковое значение
	TokenType _type;		//тип лексемы
	Token *next, *prev;
	Token *child, *parent;	//указатель на дочерние элементы и на родителя(если таковые имеются)		
	Token *val;				//ссылка на токен, который является значением идентификатора(либо на список)
	Token() { next = NULL; prev = NULL; child = NULL, parent = NULL, val = NULL, _value = ""; }
};