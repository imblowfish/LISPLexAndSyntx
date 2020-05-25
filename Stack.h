#pragma once
#include <iostream>
#include "TokenType.h"
using namespace std;
class Stack {
private:
	Token *top;
	Token *tmp, *tmp1;
public:
	Stack() :top(NULL), tmp(NULL), tmp1(NULL) { cout << "Stack constructor" << endl; }
	~Stack();
	Token Pop();
	void Push(Token&);
	bool Empty();
	Token* ShowTop();		
};