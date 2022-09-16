#ifndef INFIXEXPRESSION_H
#define INFIXEXPRESSION_H

#include<cstdlib>
#include<cstdio>
#include"Stack.h"
#include"PublicMethod.h"
#include"Operator.h"

using std::string;

class InFixTrans 
{
public:
	InFixTrans(const string& str):postfix(str),lastop(Priority::P_LEFT){}
	string work()
	{
		for (int i = 0; postfix[i] != '\0'; ++i)
		{
			if (postfix[i] == ' ') continue;
			if (isAlphabet(postfix[i]))
			{
				string varname=extractVar(postfix, i);
				stack.push(varname);
			}
			else
			{
				Operators op(getPriority(postfix[i]));

				if (op.getID() == Priority::P_CONJ)				__doCONJ();
				else if (op.getID() == Priority::P_NEG)			__doNeg();
				else if (op.getID() == Priority::P_DUAL)		__doDUAL();
				else if (op.getID() == Priority::P_IMPLY)		__doIMPLY();
				else if (op.getID() == Priority::P_XOR)			__doXOR();
				else if (op.getID() == Priority::P_DISJ)		__doDISJ();
				else { cerr << "InFixTrans Error."; exit(1); }
			}
		}
		return stack.pop();
	}
private:
	void __doNeg()
	{
		string rhs;
		rhs.assign(stack.pop());
		string tmp("");
		tmp.assign("!" + rhs);
		stack.push(getASqure(tmp));
		lastop = Priority::P_NEG;
	}

	//x&y == !(!x|!y)
	void __doCONJ()
	{
		string rhs, lhs;
		rhs.assign(stack.pop());
		lhs.assign(stack.pop());
		string tmp("");
		tmp.assign("!(!" + lhs + "|!" + rhs + ")");
		stack.push(getASqure(tmp));
		lastop = Priority::P_CONJ;
	}

	//x|y == x|y
	void __doDISJ()
	{
		string rhs, lhs;
		rhs.assign(stack.pop());
		lhs.assign(stack.pop());
		string tmp("");
		tmp.assign(lhs + "|" + rhs);
		stack.push(getASqure(tmp));
		lastop = Priority::P_DISJ;
	}

	//x^y == !( !x | y ) | !( !y | x)
	void __doXOR()
	{
		string rhs, lhs;
		rhs.assign(stack.pop());
		lhs.assign(stack.pop());
		string tmp("");
		tmp.assign("!(!"+lhs+"|"+rhs+")|!(!"+rhs+"|"+lhs+")");
		stack.push(getASqure(tmp));
		lastop = Priority::P_XOR;
	}

	//x>y == !x|y
	void __doIMPLY()
	{
		string rhs, lhs;
		rhs.assign(stack.pop());
		lhs.assign(stack.pop());
		string tmp("");
		tmp.assign("!"+lhs + "|" + rhs);
		stack.push(getASqure(tmp));
		lastop = Priority::P_IMPLY;
	}

	//x<y == !(!x|!y) | !(x|y)
	void __doDUAL()
	{
		string rhs, lhs;
		rhs.assign(stack.pop());
		lhs.assign(stack.pop());
		string tmp("");
		tmp.assign("!(!"+lhs + "|!" + rhs+")|!("+lhs+"|"+rhs+")");
		stack.push(getASqure(tmp));
		lastop = Priority::P_DUAL;
	}


	string postfix;
	Stack<string> stack;
	Operators lastop;
};


#endif // !INFIXEXPRESSION_H
