#pragma once
#include "TokenType.h"
#include <iostream>
using namespace std;
//таблица идентификаторов
class IdentTab {
private:
	Token data;							//текущий токен
	Token *begin;						//указатель на 1 элемент списка		
	Token *tmp, *tmp1;
public:
	IdentTab() :begin(NULL), tmp(NULL), tmp1(NULL) {}
	IdentTab(const IdentTab &);
	~IdentTab();
	void Copy(IdentTab&);
	void Free();
	void AddElement(Token&);			//добавление элемента в таблицу
	void AddChildEl(Token&, Token&);	//добавление элемента как дочерний к какому-либо другому элементу
	void DelChild(Token&);				//удаление дочерних элементов
	Token* FindEl(Token&);				//поиск элемента в таблице
	void AddVal(Token&, Token&);		//добавление значения элементу
	void ShowIdentTab();				//вывод таблицы на экран
	void IdentTab::ShowChild(Token&);	//показывает детей элемента
};