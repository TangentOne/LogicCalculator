#ifndef TRANSLATE_H
#define TRANSLATE_H
#include"Stack.h"
#include"Operator.h"
#include"cstdlib"
#include"Variables.h"
#include"PublicMethod.h"
using std::string;

Priority getPriority(char x)
{
	if (x == '!') { return Priority::P_NEG; }
	if (x == '&') { return Priority::P_CONJ; }
	if (x == '|') { return Priority::P_DISJ; }
	if (x == '>') { return Priority::P_IMPLY; }
	if (x == '<') { return Priority::P_DUAL; }
	if (x == '(') { return Priority::P_LEFT; }
	if (x == ')') { return Priority::P_RIGHT; }
	if (x == '^') { return Priority::P_XOR; }
	std::cerr << "No operator" << x << "exsited.";
	exit(1);
}

char getOperatorName(Priority p)
{
	if (p == Priority::P_NEG) { return '!'; }
	if (p == Priority::P_DISJ) { return '|'; }
	if (p == Priority::P_CONJ) { return '&'; }
	if (p == Priority::P_IMPLY) { return '>'; }
	if (p == Priority::P_DUAL) { return '<'; }
	if (p == Priority::P_XOR) { return '^'; }

	std::cerr << "No operator" << p << "exsited.";
	exit(1);
}

bool ExtractConst(const string& data, int& sta,bool&val)
{
	while (data[sta] == ' ') sta++;
	if (data[sta+1] == ':')
	{
		sta+=2;
		if (data[sta] == '1')val = true;
		else val = false;
		return true;
	}
	else return false;
}

class Translate
{
public:
	static void initial() {};
	Translate(const string& in) :data(in), output("") { output.clear(); }
	
	//经典逆波兰表达式过程
	void work()
	{
		for (int i = 0; data[i] != '\0'; ++i)
		{
			if (data[i] == ' ') continue;
			if (isAlphabet(data[i]))					//如果是变量，直接输出
			{
				string name=extractVar(data, i);
				bool constval=false;
				if (ExtractConst(data, i, constval)) { Variables var(name, IsConstant::IsConst); var.setVal(constval); }
				else {Variables var(name);}
				
				output += name+' ';
			}
			else                 
			{
				Operators op(getPriority(data[i]));
				if (op.getID() == Priority::P_RIGHT)	//如果扫描到右括号，符号栈一直出栈，直到找到对应的左括号
				{
					while (stack.getTop().getID() !=Priority::P_LEFT)
					{
						Operators x = stack.pop();
						output += x.getName();
					}
					stack.pop();		//去掉左括号
					continue;
				}
				else if (op.getID() == Priority::P_LEFT)		//如果找到左括号，直接入栈
				{
					stack.push(op);
				}
				else                                    //如果是其他符号，将栈顶所有比他优先级高的符号输出后入栈
				{
					while (stack.getTop().getID() >= op.getID() && !stack.isEmpty())
					{
						if (stack.getTop().getID() == op.getID() && op.getID() == Priority::P_NEG) break;
						Operators x = stack.pop();
						output += x.getName();
					}
					stack.push(op);
				}
			}
		}
		while (!stack.isEmpty()) output += stack.pop().getName();
	}

	string getTranslation() const { return output; }

private:
	Stack<Operators> stack;
	const string& data;
	string output;
};

#endif