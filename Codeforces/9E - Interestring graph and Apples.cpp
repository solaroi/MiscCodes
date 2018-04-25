#include<iostream>
#include<algorithm>
#include<vector>
#include<list>
#include<set>
using namespace std;

class DisjUnion
{
public:
	int *data_;
	int size_;
	DisjUnion(int size = 1);
	int find(int root);
	void Union(int root1, int root2);
};

DisjUnion::DisjUnion(int size)
{
	size_ = size;
	data_ = new int[size];
	for (int i = 0; i < size; ++i)
		data_[i] = -1;
}

int DisjUnion::find(int x)
{
	if (data_[x] < 0)
		return x;
	else data_[x] = find(data_[x]);
	return data_[x];
}

void DisjUnion::Union(int root1, int root2)
{
	int v1 = find(root1), v2 = find(root2);
	if (v1 < v2)
		data_[v2] = v1;
	else if (v1 > v2)
		data_[v1] = v2;
}

vector<vector<int>> graph;
int visited[51];

int GetOtherSide(int v)
{
	if (graph[v].empty())
		return v;
	int the_other_side = graph[v][0];
	visited[the_other_side] = 1;
	while (graph[the_other_side].size() >= 2)
	{
		the_other_side = visited[graph[the_other_side][0]] ? graph[the_other_side][1] : graph[the_other_side][0];
		visited[the_other_side] = 1;
	}
	return the_other_side;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int num_vertices, num_edges;
	cin >> num_vertices >> num_edges;
	graph.resize(num_vertices + 1);
	bool ispossible{ true }, hasloop{ false };
	DisjUnion cycle(num_vertices + 1);
	for (int i = 1; i <= num_edges; ++i)
	{
		int v1, v2;
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
		//if there is a vertice that connect to at least 3 other vertices, impossible
		if (graph[v1].size() > 2 || graph[v2].size() > 2)
			ispossible = false;
		if (cycle.find(v1) == cycle.find(v2))
			hasloop = true;
		cycle.Union(v1, v2);
	}
	//if there is a loop that is not a funny ring, impossible
	if (hasloop && ispossible)
	{
		int cycle_num = cycle.find(1);
		for (int v = 1; v <= num_vertices; ++v)
		{
			if (cycle.find(v) != cycle_num)
				ispossible = false;
		}
	}
	if (!ispossible)
	{
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	if (hasloop)
	{
		cout << 0 << endl;
		return 0;
	}
	else if (num_vertices == 1)
	{
		cout << 1 << endl << 1 << ' ' << 1 << endl;
		return 0;
	}
	else if (num_vertices == 2)
	{
		if (num_edges == 1)
			cout << 1 << endl << 1 << ' ' << 2 << endl;
		else cout << 2 << endl << 1 << ' ' << 2 << endl << 1 << ' ' << 2 << endl;
		return 0;
	}
	//get the 2 end points of each segments
	//for an isolated point, the end points are themselves
	vector<int> end_points_vector;
	int *terminal_pair = new int[num_vertices + 1];
	for (int i = 1; i <= num_vertices; ++i)
	{
		if (visited[i]==0 && graph[i].size() <= 1)
		{
			visited[i] = 1;
			int the_other_side = GetOtherSide(i);
			end_points_vector.push_back(i);
			end_points_vector.push_back(the_other_side);
			terminal_pair[i] = the_other_side;
			terminal_pair[the_other_side] = i;

		}
	}
	//connect those end points from smallest to largest
	sort(end_points_vector.begin(), end_points_vector.end());
	list<int> end_points_list;
	for (auto v : end_points_vector)
		end_points_list.push_back(v);
	set<pair<int, int>> edges;
	while (end_points_list.size()>2)
	{
		int v1 = *end_points_list.begin();
		end_points_list.erase(end_points_list.begin());
		for (auto itr = end_points_list.begin(); itr != end_points_list.end();++itr)
		{
			int v2 = *itr;
			//if the 2 vertices belong to different segements, connect them
			if (cycle.find(v2) != cycle.find(v1))
			{
				edges.insert(make_pair(v1, v2));
				end_points_list.erase(itr);
				cycle.Union(v1, v2);
				break;
			}
		}
	}
	edges.insert(make_pair(end_points_list.front(), end_points_list.back()));
	cout << edges.size() << endl;
	for (auto x : edges)
		cout << x.first << ' ' << x.second << endl;
	return 0;
}


