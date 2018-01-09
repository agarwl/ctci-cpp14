#include <bits/stdc++.h>
using namespace std;

bool is_unique(const string s)
{
	unordered_set<char> chars;
	for(auto & ch: s)
	{
		if(chars.count(ch))
			return false;
		else
			chars.insert(ch);
	}
	return true;
}

bool is_unique2(const string s)
{
	string s1 = s;
	sort(s1.begin(), s1.end());
	for(int i = 1; i < s1.length(); i++)
	{
		if(s[i] == s[i-1])
			return false;
	}
	return true;
}

int main()
{
	string s;
	while(true)
	{
		cout << "Enter string to check: ";
		cin >> s;
		cout << (is_unique2(s) ? "Unique" : "NOT Unique") << endl;
	}
	return 0;
}