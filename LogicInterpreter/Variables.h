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


/*
important:为了解决多个同名变量共享一个值（例如：p&q->!p中，前后两个p的值应当是同一个）
我将变量(variable)与变量的值(value)解耦，variable作为Variables类的对象单独存在，value统一储存在VariableVal数组中
每一个变量有一个指向其值的指针（指向VariableVal数组中某一位置），不同变量指向不同，名称相同的变量指向相同
这样，当改变VariableVal中的一个值时，所有的同名变量的值都会改变
*/
class Variables
{
public:
	//将变量名映射到变量编号
	static map<string, int> VariableName;

	//输入变量编号，输出该变量的值
	static bool VariableVal[maxVariables];

	//统计变量个数
	static int Varcnt;

	//输入变量编号，输出变量名
	static string VarSeq[maxVariables];

	//无参数，用于构建空栈时使用
	Variables() : name(""), val(NULL) {};

	//仅通过变量名构建变量
	Variables(string na): name(na), val(NULL)
	{
		//用于绑定变量与其对应的值
		//如果该变量非第一次出现，直接绑定对应的编号
		if (VariableName.find(name) != VariableName.end()) { val = &VariableVal[VariableName[name]]; return; }
		VariableName.emplace(name, ++Varcnt);
		VarSeq[Varcnt] = name;
		val = &VariableVal[Varcnt];
	}

	//通过变量名和值构建变量，这样会强制修改该变量指向的值(values stored in VariableVal)
	Variables(string na,bool value) :name(na), val(NULL)
	{
		if (VariableName.find(name) != VariableName.end()) { val = &VariableVal[VariableName[name]]; *val = value; return; }
		VariableName.emplace(name, ++Varcnt);
		VarSeq[Varcnt] = name;
		val = &VariableVal[Varcnt];
		*val = value;
	}

	//获取变量名
	string getName() const { return name; }

	//设置变量值，似乎没用上
	int setVal(bool& pos) { val = &pos; }
	
	//获取变量值
	int getVal() { if (val == NULL) { cerr << "Variables"<<name <<" Not yet assigned."; exit(1); } return *val; }
private:
	//变量名，用于区分变量的唯一标识
	string name;
	
	//通过val指针间接访问变量值
	bool* val;

};

//static成员类外定义
map<string, int> Variables::VariableName;
string Variables::VarSeq[maxVariables];
bool Variables::VariableVal[maxVariables];
int Variables::Varcnt=0;



#endif // !VARIABLES
