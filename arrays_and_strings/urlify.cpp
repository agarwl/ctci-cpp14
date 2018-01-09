#include <bits/stdc++.h>
using namespace std;


string urilify(string & s)
{
	int len = s.size();
	int last_index;
	for(last_index = len - 1; last_index >= 0; last_index--)
	{
		if(s[last_index] == ' ')
			continue;
		else
			break;
	}
	int end = len-1;
	for(int i = last_index; i >=0; i--)
	{
		if(s[i] != ' ')
			s[end] = s[i];
		else{
			end = end - 2;
			s.replace(end,3,"%20");
		}
		end--;
	}
	return s;
}

int main()
{
	string s = "Mr John Smith";
	s.append(string(4, ' '));
	cout << urilify(s) << endl;
}