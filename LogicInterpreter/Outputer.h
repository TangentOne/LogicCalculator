#ifndef OUTPUT_H
#define OUTPUT_H
#include"Variables.h"
#include<iostream>
using std::cout;
using std::string;


class Outputer
{
public:

	static void initial() { callTime = 0; }

	Outputer(){}
	static void outputone()
	{
		callTime++;
		if (callTime == 1) 
		{
			//¥Ú”°±ÌÕ∑
			cout << "|";
			for (int i = 1; i <= Variables::Varcnt; ++i)
			{
				cout << "$$" << Variables::VarSeq[i] << "$$" << "|";
			}
			cout<<std::endl << "|";
			for (int i = 1; i <= Variables::Varcnt; ++i)
			{
				cout << ":---:" << "|";
			}
		}
		cout <<std::endl;
		cout << "|";
		for (int i = 1; i <= Variables::Varcnt; ++i)
		{
			cout   << ((Variables::VariableVal[Variables::VariableName[Variables::VarSeq[i]]]==true)?"$$True$$":"$$False$$") << "|";
		}
		return;
	}
private:
	static int callTime;
};

int Outputer::callTime=0;


#endif // !OUTPUT_H
