#include <iostream>
using namespace std;

int visited[210][210];

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	int x{ 105 }, y{ 105 };
	visited[105][105] = 1;
	char c{ ' ' };
	while (true)
	{
		cin.get(c);
		if (c == '\n')
			break;
		else if (c == 'U')
			++y;
		else if (c == 'D')
			--y;
		else if (c == 'R')
			++x;
		else --x;
		if (visited[x][y] + visited[x][y + 1] + visited[x][y - 1] + visited[x - 1][y] + visited[x + 1][y] > 1)
		{
			cout << "BUG" << endl;
			return 0;
		}
		visited[x][y] = 1;
	}
	cout << "OK" << endl;
	return 0;
}
