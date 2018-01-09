#include <bits/stdc++.h>
using namespace std;

// proper prefix array
vector<int> create_prefix_arr(const string & s)
{
	int len = s.size();
	if (len <= 1) return {-1};
	vector<int> p(len, -1);
	for(int i = 1; i < len; i++)
	{
		int j = p[i-1];
		if(j == -1)
			p[i] = (s[i] == s[0])? 0:-1;
		while(j != -1)
		{
			if(s[j+1] == s[i])
			{
				p[i] = j + 1;
				break;
			}
			else
				j = p[j];
		}
	}
	return p;
}

// Checks whether s2 is a substring of s1 using KMP
bool isSubstring(const string & s1, const string & s2)
{
	auto prefix_arr = create_prefix_arr(s2);
	int i1 = 0, i2 = 0;
	while(i1 < s1.length() && i2 < s2.length())
	{
		if(s1[i1] == s2[i2])
		{
			i2++;
			i1++;
		}
		else
		{
			if(i2 != 0)
				i2 = prefix_arr[i2-1] + 1;
			else
				i1++;
		}
	}
	return (i2 == s2.length());
}

bool isSubstringNaive(const string & s1, const string & s2)
{
	int j;
	for(int i = 0; i < s1.length(); i++)
	{
		for(j = 0; j < s2.length() && i+j < s1.length(); j++)
		{
			if(s1[i+j] == s2[j])
				continue;
			else
				break;
		}
		if( j == s2.length())
			return true;
	}
	return false;
}

bool check_rotation(const string & s1, const string & s2)
{
	if(s1.size() != s2.size())
		return false;
	string s = s1 + s1;
	return isSubstring(s, s2);
}

int main()
{
	string s[2];
	while(true){
		for(int i = 0; i < 2; i++)
		{
			cout << "Enter string " << i+1 << ": ";
			getline(cin, s[i]);
		}
		bool rot = check_rotation(s[0], s[1]);
		cout << (rot? "True": "False") << endl;
	}
	return 0;
}