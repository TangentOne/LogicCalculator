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

enum IsConstant
{
	NonConst, IsConst
};


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

	//��ʼ��
	static void initial() 
	{
		VariableName.clear(); 
		for (int i = 0; i <= Varcnt; ++i) ConstFlag[i]=VariableVal[i] = 0;
		for (int i = 0; i <= Varcnt; ++i) VarSeq[i].clear();
		Varcnt = 0;
	}


	//��������ӳ�䵽�������
	static map<string, int> VariableName;

	//���������ţ�����ñ�����ֵ
	static bool VariableVal[maxVariables];

	//�ж����������ֵ�Ƿ���һ����ֵ
	static bool ConstFlag[maxVariables];

	//ͳ�Ʊ�������
	static int Varcnt;

	//���������ţ����������
	static string VarSeq[maxVariables];

	//�޲��������ڹ�����ջʱʹ��
	Variables() : name(""), val(NULL) {};

	//��ͨ����������������
	explicit Variables(string na,IsConstant con=IsConstant::NonConst): name(na), val(NULL)
	{		
		//���ڰ󶨱��������Ӧ��ֵ
		//����ñ����ǵ�һ�γ��֣�ֱ�Ӱ󶨶�Ӧ�ı��
		
		if (VariableName.find(name) != VariableName.end()) 
		{ 
			if (con == IsConstant::IsConst)	ConstFlag[VariableName[name]] = true; //�����һ������ֵ����ConstFlag=1
			val = &VariableVal[VariableName[name]]; 
			return; 
		}
		else
		{
			VariableName.emplace(name, ++Varcnt);
			VarSeq[Varcnt] = name;
			val = &VariableVal[Varcnt];
			if (con == IsConstant::IsConst)	ConstFlag[Varcnt] = true; //�����һ������ֵ����ConstFlag=1
		}
		
		
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

	//���ñ���ֵ
	void setVal(bool value) { Variables::VariableVal[VariableName[name]] = value; }
	
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
bool Variables::ConstFlag[maxVariables];
int Variables::Varcnt=0;




#endif // !VARIABLES
