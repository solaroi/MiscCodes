#include <iterator>
#include <vector>
#include <array>
#include <deque>
#include <map>
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include "F:/Visual Studio 2015/Resource/DisjSets.h"
using namespace std;
#define EAST  0
#define SOUTH 1
#define WEST  2
#define NORTH 3
using ADJACENT_TYPE = int;
using PATH = vector<array<int, 2>>;
using AXIS = array<int, 2> ;
class Maze
{
public:
	Maze(const int rows = 10, const int cols = 10);
	void LayOut();
	int RandomAdjacentPos(const int CellNum, long RandomSeed);
	ADJACENT_TYPE GetAdjacentType(const int BasePos, const int AdjacentPos);
	PATH FindPath();
	bool FindPath(const int StartRows, const int StartCols, vector<int> &Visited, vector<int> &Prev);
	PATH ShortestPath();
	void Print(ostream &Output);
	vector<vector<array<int, 4>>> M;
	int NumRows, NumCols;
};
Maze::Maze(const int rows, const int cols)
{
	NumRows = rows;
	NumCols = cols;
	M.resize(rows);
	for (auto &v : M)
	{
		v.resize(cols);
		for (auto a : v)
		{
			a[0] = 0; a[1] = 0; a[2] = 0; a[3] = 0;
		}
	}
}

void Maze::LayOut()
{
	int StartNum = 0;
	int EndNum = NumCols*NumRows - 1;
	DisjSets MazeDS(EndNum + 1);
	vector<int> RandomPosition; RandomPosition.resize(EndNum + 1);
	for (auto i = 0; i <= EndNum; ++i)
		RandomPosition[i] = i;
	random_shuffle(RandomPosition.begin(), RandomPosition.end());
	long RandomSeed = 0;
	while (MazeDS.Find(EndNum) != MazeDS.Find(StartNum))
	{
		int BasePos = RandomPosition[RandomSeed % (EndNum + 1)], AdjacentPos = RandomAdjacentPos(BasePos, RandomSeed);
		int RootBase = MazeDS.Find(BasePos), RootAdj = MazeDS.Find(AdjacentPos);
		if (RootBase != RootAdj)
		{
			ADJACENT_TYPE Type = GetAdjacentType(BasePos, AdjacentPos);
			switch (Type)
			{
			case NORTH: {M[BasePos / NumCols][BasePos%NumCols][NORTH] = 1; M[AdjacentPos / NumCols][AdjacentPos%NumCols][SOUTH] = 1; break; }
			case EAST: {M[BasePos / NumCols][BasePos%NumCols][EAST] = 1;  M[AdjacentPos / NumCols][AdjacentPos%NumCols][WEST] = 1; break; }
			case SOUTH: {M[BasePos / NumCols][BasePos%NumCols][SOUTH] = 1; M[AdjacentPos / NumCols][AdjacentPos%NumCols][NORTH] = 1; break; }
			case WEST: {M[BasePos / NumCols][BasePos%NumCols][WEST] = 1;  M[AdjacentPos / NumCols][AdjacentPos%NumCols][EAST] = 1; break; }
			default: {cout << " Postion pair error" << endl;   break; }
			}
			MazeDS.Union(RootBase, RootAdj);
		}
		++RandomSeed;
	}
}

int Maze::RandomAdjacentPos(const int CellNum, long RandomSeed)
{
	int EndNum = NumRows*NumCols - 1;
	vector<int> AdjacentCells;
	if (CellNum - 1 >= 0 && CellNum / NumCols == (CellNum - 1) / NumCols)
		AdjacentCells.push_back(CellNum - 1);
	if (CellNum + 1 <= EndNum && CellNum / NumCols == (CellNum + 1) / NumCols)
		AdjacentCells.push_back(CellNum + 1);
	if (CellNum - NumCols >= 0)
		AdjacentCells.push_back(CellNum - NumCols);
	if (CellNum + NumCols <= EndNum)
		AdjacentCells.push_back(CellNum + NumCols);
	default_random_engine generator(RandomSeed / 5 % 65536);//To get a different direction, change this statement e.g. 3->5
	uniform_int_distribution<int> distribution(0, AdjacentCells.size() - 1);
	int Index = distribution(generator);
	return AdjacentCells[Index];
}

