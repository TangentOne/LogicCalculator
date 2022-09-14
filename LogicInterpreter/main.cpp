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


int workTime = 0;

string Change(string str)
{
	size_t last = 0;
	while ((last=str.find('>',last+1)) != string::npos) { str.replace(last, 1, "\\rightarrow "); }
	while ((last = str.find('<', last + 1)) != string::npos) { str.replace(last, 1, "\\leftrightarrow "); }
	while ((last = str.find('&', last + 1)) != string::npos) { str.replace(last, 1, "\\land "); }
	while ((last = str.find('|', last + 1)) != string::npos) { str.replace(last, 1, "\\lor "); }
	while ((last = str.find('^', last + 1)) != string::npos) { str.replace(last, 1, "\\bigoplus "); }
	while ((last = str.find('!', last + 1)) != string::npos) { str.replace(last, 1, "\\neg "); }

	return str;
}

void workOne(const string& str)
{
	Change(str);
	cout << "### Phase  " << ++workTime<<"."<<"$$" << Change(str)<<"$$\n\n";
	initial();
	string postfix = getPostfixNotion(str);
	Assign assigner(postfix, Variables::Varcnt);
	assigner.work();
	
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
	
	workOne("(p&!(r&s))>!q");
	workOne("(q>!p)<(p<q)");
	workOne("(p^q)>(p^!q)");



	fclose(stdout);
	system("start 1.md");
	return 0;
}