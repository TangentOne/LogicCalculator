#ifndef ASSIGN_H
#define ASSIGN_H

#include<iostream>
#include"Calculator.h"
#include"Outputer.h"
using std::string;


class Assign
{
public:
	Assign(const string& str,int initialVarNum) :postfix(str),maxstep(initialVarNum) {};
	
	//递归赋值
	void dfs(int step)
	{
		//复制完成后，开始计算，输出结果
		if (step == maxstep + 1) { Calculator ca(postfix); ca.work(); Outputer out; out.outputone(); return; }
		for (int i = 0; i <= 1; ++i)
		{
			if (Variables::ConstFlag[step] != 1) Variables::VariableVal[step] = i;
			else i++;
			dfs(step + 1);
		}
	}

	void work()
	{
		dfs(1);
	}

private:
	const string postfix;
	int maxstep;
};



#endif // !ASSIGN_H
