#include <vector>
#include <map>
#include <set>
#include <string>
#include <array>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

vector<vector<int>> bipartite_graph;
//map<int, set<array<int, 2>>> bipartite_graph_right;
vector<int> lvisited;
vector<int> rvisited;
vector<int> target;
vector<int> slack;
vector<int> lvalue, rvalue;

//find an argumenting path 
bool find_path(int lnum)
{
	lvisited[lnum] = 1;
	for (size_t rnum=0;rnum<bipartite_graph[lnum].size();++rnum)
	{
		int diff = lvalue[lnum] + rvalue[rnum] - bipartite_graph[lnum][rnum];
		if (diff == 0 && rvisited[rnum] == 0)
		{
			rvisited[rnum] = 1;
			if (target[rnum] < 0 || find_path(target[rnum]))
			{
				target[rnum] = lnum;
				return true;
			}
		}
	}
	return false;
}

//KM algorithm
int km_match()
{
	//init
	int num_left = bipartite_graph.size(), num_right = bipartite_graph.front().size();
	for (auto i = 0; i < num_right; ++i)
		rvalue[i] = 0;
	for (auto i = 0; i < num_left; ++i)
	{
		lvalue[i] = -numeric_limits<int>::max();
		for (auto j = 0; j < num_right; ++j)
		{
			if (lvalue[i] < bipartite_graph[i][j])
				lvalue[i] = bipartite_graph[i][j];
		}
	}
	//for every vertex in the left, find an argumenting path
	for (auto lnum = 0; lnum < num_left; ++lnum)
	{
		//loop until an argumenting path beginning at lnum is found
		while (true)
		{
			lvisited.assign(num_left, 0);
			rvisited.assign(num_right, 0);
			if (find_path(lnum))
				break;
			//if an argumenting path can not be found, then an argumenting tree has been found, denoted by rvisited and lvisited
			//update the lvalue and rvalue of vertex in the argumenting tree to allow expand the sub-graph
			int d = numeric_limits<int>::max();
			for (auto i = 0; i<num_left; ++i)
			{
				if (lvisited[i] != 0)
				{
					for (auto j = 0; j < num_right; ++j)
					{
						int diff = lvalue[i] + rvalue[j] - bipartite_graph[i][j];
						if (diff > 0 && d > diff)
							d = diff;
					}
				}
			}
			for (auto i = 0; i < num_left; ++i)
			{
				if (lvisited[i] != 0)
					lvalue[i] = lvalue[i] - d;
			}
			for (auto i = 0; i < num_right; ++i)
			{
				if (rvisited[i] != 0)
					rvalue[i] = rvalue[i] + d;
			}
		}
	}

	int cost = 0;
	for (auto i = 0; i < num_right; ++i)
	{
		if (target[i] >= 0)
			cost = cost + bipartite_graph[target[i]][i];
	}
	return cost;
}

int main()
{
	while (true)
	{
		int rows, cols;
		cin >> rows >> cols;
		if (rows == 0 && cols == 0)
			break;
		vector<vector<char>> input_matrix;
		input_matrix.resize(rows);
		string line;
		getline(cin, line);
		for (auto i = 0; i < rows; ++i)
		{
			getline(cin, line);
			for (auto j = 0; j < cols; ++j)
				input_matrix[i].push_back(line[j]);
		}

		vector<array<int, 2>> man;
		vector<array<int, 2>> house;
		for (auto i = 0; i < rows; ++i)
		{
			for (auto j = 0; j < cols; ++j)
			{
				array<int, 2> pos;
				pos[0] = i; pos[1] = j;
				if (input_matrix[i][j] == 'm')
					man.push_back(pos);
				if (input_matrix[i][j] == 'H')
					house.push_back(pos);
			}
		}
		
		//create the graph
		int num_left = man.size(), num_right = house.size();
		bipartite_graph.resize(num_left);
		for (auto &row : bipartite_graph)
			row.resize(num_right);
		for (auto i = 0; i < num_left; ++i)
			for (auto j = 0; j < num_right; ++j)
				bipartite_graph[i][j] = -abs(man[i].front() - house[j].front()) - abs(man[i].back() - house[j].back());
		lvisited.resize(num_left);
		rvisited.resize(num_right);
		target.clear();
		target.resize(num_right, -1);
		lvalue.resize(num_left);
		rvalue.resize(num_right);
		int cost = km_match();
		cout << -cost << endl;

	}
	return 0;
}

