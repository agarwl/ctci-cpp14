#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int> > matrix;


matrix rotate_naive(const matrix & m)
{
	int N = m.size();
	if(N == 0)
		return m;
	int M = m[0].size();

	matrix X(M, vector<int>(N));
	for(int i =0; i < N; i++)
		for(int j = 0; j < M; j++)
		{
			X[j][N-1-i] = m[i][j];
		}
	return X;
}

// assume matrix is N X N
void rotate_matrix(matrix & m)
{
	int N = m.size();
	if(N == 0) return;
	int temp;
	for(int i = 0; i < N/2; i++)
		for(int j = i; j <= (N-i)/2; j++)
		{
			temp = m[i][j];
			m[i][j] = m[N-1-j][i];
			m[N-1-j][i] = m[N-1-i][N-1-j];
			m[N-1-i][N-1-j] = m[j][N-1-i];
			m[j][N-1-i] = temp;
		}
	return;
}

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

int main()
{
	int N;
	while(true)
	{
		cout << "Enter N: ";
		cin >> N;
		matrix m(N, vector<int>(N));
		cout << "Enter the matrix" << endl;
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				cin >> m[i][j];
		matrix m1 = rotate_naive(m);
		rotate_matrix(m);
		assert(m1 == m);
		// print_matrix(m);
		// print_matrix(m1);
	}
}