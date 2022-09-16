#include<iostream>
#pragma warning (disable:4996)
#include"Translate.h"
#include"Assign.h"
#include"Calculator.h"
#include"windows.h"
#include"InfixExpression.h"
#include<fstream>

using namespace std;
using std::string;
ifstream ifs("input.md");

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
//读入一个表达式，并进行求解和输出
void workOne(const string& str)
{
	cout << "### Phase  " << ++workTime << ".\n";
	cout<< "$$\n" << Change(str) << "\n$$\n\n";

	initial();
	string postfix = getPostfixNotion(str);
	InFixTrans inf(postfix);
	Assign assigner(postfix, Variables::Varcnt);

	cout << "#### 1.Simplified Version\n\n";
	string simplified = inf.work();
	cout << "$$\n"<<Change(simplified)<<"\n$$";
	cout << "\n\n" << "`"<<simplified<<"`";
	cout << "\n\n\n";

	cout << "#### 2.Truth Table\n\n";
	assigner.work();

	cout << "\n\n\n\n\n\n\n";
}


//从文件中读入
const int maxLength = 5000;
char buffer[maxLength+10];
void readFromFile()
{
	if (!ifs) { cout << "File Not Exsited."; exit(1); }
	string str;
	int maxTurn = 1000;
	while (maxTurn--)
	{
		ifs.getline(buffer,maxLength);
		string str(buffer);
		if (str == "**Start From Next Line**") continue;
		if (str == "**Stop At Here**") break;
		if (str[0] == '/' && str[1] == '/') continue;
		if (str == "") continue;
		workOne(str);
	}
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
	freopen("output.md", "w", stdout);
	
	readFromFile();

	//workOne("(p&!(r&s))>!q");
	//workOne("(q>!p)<(p<q)");
	//workOne("(p^q)>(p^!q)");



	fclose(stdout);
	system("start output.md");
	return 0;
}