#include "stdafx.h"
#include "syntx.h"
#include <string>

static int lvl=0;
static int exprNum = 0;

Syntx::Syntx(TagList &t, IdentTab &it): tList(t), idTab(it){
	std::cout << "Syntx contructor" << endl;
	for (int i = 0; i < 15; i++) {
		expressions[i] = new AriphTree();
	}
	arTree = expressions[exprNum];
	if (!this->Parse()) SyntxErr("The program will not be compiled due to errors");
	/*for (int i = 0; i < exprNum; i++) {
		//cout << "AriphTree number " << i << endl;
		//expressions[i]->ShowTree();
		
		//expressions[i]->DeleteTree();
	}*/
	tree.ConnectExpr(expressions);
	tree.ConnectIdents(&idTab);
	it.Copy(idTab);
}

Syntx::~Syntx() {
	std::cout << "Syntx destructor" << endl;
}

bool Syntx::Parse() {
	std::cout << "Program Syntax analyse" << endl;
	return On_P();
}

bool Syntx::On_P() {
	std::cout << "############################" << endl;
	Token t;
	nowStat = P;
	tree.Add(nowStat);
	while (tList.CheckNext()) {
		tList.SaveStatement();
		if (!On_Function()) {
			tList.RollBack();
			if (!On_FuncCall()) {
				tList.RollBack();
				if (!On_WriteLine()) {
					tList.RollBack();
					if (!On_Cycle()) return false;
				}
			}
		}
	}
	std::cout << "############################" << endl;
	std::cout << "Syntax analys complete" << endl;
	tree.Show();
	return true;
}

bool Syntx::On_Append() {
	Token t;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	if (!tList.Show(t)) return false;
	if (t._value != "append") return false;
	cout << "Append detected" << endl;
	//
	tree.Add(APPEND);
	tree.LevelDown();
	//
	tList.SaveStatement();
	while (tList.Show(t) && t._type != RPAR) {
		tList.Back();
		tList.SaveStatement();
		if (!On_FuncCall()) {
			tList.RollBack();
			if (!On_ListOperation()) return false;
		}
	}
	//
	tree.LevelUp();
	//
	return true;
}

bool Syntx::On_CarCdr() {
	Token t;
	Token save;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	save = t;
	if (!tList.Show(t)) return false;
	if (t._value != "car") {
		if (t._value != "cdr") return false;
		else cout << "Cdr detected" << endl;
		//
		if (ExprDet != NON) {
			expr.AddOne(save);
			expr.AddOne(t);
		}
		//
	}
	else {
		cout << "Car detected" << endl;
		//
		if (ExprDet != NON) {
			expr.AddOne(save);
			expr.AddOne(t);
		}
		//
	}
	//
	if (ExprDet == NON) {
		cout << "Expression = NON" << endl;
		tree.Add(CARCDR, t._value);
		tree.LevelDown();
	}
	//
	if (!On_ID()) return false;
	if (!tList.Show(t)) return false;
	if (t._type != RPAR)return false;
	if (ExprDet != NON) expr.AddOne(t);
	tList.SaveStatement();
	//
	if (ExprDet == NON) {
		cout << "Expression = NON on ending" << endl;
		tree.LevelUp();
	}
	//
	if (!On_CarCdr()) tList.RollBack();
	return true;
}

bool Syntx::On_Cond() {
	Token t;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	if (!tList.Show(t)) return false;
	if (t._value != "cond") return false;
	std::cout << "Cond detected" << endl;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	//
	tree.Add(COND);
	tree.LevelDown();
	tree.Add(EXPRESSION);//в expr ничего не записываем, ибо потом будем связывать с бинарными деревьями
	//
	if (!On_Expression()) return false;
	//
	
	//
	tList.SaveStatement();
	if (!On_FuncBlock()) {
		tList.RollBack();
		if (!On_ID()) {
			tList.RollBack();
			if (!tList.Show(t)) return false;
			if (t._type != RES) return false;
			else {
				std::cout << "Res word = " << t._value << " detected" << endl;
				if (t._value == "nil") tree.Add(NIL);
				//здесь добавлять NIL

				//
			}
		}
	}
	if (!tList.Show(t)) return false;
	if (t._type != RPAR) return false;
	tList.SaveStatement();
	if (!On_ElseCond()) tList.RollBack();
	if (!tList.Show(t)) return false;
	if (t._type != RPAR) return false;
	tree.LevelUp();
	return true;
}