ADJACENT_TYPE Maze::GetAdjacentType(const int BasePos, const int AdjacentPos)
{
	int Diff = AdjacentPos - BasePos;
	if (Diff == 1)
		return EAST;
	else if (Diff == -1)
		return WEST;
	else if (Diff == NumCols)
		return SOUTH;
	else if (Diff == -NumCols)
		return NORTH;
	else return -1;
}

//DFS
bool Maze::FindPath(const int X, const int Y, vector<int> &Visited, vector<int> &Prev)
{
	int CellNum = X*NumCols + Y;
	Visited[CellNum] = 1;
	if (X == NumRows - 1 && Y == NumCols - 1)
		return true;
	if (M[X][Y][EAST] == 1 && Visited[CellNum + 1] == 0)
	{
		Prev[CellNum + 1] = CellNum;
		if (FindPath(X, Y + 1, Visited, Prev))
			return true;
	}
	if (M[X][Y][SOUTH] == 1 && Visited[CellNum + NumCols] == 0)
	{
		Prev[CellNum + NumCols] = CellNum;
		if (FindPath(X + 1, Y, Visited, Prev))
			return true;
	}

	if (M[X][Y][WEST] == 1 && Visited[CellNum - 1] == 0)
	{
		Prev[CellNum - 1] = CellNum;
		if (FindPath(X, Y - 1, Visited, Prev))
			return true;
	}
	if (M[X][Y][NORTH] == 1 && Visited[CellNum - NumCols] == 0)
	{
		Prev[CellNum - NumCols] = CellNum;
		if (FindPath(X - 1, Y, Visited, Prev))
			return true;
	}
	return false;
}

PATH Maze::FindPath()
{
	vector<array<int, 2>> Path;
	vector<int> Visited, Prev;
	Visited.resize(NumCols*NumRows);
	Prev.resize(NumCols*NumRows);
	bool IsFind = FindPath(0, 0, Visited, Prev);
	if (IsFind)
	{
		int CellNum = NumCols*NumRows - 1;
		while (CellNum != 0)
		{
			Path.push_back({ CellNum / NumCols,CellNum%NumCols });
			CellNum = Prev[CellNum];
		}
		Path.push_back({ 0,0 });
		reverse(Path.begin(), Path.end());
	}
	else return{ { -1,-1 } };
	return Path;
}

//BFS
PATH Maze::ShortestPath()
{
	PATH Path;
	vector<AXIS> Known;
	map<AXIS, int> Distance;
	map<AXIS, AXIS> Prev;
	deque<AXIS> Unknown;
	Unknown.push_back({ 0, 0 });
	int X, Y;
	while (!Unknown.empty())
	{
		AXIS Curr = Unknown.front(); Unknown.pop_front();
		Known.push_back(Curr);
		X = Curr[0]; Y = Curr[1];
		if (M[X][Y][EAST] == 1 && none_of(Known.cbegin(), Known.cend(), [X, Y](AXIS A) {return A[0]==X && A[1]==Y+1; }))
		{
			Prev[{X, Y + 1}] = Curr;
			Distance[{X, Y + 1}] = Distance[Curr] + 1;
			Unknown.push_back({ X,Y + 1 });
		}
		if (M[X][Y][SOUTH] == 1 && none_of(Known.cbegin(), Known.cend(), [X, Y](AXIS A) {return A[0] == X+1 && A[1] == Y; }))
		{
			Prev[{X + 1, Y}] = Curr;
			Distance[{X + 1, Y}] = Distance[Curr] + 1;
			Unknown.push_back({ X + 1, Y });
		}
		if (M[X][Y][WEST] == 1 && none_of(Known.cbegin(), Known.cend(), [X, Y](AXIS A) {return A[0] == X && A[1] == Y-1; }))
		{
			Prev[{X, Y - 1}] = Curr;
			Distance[{X, Y - 1}] = Distance[Curr] + 1;
			Unknown.push_back({ X, Y - 1 });
		}
		if (M[X][Y][NORTH] == 1 && none_of(Known.cbegin(), Known.cend(), [X, Y](AXIS A) {return A[0] == X-1 && A[1] == Y; }))
		{
			Prev[{X - 1, Y}] = Curr;
			Distance[{X - 1, Y}] = Distance[Curr] + 1;
			Unknown.push_back({ X - 1, Y });
		}
	}
	int NR = NumRows - 1, NC = NumCols - 1;
	if (none_of(Known.cbegin(), Known.cend(), [NR, NC](AXIS A) {return A[0] == NR && A[1] == NC; }))
		return{ {-1,-1} };
	X = NR; Y = NR; AXIS A;
	Path.push_back({ X,Y });
	while (X != 0 || Y != 0)
	{
		A = Prev.at({X, Y});
		X = A[0]; Y = A[1];
		Path.push_back({ X,Y });
	}
	reverse(Path.begin(), Path.end());
	return Path;
}

