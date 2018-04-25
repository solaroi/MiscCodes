#include <iostream>
#include <fstream> 
#include <sstream> 
#include <array>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <ctime>
#include <iomanip>
using namespace std;

//using SEGMENT = array<double, 4>;
//using SEG_MAP = list<SEGMENT>;
//using LINE = list<SEGMENT>;
//using LINE_MAP = list<LINE>;

typedef array<double, 4> SEGMENT;//Segment which contains 2 points, 4 coodinates
typedef list<SEGMENT> SEG_MAP;//Map consists of Segments
typedef list<SEGMENT> LINE;//Line consists of a set of Co-linear Segments 
typedef list<LINE> LINE_MAP;//Map consists of Line

const size_t X1 = 0, Y1 = 1, X2 = 2, Y2 = 3;

//judge collinearity of 2 segments
bool ColLinear(const SEGMENT &Seg1, const SEGMENT &Seg2)
{
	if ((Seg1[X2] - Seg1[X1])*(Seg2[Y2] - Seg2[Y1]) == (Seg2[X2] - Seg2[X1])*(Seg1[Y2] - Seg1[Y1]) && \
		(Seg1[X2] - Seg1[X1])*(Seg2[Y1] - Seg1[Y1]) == (Seg2[X1] - Seg1[X1])*(Seg1[Y2] - Seg1[Y1]))
		return true;
	else return false;
}

//judge collinearity of 1 line and 1 segment
bool ColLinear(const SEGMENT &Seg, const LINE &Line)
{
	if (Line.size() == 0)
		return true;
	SEGMENT Seg2 = Line.front();
	return ColLinear(Seg, Seg2);

}

//Add a map of segments into a map of lines by
//putting co-linear segments in one line
LINE_MAP Classify(const SEG_MAP &OrignMap, LINE_MAP &ClsfydMap)
{
	
	for (auto Seg : OrignMap)
	{
		if (ClsfydMap.size() == 0)
		{
			LINE Line; Line.push_back(Seg);
			ClsfydMap.push_back(Line);
		}
		else
		{
			bool IsColLinear = false;
			for (auto &L : ClsfydMap)
			{
				if (ColLinear(Seg, L))
				{
					L.push_back(Seg); IsColLinear = true; break;
				}
			}
			if (!IsColLinear)
			{
				LINE Line; Line.push_back(Seg);
				ClsfydMap.push_back(Line);
			}
		}
	}
	return ClsfydMap;
}

//judge whether there is any overlap in two co-linear segments
bool IsOverlap(const SEGMENT &Seg1, const SEGMENT &Seg2)
{
	if (Seg1[X1] == Seg1[X2] && Seg1[X1] == Seg2[X1])
		return ((Seg1[Y1] >= Seg2[Y1] && Seg1[Y1] <= Seg2[Y2]) || \
		(Seg1[Y1] <= Seg2[Y1] && Seg1[Y2] >= Seg2[Y1]));
	else return ((Seg1[X1] >= Seg2[X1] && Seg1[X1] <= Seg2[X2]) || \
		(Seg1[X1] <= Seg2[X1] && Seg1[X2] >= Seg2[X1]));
}

//merge two overlapped segments into one
SEGMENT Merge(const SEGMENT &Seg1, const SEGMENT &Seg2)
{
	SEGMENT Seg, lowSeg, upperSeg;
	if (Seg1[X1] == Seg1[X2])
	{ 
		lowSeg = Seg1[Y1] <= Seg2[Y1] ? Seg1 : Seg2;
		upperSeg = Seg1[Y2] >= Seg2[Y2] ? Seg1 : Seg2;
	}
	else
	{
		lowSeg = Seg1[X1] <= Seg2[X1] ? Seg1 : Seg2;
		upperSeg = Seg1[X2] >= Seg2[X2] ? Seg1 : Seg2;
	}
	Seg[X1] = lowSeg[X1];	Seg[Y1] = lowSeg[Y1];
	Seg[X2] = upperSeg[X2];	Seg[Y2] = upperSeg[Y2];
	return Seg;
}

//Simplify a line by merging its overlaped segments
LINE Merge(LINE &OrignLine)
{
	if (OrignLine.size() == 1)
		return OrignLine;
	LINE Line;
	Line.push_back(OrignLine.front());
	for (auto itr = ++OrignLine.begin(); itr != OrignLine.end(); ++itr)
	{
		SEGMENT MergedSeg = *itr;
		auto ItrNew = Line.begin();
		while (ItrNew != Line.end())
		{
			if (IsOverlap(*ItrNew, MergedSeg))
			{
				MergedSeg = Merge(*ItrNew, MergedSeg);
				ItrNew = Line.erase(ItrNew);
				continue;
			}
			++ItrNew;
		}
		Line.push_back(MergedSeg);
	}
	return Line;
}


int main()
{

	int SegNum;
	while (cin >> SegNum)
	{
		if (SegNum == 0)
			break;
		SEG_MAP OrignMap;
		SEGMENT Segmnt;
		for (auto i = 1; i <= SegNum; ++i)
		{
			cin >> Segmnt[X1] >> Segmnt[Y1] >> Segmnt[X2] >> Segmnt[Y2];
			if (Segmnt[X1] > Segmnt[X2])
			{
				double Temp;
				Temp = Segmnt[X1]; Segmnt[X1] = Segmnt[X2]; Segmnt[X2] = Temp;
				Temp = Segmnt[Y1]; Segmnt[Y1] = Segmnt[Y2]; Segmnt[Y2] = Temp;
			}
			else if (Segmnt[X1] == Segmnt[X2])
			{
				double Temp;
				Temp = Segmnt[Y1];
				Segmnt[Y1] = Segmnt[Y1] <= Segmnt[Y2] ? Segmnt[Y1] : Segmnt[Y2];
				Segmnt[Y2] = Temp >  Segmnt[Y2] ? Temp : Segmnt[Y2];
			}
			OrignMap.push_back(Segmnt);
		}
		LINE_MAP ClsfydMap;
		Classify(OrignMap, ClsfydMap);
		int Cnt = 0;
		for (auto &L : ClsfydMap)
		{
			L = Merge(L);
			Cnt = Cnt + L.size();
		}
		cout << Cnt << endl;
		/*for (auto L : ClsfydMap)
		{
		for (auto S : L)
		cout << S[X1] << " " << S[Y1] << " " << S[X2] << " " << S[Y2] << "     ";
		cout << endl;
		}
		cout << endl;*/
	}
	return 0;
}