bool Syntx::On_Concatenate() {
	Token t;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	if (!tList.Show(t)) return false;
	if (t._value != "concatenate") return false;
	cout << "Concatenate detected" << endl;
	//
	tree.Add(CONCATENATE);
	tree.LevelDown();
	//
	if (!tList.Show(t)) return false;
	if (t._type != APOST) return false;
	if (!On_ID()) return false;
	while (tList.Show(t) && t._type != RPAR) {
		if (t._type != STRING) {
			tList.Back();
			if (!On_WriteToString()) return false;
		} else {
			tree.Add(STRINGVAL, t._value);
			cout << "String = \"" << t._value << "\" detected" << endl;
		}
	}
	//
	tree.LevelUp();
	//
	return true;
}

bool Syntx::On_Cons() {
	Token t;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	if (!tList.Show(t)) return false;
	if (t._value != "cons") return false;
	cout << "Cons detected" << endl;
	//
	tree.Add(CONS);
	tree.LevelDown();
	//
	if (!On_CarCdr()) return false;
	tList.SaveStatement();
	if (!On_FuncCall()) {
		tList.RollBack();
		if (!tList.Show(t)) return false;
		if (t._type != RES) return false;
		else {
			cout << "Res word = " << t._value << " detected" << endl;
			if (t._value == "nil") tree.Add(NIL);
		}
	}
	if (!tList.Show(t)) return false;
	if (t._type != RPAR) return false;
	cout << "Exit from cons" << endl;
	//
	tree.LevelUp();
	//
	return true;
}

bool Syntx::On_Cycle() {
	Token t;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	if (!tList.Show(t)) return false;
	if (t._value != "loop") return false;
	if (!tList.Show(t)) return false;
	if (t._value != "for") return false;
	//
	tree.Add(CYCLE, "for");
	tree.LevelDown();
	//
	if (!On_ID()) return false;
	if (!tList.Show(t)) return false;
	if (t._value != "from") return false;
	if (!On_Num()) return false;
	if (!tList.Show(t)) return false;
	if (t._value != "to") return false;
	if (!On_Num()) return false;
	if (!tList.Show(t)) return false;
	if (t._value != "do") return false;
	if (!On_WriteLine()) return false;
	if (!tList.Show(t)) return false;
	if (t._type != RPAR) return false;
	cout << "Cycle loop detected" << endl;
	//
	tree.LevelUp();
	//
	return true;
}

bool Syntx::On_ElseCond() {
	Token t;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	if (!tList.Show(t)) return false;
	if (t._value != "t" && t._value!="T") {
		cout << "else cond detected" << endl;
		//
		tree.Add(ELSECOND);
		tree.LevelDown();
		//
		tList.Back();
		tList.SaveStatement();
		if (!On_ListOperation()){
			tList.RollBack();
			//
			tree.Add(EXPRESSION);
			//
			if (!On_Expression()) return false;
		}
		tList.SaveStatement();
		if (!On_ListOperation()) {
			tList.RollBack();
			if (!On_FuncBlock()) {
				tList.RollBack();
				if (!On_FuncCall()) {
					tList.RollBack();
					if (!On_ID()) {
						tList.RollBack();
						if (!tList.Show(t)) return false;
						if (t._type != RES) return false;
						else std::cout << "Res word = " << t._value << " detected" << endl;
					}
				}
			}
		}
	}else {
		cout << "else t detected" << endl;
		//
		tree.Add(ELSECOND);
		tree.LevelDown();
		//
		tList.SaveStatement();
		if (!On_ListOperation()) {
			tList.RollBack();
			if(!On_FuncCall()) return false;
		}
	}
	if (!tList.Show(t)) return false;
	if (t._type != RPAR) return false;
	tList.SaveStatement();
	//
	tree.LevelUp();
	//
	if (!On_ElseCond()) tList.RollBack();
	return true;
}

