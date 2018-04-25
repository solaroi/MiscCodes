#include <iostream>
#include <set>
using namespace std;

int num_row, num_col, pres_row{ -1 }, pres_col{ -1 };
char **matrix, pres;
set<char> deputy;
bool **visited;
 
int main()
{
	cin >> num_row >> num_col >> pres;
	matrix = new char*[num_row];
	for (auto i = 0; i < num_row; ++i)
	{
		matrix[i] = new char[num_col];
		for (auto j = 0; j < num_col; ++j)
		{
			cin >> matrix[i][j];
			if (pres_row < 0 && matrix[i][j] == pres)
			{
				pres_row = i; pres_col = j;
			}
		}
	}

	//search the surounding grid of the president's table in clockwise direction
	int step[4][2], judge[4][2], dir{ 0 };
	step[0][0] = 0;  step[0][1] = 1;  judge[0][0] = 1;  judge[0][1] = 0;
	step[1][0] = 1;  step[1][1] = 0;  judge[1][0] = 0;  judge[1][1] = -1;
	step[2][0] = 0;  step[2][1] = -1; judge[2][0] = -1; judge[2][1] = 0;
	step[3][0] = -1; step[3][1] = 0;  judge[3][0] = 0;  judge[3][1] = 1;
	auto i = pres_row - 1, j = pres_col;
	while (dir<4)
	{
		auto rstep = step[dir][0]; auto cstep = step[dir][1];
		auto rjudge = judge[dir][0]; auto cjudge = judge[dir][1];
		bool has_neighbor = i >= 0 && i < num_row && j >= 0 && j < num_col;
		while (true)
		{
			if (!(i + rjudge >= 0 && i + rjudge < num_row && j + cjudge >= 0 && j + cjudge < num_col)\
				|| matrix[i + rjudge][j + cjudge] != pres)
			{
				i += rjudge; j += cjudge; break;
			}
			if (has_neighbor && matrix[i][j] != '.')
				deputy.insert(matrix[i][j]);
			i += rstep; j += cstep;
		}
		++dir;
	}
	cout << deputy.size() << endl;
	return 0;
}

//#include <iostream>
//#include <set>
//
//using namespace std;
//int num_row, num_col, pres_row{ -1 }, pres_col{ -1 };
//char **matrix, pres;
//set<char> deputy;
//bool **visited;
//
//
//void search(int i, int j)
//{
//	visited[i][j] = true;
//	int dir[4][2];
//	dir[0][0] = i;     dir[0][1] = j - 1;
//	dir[1][0] = i - 1; dir[1][1] = j;
//	dir[2][0] = i;     dir[2][1] = j + 1;
//	dir[3][0] = i + 1; dir[3][1] = j;
//	for (auto i = 0; i < 4; ++i)
//	{
//		auto r = dir[i][0], c = dir[i][1];
//		if (r >= 0 && r < num_row && c >= 0 && c < num_col)
//		{
//			if (matrix[r][c] == pres)
//			{
//				if (!visited[r][c])
//					search(r, c);
//			}
//			else if (matrix[r][c] != '.')
//				deputy.insert(matrix[r][c]);
//		}
//	}
//}
//
//int main()
//{
//	cin >> num_row >> num_col >> pres;
//	matrix = new char*[num_row];
//	visited = new bool*[num_row];
//	for (auto i = 0; i < num_row; ++i)
//	{
//		matrix[i] = new char[num_col];
//		visited[i] = new bool[num_col];
//		for (auto j = 0; j < num_col; ++j)
//		{
//			cin >> matrix[i][j];
//			visited[i][j] = false;
//			if (pres_row < 0 && matrix[i][j] == pres)
//			{
//				pres_row = i; pres_col = j;
//			}
//		}
//	}
//	search(pres_row, pres_col);
//	cout << deputy.size() << endl;
//	for (auto i = 0; i < num_row; ++i)
//		delete matrix[i], visited[i];
//	delete matrix, visited;
//	return 0;
//}