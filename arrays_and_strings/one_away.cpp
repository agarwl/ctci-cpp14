#include <bits/stdc++.h>
using namespace std;

bool is_equal(const string & s1, const string & s2)
{
	return (s1 == s2);
}

bool check_dist(const string & s1, const string & s2)
{
	int len1 = s1.length(), len2 = s2.length();
	if (abs(len1 - len2) > 1)
		return false;
	for(int i = 0; i < min(len1, len2); i++)
	{
		if(s1[i] == s2[i])
			continue;
		else
		{
			int ind = (len1 > len2)? 1: 0;
			string a1 = s1.substr(i + ind), a2 =s2.substr(i + 1-ind);
			bool edit_dist = is_equal(a1, a2);
			if((len1 == len2) && !edit_dist)
			{
				a1 = s1.substr(i+1);
				a2 = s2.substr(i+1);
				edit_dist = is_equal(a1, a2);
			}
			return edit_dist;
		}
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
		bool check_distance = check_dist(s[0], s[1]);
		cout << (check_distance? "True": "False") << endl;
	}
	return 0;

}