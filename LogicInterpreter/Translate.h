#ifndef TRANSLATE_H
#define TRANSLATE_H
#include"Stack.h"
#include"Operator.h"
#include"cstdlib"
#include"Variables.h"
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

class Translate
{
public:
	Translate(const string& in) :data(in), output("") { output.clear(); }
	void work()
	{
		for (int i = 0; data[i] != '\0'; ++i)
		{
			if (isAlphabet(data[i]))					//����Ǳ�����ֱ�����
			{
				string name=extractVar(data, i);
				Variables var(name);
				output += name+' ';
			}
			else                 
			{
				Operators op(getPriority(data[i]));
				if (op.getID() == Priority::P_RIGHT)	//���ɨ�赽�����ţ�����ջһֱ��ջ��ֱ���ҵ���Ӧ��������
				{
					while (stack.getTop().getID() !=Priority::P_LEFT)
					{
						Operators x = stack.pop();
						output += x.getName();
					}
					stack.pop();		//ȥ��������
					continue;
				}
				else if (op.getID() == Priority::P_LEFT)		//����ҵ������ţ�ֱ����ջ
				{
					stack.push(op);
				}
				else                                    //������������ţ���ջ�����б������ȼ��ߵķ����������ջ
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