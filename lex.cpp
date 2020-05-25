#include "stdafx.h"
#include "lex.h"

map<Input, Result> M;	//таблицы переходов КА

//конструктор, в нем открываем файл и вызываем инициализацию КА
Lex::Lex(const char *filename) {
	cout << "Lex constructor" << endl;
	file.open(filename, ios::in);
	if (!file.is_open()) LexErr("Error open file");
	file.unsetf(ios::skipws);
	this->Init();
}

//деструктор, закрываем файл
Lex::~Lex() {
	file.close();
	cout << "Close file" << endl;
	cout << "Lex destructor" << endl;
	getchar();
}

//функция, удаляющая пробелы в строке
string Lex::Trim(const string &str) {
	string::const_iterator it1 = str.begin();
	string::const_iterator it2 = str.end();
	while (it1 != str.end() && (*it1 == ' ' || *it1 == '\n' || *it1=='\t' || *it1 == '"')) it1++;
	return string(it1, it2);
}

//ищем строку в списке зарезервированных слов
bool Lex::IsReserved(string str) {
	for (int i = 0; i<27; i++) {
		if(str == ResWord[i]) return true;
	}
	return false;
}

char Lex::IgnoringComment(char c) {
	if (c == ';') {
		while (c != '\n' && !file.eof()) file >> c;
	}
	else {
		int check = 0;					  //для проверки на правильность многострочных комментариев
		file >> c;
		check++;
		while (c != '#' && !file.eof()) { //пока не конец файла и не #
			if (c == '|') check--;
			file >> c;
		}
		check++;
		//если после прохода комментария значение check !=0, то содержится ошибка
		if (check != 0) LexErr("Error placing comments symbols"); 
		file >> c;
	}
	return c;
}

//чтение токенов из файла
bool Lex::GetToken(Token& token) {
	TokenType type;
	string value;			//строка для записи токена
	Statement current = S0; //начальное состояние
	Result res;				//результат поиска символа в таблице
	char c;
	
	map<Input, Result>::const_iterator it;
	while (!file.eof()) {
		file>>c;
		//cout << "Character " << c << endl;
		if (c == ';' || c=='#') c = IgnoringComment(c); //обработка комментариев
		if (file.eof()) {
			token._value = "End";
			continue;
		} //если комментарий в конце файла, continue и выход из цикла

		it = M.find(Input(current, c));					//ищем прочитанный символ в таблице состояний КА, записываем в it
		if (it == M.end()) {
			//cout << current << endl;
			LexErr("Incorrect character");				//если такого символа нет(указатель на M.end()), то неправильный символ
		}
		res = it->second;								//записываем в res Output для прочитанного символа
		//если арифметическая операция, переход к кон. состоянию, либо след. символ конец файла
		if ((res.first >= S3 && res.first <= S111) || file.peek() <= 0) { 
			if (res.first != S111) value += c;
			else file.seekg(-1, ios::cur);				//иначе возвращаем прочитанный символ в поток

			switch (res.second) {						//проверяем тип по типу токенов
			case O1:
				if (IsReserved(Trim(value))) type = RES;//если зарезрвировано, то тип RES
				else type = ID;							//иначе идентификатор
			break;
			case O2:
				type = NUM;
			break;
			case O3:
				type = PLUS;
			break;
			case O4:
				file >> c;
				if (c != '\n' && c != ' ' && c != '\t') { file.seekg(-1, ios::cur); continue; }
				file.seekg(-1, ios::cur);
				type = MINUS;
			break;
			case O5:
				type = LPAR;
			break;
			case O6:
				type = RPAR;
			break;
			case O7:
				type = MUL;
			break; 
			case O8:
				type = DIV;
				break;
			case O9:
				file >> c;
				if (c != '=') {
					file.seekg(-1, ios::cur);
					value = ">";
					type = MORE;
				}
				else {
					type = MOREEQ;
					value = ">=";
				}
				break;
			case O10:
				type = LESS;
				break;
			break;
			case O11:
				type = APOST;
				break;
			case O12:
				//обработка строк, подходит только для ситуации с языком, где строки записываются только между двойными кавычками
				//type = QUOT;
				file >> c; 
				while (!file.eof() && c != '"') { value += c; file >> c;}
				if (file.eof()) LexErr("String bracket error");
				type = STRING;
				value = Trim(value);
				break;
			case O13:
				type = COMMA;
				break;
			case O14:
				type = EQUAL;
				break;
			default:
				LexErr("Lexical Error");
			}
			token._type = type;						//записываем в токен значение типа
			token._value = Trim(value);				//избавляем строку от пробелов и записываем в токен
			return true;
		}
		current = res.first;						//если не арифм. и не переход к кон. состоянию, то сохраняем текущее состояние
		value += c;									//и накапливаем символ в строку
	}
	return false;
}

//инициализация таблицы переходов КА
void Lex::Init(void) {
	char c,c1,c2;
	//cout << "Character initialization..." << endl;
	//инициализация букв
	cout << "Letters" << endl;
	for (c = 65; c <= 90; c++) {
		cout << c << " ";
		cout << char(int(c+32)) << " ";
		M.insert(Item(Input(S0, c), Result(S1, O1)));
		M.insert(Item(Input(S0, char(int(c + 32))), Result(S1, O1)));
		M.insert(Item(Input(S1, c), Result(S1, O1)));
		M.insert(Item(Input(S1, char(int(c + 32))), Result(S1, O1)));
	}
	cout << endl << "Numbers" << endl;
	for (c = 48; c <= 57; c++) {
		cout << c << " ";
		M.insert(Item(Input(S0, c), Result(S2, O2)));
		M.insert(Item(Input(S1, c), Result(S1, O1)));
		M.insert(Item(Input(S2, c), Result(S2, O2)));
		M.insert(Item(Input(S3, c), Result(S2, O2)));
	}
	cout << endl << "Symbols" << endl;
	char symbols[4] = { '-', '>', '=', '<' };
	//символы, которые могут быть частью идентификатора. Да, некрасиво:(
	for(int i=0;i<4;i++) M.insert(Item(Input(S1, symbols[i]), Result(S1, O1)));
	//инициализация арифметических символов, скобок и т.д.
	for (int i = S3, j=0; i <= S14, j<12; i++, j++) {
		cout << Characters[j] << " ";
		M.insert(Item(Input(S0, Characters[j]), Result(Statement(i), Output(i))));
		M.insert(Item(Input(S1, Characters[j]), Result(S111, O1)));
		M.insert(Item(Input(S2, Characters[j]), Result(S111, O2)));
	}
	//пробелы
	c = ' ', c1 = '\n', c2='\t';
	int k = S0;
	cout << endl << "Blanks" << endl;
	for (int i = S0, j=O0; i <= S14, j <= O14; i++, j++) {
		M.insert(Item(Input(Statement(i), c), Result(Statement(k), Output(j))));
		M.insert(Item(Input(Statement(i), c1), Result(Statement(k), Output(j))));
		M.insert(Item(Input(Statement(i), c2), Result(Statement(k), Output(j))));
		k = S111;
	}
	cout << "Characters are initialized" << endl;
}
//две функции ниже не нужны, избавлюсь в ближайшее время, их заменяют аналоги из TagList
void Lex::SaveStatement() {
	_position = file.tellg();	//сохраняем указатель на нынешний элемент потока ввода в _position
}

void Lex::RollBack() {
	file.seekg(_position);
}
