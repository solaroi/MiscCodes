#include <iostream>
#include <fstream> 
#include <sstream> 
#include <deque>
#include <string>
#include <vector>
using namespace std;
//
//
bool IsWinnable(deque<int> &Cards)
{
	int Cnt = 1;
	for (auto i = 1; i <= Cards.size(); ++i)
	{
		if (Cards[i - 1] == Cnt)
			return true;
		if (Cnt == 13)
			Cnt = 1;
		else ++Cnt;
	}
	return false;
}

int main()
{
	/*fstream Input; int inTemp;
	Input.open("Test0.txt");*/
	int CaseNum = 0;
	cin >> CaseNum;
	for(auto CaseCnt=1;CaseCnt<=CaseNum;++CaseCnt)
	{
		
		/*string inStr;
		getline(cin, inStr);
		deque<int> Cards; int UsrNum,inTemp;
		istringstream isstrm(inStr);
		while (isstrm >> inTemp)
			Cards.push_back(inTemp);
		UsrNum = Cards.front();
		Cards.pop_front();*/
		deque<int> Cards; int UsrNum, CinBuff;
		cin >> UsrNum;
		for (auto i = 1; i <= 52; ++i)
		{
			cin >> CinBuff;
			Cards.push_back(CinBuff);
		}
		cout << "Case " << CaseCnt << ": ";

		//UsrNum deque to represent UsrNum players' cards, indexed from 1 to UsrNum
		vector<deque<int>> Plyer;
		for (auto i = 0; i <= UsrNum; ++i)
		{
			if (i != 1)
			{
				deque<int> nextDeck;
				Plyer.push_back(nextDeck);
			}
			else Plyer.push_back(Cards);
			
		}

		int *Cnt = new int[UsrNum + 1], *Poped = new int[UsrNum + 1], \
			*CntJ = new int[UsrNum + 1], *CardNum= new int[UsrNum + 1];
		bool *Pause=new bool[UsrNum+1], *Start = new bool[UsrNum+1], \
			*AccumRemain = new bool[UsrNum + 1], IsNoSolution=false;
		for (auto i = 0; i <= UsrNum; ++i)
		{
			Cnt[i] = 0; Poped[i] = 0; CntJ[i] = 0; CardNum[i] = 0;
			Pause[i] = false; Start[i] = false; AccumRemain[i] = true;
		}
		Start[1] = true, Pause[1] = false; AccumRemain[0] = false;

		/*cout << UsrNum << " " << endl;
		for (auto p = Plyer[1].begin(); p != Plyer[1].end(); ++p)
			cout << *p << " ";
		cout << endl;
*/

		
		while (!IsNoSolution)
		{
			//counting for every player
			for (auto UID = 1; UID <= UsrNum; ++UID)
			{
				if (!Start[UID])
					continue;
				if (Pause[UID])
					continue;
				if (Cnt[UID] == 13)
					Cnt[UID] = 1;
				else ++Cnt[UID];
			}

			//action of every player one by one
			for (auto UID = 1; UID <= UsrNum; ++UID)
			{
				//receive cards from prev player
				if (Poped[UID - 1] != 0)
				{
					Start[UID] = true;
					Pause[UID] = false;
					Plyer[UID].push_back(Poped[UID - 1]);
					Poped[UID - 1] = 0;
				}

				//matching procedure
				if (Plyer[UID].size() != 0)
				{
					if (Cnt[UID] == Plyer[UID].front())
					{
						//cout << Cnt[UID] << " ";
						Poped[UID] = Cnt[UID];
						Plyer[UID].pop_front();
					}
					else
					{
						Plyer[UID].push_back(Plyer[UID].front());
						Plyer[UID].pop_front();
					}
				}
			
				//if cards run out, pause
				if (Plyer[UID].size() == 0 && Start[UID] && !Pause[UID])
				{
					if (!AccumRemain[UID - 1])
					{
						cout << Poped[UID] << " ";
						AccumRemain[UID] = false;
						if (UID == UsrNum)
						{
							cout << endl; IsNoSolution = true; break;
						}
							
					}
					Pause[UID] = true;
				}

				//if prev players done, record and check
				if (!AccumRemain[UID - 1] && !Pause[UID] && Plyer[UID].size() % 13 == 0)
				{
					if (!IsWinnable(Plyer[UID]))
					{
						cout << "unwinnable" << endl;
						IsNoSolution = true;
					}
						
				}
					

			}
		}
	}

	return 0;
}

