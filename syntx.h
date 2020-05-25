#pragma once
//�������������� ���������� �������� ������� ��������� �� ���������� ���������� �����
#include <iostream>
#include "lex.h"
#include "TagList.h"
#include "IdentTab.h"
#include "SyntxConstruct.h"
#include "AriphTree.h"
#include "Tree.h"
#include "Stack.h"
using namespace std;

class Syntx {
	private:
		SyntxConstruct nowStat = NON;	//������� ���������
		//SyntxConstruct parStat = NON;	//��������� ������
		SyntxConstruct ExprDet = NON;	//��������� ���������(������, ���������� ������ �������� �� bool)
		Token *nowEl = NULL;
		TagList tList;		//������� �����
		IdentTab idTab;		//������� ���������������
		AriphTree *arTree;	//������ ��� ������ ��������������� ���������
		Tree tree;
		TagList expr;		//���������, ������� � ���������� ���������� ��������� ������ ��� �������
		Stack stack;		//���� ��� ��������� ���������
		AriphTree *expressions[15];
		//������� ������
		bool On_P();	   //������ ���������
		bool On_Function();
		bool On_FuncCall();
		bool On_SetQ();
		bool On_Cond();
		bool On_ElseCond();
		bool On_ParFunc();
		bool On_ID();
		bool On_ListStruct();
		bool On_Num();
		bool On_FuncBlock();
		bool On_Expression();
		bool On_Predic();
		bool On_ListOperation();
		bool On_WriteLine();
		bool On_Cycle();
		bool On_If();
		bool On_List();
		bool On_LogicOperator();
		bool On_Member();
		bool On_Cons();
		bool On_Append();
		bool On_CarCdr();
		bool On_Concatenate();
		bool On_WriteToString();
	public:
		Syntx(TagList &, IdentTab &);
		~Syntx();
		void SyntxErr(string str) {
			cout << "Syntax Error:" << str << endl;
			system("pause");
			exit(1);
		}
		bool Parse(); //������� ������� ������� ���������
};