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
important:Ϊ�˽�����ͬ����������һ��ֵ�����磺p&q->!p�У�ǰ������p��ֵӦ����ͬһ����
�ҽ�����(variable)�������ֵ(value)���variable��ΪVariables��Ķ��󵥶����ڣ�valueͳһ������VariableVal������
ÿһ��������һ��ָ����ֵ��ָ�루ָ��VariableVal������ĳһλ�ã�����ͬ����ָ��ͬ��������ͬ�ı���ָ����ͬ
���������ı�VariableVal�е�һ��ֵʱ�����е�ͬ��������ֵ����ı�
*/
class Variables
{
public:
	//��������ӳ�䵽�������
	static map<string, int> VariableName;

	//���������ţ�����ñ�����ֵ
	static bool VariableVal[maxVariables];

	//ͳ�Ʊ�������
	static int Varcnt;

	//���������ţ����������
	static string VarSeq[maxVariables];

	//�޲��������ڹ�����ջʱʹ��
	Variables() : name(""), val(NULL) {};

	//��ͨ����������������
	Variables(string na): name(na), val(NULL)
	{
		//���ڰ󶨱��������Ӧ��ֵ
		//����ñ����ǵ�һ�γ��֣�ֱ�Ӱ󶨶�Ӧ�ı��
		if (VariableName.find(name) != VariableName.end()) { val = &VariableVal[VariableName[name]]; return; }
		VariableName.emplace(name, ++Varcnt);
		VarSeq[Varcnt] = name;
		val = &VariableVal[Varcnt];
	}

	//ͨ����������ֵ����������������ǿ���޸ĸñ���ָ���ֵ(values stored in VariableVal)
	Variables(string na,bool value) :name(na), val(NULL)
	{
		if (VariableName.find(name) != VariableName.end()) { val = &VariableVal[VariableName[name]]; *val = value; return; }
		VariableName.emplace(name, ++Varcnt);
		VarSeq[Varcnt] = name;
		val = &VariableVal[Varcnt];
		*val = value;
	}

	//��ȡ������
	string getName() const { return name; }

	//���ñ���ֵ���ƺ�û����
	int setVal(bool& pos) { val = &pos; }
	
	//��ȡ����ֵ
	int getVal() { if (val == NULL) { cerr << "Variables"<<name <<" Not yet assigned."; exit(1); } return *val; }
private:
	//���������������ֱ�����Ψһ��ʶ
	string name;
	
	//ͨ��valָ���ӷ��ʱ���ֵ
	bool* val;

};

//static��Ա���ⶨ��
map<string, int> Variables::VariableName;
string Variables::VarSeq[maxVariables];
bool Variables::VariableVal[maxVariables];
int Variables::Varcnt=0;



#endif // !VARIABLES
