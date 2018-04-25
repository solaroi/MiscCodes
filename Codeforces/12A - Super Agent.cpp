#include<iostream>
using namespace std;
char keyboard[3][3];


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			cin >> keyboard[i][j];
	for (int i = 0; i < 3; ++i)
	{
		if (keyboard[0][i] != keyboard[2][2 - i])
		{
			cout << "NO" << endl;
			return 0;
		}
	}
	if (keyboard[1][0] != keyboard[1][2])
	{
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	return 0;
}


