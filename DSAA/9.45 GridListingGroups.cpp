#include <iostream>
#include <vector>
#include <array>
#include <map>
using namespace std;
using AXIS = array<int, 2>;
using GRID = vector < vector<int >> ;
using GROUP = vector<array<int, 2>>;
using GROUPS = vector<GROUP>;

bool IsInGroups(AXIS Axis0, GROUPS &Groups)
{
	for (auto Group : Groups)
	{
		for (auto Axis : Group)
		{
			if (Axis == Axis0)
				return true;
		}
	}
	return false;
}
void AddInGroups(AXIS Axis, GROUP &Group, GRID &Grid, map<AXIS,bool> &Visited)
{
	Visited[Axis] = true;
	Group.push_back(Axis);
	int X = Axis[0], Y = Axis[1];
	if (Y + 1 < 10 && Grid[X][Y + 1] == 1 && !Visited.at({ X,Y + 1 }))
		AddInGroups({ X,Y + 1 }, Group, Grid, Visited);
	if (Y - 1 > 0 && Grid[X][Y - 1] == 1 && !Visited.at({ X,Y - 1 }))
		AddInGroups({ X,Y - 1 }, Group, Grid, Visited);
	if (X + 1 < 10 && Grid[X + 1][Y] == 1 && !Visited.at({ X + 1,Y }))
		AddInGroups({ X + 1,Y }, Group, Grid, Visited);
	if (X - 1 > 0 && Grid[X - 1][Y] == 1 && !Visited.at({ X - 1,Y }))
		AddInGroups({ X - 1,Y }, Group, Grid, Visited);
}

int main()
{
	GRID G;
	G.resize(10);
	for (auto &Rows : G)
		Rows.resize(10);
	G[0][9] = 1;
	G[1][3] = G[1][4] = G[1][9] = 1;
	G[3][4] = G[3][7] = 1;
	G[4][3] = G[4][7] = 1;
	G[5][7] = G[5][8] = 1;
	G[6][4] = G[6][5] = 1;
	for (auto Rows : G)
	{
		for (auto cell : Rows)
			cout << cell << " ";
		cout << endl;
	}
	GROUPS Groups;
	map<AXIS, bool> Visited;
	for (auto Rows = 0; Rows < 10; ++Rows)
		for (auto Cols = 0; Cols < 10; ++Cols)
			Visited[{Rows, Cols}] = false;

	for (auto Rows=0;Rows<10;++Rows)
	{
		for (auto Cols=0;Cols<10;++Cols)
		{
			if (G[Rows][Cols] == 1 && !Visited.at({ Rows,Cols }) && !IsInGroups({ Rows,Cols }, Groups))
			{
				GROUP Group;
				AddInGroups({ Rows,Cols }, Group, G, Visited);
				Groups.push_back(Group);
			}
		}
	}

	for (auto Group : Groups)
	{
		for (auto Axis : Group)
			cout << "(" << Axis[0] << ", " << Axis[1] << ")";
		cout << endl;
	}

	return 0;
}