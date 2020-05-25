#pragma once
//������� ��������� � ����. ���������� �� �������� ������ � ������������� � �������, ����� ������������� �� ������� ��������
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "TokenType.h"
using namespace std;

//��������� ���������
enum Statement {S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S111}; //S111 ��������� ���������

//��������� �������� ��������
enum Output {O0, O1, O2, O3, O4, O5, O6, O7, O8, O9, O10, O11, O12, O13, O14, O111};	   //O111 ������

typedef pair<Statement, Output> Result; //����(����� ��������� & �������� ������)
typedef pair<Statement, char> Input;	//����(������� ��������� & �� ������)
typedef pair<Input, Result> Item;		//������� ������� ���������
extern map<Input, Result> M;			//������� ��������� ��� ��������

class Lex {
	private:
		char Characters[12] = { '+','-','(', ')', '*', '/', '>', '<', '\'', '"', ',', '='}; //�����. �������
		ifstream file;
		string ResWord[27] = {"setf", "defvar", "cons", "defun", "cond", "equal", "write-line", //����������������� �����
							 "setq", "concatenate", "write-to-string", "t", "T", "member",
							 "not", "null", "nil", "car", "cdr", "sqrt", "append", "if", "for", 
							 "loop", "do", "from", "to", "or"};	
		std::iostream::pos_type _position;					//��������� �� ����������� �������� ������
		string Trim(const string &str);
		char IgnoringComment(char);
		bool IsReserved(string);	//��� ��������� ��������������, ��������� ����� � ���. �������, ���� ���������� ����, ������ ��� ������ RES
		void Init(void);			//������������� ������� ��
		inline void LexErr(string str) {
			cout << "Error lex: " << str << endl;
			getchar();
			exit(1);
		}
	public:
		Lex(const char *filename);
		~Lex();
		bool GetToken(Token &);		//��������� ��������� �������
		void SaveStatement();		//���������� ���������
		void RollBack();			//����� � ������������ ���������
};
