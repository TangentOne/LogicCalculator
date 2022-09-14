#include<iostream>
#pragma warning (disable:4996)
#include"Translate.h"
#include"Assign.h"
#include"Calculator.h"
#include"windows.h"
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
	cout << "### Phase  " << ++workTime << ".\n";
	cout<< "$$\n" << Change(str) << "\n$$\n\n";
	cout << "#### 1.Truth Table\n\n";
	initial();
	string postfix = getPostfixNotion(str);
	Assign assigner(postfix, Variables::Varcnt);
	assigner.work();
	cout << "\n\n\n\n\n\n\n";
}

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