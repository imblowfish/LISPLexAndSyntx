#pragma once
//таблица тегов(токенов)
#include <iostream>
#include "TokenType.h"
using namespace std;
class TagList {
private:
	Token token;
	Token *begin;
	Token *tmp, *tmp1;
	Token *_position;
public:
	TagList();
	TagList(const TagList &);
	void Free();
	~TagList();
	void AddOne(Token &t);
	bool Back();
	bool Next();
	bool CheckNext();
	bool Show(Token&);
	void ShowTagList();
	void SaveStatement();
	void RollBack();
	void GoToBegin();
	void DelEl();
	bool GetEl(Token &);
};