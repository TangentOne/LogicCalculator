#ifndef PUBLICMETHOD_H
#define PUBLICMETHOD_H


bool isAlphabet(char x)
{
	if (x >= 'a' && x <= 'z') return true;
	if (x >= 'A' && x <= 'Z')return true;
	return false;
}

string extractVar(const string& data, int& sta)
{
	string tmp;
	for (; isAlphabet(data[sta]); ++sta)
	{
		tmp += data[sta];
	}
	sta--;
	return tmp;
}

//将字符串中的逻辑符号转换为markdown输出
string Change(string str)
{
	size_t last = 0;
	while ((last = str.find('>', last + 1)) != string::npos) { str.replace(last, 1, "\\rightarrow "); }
	while ((last = str.find('<', last + 1)) != string::npos) { str.replace(last, 1, "\\leftrightarrow "); }
	while ((last = str.find('&', last + 1)) != string::npos) { str.replace(last, 1, "\\land "); }
	while ((last = str.find('|', last + 1)) != string::npos) { str.replace(last, 1, "\\lor "); }
	while ((last = str.find('^', last + 1)) != string::npos) { str.replace(last, 1, "\\bigoplus "); }
	while ((last = str.find('!', last + 1)) != string::npos) { str.replace(last, 1, "\\neg "); }

	return str;
}


Priority getPriority(char x)
{
	if (x == '!') { return Priority::P_NEG; }
	if (x == '&') { return Priority::P_CONJ; }
	if (x == '|') { return Priority::P_DISJ; }
	if (x == '>') { return Priority::P_IMPLY; }
	if (x == '<') { return Priority::P_DUAL; }
	if (x == '(') { return Priority::P_LEFT; }
	if (x == ')') { return Priority::P_RIGHT; }
	if (x == '^') { return Priority::P_XOR; }
	std::cerr << "No operator" << x << "exsited.";
	exit(1);
}

char getOperatorName(Priority p)
{
	if (p == Priority::P_NEG) { return '!'; }
	if (p == Priority::P_DISJ) { return '|'; }
	if (p == Priority::P_CONJ) { return '&'; }
	if (p == Priority::P_IMPLY) { return '>'; }
	if (p == Priority::P_DUAL) { return '<'; }
	if (p == Priority::P_XOR) { return '^'; }

	std::cerr << "No operator" << p << "exsited.";
	exit(1);
}

bool ExtractConst(const string& data, int& sta, bool& val)
{
	while (data[sta] == ' ') sta++;
	if (data[sta + 1] == ':')
	{
		sta += 2;
		if (data[sta] == '1')val = true;
		else val = false;
		return true;
	}
	else return false;
}

string getASqure(string name)
{
	return '(' + name + ')';
}


#endif // !PUBLICMETHOD_H
