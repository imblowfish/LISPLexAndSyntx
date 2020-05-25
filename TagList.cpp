#include "stdafx.h"
#include "TagList.h"

TagList::TagList() {
	cout << "TagList constructor" << endl;
	//getchar();
	begin = NULL;
	tmp = NULL;
	tmp1 = NULL;
}
//конструктор копирования
TagList::TagList(const TagList &t){
	Token *temp = t.begin;
	while (temp->next) {
		this->AddOne(*temp);
		temp = temp->next;
	}
	this->AddOne(*temp);
	this->tmp = this->begin;
	cout << "TagList copyConstructor" << endl;
}
TagList::~TagList() {//уничтожитель всего и вся. Инквизитор, бог империума, стиратель, судья и палач в одном лице
	cout << "TagList destructor" << endl;
	if (begin == NULL) { //если первый элемент(и т.д.) См в палеховой 2 семак
		cout << "List = NULL" << endl;
		//cout << "List free No el" << endl;
		return;
	}
	if (begin->next == NULL) {
		//cout << "One el" << endl;
		cout << "List free One Element" << endl;
		delete begin;
		return;
	}
	tmp = begin;
	while (tmp) {
		begin = tmp->next;
		//cout << "delete "<< tmp->_value << endl;
		delete tmp;
		tmp = begin;
	}
	delete begin;
	cout << "TagList list are free" << endl;
	//getchar();
	return;
}
//добавление элемента в конец списка
void TagList::AddOne(Token &t) {
	//cout << "Lexem: '" << t._value << "' " << "Type: " << t._type << endl;
	if (begin == NULL) {
		begin = new Token();
		//cout << "First el" << endl;
		//getchar();
		begin->_type = t._type;
		begin->_value = t._value;
		begin->next = NULL;
		//cout << "Lexem is first added " << begin->_value << endl;
		//getchar();
		return;
	}
	tmp = begin;
	if (begin->next == NULL) {
		tmp->next = new Token();
		tmp = tmp->next;
		tmp->_type = t._type;
		tmp->_value = t._value;
		tmp->next = NULL;
		tmp->prev = begin;
		//cout << "Lexem is two added " << tmp->_value<<endl;
		//getchar();
		return;
	}
	while (tmp->next) tmp = tmp->next;
	tmp->next = new Token();
	tmp1 = tmp;
	tmp = tmp->next;
	tmp->_type = t._type;
	tmp->_value = t._value;
	tmp->next = NULL;
	tmp->prev = tmp1;
	begin->prev = NULL;
	//cout << "Lexem is added " << tmp->_value<<endl;
	tmp = begin;
	tmp1 = NULL;
	return;
}
//на один элемент назад
bool TagList::Back() {
	if (tmp->prev) {
		tmp = tmp->prev;
		return true;
	}
	else{
		cout << "First element" << endl;
		return false;
	}
}
//очистка
void TagList::Free() {
	if (begin == NULL) { //если первый элемент(и т.д.) См в палеховой 2 семак
		cout << "List = NULL" << endl;
		//cout << "List free No el" << endl;
		return;
	}
	if (begin->next == NULL) {
		//cout << "One el" << endl;
		cout << "List free One Element" << endl;
		delete begin;
		return;
	}
	tmp = begin;
	while (tmp) {
		begin = tmp->next;
		//cout << "delete "<< tmp->_value << endl;
		delete tmp;
		tmp = begin;
	}
	delete begin;
	tmp1 = NULL;
	cout << "TagList list are free" << endl;
	//getchar();
	return;
}
//на один вперед
bool TagList::Next() {
	if (tmp->next) {
		//cout << "Cur el " << tmp->_value << endl;
		//cout << "Next el " << tmp->next->_value << endl;
		tmp = tmp->next;
		//getchar();
		return true;
	}
	else {
		//cout << "Last element" << endl;
		return false;
	}
}
//проверить, является ли текущий элемент последним
bool TagList::CheckNext() {
	if (tmp->next) return true;
	return false;
}
bool TagList::GetEl(Token &t) {
	if (!tmp1) {
		tmp1 = begin;
		t._value = tmp1->_value;
		t._type = tmp1->_type;
		return true;
	}
	if (!tmp1->next) return false;
	else {
		tmp1 = tmp1->next;
		t._value = tmp1->_value;
		t._type = tmp1->_type;
		return true;
	}
}
void TagList::GoToBegin() {
	tmp1 = begin;
	return;
}
void TagList::DelEl() {
	Token* del;
	del = tmp1;
	tmp1 = tmp1->next;
	tmp1->prev = del->prev;
	delete del;
	del = NULL;
}

//выводит текущий элемент
bool TagList::Show(Token &t) {
	if (tmp) {
		//cout << "val=" << tmp->_value << " type=" << tmp->_type << endl;
		t._value = tmp->_value;
		t._type = tmp->_type;
		if (tmp->parent && tmp->_type == LOCALID) {
			t.parent = new Token();
			t.parent->_value = tmp->parent->_value;
		}
		this->Next();
		return true;
	}
	else return false;
	//cout << "val=" << tmp->_value << " type=" << tmp->_type << endl;
}
//показывает список тегов
void TagList::ShowTagList() {
	if (begin == NULL) {
		cout << "List = NULL" << endl;
		return;
	}
	tmp = begin;
	while (tmp->next) {
		cout << "Lexem: '" << tmp->_value << "' " << "Type: " << types[tmp->_type] << endl;
		tmp = tmp->next;
	}
	cout << "Lexem: '" << tmp->_value << "' " << "Type: " << types[tmp->_type] << endl;
	tmp = begin;
	return;
}
//сохранение состояния(аналог из lisp.cpp
void TagList::SaveStatement() {
	_position = tmp;
	//cout << "Save statement " << _position->_value << endl;
}
//тоже самое
void TagList::RollBack() {
	tmp = _position;
	//cout << "RollBack to " << tmp->_value << endl;
}