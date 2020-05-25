#include "stdafx.h"
#include "AriphTree.h"

AriphTree::AriphTree(const AriphTree&) {
	cout << "BinTree copy constructor" << endl;
}

AriphTree::~AriphTree() {
	cout << "AriphTree destructor" << endl;
	//getchar();
}

void AriphTree::Add(TagList &tList) {
	//процесс разбора входящего TagList на дерево
	cout << "Expression was added in AriphTree" << endl;
	//cout << "In bin Tree TagList" << endl;
	tList.ShowTagList();
	Parse(tList);
	//Show(root);
	//Free(root);
	/*Parse(tList);
	Show(root);
	Free(root);
	root = NULL;
	pos = NULL;
	save = NULL;
	tab = "";
	lvl = 0;*/
	//getchar();
}

void AriphTree::Parse(TagList &tList) {
	cout << "Parse Expression" << endl;
	Token t;
	while (tList.GetEl(t)) {
		AddEl(t);
		//Show(root);
		//getchar();
	}
}

void AriphTree::AddEl(Token &t) {
	//переписать под скобки
	cout << "READ ELEMENT " << t._value << endl;
	if (t._type == LPAR) {
		if (!root) {
			cout << "!root LPAR" << endl;
			return;
		}
		else if (last != "el") LevelDown();
		return;
	} else if (t._type == RPAR && last=="el") {
		LevelUp();
		return;
	}
	if (t._type > NUM && t._type < LOCALID) {
		if (root == NULL) {
			cout << "Add root" << endl;
			root = new AriphNode();
			root->data = t;
			pos = root;
			last = "sign";
			return;
		}
		tmp = pos;
		if (!tmp) {
			tmp = new AriphNode();
			tmp->data = t;
			tmp->parent = save;
			pos = tmp;
			save->child = pos;
			return;
		}
		cout << "Add sign" << endl;
		while (tmp->next) tmp = tmp->next;
		tmp->next = new AriphNode();
		tmp->next->prev = tmp;
		tmp = tmp->next;
		if (pos->parent) tmp->parent = pos->parent;
		tmp->data = t;
		pos = tmp;
		last = "sign";
		return;
	} else {
		if(last == "sign") LevelDown();
		cout << "Add el" << endl;
		tmp = pos;
		if (!tmp) {
			tmp = new AriphNode();
			tmp->data = t;
			tmp->parent = save;
			pos = tmp;
			save->child = pos;
			last = "el";
			return;
		}
		while (tmp->next) tmp = tmp->next;
		tmp->next = new AriphNode();
		tmp->next->prev = tmp;
		tmp = tmp->next;
		if (pos->parent) tmp->parent = pos->parent;
		tmp->data = t;
		pos = tmp;
		last = "el";
		return;
	}
}

void AriphTree::Free(AriphNode *node) {
	if (!node) return;
	AriphNode *check;
	check = node;
	while (check) {
		if (check->child) {
			cout << check->data._value << " go to child" << endl;
			Free(check->child);
		}
		tmp1 = check;
		cout << "Delete " << tmp1->data._value << endl;
		check = check->next;
		delete tmp1;
	}
}

void AriphTree::Show(AriphNode *node) {
	if (!node) {
		cout << "!node in Show" << endl;
		return;
	}
	AriphNode *check;
	check = node;
	int i;
	while (check) {
		i = 0;
		tab = "";
		while (i < lvl) {
			tab += '\t';
			i++;
		}
		cout<<tab << check->data._value << endl;
		cout <<tab<< "------" << endl;
		if (check->child) {
			lvl++;
			Show(check->child);
			tmp1 = NULL;
			lvl--;
		}
		check = check->next;
	}
}

void AriphTree::LevelUp() {
	if (!pos) {
		cout << "!pos levelUp" << endl;
		return;
	}
	if (pos->parent) {
		cout << "Level up" << endl;
		pos = pos->parent;
	} else {
		cout << "First level" << endl;
		return;
	}
}

void AriphTree::LevelDown() {
	if (!pos) return;
	cout << "level down" << endl;
	save = pos;
	pos = pos->child;
}