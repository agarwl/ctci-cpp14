#include <bits/stdc++.h>
using namespace std;

bool check_palindrome_perm(const string & s)
{
	unordered_map<char, int> counts;
	int len_palin = 0;
	for(auto ch : s)
	{
		if(ch != ' '){
			len_palin++;
			ch = tolower(ch);
			if(counts.count(ch))
				counts[ch]++;
			else
				counts[ch] = 1;
		}
	}
	int num_odd = 0;
	for(auto it=counts.begin(); it!= counts.end(); it++)
	{
		if(it->second % 2)
			num_odd++;
	}
	return (len_palin%2 - num_odd) == 0;
}

int main()
{
	string s;
	bool is_palin_perm;
	while(true){
		cout << "Enter the string: ";
		getline(cin, s);
		is_palin_perm = check_palindrome_perm(s);
		cout << (is_palin_perm?"True": "False") << endl;
	}
	return 0;
}