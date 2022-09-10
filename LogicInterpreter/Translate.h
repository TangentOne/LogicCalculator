#ifndef TRANSLATE_H
#define TRANSLATE_H
#include"Stack.h"
#include"Operator.h"
#include"cstdlib"
using std::string;

bool isAlphabet(char x)
{
	if (x >= 'a' && x <= 'z') return true;
	if (x >= 'A' && x <= 'Z')return true;
	return false;
}

string extractVar(const string& data, int& sta)
{
	string tmp;
	for (; isAlphabet(data[sta]); ++sta)
	{
		tmp += data[sta];
	}
	sta--;
	return tmp;
}

Priority getPriority(char x)
{
	if (x == '!') { return Priority::P_NEG; }
	if (x == '&') { return Priority::P_CONJ; }
	if (x == '|') { return Priority::P_DISJ; }
	if (x == '>') { return Priority::P_IMPLY; }
	if (x == '<') { return Priority::P_DUAL; }
	if (x == '(') { return Priority::P_LEFT; }
	if (x == ')') { return Priority::P_RIGHT; }

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
	
	std::cerr << "No operator" << p << "exsited.";
	exit(1);
}

class Translate
{
public:
	Translate(const string& in) :data(in), output("") { output.clear(); }
	void work()
	{
		for (int i = 0; data[i] != '\0'; ++i)
		{
			if (isAlphabet(data[i]))					//如果是变量，直接输出
			{
				string name=extractVar(data, i);
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