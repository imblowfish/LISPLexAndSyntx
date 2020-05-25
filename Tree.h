#pragma once
//промежуточное дерево программы
#include "IdentTab.h"
#include "SyntxConstruct.h"
#include "AriphTree.h"
using namespace std;

class Node {
private:

public:
	//значение, указатель на сына, указатель на родителя
	SyntxConstruct data;
	string val;
	string parent;
	AriphTree *expr;
	Token *ident;
	Node *next, *prev, *down, *up;
	Node() :next(NULL), prev(NULL), down(NULL), up(NULL), expr(NULL) {
		parent = ""; val = "";
	}
};

class Tree {
private:
	Node *root;					//корень(или begin)
	Node *position, *tmp, *tmp1;//текущая позиция
	Node *savePar;				//сохранение положения родителя текущего нода
	Node *expressions[15];
	Node *idents[51];
	int lvl;					//уровень дерева
	string prog;
	string nowFunction = "";
	int numExpr = 0;
	int numId = 0;
	//int numArr = 0;
	void Free(Node *);
	void FindExpr(Node *);
	void FindIdents(Node *);
	void AddExpr(Node *, AriphTree *);
public:
	Tree():root(NULL), position(NULL), tmp(NULL), savePar(NULL), tmp1(NULL){ 
		cout << "Tree constructor" << endl; 
		for (int i = 0; i < 15; i++) {
			expressions[i] = new Node();
		}
		for (int i = 0; i < 51; i++) {
			idents[i] = new Node();
		}
	}
	Tree(const Tree&);
	~Tree();
	//для тестирования
	void Add(SyntxConstruct, string name="");
	void LevelUp();							//перейти на 1 уровень выше в дереве
	void DeleteTree() {
		Free(root);
		root = NULL;
	}
	void LevelDown();						//на 1 ниже в дереве
	void Show();							//отображение дерева
	void ConnectExpr(AriphTree *[15]);			//связывание выражений с пром. деревом
	void ConnectIdents(IdentTab *);
};