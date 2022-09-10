#ifndef OPERATOR_H
#define OPERATOR_H

#include"Stack.h"
/*
operator�����ȼ�ͬʱ�������������
NEG>CON>DIS>IMPLY>DUAL
*/
enum Priority
{
	P_LEFT,P_DUAL,P_IMPLY,P_DISJ,P_CONJ,P_NEG,P_RIGHT
};

class Operators: public StackItem
{
public:
	Operators() :StackItem(StackItemID::SI_VAR), pri(P_DUAL) {};
	Operators(Priority p) :StackItem(StackItemID::SI_VAR),pri(p) {};
	Operators(char x) :StackItem(StackItemID::SI_VAR)
	{
		if (x == '!') { pri = Priority::P_NEG;  }
		if (x == '&') { pri = Priority::P_CONJ; }
		if (x == '|') { pri = Priority::P_DISJ; }
		if (x == '>') { pri = Priority::P_IMPLY;}
		if (x == '<') { pri = Priority::P_DUAL; }
	}
	Priority getID()const { return pri; }
	char getName()
	{
		if (pri == Priority::P_NEG) return '!';
		if (pri == Priority::P_CONJ) return '&';
		if (pri == Priority::P_DISJ) return '|';
		if (pri == Priority::P_IMPLY) return '>';
		if (pri == Priority::P_DUAL) return '<';
		cerr << "No name!"; exit(1);
	}
private:
	Priority pri;
};


#endif // !Operator
