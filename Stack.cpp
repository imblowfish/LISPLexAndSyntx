#include "stdafx.h"
#include <iostream>
#include <string>
#include "Stack.h"
using namespace std;

Stack::~Stack() {
	while (!Empty()) Pop();
	cout << "Stack destructor" << endl;
}

Token Stack::Pop() {
	Token t;
	tmp = top;
	top = top->prev;
	t._value = tmp->_value;
	t._type = tmp->_type;
	delete tmp;
	return t;
}

void Stack::Push(Token &t) {
	if (top == NULL) {
		top = new Token();
		top->_value = t._value;
		top->_type = t._type;
		top->next = NULL;
		top->prev = NULL;
		cout << "Element " << t._value << " is added in stack" << endl;
		//getchar();
		return;
	}
	tmp = top;
	tmp->next = new Token();
	tmp = tmp->next;
	tmp->_value = t._value;
	tmp->_type = t._type;
	tmp->prev = top;
	tmp->next = NULL;
	top = tmp;
	cout << "Element " << t._value << " is added in stack" << endl;
	//getchar();
}

bool Stack::Empty() {
	if (top ==  NULL) return true;
	else return false;
}

Token* Stack::ShowTop() {
	if (Empty()) return NULL;
	return top;
}