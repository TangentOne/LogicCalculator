#include<iostream>
#pragma warning (disable:4996)
#include"Translate.h"
#include"Assign.h"
#include"Calculator.h"
#include"windows.h"
using namespace std;
using std::string;


string getPostfixNotion(const string& PrefixNotion)
{
	string tmp;
	Translate* tr;
	tr = new Translate(PrefixNotion);
	tr->work();
	tmp.assign(tr->getTranslation());
	delete tr;
	return tmp;
}

void initial()
{
	Calculator::initial();
	Translate::initial();
	Operators::initial();
	Variables::initial();
	Outputer::initial();
}

/*
& and
| or
^ xor
> ->
< <->

*/
int main()
{
	freopen("1.md", "w", stdout);
	string ss("p & q:1 > r");
	string postfix = getPostfixNotion(ss);
	cout << postfix << endl;
	Assign assigner1(postfix,Variables::Varcnt);
	assigner1.work();

	cout << endl<<endl<<endl;
	initial();


	fclose(stdout);
	system("start 1.md");
	return 0;
}