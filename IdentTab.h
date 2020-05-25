#pragma once
#include "TokenType.h"
#include <iostream>
using namespace std;
//������� ���������������
class IdentTab {
private:
	Token data;							//������� �����
	Token *begin;						//��������� �� 1 ������� ������		
	Token *tmp, *tmp1;
public:
	IdentTab() :begin(NULL), tmp(NULL), tmp1(NULL) {}
	IdentTab(const IdentTab &);
	~IdentTab();
	void Copy(IdentTab&);
	void Free();
	void AddElement(Token&);			//���������� �������� � �������
	void AddChildEl(Token&, Token&);	//���������� �������� ��� �������� � ������-���� ������� ��������
	void DelChild(Token&);				//�������� �������� ���������
	Token* FindEl(Token&);				//����� �������� � �������
	void AddVal(Token&, Token&);		//���������� �������� ��������
	void ShowIdentTab();				//����� ������� �� �����
	void IdentTab::ShowChild(Token&);	//���������� ����� ��������
};