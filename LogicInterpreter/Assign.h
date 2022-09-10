#ifndef ASSIGN_H
#define ASSIGN_H

#include<iostream>
using std::string;


class Assign
{
public:
	Assign(const string& str,int initialVarNum) :postfix(str),maxstep(initialVarNum) {};

	void work()
	{
		
	}

private:
	const string postfix;
	int maxstep;
};



#endif // !ASSIGN_H
