#include<iostream>
using namespace std;
int num_vertices, num_edges, max_state;
bool **graph;
//num_paths[state][v] is the number of paths from the smallest vertice of state to v
//state represents a collection of vertices in a path by using its bit. for example, the v bit of state must be 1
long long **num_paths;

void init()
{
	graph = new bool*[num_vertices];
	for (int i = 0; i < num_vertices; ++i)
	{
		graph[i] = new bool[num_vertices];
		for (int j = 0; j < num_vertices; ++j)
			graph[i][j] = false;
	}
	max_state = (1 << num_vertices) - 1;
	num_paths = new long long*[max_state + 1];
	for (int i = 0; i <= max_state; ++i)
	{
		num_paths[i] = new long long[num_vertices + 1];
		for (int j = 0; j <= num_vertices; ++j)
			num_paths[i][j] = 0;
	}
	for (int i = 0; i < num_vertices; ++i)
		num_paths[1 << i][i] = 1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> num_vertices >> num_edges;
	init();
	for (int i = 1; i <= num_edges; ++i)
	{
		int v1, v2;
		cin >> v1 >> v2;
		--v1; --v2;
		graph[v1][v2] = true;
		graph[v2][v1] = true;
	}
	long long num_circles{ 0 };
	for (int state = 1; state <= max_state; ++state)
	{
		int start;
		//find the smallest vertice in state
		for (start = 0; start < num_vertices; ++start)
			if (state & 1 << start)
				break;
		for (int endp = start; endp < num_vertices; ++endp)
		{
			if ((state & 1 << endp) && num_paths[state][endp] > 0)
			{
				if(graph[endp][start] && ((1 << start | 1 << endp) != state))
					num_circles += num_paths[state][endp];
				for (int new_endp = start + 1; new_endp < num_vertices; ++new_endp)
					if (graph[endp][new_endp] && (state & 1 << new_endp) == 0)
						num_paths[state | 1 << new_endp][new_endp] += num_paths[state][endp];
			}
		}
	}
	cout << num_circles / 2 << endl;
	return 0;
}


