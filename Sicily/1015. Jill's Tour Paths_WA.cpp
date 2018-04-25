
#include <iostream>
#include <map>
#include <array>
#include <set>
#include <vector>
using namespace std;
map<int, set<array<int, 2>>> graph;
int start, dest, max_dist;
set<vector<int>> routes;
vector<int> visited;
vector<int> next_vertex;
vector<int> weight;

void find(int x)
{
	if (x == dest)
	{
		if (weight[dest] <= max_dist)
		{
			vector<int> route;
			route.push_back(weight[dest]);
			for (int v = start; v != 0; v = next_vertex[v])
				route.push_back(v);
			routes.insert(route);
		}
		return;
	}
	visited[x] = 1;
	for (auto p : graph[x])
	{
		int end = p.front(), weig = p.back();
		if (visited[end] == 0)
		{
			next_vertex[x] = end;
			weight[end] = weight[x] + weig;
			find(end);
		}

	}
	visited[x] = 0;
}

int main()
{
	int i = 1;
	while (true)
	{
		graph.clear();
		int num_vertex, num_edge;
		cin >> num_vertex;
		if (num_vertex == -1)
			break;
		cin >> num_edge;
		for (auto i = 0; i < num_edge; ++i)
		{
			int v1, v2, dist;
			cin >> v1 >> v2 >> dist;
			array<int, 2> v1tov2;
			v1tov2.front() = v2; v1tov2.back() = dist;
			graph[v1].insert(v1tov2);
			v1tov2.front() = v1; 
			graph[v2].insert(v1tov2);
		}
		cin >> start >> dest >> max_dist;
		
		visited.resize(num_vertex + 1, 0); visited.assign(num_vertex + 1, 0);
		next_vertex.resize(num_vertex + 1); next_vertex.assign(num_vertex + 1, 0);
		weight.resize(num_vertex + 1, 0); weight.assign(num_vertex + 1, 0);
		routes.clear();
		find(start);
		cout << "Case " << i <<":"<<endl;
		if (routes.empty())
			cout << "&nbsp;NO ACCEPTABLE TOURS" << endl;
		else
		{
			for (auto route : routes)
			{
				cout << "&nbsp;" << route[0] << ": ";
				for (auto itr = ++route.cbegin(); itr != route.cend(); ++itr)
					cout << *itr << " ";
				cout << endl;
			}
		}
		++i;
	}
}