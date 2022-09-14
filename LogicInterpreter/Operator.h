#ifndef OPERATOR_H
#define OPERATOR_H

#include"Stack.h"
#include<iostream>
using std::string;
/*
operator的优先级同时代表其具体类型
NEG>CON>DIS>IMPLY>DUAL
*/
enum Priority
{
	P_LEFT,P_DUAL,P_IMPLY,P_XOR,P_DISJ,P_CONJ,P_NEG,P_RIGHT
};

class Operators
{
public:
	static void initial() {};
	Operators() : pri(P_DUAL) {};
	Operators(Priority p):pri(p) {};
	
	//自动分配
	Operators(char x) 
	{
		if (x == '!') { pri = Priority::P_NEG;  }
		if (x == '&') { pri = Priority::P_CONJ; }
		if (x == '|') { pri = Priority::P_DISJ; }
		if (x == '>') { pri = Priority::P_IMPLY;}
		if (x == '<') { pri = Priority::P_DUAL; }
		if (x == '^') { pri = Priority::P_XOR;  } 
	}

	//获得Operator的优先级/具体类型
	Priority getID()const { return pri; }

	char getName()
	{
		if (pri == Priority::P_NEG) return '!'  ;
		if (pri == Priority::P_CONJ) return '&' ;
		if (pri == Priority::P_DISJ) return '|' ;
		if (pri == Priority::P_IMPLY) return '>';
		if (pri == Priority::P_DUAL) return '<' ;
		if (pri == Priority::P_XOR) return '^'  ;

		cerr << "No name!"; exit(1);
	}

	//string getOutputName()
	//{
	//	if (pri == Priority::P_NEG) return "\\neg";
	//	if (pri == Priority::P_CONJ) return "\\land";
	//	if (pri == Priority::P_DISJ) return "\\lor";
	//	if (pri == Priority::P_IMPLY) return "\\rightarrow";
	//	if (pri == Priority::P_DUAL) return "\\LeftRightArrow";
	//	if (pri == Priority::P_XOR) return "\\bigoplus";

	//	cerr << "No name!"; exit(1);
	//}
private:
	Priority pri;
};


#endif // !Operator