bool Syntx::On_Expression() {
	cout << "Enter in Expression" << endl;
	Token t;
	int i = 1;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	tList.SaveStatement();
	lvl++;
	expr.AddOne(t);
	while (tList.Show(t) && t._type != RPAR) {
		ExprDet = EXPRESSION;
		if (t._type == LPAR) {
			tList.Back();
			tList.SaveStatement();
			lvl++;
			if (!On_Expression()) return false;
			else {
				lvl--;
				continue;
			}
		}
		else i++;
		tList.Back();
		if (!On_LogicOperator()) {
			tList.RollBack();
			if (!tList.Show(t)) return false;
			if (t._type < PLUS || t._type > MOREEQ) {
				if (t._value != "sqrt")	return false;
				else {
					cout << "Sqrt detected" << endl;
					//
					expr.AddOne(t);
					//stack.Push(t);
					//getchar();
					//
				}
			}
			else {
				cout << "Ariphmetic operator = " << t._value << " detected" << endl;
				//
				//if (t._type > MINUS) {
				expr.AddOne(t);
					//while (!stack.Empty()) expr.AddOne(stack.Pop());
					//stack.Push(t);
				//} else {
					//stack.Push(t);
				//}
				
				//getchar();
				//
				
			}
		}
		//lvl--;
		tList.SaveStatement();
		//getchar();
		if (!On_List()) {
			tList.RollBack();
			if (!On_CarCdr()) {
				tList.RollBack();
				if (!On_ListOperation()) {
					tList.RollBack();
				}
			}
		}
		else {
			tList.SaveStatement();
			if (!On_CarCdr()) {
				tList.RollBack();
				if (!On_FuncCall()) tList.RollBack();
			}
		}
	}
	lvl--;
	expr.AddOne(t);
	ExprDet = NON;
	if (lvl == 0) {
		arTree->Add(expr);
		if (exprNum < 15) exprNum++;
		else {
			exprNum = 0;
			cout << "Expression array overflow" << endl;
			getchar();
		}
		arTree = expressions[exprNum];
		expr.Free();
		//cout << "End expr" << endl;
		//getchar();
	}
	cout << "Expression detected" << endl;
	return true;
}

bool Syntx::On_FuncBlock() {
	cout << "Enter in FuncBlock" << endl;
	nowStat = FUNCBLOCK;
	tList.SaveStatement();
	if (!On_Predic()) {
		tList.RollBack();
		if (!On_WriteLine()) {
			tList.RollBack();
			if (!On_SetQ()) return false;
			
		}
	}
	tList.SaveStatement();
	if (!On_FuncBlock()) tList.RollBack();
	cout << "Exit from funcblock" << endl;
	nowStat = NON;
	return true;
}

bool Syntx::On_FuncCall() {
	Token t;
	Token save;
	bool exp = false;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	save = t;
	if (!tList.Show(t)) return false;
	if (t._type != ID) return false;
	cout << "Function call with ID = " << t._value << " detected" << endl;
	//

	if (nowStat == NON) nowStat = FUNCCALL;
	//
	if (ExprDet != NON) {
		exp = true;
		t._type = FUNCID;
		expr.AddOne(save);
		expr.AddOne(t);
		
	} else if (ExprDet == NON) tree.Add(FUNCCALL, t._value);
	//
	tree.LevelDown();
	//
	tList.SaveStatement();
	if (!On_FuncCall()) {
		tList.RollBack();
		if (!On_CarCdr()) {
			tList.RollBack();
			if (!On_List()) {
				tList.RollBack();
				if (!On_ListStruct()) {
					tList.RollBack();
					if (!On_Expression()) return false;
				}
			}//else tree.Add(LIST);	//!!!!!!!!
		}
	}
	tList.SaveStatement();
	if (!On_CarCdr()) {
		tList.RollBack();
		if (!On_ID()) {
			tList.RollBack();
			if (!On_FuncCall()) tList.RollBack();
		}
	}
	if (!tList.Show(t)) return false;
	if (t._type != RPAR) return false;
	if (exp) expr.AddOne(t);
	//tList.SaveStatement();
	cout << "FuncCall detected" << endl;
	//
	tree.LevelUp();
	if (nowStat == FUNCCALL) nowStat = NON;
	//
	return true;
}

bool Syntx::On_Function() {
	std::cout << "Enter in Function" << endl;
	Token t;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) SyntxErr("Brankets Error In Function");
	if (!tList.Show(t)) return false;
	if (t._value != "defun") return false;
	if (!tList.Show(t)) return false;
	if (t._type != ID) SyntxErr("No function name");
	//
	//cout << "AAAA" << endl;
	nowEl = &t;
	nowEl->_type = FUNCID;
	tree.Add(FUNCTION, t._value);
	idTab.AddElement(t);
	tree.LevelDown();
	//
	std::cout << "Function ID = " << t._value << " detected" << endl;
	//nowStat = FUNCTION;
	//Здесь будет связка параметров функции
	if (!On_ParFunc()) return false;
	//и после переходим на уровень вниз
	nowStat = FUNCTION;
	
	if (!On_FuncBlock()) SyntxErr("FuncBlock Error");
	if (!tList.Show(t)) return false;
	if (t._type != RPAR) SyntxErr("Brankets Error In Function");
	nowStat = NON;
	//cout << "Exit from function" << endl;
	tree.LevelUp();
	return true;
}

