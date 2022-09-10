#include<iostream>
#include"Translate.h"
#include"Assign.h"
#include"Calculator.h"
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



int main()
{
	string ss("(p^q)>(p^!q)");
	string postfix = getPostfixNotion(ss);
	cout << postfix << endl;
	Assign assigner(postfix,Variables::Varcnt);
	assigner.work();

	return 0;
}