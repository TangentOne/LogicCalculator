#ifndef CALCULATOR_H
#define CALCULATOR_H

#include"Variables.h"
#include"Operator.h"
#include"Stack.h"
#include<iostream>
#include<cstdlib>
using std::string;

bool getDualAns(bool a,bool b)
{
	return (a & b) | (!a & !b);
}

bool getImplyAns(bool a,bool b)
{
	return (!a | b);
}


class Calculator
{
public:

	Calculator(string ss):Postfix(ss){}
	bool work()
	{
		for (int i = 0; Postfix[i] != '\0'; ++i)
		{
			if (Postfix[i] == ' ') continue;
			if (isAlphabet(Postfix[i]))
			{
				string name = extractVar(Postfix, i);
				Variables var(name);
				stack.push(var);
			}
			else
			{
				Operators op(Postfix[i]);
				if (op.getID() == Priority::P_NEG)
				{
					Variables var = stack.pop();
					Variables var2('!'+getASqure(var.getName()), !var.getVal());
					stack.push(var2);
				}
				else if (op.getID() == Priority::P_CONJ)
				{
					Variables var1 = stack.pop();
					Variables var2 = stack.pop();
					Variables var3(getASqure(var2.getName())+"&"+getASqure(var1.getName()), (var2.getVal()&var1.getVal()));
					stack.push(var3);
				}
				else if (op.getID() == Priority::P_DISJ)
				{
					Variables var1 = stack.pop();
					Variables var2 = stack.pop();
					Variables var3(getASqure(var2.getName()) + "|" + getASqure(var1.getName()), (var2.getVal() | var1.getVal()));
					stack.push(var3);
				}
				else if (op.getID() == Priority::P_DUAL)
				{
					Variables var1 = stack.pop();
					Variables var2 = stack.pop();
					Variables var3(getASqure(var2.getName()) + "<" + getASqure(var1.getName()),getDualAns(var2.getVal(),var1.getVal()));
					stack.push(var3);
				}
				else if (op.getID() == Priority::P_IMPLY)
				{
					Variables var1 = stack.pop();
					Variables var2 = stack.pop();
					Variables var3(getASqure(var2.getName()) + ">" + getASqure(var1.getName()), getImplyAns(var2.getVal(),var1.getVal()));
					stack.push(var3);
				}
			}
		}

		
		return stack.pop().getVal();
	}
private:
	string Postfix;
	Stack<Variables> stack;
	
};






#endif // !CALCULATOR_H
