#ifndef VARIABLES_H
#define VARIABLES_H
#include"Stack.h"
#include<iostream>
#include<map>
#include<cstdio>
#include<cstdlib>
using std::cerr;
using std::string;
using std::map;

string getASqure(string name)
{
	return '(' + name + ')';
}

const int maxVariables = 500;

class Variables:public StackItem 
{
public:
	static map<string, int> VariableName;
	static bool VariableVal[maxVariables];
	static int Varcnt;
	static string VarSeq[maxVariables];

	Variables() :StackItem(StackItemID::SI_VAR), name(""), val(NULL) {};

	Variables(string na):StackItem(StackItemID::SI_VAR), name(na), val(NULL)
	{
		if (VariableName.find(name) != VariableName.end()) { val = &VariableVal[VariableName[name]]; return; }
		VariableName.emplace(name, ++Varcnt);
		VarSeq[Varcnt] = name;
		val = &VariableVal[Varcnt];
	}

	Variables(string na,bool value) :StackItem(StackItemID::SI_VAR), name(na), val(NULL)
	{
		if (VariableName.find(name) != VariableName.end()) { val = &VariableVal[VariableName[name]]; *val = value; return; }
		VariableName.emplace(name, ++Varcnt);
		VarSeq[Varcnt] = name;
		val = &VariableVal[Varcnt];
		*val = value;
	}

	string getName() const { return name; }


	int setVal(bool& pos) { val = &pos; }
	int getVal() { if (val == NULL) { cerr << "Variables"<<name <<" Not yet assigned."; exit(1); } return *val; }
private:
	string name;
	bool* val;

};

map<string, int> Variables::VariableName;
string Variables::VarSeq[maxVariables];
bool Variables::VariableVal[maxVariables];
int Variables::Varcnt=0;



#endif // !VARIABLES
