#pragma once
//������������� ������ ���������
#include "IdentTab.h"
#include "SyntxConstruct.h"
#include "AriphTree.h"
using namespace std;

class Node {
private:

public:
	//��������, ��������� �� ����, ��������� �� ��������
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
	Node *root;					//������(��� begin)
	Node *position, *tmp, *tmp1;//������� �������
	Node *savePar;				//���������� ��������� �������� �������� ����
	Node *expressions[15];
	Node *idents[51];
	int lvl;					//������� ������
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
	//��� ������������
	void Add(SyntxConstruct, string name="");
	void LevelUp();							//������� �� 1 ������� ���� � ������
	void DeleteTree() {
		Free(root);
		root = NULL;
	}
	void LevelDown();						//�� 1 ���� � ������
	void Show();							//����������� ������
	void ConnectExpr(AriphTree *[15]);			//���������� ��������� � ����. �������
	void ConnectIdents(IdentTab *);
};