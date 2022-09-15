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




#endif // !PUBLICMETHOD_H
