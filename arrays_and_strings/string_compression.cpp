#include <bits/stdc++.h>
using namespace std;

string compressed(const string & s)
{
	string compressed = "";
	int count = 1;
	int len = s.length();
	for(int i = 1; i <= len; i++)
	{
		if(i == len || s[i] != s[i-1])
		{
			compressed += s[i-1];
			compressed += to_string(count);
			count = 1;
		}
		else
			count++;
	}
	if(compressed.length() < len)
		return compressed;
	else
		return s;
}

int main()
{
	string s;
	while(true)
	{
		cout << "Enter string: ";
		getline(cin, s);
		cout << "Compressed: " << compressed(s) << endl;
	}
	return 0;
}