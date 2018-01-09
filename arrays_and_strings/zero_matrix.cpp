#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int> > matrix;

void print_matrix(const matrix & m)
{
	int N = m.size();
	if(N == 0)
		return;
	cout << "Printing matrix..." << endl;
	for (int i = 0; i < N; ++i)
	{
		for(int j = 0 ; j < m[0].size(); j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	return;
}

void create_zeros(matrix & m)
{
	int N = m.size();
	unordered_set<int> rows, cols;
	for(int i =0; i < N; i++)
		for(int j =0; j < m[0].size(); j++)
		{
			if(m[i][j] == 0)
			{
				rows.insert(i);
				cols.insert(j);
			}
		}
	for(auto it = rows.begin(); it!= rows.end(); it++)
	{
		int row = *it;
		for(int i = 0; i < m[row].size(); i++)
			m[row][i] = 0;
	}
	for(auto it = cols.begin(); it!= cols.end(); it++)
	{
		int col = *it;
		for(int i = 0; i < N; i++)
			m[i][col] = 0;
	}
}

int main()
{
	int N, M;
	while(true)
	{
		cout << "Enter N: ";
		cin >> N;
		cout << "Enter M: ";
		cin >> M;
		matrix m(N, vector<int>(M));
		cout << "Enter the matrix" << endl;
		for(int i = 0; i < N; i++)
			for(int j = 0; j < M; j++)
				cin >> m[i][j];
		create_zeros(m);
		print_matrix(m);
	}
}