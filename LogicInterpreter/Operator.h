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

class Operators
{
public:
	Operators() : pri(P_DUAL) {};
	Operators(Priority p):pri(p) {};
	
	//�Զ�����
	Operators(char x) 
	{
		if (x == '!') { pri = Priority::P_NEG;  }
		if (x == '&') { pri = Priority::P_CONJ; }
		if (x == '|') { pri = Priority::P_DISJ; }
		if (x == '>') { pri = Priority::P_IMPLY;}
		if (x == '<') { pri = Priority::P_DUAL; }
	}

	//���Operator�����ȼ�/��������
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
