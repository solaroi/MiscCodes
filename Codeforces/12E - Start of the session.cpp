#include<iostream>
using namespace std;
int len;
int matrix[1000][1000];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> len;
	for (int i = 0; i < len - 1; ++i)
		matrix[0][i] = i + 1;
	for (int i = 1; i < len - 1; ++i)
		for (int j = 0; j < len - 1; ++j)
			matrix[i][j] = matrix[i - 1][(j + 1) % (len - 1)];
	for (int i = 0; i < len-1; ++i)
	{
		matrix[i][len - 1] = matrix[i][i];
		matrix[len - 1][i] = matrix[i][len - 1];
		matrix[i][i] = 0;
	}
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < len; ++j)
			cout << matrix[i][j]<<' ';
		cout << endl;
	}
		
	return 0;
}