void Maze::Print(ostream &Output)
{
	for (auto rows : M)
	{
		for (auto cols : rows)
		{
			for (auto w : cols)
				Output << w;
			Output << " ";
		}
		Output << endl;
	}
	fstream output("F:/Visual Studio 2015/src.cpp");
	for (auto rows : M)
	{
		Output << " ";
		for (auto cols : rows)
		{
			if (cols[NORTH] == 0)
				Output << "=== ";
			else Output << "    ";
		}
		Output << endl;
		for (auto cols : rows)
		{
			if (cols[WEST] == 0)
				Output << "|   ";
			else Output << "    ";
		}
		Output << "|" << endl;
	}
	for (auto i = 0; i < NumCols; ++i)
		Output << " ===";
	Output << endl;
}


int main()
{
	Maze m(10, 10);
	vector<array<int, 2>> Path;
	m.LayOut();
	m.Print(cout);
	ofstream OutFile;
	OutFile.open("F:/Visual Studio 2015/src.cpp", ofstream::out | ofstream::app);
	m.Print(OutFile);
	Path = m.FindPath();
	cout << "Find a path:" << endl;
	for (auto itr = Path.cbegin(); itr != Path.cend(); ++itr)
		cout << "(" << (*itr)[0] << ", " << (*itr)[1] << ")  ";
	cout << endl;
	Path = m.ShortestPath();
	cout << "Shortest path:" << endl;
	for (auto itr = Path.cbegin(); itr != Path.cend(); ++itr)
		cout << "(" << (*itr)[0] << ", " << (*itr)[1] << ")  ";
	cout << endl;
	return 0;
}
1000 0110 1100 0110 1100 1010 0110 0100 1100 0110 
1100 1011 0111 1101 1111 0110 0101 0101 0001 0101 
0101 1000 0011 0001 0101 0101 1001 1011 1010 0111 
0001 1000 1110 1010 0011 1001 1010 1110 0110 0001 
1100 1110 0111 0100 0100 1000 1010 0011 0001 0100 
0101 0101 0001 1001 1011 1010 0110 1000 1110 0011 
0001 1101 1110 1110 1010 1110 0111 1100 1011 0010 
1100 0011 0001 0101 0100 0001 0001 1001 1110 0010 
1101 1010 0010 1001 1111 1110 1010 0110 1001 0110 
1001 1010 1010 0010 0001 0001 1000 1011 1010 0011 
 === === === === === === === === === === 
|       |       |           |   |       |
 ===                 ===                 
|           |           |   |   |   |   |
     ===                         ===     
|   |       |   |   |   |               |
     === === ===         === === ===     
|   |               |               |   |
 === ===     === === === ===         === 
|           |   |   |           |   |   |
                     === === === ===     
|   |   |   |               |           |
         === === === ===     ===     === 
|   |                       |           |
 ===             ===             === === 
|       |   |   |   |   |   |           |
     === ===         === === ===     === 
|           |                   |       |
     === === ===         ===     ===     
|               |   |   |               |
 === === === === === === === === === ===
