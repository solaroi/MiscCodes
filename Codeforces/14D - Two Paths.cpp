#include<iostream>
#include<algorithm>
#include<deque>
using namespace std;

int num_cities;
int map[201][201];
int roads[201][2];
deque<int> cities, depth;

//dfs: calculate the depth of all nodes
void Cal_Depth_DFS(int start)
{
	for (int i = 1; i <= num_cities; ++i)
	{
		if (map[start][i] == 1 && depth[i] < 0)
		{
			depth[i] = depth[start] + 1;
			Cal_Depth_DFS(i);
		}
	}
}

//bfs: calculate the depth of all nodes
void Cal_Depth_BFS(int root)
{
	cities.clear();
	depth[root] = 0;
	cities.push_back(root);
	int c;
	while (!cities.empty())
	{
		c = cities.front();
		cities.pop_front();
		for (int i = 1; i <= num_cities; ++i)
		{
			if (map[c][i] == 1 && depth[i] < 0)
			{
				depth[i] = depth[c] + 1;
				cities.push_back(i);
			}
		}
	}
}

int diameter(int root)
{
	depth.assign(num_cities + 1, -1);
	depth[root] = 0;
	Cal_Depth_DFS(root);
	auto start_city_itr = max_element(depth.cbegin(), depth.cend());
	int start_city = distance(depth.cbegin(), start_city_itr);
	depth.assign(num_cities + 1, -1);
	depth[start_city] = 0;
	Cal_Depth_DFS(start_city);
	auto end_city_itr = max_element(depth.cbegin(), depth.cend());
	return *end_city_itr;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	

	cin >> num_cities;
	int x, y;
	for (int i = 1; i < num_cities; ++i)
	{
		cin >> x >> y;
		map[x][y] = 1;
		map[y][x] = 1;
		roads[i][0] = x;
		roads[i][1] = y;
	}
	int max_profit{ 0 };
	for (int i = 1; i < num_cities; ++i)
	{
		int x = roads[i][0], y = roads[i][1];
		map[x][y] = 0; map[y][x] = 0;
		int d1 = diameter(x), d2 = diameter(y);
		max_profit = max(max_profit, d1*d2);
		map[x][y] = 1; map[y][x] = 1;
	}
	cout << max_profit << endl;
	return 0;
}
