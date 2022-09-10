#ifndef OUTPUT_H
#define OUTPUT_H
#include"Variables.h"
#include<iostream>
using std::cout;
using std::string;

class Outputer
{
public:
	Outputer(){}
	static void outputone()
	{
		callTime++;
		if (callTime == 1) 
		{
			//��ӡ��ͷ
			for (int i = 1; i <= Variables::Varcnt; ++i)
			{
				cout << Variables::VarSeq[i] << "\t\t";
			}
		}
		cout <<std::endl;
		for (int i = 1; i <= Variables::Varcnt; ++i)
		{
			cout << Variables::VariableVal[Variables::VariableName[Variables::VarSeq[i]]] << "\t\t";
		}
		return;
	}
private:
	static int callTime;
};

int Outputer::callTime=0;


#endif // !OUTPUT_H
