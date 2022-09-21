#include<iostream>
#pragma warning (disable:4996)
#include"Translate.h"
#include"Assign.h"
#include"Calculator.h"
#include"windows.h"
#include"InfixExpression.h"
#include"QuickCalculator.h"
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
	InFixTrans* inf=new InFixTrans(postfix);
	Assign* assigner=new Assign(postfix, Variables::Varcnt);

	cout << "#### 1.Simplified Version\n\n";
	string simplified = inf->work();
	cout << "$$\n"<<Change(simplified)<<"\n$$";
	cout << "\n\n" <<"Raw Version:" << "`" << simplified << "`";
	cout << "\n\n\n";

	cout << "#### 2.Truth Table\n\n";
	assigner->work();

	delete assigner; delete inf;

	cout << "\n\n\n\n\n\n\n";
}




/// //////////////////////////////////////////////////////////
string expression1, expression2;
void NotTheSame(string errorMessage)
{
	cout << "Not The Same.\n"<<errorMessage;
}

//Compare的帮手函数，用于截断str，并且储存到out1和out2中
void getTwoExpression(const string& origin, string& out1, string& out2)
{
	int equalCNT = 0,last=0;
	while ((last = origin.find("==", last)) != string::npos) { 
		last++; equalCNT++; 
	}
	if (equalCNT != 1) { cerr << "MOre Than One Equal...(TO BE IMPLENMENTATION)"; exit(1); }

	out1.assign(origin.substr(0, last=origin.find("==")));
	out2.assign(origin.substr(size_t(last + 2)));
	return;
}

//判断exp2中的变量是否全在exp1中，如果是则返回1，否则返回0
bool CheckVariables(string exp1, string exp2)
{
	Variables::initial();
	exp1 = getPostfixNotion(exp1);
	int VarCnt1 = Variables::Varcnt;
	exp2 = getPostfixNotion(exp2);
	return VarCnt1 == Variables::Varcnt;
}

//
void printTitle()
{
	//打印表头
	cout << "|";
	for (int i = 1; i <= Variables::Varcnt; ++i)
	{
		cout << "$$" << Variables::VarSeq[i] << "$$" << "|";
	}
	cout << "$$" << Change(expression1) << "$$" << "|";
	cout << "$$" << Change(expression2) << "$$" << "|";
	cout << std::endl << "|";
	for (int i = 1; i <= Variables::Varcnt+2; ++i)
	{
		cout << ":---:" << "|";
	}
	
	return;
}

//
int NotequalCallTime = 0;
void NotEqual(int ExpAns1,int ExpAns2)
{
	NotequalCallTime++;
	if (NotequalCallTime == 1) { printTitle(); }
	cout << std::endl;
	cout << "|";
	for (int i = 1; i <= Variables::Varcnt; ++i)
	{
		cout << ((Variables::VariableVal[Variables::VariableName[Variables::VarSeq[i]]] == true) ? "$$True$$" : "$$False$$") << "|";
	}
	cout << (ExpAns1 == 1 ? "$$True$$" : "$$False$$") << "|";
	cout << (ExpAns2 == 1 ? "$$True$$" : "$$False$$") << "|";
}

//快速计算
void CalculateTwo(string exp1,string exp2)
{
	QuickCalculator qc(exp1);
	int ans1 = qc.work();
	qc.assign(exp2);
	int ans2 = qc.work();
	if (ans1 != ans2) { NotEqual(ans1, ans2); }
}

void QuickAssign(int step,string* str1,string* str2)
{
	if (step == Variables::Varcnt + 1) { CalculateTwo(*str1,*str2); return; }
	for (int i = 0; i <= 1; ++i)
	{
		Variables::VariableVal[step] = i;
		QuickAssign(step+1, str1, str2);
	}
	
}


//对比的主逻辑
void Compare(const string& str)
{
	NotequalCallTime = 0;
	cout << "### Phase  " << ++workTime << ".\n";
	
	getTwoExpression(str, expression1, expression2);
	cout << "#### Compare: \n$$\n" << Change(expression1)<<"\\quad and \\quad"<<Change(expression2)<<"\n$$" << endl;
	
	//if (CheckVariables(expression1, expression2) == 0) { NotTheSame("**Variables Not Match**"); cout << "\n\n\n\n\n\n\n"; return; }
	//if (CheckVariables(expression2, expression1) == 0) { NotTheSame("**Variables Not Match**"); cout << "\n\n\n\n\n\n\n"; return; }

	string exp1 = getPostfixNotion(expression1);
	string exp2 = getPostfixNotion(expression2);

	QuickAssign(1, &exp1, &exp2);

	if (!NotequalCallTime) cout << "Expression 1 and Expression 2 are **logically equal**.";
	else { cout << endl << endl; NotTheSame("**Value Not Match.**"); }
	cout << "\n\n\n\n\n\n\n";
	return;


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
		if (str.find("==") != string::npos) Compare(str);
		else workOne(str);
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

	fclose(stdout);
	system("start output.md");
	return 0;
}