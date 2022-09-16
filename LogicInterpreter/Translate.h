#ifndef TRANSLATE_H
#define TRANSLATE_H
#include"Stack.h"
#include"Operator.h"
#include"cstdlib"
#include"Variables.h"
#include"PublicMethod.h"
using std::string;



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