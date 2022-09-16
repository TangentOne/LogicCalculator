#ifndef STACK_H
#define STACK_H

#include<iostream>

using std::cerr;
const int maxStacks = 500;
using std::string;

template<typename T>
class Stack
{
public:
	Stack() :top(0), data{} {}
	T pop() { if (top == 0) { cerr << "StackEmpty!"; exit(1); }; return data[top--]; };
	T getTop() const { return data[top]; }
	bool isEmpty()const { return !top; }
	void push(T x) { if (top == maxStacks) { cerr << "StackOverFlow!"; exit(1); }; data[++top] = x; };

	int getNum()const { return top; }
private:
	int top;
	T data[maxStacks];
};





#endif