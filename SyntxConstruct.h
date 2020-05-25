#pragma once
#include <string>
using namespace std;
//класс синтаксических конструкций, которыми будет заполняться пром дерево
static string sConstruct[28] = { "P", "Apnd", "CrCdr", "Cond", "Conc", "Cons", "Cycle", "ElCnd", "Expr",
								 "FCall", "FBlock", "Func", "If","LogOp", "ListOp", "List",
								 "ListSt", "Memb", "ParF", "Pred", "SetQ", "WriteL",  "WrTStr", "String", 
								 "Id", "Num", "NIL", "NON"};
//набор синтаксических конструкций языка(требуется для построения дерева
enum SyntxConstruct {
	P,				//0
	APPEND,			//1
	CARCDR,			//2
	COND,			//3
	CONCATENATE,	//4	
	CONS,			//5
	CYCLE,			//6
	ELSECOND,		//7
	EXPRESSION,		//8
	FUNCCALL,		//9
	FUNCBLOCK,		//10
	FUNCTION,		//11
	IF,				//12
	LOGICOPERATOR,	//13
	LISTOPERATION,	//14
	LIST,			//15
	LISTSTRUCT,		//16
	MEMBER,			//17
	PARFUNC,		//18
	PREDIC,			//19
	SETQ,			//20
	WRITELINE,		//21
	WRITETOSTRING,	//22
	STRINGVAL,		//23
	IDVAL,			//24
	NUMVAL,			//25
	NIL,			//26
	NON				//27
};