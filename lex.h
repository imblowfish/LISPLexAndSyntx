#pragma once
//символы поступают в лекс. анализатор из входного потока и преобразуются в лексемы, затем раскидываются по таблице символов
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "TokenType.h"
using namespace std;

//множество состояний
enum Statement {S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S111}; //S111 последнее состояние

//множество выходных сигналов
enum Output {O0, O1, O2, O3, O4, O5, O6, O7, O8, O9, O10, O11, O12, O13, O14, O111};	   //O111 ошибка

typedef pair<Statement, Output> Result; //пара(Новое состояние & выходной сигнал)
typedef pair<Statement, char> Input;	//пара(Текущее состояние & вх символ)
typedef pair<Input, Result> Item;		//Элемент таблицы переходов
extern map<Input, Result> M;			//Таблица переходов кон автомата

class Lex {
	private:
		char Characters[12] = { '+','-','(', ')', '*', '/', '>', '<', '\'', '"', ',', '='}; //арифм. символы
		ifstream file;
		string ResWord[27] = {"setf", "defvar", "cons", "defun", "cond", "equal", "write-line", //зарезервированные слова
							 "setq", "concatenate", "write-to-string", "t", "T", "member",
							 "not", "null", "nil", "car", "cdr", "sqrt", "append", "if", "for", 
							 "loop", "do", "from", "to", "or"};	
		std::iostream::pos_type _position;					//указатель на сохраненный фрагмент потока
		string Trim(const string &str);
		char IgnoringComment(char);
		bool IsReserved(string);	//при прочтении идентификатора, проверяем слово с рез. словами, если совпадение есть, делаем тип токена RES
		void Init(void);			//инициализация таблицы КА
		inline void LexErr(string str) {
			cout << "Error lex: " << str << endl;
			getchar();
			exit(1);
		}
	public:
		Lex(const char *filename);
		~Lex();
		bool GetToken(Token &);		//получение очередной лексемы
		void SaveStatement();		//сохранение состояния
		void RollBack();			//откат к сохраненному состоянию
};
