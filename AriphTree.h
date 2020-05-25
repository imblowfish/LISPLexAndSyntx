#pragma once
#include <iostream>
#include <string>
#include "IdentTab.h"
#include "TagList.h"
#include "Stack.h"
using namespace std;
//дерево для записи арифметических выражений
class AriphNode {
private:

public:
	//левый правый сыновья, значение
	Token data;
	AriphNode *next, *prev;
	AriphNode *child;
	AriphNode *parent;
	AriphNode():child(NULL), parent(NULL), next(NULL), prev(NULL){}
};

class AriphTree {
private:
	//корень
	string expr;
	AriphNode *root;
	AriphNode *tmp, *tmp1, *save;
	AriphNode *pos;
	string tab = "";
	string last = "";
	int lvl = 0;
	void AddEl(Token &);
	void Parse(TagList&);
	void Show(AriphNode *);
	void Free(AriphNode *);
	void LevelDown();
	void LevelUp();
public:
	AriphTree():root(NULL), tmp(NULL), tmp1(NULL), save(NULL), pos(NULL){ cout << "BinTree constructor" << endl; }
	AriphTree(const AriphTree&);
	~AriphTree();
	void Add(TagList&);
	void ()
	void ShowTree() {
		Show(this->root); getchar();
	}
	void DeleteTree() {
		Free(this->root);
		root = NULL;
		pos = NULL;
		save = NULL;
		tab = "";
		lvl = 0;
		last = "";
	}
};