bool Syntx::On_ID() {
	Token t;
	if (!tList.Show(t)) return false;
	if (t._type != ID) return false;
	//
	//cout << "DFDF" << endl;
	
	if (nowStat == PARFUNC) {
		t._type = FUNCPAR;
		idTab.AddChildEl(*nowEl, t);
		tree.Add(PARFUNC, t._value);
	}
	else if (nowStat == FUNCBLOCK) {
		t._type = LOCALID;
		idTab.AddChildEl(*nowEl, t);
	} else if (nowStat == FUNCCALL) {
		tree.Add(IDVAL,t._value);
	} else {
		idTab.AddElement(t);
	}
	if (ExprDet != NON) {
		expr.AddOne(t);
	} else {
		if(nowStat == FUNCBLOCK || nowStat == NON) tree.Add(IDVAL, t._value);
	}
	//
	std::cout << "ID = " << t._value << " detected" << endl;
	tList.SaveStatement();
	if (!On_ID()) tList.RollBack();
	return true;
}

bool Syntx::On_If() {
	Token t;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	if (!tList.Show(t)) return false;
	if (t._value != "if") return false;
	cout << "If detected" << endl;
	//
	tree.Add(IF);
	tree.LevelDown();
	tree.Add(EXPRESSION);
	//
	cout << "EXPRESSION" << endl;
	if (!On_Expression()) return false;
	if (!On_SetQ()) return false;
	//
	tree.Add(EXPRESSION);
	//
	if (!On_Expression()) return false;
	if (!tList.Show(t)) return false;
	if (t._type != RPAR) return false;
	cout << "Exit from if" << endl;
	tree.LevelUp();
	return true;
}

bool Syntx::On_LogicOperator() {
	Token t;
	string LogOp[7] = { "equal", "not", "or", "<", ">", "null",">="};
	if (!tList.Show(t)) return false;
	for (int i = 0; i < 7; i++)
		if (t._value == LogOp[i]) {
			cout << "Logic operator = " << t._value << " detected" << endl;
			//binTree.AddEl(t);
			//
			//while (!stack.Empty()) expr.AddOne(stack.Pop());
			expr.AddOne(t);
			//
			return true;
		}
	return false;
	cout << "Logic operator = " << t._value << " detected" << endl;
	return true;
}

bool Syntx::On_ListOperation() {
	tList.SaveStatement();
	if (!On_Append()) {
		tList.RollBack();
		if (!On_Cons()) {
			tList.RollBack();
			if (!On_Member()) return false;
		}
	}
	return true;
}

bool Syntx::On_List() {
	tList.SaveStatement();
	if (!On_ID()) {
		tList.RollBack();
		if (!On_Num()) return false;
	}
	tList.SaveStatement();
	if (!On_List()) tList.RollBack();
	cout << "List detected" << endl;
	return true;
}

bool Syntx::On_ListStruct() {
	Token t;
	if (!tList.Show(t)) return false;
	if (t._type != APOST) {
		if (t._type != LPAR) return false;
		//
		tree.Add(LISTSTRUCT);
		tree.LevelDown();
		//
		if (!On_Num()) {
			tree.Add(NON);
			tree.LevelUp();		
			return false;
		}
		if (!tList.Show(t)) return false;
		if (t._type != RPAR) return false;
		cout << "ListStruct detected" << endl;
		//
		
		//
		//getchar();
	}
	else {
		if (!tList.Show(t)) return false;
		if (t._type != LPAR) return false;
		//
		tree.Add(LISTSTRUCT);
		tree.LevelDown();
		nowStat = FUNCCALL;
		//
		if (!On_Num()) return false;
		//

		//
		if (!tList.Show(t)) return false;
		if (t._type != RPAR) return false;
		cout << "Quot List Struct Detected" << endl;
		//
		
		//
	}
	tList.SaveStatement();
	//
	tree.LevelUp();
	//
	if (!On_ListStruct()) tList.RollBack();
	//getchar();
	return true;
}

