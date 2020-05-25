#include "stdafx.h"
#include <iostream>
#include "IdentTab.h"
using namespace std;

static int level = 0;

IdentTab::~IdentTab() {
	cout << "IdentTab destructor" << endl;
	this->Free();
	cout << "IdentTab list are free" << endl;
	return;
}

void IdentTab::Free() {
	if (begin == NULL) {
		//cout << "List = NULL" << endl;
		return;
	}
	if (begin->next == NULL) {
		if (begin->child != NULL) DelChild(*begin);
		delete begin;
		//cout << "List free one element" << endl;
		return;
	}
	tmp = begin;
	while (tmp) {
		begin = tmp->next;
		if (tmp->child != NULL) {
			DelChild(*tmp);
		}
		delete tmp;
		tmp = begin;
	}
	delete begin;
}

IdentTab::IdentTab(const IdentTab &idTab) {
	//cout << "IdentTab Copy constructor" << endl;
	//getchar();
	Token *temp = idTab.begin;
	Token *temp1;
	while (temp) {
		this->AddElement(*temp);
		if (temp->child) {
			temp1 = temp->child;
			while (temp1) {
				this->AddChildEl(*temp, *temp1);
				temp1 = temp1->next;
			}
		}
		temp = temp->next;
	}
	temp = NULL;
	temp1 = NULL;
	return;
}

void IdentTab::Copy(IdentTab &idTab) {
	this->Free();
	if (idTab.begin == NULL) {
		return;
	}
	Token *temp = idTab.begin;
	Token *temp1;
	while (temp) {
		this->AddElement(*temp);
		if (temp->child != NULL) {
			temp1 = temp->child;
			while (temp1) {
				this->AddChildEl(*temp, *temp1);
				temp1 = temp1->next;
			}
		}
		temp = temp->next;
	}
	temp = temp1 = NULL;
}

void IdentTab::AddElement(Token &id) {
	Token *check;
	check = FindEl(id);
	if (check != NULL) {
		//cout << "Element is already exist" << endl;
		check = NULL;
		return;
	}
	if (begin == NULL) {
		begin = new Token();
		begin->_value = id._value;
		begin->_type = id._type;
		begin->next = NULL;
		begin->prev = NULL;
		//cout << "Element with name " << id._value << " is added in IdentTab" << endl;
		return;
	}
	tmp = begin;
	if (begin->next == NULL) {
		begin->next = new Token();
		tmp = begin->next;
		tmp->_value = id._value;
		tmp->_type = id._type;
		tmp->next = NULL;
		tmp->prev = begin;
		check = NULL;
		//cout << "Element with name " << id._value << " is added in IdentTab" << endl;
		return;
	}
	while (tmp->next) tmp = tmp->next;
	tmp->next = new Token();
	tmp1 = tmp;
	tmp = tmp->next;
	tmp->_value = id._value;
	tmp->_type = id._type;
	tmp->next = NULL;
	tmp->prev = tmp1;
	tmp = begin;
	check = NULL;
	//cout << "Element with name " << id._value << " is added in IdentTab" << endl;
	return;
}

void IdentTab::AddChildEl(Token &parentId, Token &childId) {
	childId.parent = &parentId;
	if (parentId._value == childId._value) {
		//cout << "Child and parent names are equals" << endl;
		return;
	}
	if (begin == NULL) {
		//cout << "List = NULL" << endl;
		return;
	}
	Token *check;
	check = FindEl(childId);
	if (check != NULL) return;
	check = FindEl(parentId);
	if (check == NULL) return;
	if (check->child == NULL) {
		check->child = new Token();
		tmp1 = check->child;
		tmp1->_value = childId._value;
		tmp1->_type = childId._type;
		tmp1->next = NULL;
		tmp1->prev = NULL;
		tmp1->parent = check;
		check = NULL;
		//cout << "Element with name " << childId._value << " is added as a child of element " << parentId._value << endl;
		return;
	}
	tmp1 = check->child;
	while (tmp1->next) tmp1 = tmp1->next;
	tmp1->next = new Token();
	tmp1->next->parent = check;
	tmp1 = tmp1;
	tmp1 = tmp1->next;
	tmp->prev = tmp1;
	tmp1->next = NULL;
	tmp1->_value = childId._value;
	tmp1->_type = childId._type;
	check = NULL;
	//cout << "Element with name " << childId._value << " is added as a child of element " << parentId._value << endl;*/
	return;
}

void IdentTab::ShowIdentTab() {
	cout << "Show IdentTab elements" << endl;
	if (begin == NULL) {
		cout << "Can't show, because IdentTab is empty" << endl;
		return;
	}
	tmp = begin;
	while (tmp) {
		cout << "-----------------" << endl;
		cout << "Name: " << tmp->_value << endl;
		cout << "Type: " << types[tmp->_type] << endl;
		if (tmp->child != NULL) ShowChild(*tmp);
		tmp = tmp->next;
	}
	cout << "-----------------" << endl;
}

void IdentTab::ShowChild(Token &id) {
	level++;
	if (id.child == NULL) {
		cout << "List child are free" << endl;
		return;
	}
	Token *el;
	el = id.child;
	string tab = "";
	int i=0;
	while (i < level) {
		tab += "\t";
		i++;
	}
	while (el) {
		cout << tab << "***********" << endl;
		cout << tab << "Name: " << el->_value << endl;
		cout << tab << "Type: " << types[el->_type] << endl;
		cout << tab << "Parent: " << el->parent->_value << endl;
		if (el->child) ShowChild(*el);
		el = el->next;
	}
	cout << tab << "***********" << endl;
	el = NULL;
	level--;
	return;
}

void IdentTab::DelChild(Token &id) {
	if (id.child == NULL) {
		//cout << "List child are free" << endl;
		return;
	}
	Token *el;
	el = id.child;
	while (el) {
		id.child = id.child->next;
		delete el;
		el = id.child;
	}
	id.child = NULL;
	//cout << "All child of element "<<id._value<< " are free" << endl;
	return;
}

Token* IdentTab::FindEl(Token &id) {
	tmp = begin;
	while (tmp) {
		if (tmp->_value == id._value) return tmp;
		if (tmp->child) {
			tmp1 = tmp->child;
			while (tmp1) {
				if (tmp1->_value == id._value) {
					if (tmp1->parent->_value == id.parent->_value) return tmp1;
				}
				tmp1 = tmp1->next;
			}
		}
		tmp = tmp->next;
	}
	return NULL;
}

void IdentTab::AddVal(Token &id, Token &val) {
	//cout << "Element with name " << id._value << " initialized with value " << val._value << endl;
	return;
}