#ifndef QUICKCALCULATOR
#define QUICKCALCULATOR
#include"Stack.h"
#include"PublicMethod.h"
#include"Operator.h"
#include"Variables.h"

using std::string;

class QuickCalculator
{
public:
	static void initial() {};
	QuickCalculator(string ss) :Postfix(ss) {}


	int work()
	{
		for (int i = 0; Postfix[i] != '\0'; ++i)
		{
			if (Postfix[i] == ' ') continue;
			if (isAlphabet(Postfix[i]))
			{
				string name = extractVar(Postfix, i);
				int var(Variables::VariableVal[Variables::VariableName[name]]);
				stack.push(var);
			}
			else
			{
				Operators op(Postfix[i]);
				if (op.getID() == Priority::P_NEG)			__doNeg();
				else if (op.getID() == Priority::P_CONJ)	__doCon();
				else if (op.getID() == Priority::P_DISJ)	__doDis();
				else if (op.getID() == Priority::P_DUAL)	__doDual();
				else if (op.getID() == Priority::P_IMPLY)	__doImpl();
				else if (op.getID() == Priority::P_XOR)		__doXor();
			}
		}
		return stack.pop();
	}

	void assign(const string& postfixNotion) { Postfix.assign(postfixNotion); }

private:

	void __doNeg()
	{
		int var = stack.pop();
		stack.push(!var);
	}

	void __doCon()
	{
		int var1 = stack.pop();
		int var2 = stack.pop();
		stack.push(var1&var2);
	}

	void __doDis()
	{
		int var1 = stack.pop();
		int var2 = stack.pop();
		stack.push(var1|var2);
	}

	void __doDual()
	{
		int var1 = stack.pop();
		int var2 = stack.pop();
		stack.push((var1&var2)|(!var1&!var2));
	}

	void __doImpl()
	{
		int var1 = stack.pop();
		int var2 = stack.pop();
		stack.push(!var2|var1);
	}

	void __doXor()
	{
		int var1 = stack.pop();
		int var2 = stack.pop();
		stack.push(var1^var2);
	}


	string Postfix;
	Stack<int> stack;






};

#endif // !QUICKCALCULATOR
