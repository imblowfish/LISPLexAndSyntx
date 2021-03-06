#include "stdafx.h"
#include "lex.h"
#include "syntx.h"
#include "TagList.h"
#include "IdentTab.h"
#include "Tree.h"
#include "AriphTree.h"
#include "Stack.h"
#include "TokenType.h"
using namespace std;

//файлы с программами
char* prog1 = "programs/quad.txt";
char* prog2 = "programs/sorting.txt";
char* prog3 = "programs/mult.txt";
char* prog4 = "programs/factorial.txt";
char* testprog = "programs/testprog.txt"; //для тестирования конструкций(по сути не требуется)

#define LEXICAL							  //для тестирования лексического анализатора
#define SYNTAX							  //для тестирования синт анализатора

//										ЗАДАЧИ
/*
	- синтаксический готов
*/

int main() {
#ifdef LEXICAL
	Lex lex(prog1);
	TagList tList;									//двусвязный список тегов
	IdentTab idTab;									//таблица идентификаторов
	Token token;									//токен для считывания из файла
	while (lex.GetToken(token)) tList.AddOne(token);//получаем токен из потока
	//tList.ShowTagList();							//просматриваем список тегов
#endif
#ifdef SYNTAX
	//здесь список тегов должен быть передан синтаксическому ан. для дальнейшего разбора
	Syntx syntx(tList, idTab);						//синтаксический анализатор, отправляет список тегов и пустую таблицу идент.
	idTab.ShowIdentTab();							//просматриваем таблицу идентификаторов
#endif
	system("pause");
    return 0;
}

