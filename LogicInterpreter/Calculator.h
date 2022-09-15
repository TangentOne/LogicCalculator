#ifndef CALCULATOR_H
#define CALCULATOR_H

#include"Variables.h"
#include"Operator.h"
#include"Stack.h"
#include"PublicMethod.h"
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

bool getXorAns(bool a, bool b)
{
	return (!a & b) | (a & !b);
}

class Calculator
{
public:
	static void initial() {};
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
				if (op.getID() == Priority::P_NEG) __doNeg();
				else if (op.getID() == Priority::P_CONJ) __doCon();
				else if (op.getID() == Priority::P_DISJ) __doDis();
				else if (op.getID() == Priority::P_DUAL) __doDual();
				else if (op.getID() == Priority::P_IMPLY) __doImpl();
				else if (op.getID() == Priority::P_XOR) __doXor();
			}
		}

		
		return stack.pop().getVal();
	}
private:

	void __doNeg()
	{
		Variables var = stack.pop();
		Variables var2("\\neg" + getASqure(var.getName()), !var.getVal());
		stack.push(var2);
	}
	
	void __doCon()
	{
		Variables var1 = stack.pop();
		Variables var2 = stack.pop();
		Variables var3(getASqure(var2.getName()) + "\\land " + getASqure(var1.getName()), (var2.getVal() & var1.getVal()));
		stack.push(var3);
	}
	
	void __doDis()
	{
		Variables var1 = stack.pop();
		Variables var2 = stack.pop();
		Variables var3(getASqure(var2.getName()) + "\\lor " + getASqure(var1.getName()), (var2.getVal() | var1.getVal()));
		stack.push(var3);
	}
	
	void __doDual()
	{
		Variables var1 = stack.pop();
		Variables var2 = stack.pop();
		Variables var3(getASqure(var2.getName()) + "\\leftrightarrow " + getASqure(var1.getName()), getDualAns(var2.getVal(), var1.getVal()));
		stack.push(var3);
	}
	
	void __doImpl()
	{
		Variables var1 = stack.pop();
		Variables var2 = stack.pop();
		Variables var3(getASqure(var2.getName()) + "\\rightarrow " + getASqure(var1.getName()), getImplyAns(var2.getVal(), var1.getVal()));
		stack.push(var3);
	}
	
	void __doXor()
	{
		Variables var1 = stack.pop();
		Variables var2 = stack.pop();
		Variables var3(getASqure(var2.getName()) + "\\bigoplus" + getASqure(var1.getName()), getXorAns(var2.getVal(), var1.getVal()));
		stack.push(var3);
	}


	string Postfix;
	Stack<Variables> stack;
	
};






#endif // !CALCULATOR_H
