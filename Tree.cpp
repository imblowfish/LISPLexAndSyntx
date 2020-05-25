#include "stdafx.h"
#include "Tree.h"
//unsigned int lvl = 0;


Tree::Tree(const Tree&) {
	cout << "Tree copy constructor" << endl;
}

Tree::~Tree() {
	cout << "Tree destructor" << endl;
	if (root == NULL) {
		cout << "Tree = NULL" << endl;
		return;
	}
	for (int i = 0; i < 15; i++) expressions[i] = NULL;
	for (int i = 0; i < 51; i++) idents[i] = NULL;
	tmp = root;
	Free(tmp);
	root = NULL;
	//Free(root);
	cout << "Tree are free" << endl;
}

void Tree::Free(Node *n) {
	if (n == NULL) {
		cout << "Tree = NULL" << endl;
		getchar();
		return;
	}
	while (n->next) {
		if (n->down) {
			//cout << "Down" << endl;
			tmp = n->down;
			Free(tmp);
			tmp = NULL;
		}
		tmp = n;
		n = n->next;
		//cout << "DELETE" << endl;
		//cout << sConstruct[tmp->data] <<" "<< tmp->val<< endl;
		//if (n->next != NULL) cout << sConstruct[n->next->data] << endl;
		//getchar();
		delete tmp;
		tmp = NULL;
	}
	if (n->down) {
		//cout << "Down" << endl;
		tmp = n->down;
		Free(tmp);
		tmp = NULL;
	}
	/*if (n->up) {
		cout << "Up" << endl;
		tmp = n;
		n = n->up;
		delete tmp;
		tmp = NULL;
		Free(n);
		return;
	}*/
	/*cout << sConstruct[n->data] << endl;
	if (n->val != "") cout << n->val << endl;*/
	//cout << "DELETE" << endl;
	//cout << sConstruct[n->data] << " " << n->val << endl;
	delete n;
	n = NULL;
}

void Tree::Add(SyntxConstruct data, string name) {
	//cout << "Add "<< sConstruct[data] <<" in tree. LEVEL = "<<lvl << endl;
	//getchar();
	//дерево, которое заполняется в строку prog. Нужно для тестирования заполнения дерева
	int i = lvl;
	string tab;
	while (i != 0) {
		tab += "\t";
		i--;
	}
	prog += tab;
	prog += "->";
	prog += sConstruct[data];
	if (name != "") {
		prog += "\n";
		prog += tab;
		prog += "------";
		prog += "\n";
		prog += tab;
		prog += name;
		prog += "\n";
		prog += tab;
		prog += "------";
	}
	prog += "\n";

	//добавение элемента к дереву
	if (root == NULL) {
		cout << "root = NULL" << endl;
		root = new Node();
		root->data = data;
		root->val = name;
		position = root;
		//cout << sConstruct[root->data] << endl;
		//if(root->val!="") cout << root->val << endl;
		//getchar();
		return;
	}
	if (position != NULL) {
		position->next = new Node();
		tmp = position;
		position = position->next;
		position->data = data;
		position->val = name;
		position->down = NULL;
		if (tmp->up) position->up = tmp->up;
		position->prev = tmp;
		tmp = NULL;
		//getchar();
		return;
	} else {
		position = new Node();
		position->data = data;
		position->val = name;
		position->up = savePar;
		savePar->down = position;
		savePar = NULL;
		return;
	}
}

void Tree::LevelUp() {
	if (position->up == NULL) {
		cout << "Now is first lvl" << endl;
		getchar();
		return;
	}
	lvl--;
	position = position->up;
	//cout << "Level up. LEVEL = " <<lvl<< endl;
	//getchar();
}

void Tree::LevelDown() {
	lvl++;
	savePar = position;
	position = position->down;
	//cout << "Level down. LEVEL = " << lvl << endl;
	//getchar();
}

void Tree::Show() {
	cout << "Show Tree" << endl;
	cout << prog << endl;
	getchar();
}

void Tree::ConnectExpr(AriphTree *aTree[15]) {
	cout << "ConnectExpr" << endl;
	//поиск выражения
	FindExpr(root);
	for (int i = 0; i < numExpr; i++) {
		//cout << sConstruct[expressions[i]->data] << endl;
		//aTree[i]->ShowTree();
		AddExpr(expressions[i], aTree[i]);
		/*cout << "After equal" << endl;
		cout <<"parent = "<< sConstruct[expressions[i]->up->data] << endl;
		expressions[i]->expr->ShowTree();
		getchar();*/
	}
	cout << "All expressions are connected with AriphTrees" << endl;
	getchar();
}

void Tree::FindExpr(Node *n) {
	if (!n) {
		cout << "!n in FindExpr" << endl;
		return;
	}
	Node *check;
	check = n;
	while (check) {
		if (check->data == EXPRESSION) {
			expressions[numExpr] = check;
			if(numExpr<15)numExpr++;
			else {
				cout << "Tree expressions overflow" << endl;
				numExpr = 0;
			}
		}
		if (check->down) FindExpr(check->down);
		check = check->next;
	}
}

void Tree::AddExpr(Node *n, AriphTree *aT) {
	cout << "Add expression" << endl;
	if (!n->expr) {
		n->expr = new AriphTree();
		n->expr = aT;
		return;
	}
	n->expr = aT;
}

void Tree::ConnectIdents(IdentTab *idTab) {
	cout << "Connect Idents" << endl;
	Token t;
	t.parent = new Token();
	idTab->ShowIdentTab();
	FindIdents(root);
	for (int i = 0; i < numId; i++) {
		t._value = idents[i]->val;
		t.parent->_value = idents[i]->parent;
		cout << i<<" Ident value = " << idents[i]->val << endl;
		idents[i]->ident = idTab->FindEl(t);
		if (idents[i]->ident == NULL) {
			//cout << "Not found" << endl;
			//cout << t._value << endl;
		} else {
			//cout << "Found" << endl;
			//cout << idents[i]->ident->_value << endl;
		}
	}
	cout << "All ID's are connected" << endl;
	getchar();
}

void Tree::FindIdents(Node *n) {
	if (!n) return;
	Node *check = n;
	while (check) {
		if (check->data == IDVAL || check->data == FUNCTION || check->data == PARFUNC || check->data == FUNCCALL) {
			if (check->data == FUNCTION) nowFunction = check->val;
			if (check->data == IDVAL || check->data == PARFUNC || check->data == FUNCCALL) check->parent = nowFunction;
			idents[numId] = check;
			if (numId < 51) numId++;
			else {
				cout << "idents overflow" << endl;
				numId = 0;
				getchar();
			}
		}
		if (check->down) FindIdents(check->down);
		check = check->next;
	}
	return;
}