bool Syntx::On_Num() {
	Token t;
	if (!tList.Show(t)) return false;
	if (t._type != NUM) return false;
	std::cout << "NUM = " << t._value << " detected" << endl;
	//
	if (ExprDet != NON) {
		expr.AddOne(t);
	} else {
		if (nowStat == FUNCBLOCK) tree.Add(NUMVAL, t._value);
	}
	if (nowStat == FUNCCALL || nowStat == NON) tree.Add(NUMVAL, t._value);
	//
	tList.SaveStatement();
	if (!On_Num()) tList.RollBack();
	return true;
}

bool Syntx::On_Member() {
	Token t;
	Token save;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	save = t;
	if(!tList.Show(t)) return false;
	if (t._value != "member") return false;
	cout << "Member detected" << endl;
	//
	//
	if (ExprDet != NON) {
		expr.AddOne(save);
		expr.AddOne(t);
	}
	else tree.Add(MEMBER);
	if(ExprDet == NON) tree.LevelDown();
	if (!On_CarCdr()) return false;
	if (!On_ID()) return false;
	if(!tList.Show(t)) return false;
	if (t._type != RPAR) return false;
	if (ExprDet != NON) expr.AddOne(t);
	//
	if(ExprDet == NON) tree.LevelUp();
	//
	return true;
}

bool Syntx::On_ParFunc() {
	//cout << "Enter in ParFunc" << endl;
	Token t;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	//cout << "In ParFunc ";
	nowStat = PARFUNC;
	if (!On_ID()) return false;
	//cout << "In ParFunc ";
	if (!tList.Show(t)) return false;
	if (t._type != RPAR) return false;
	cout << "Function parametres detected" << endl;
	return true;
}

bool Syntx::On_Predic() {
	Token t;
	tList.SaveStatement();
	if (!On_Cond()) {
		tList.RollBack();
		if (!On_If()) return false;
	}
	return true;
}

bool Syntx::On_SetQ() {
	Token t;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	if (!tList.Show(t)) return false;
	if (t._value != "setq") return false;
	//
	//if (nowStat == FUNCBLOCK) tree.AddSon(SETQ);
	//
	cout << "Setq detected" << endl;
	//
	tree.Add(SETQ);
	tree.LevelDown();
	//
	if (!On_ID()) return false;
	//
	//tree.LevelDown();
	//
	tList.SaveStatement();
	if (!On_List()){
		tList.RollBack();
		//
		tree.Add(EXPRESSION);
		//
		if (!On_Expression())  return false;
	}
	if (!tList.Show(t)) return false;
	if (t._type != RPAR) return false;
	//
	tree.LevelUp();
	//
	return true;
}

bool Syntx::On_WriteLine() {
	//cout << "Enter in WriteLine" << endl;
	Token t;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	if (!tList.Show(t)) return false;
	if (t._value != "write-line") return false;
	cout << "WriteLine detected" << endl;
	if (!tList.Show(t)) return false;
	//
	tree.Add(WRITELINE);
	tree.LevelDown();
	//
	if (t._type != STRING) {
		tList.Back();
		if (!On_Concatenate()) return false;
	} else {
		tree.Add(STRINGVAL, t._value);
		cout << "String detected = \"" << t._value << "\"" << endl;
	}
	if (!tList.Show(t)) return false;
	if (t._type != RPAR) return false;
	cout << "Exit from write-line" << endl;
	//cout << "WRITELINE DETECTED" << endl;
	//
	tree.LevelUp();
	//
	return true;
}

bool Syntx::On_WriteToString() {
	Token t;
	if (!tList.Show(t)) return false;
	if (t._type != LPAR) return false;
	if (!tList.Show(t)) return false;
	if (t._value != "write-to-string") return false;
	cout << "WriteToString detected" << endl;
	tList.SaveStatement();
	//
	tree.Add(WRITETOSTRING);
	tree.LevelDown();
	//
	if (!On_FuncCall())
	{
		tList.RollBack();
		if (!On_Expression()){
			tList.RollBack();
			if (!On_List())
			{
				tList.RollBack();
				if (!On_ListStruct()) return false;
			}
		} else tree.Add(EXPRESSION); //!!!!!
	}
	cout << "The expression is written in a string" << endl;
	if (!tList.Show(t)) return false;
	if (t._type != RPAR) return false;
	//
	tree.LevelUp();
	//
	return true;
}









