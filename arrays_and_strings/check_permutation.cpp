#include <bits/stdc++.h>
using namespace std;

bool check_permuation(const string & s1, const string & s2)
{
	unordered_map<char, int> char_counts;
	for(auto const & ch : s1)
	{
		if(char_counts.count(ch))
			char_counts[ch] += 1;
		else
			char_counts[ch] = 1;
	}
	for(auto const & ch : s2)
	{
		if(char_counts.count(ch))
		{
			char_counts[ch]--;
			if(char_counts[ch] < 0)
				return false;
		}
		else
			return false;
	}
	return true;
}

int main()
{
	string s[2];
	while(true){
		for(int i = 0; i < 2; i++)
		{
			cout << "Enter string " << i+1 << ": ";
			cin >> s[i];
		}
		bool perm = check_permuation(s[0], s[1]);
		cout << (perm? "Permuation": "Not Permuation") << endl;
	}
	return 0;
}