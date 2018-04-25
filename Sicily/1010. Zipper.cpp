The training data of this problem is absolutely wrong!!!
From the discussion above, almost all of us get the same idea: dispose from the header or the back of the mixed string char by char.
The bug is that as long as your program starts at the header, you'll encounter a limited time problem no matter which recusion style you use. And if you change to the opposite direction, everything gets good.
Note that when both header char of the 1st and 2nd string matchs that of the mixed string, we need to check both of them. But if the first situation turns out to return a correct value, then there is no need to check the 2nd and vice versa.
At first, I stucked in the problem of time limited. Someone says don't use recursion, use the dynamic programing. I don't know what is a DP, but I thought the the time may be consumed by too many fuction calls. So I choose the non-recursion style, preserve the necessary information into a vector when
the program gets to branches. Unfortunately£¬it doesn't work until I find this bug.
I tested the 2 different recursion style by inserting ++Counter in each if statement and the result is as what I had thought: a so-called dp solution or a bool return solution do the same number of judges. Since the length of the string is no more than 2*200, function calls won't waste too much time.
The root of this bug might be that there are too many cases like "cat tree catrtee" in the data set which need our program to branch when we start at the beginning of the string. But if we start at the end, no branch is need at all. The data set should include more cases like "cat tree ctatree" to get a balance.
Hope someone to fix this bug.

//handling from the beginning of string get into a time limited problem
#include <iostream>
#include <string>
#include <vector>
#include <array>
using namespace std;
int NumDataSets;
string Str1, Str2, StrMix;
vector<array<int, 3>> PosReserved;
bool IsValid;
int Count;//just for testing the bug of data set, please ignore it 
//bool Check(int PosStr1, int PosStr2, int PosStrMix)
//{
//    if (PosStrMix >= StrMix.length())
//        return true;
//    else
//    {
//        if (PosStr1<Str1.length() && StrMix[PosStrMix] == Str1[PosStr1])
//        {
//            if (PosStr2 < Str2.length() && StrMix[PosStrMix] == Str2[PosStr2])
//                return Check(PosStr1+1, PosStr2, PosStrMix+1) || Check(PosStr1, PosStr2+1, PosStrMix+1);
//            else return Check(PosStr1+1, PosStr2, PosStrMix+1);
//        }
//        else if (PosStr2 < Str2.length() && StrMix[PosStrMix] == Str2[PosStr2])
//        {
//            return Check(PosStr1, PosStr2+1, PosStrMix+1);
//        }
//        else return false;
//    }
//}

void Check(int PosStr1, int PosStr2, int PosStrMix)
{
    if (IsValid)
        return;
    if (PosStrMix >= StrMix.length())
    {
        IsValid = true; return;
    }
    if (PosStr1<Str1.length() && StrMix[PosStrMix] == Str1[PosStr1])
    {
        Check(PosStr1 + 1, PosStr2, PosStrMix + 1);
        //for the case of both str's current head char equals to the mixed
        //if the 1st is the right choice, there is no need to check the 2nd
        if (IsValid)
            return; 
    }
    if (PosStr2 < Str2.length() && StrMix[PosStrMix] == Str2[PosStr2])
    {
        Check(PosStr1, PosStr2 + 1, PosStrMix + 1);
    }
}

int main()
{
    //Solution1
    /*cin >> NumDataSets;
    for (auto Num = 1; Num <= NumDataSets; ++Num)
    {
        cin >> Str1 >> Str2 >> StrMix;
        if (Check(0, 0, 0))
            cout <<"Data set "<<Num<< ": yes" << endl;
        else cout << "Data set " << Num << ": no" << endl;
    }*/
    
    //Solution2
    /*cin >> NumDataSets;
    for (auto Num = 1; Num <= NumDataSets; ++Num)
    {
        cin >> Str1 >> Str2 >> StrMix;
        int PosStr1 = 0, PosStr2 = 0, PosStrMix = 0;
        PosReserved.clear();
        while (true)
        {
            if (PosStrMix >= StrMix.size())
            {
                cout << "Data set " << Num << ": yes" << endl; break;
            }
            else
            {
                if (PosStr1<Str1.size() && StrMix[PosStrMix] == Str1[PosStr1])
                {
                    if (PosStr2 < Str2.size() && StrMix[PosStrMix] == Str2[PosStr2])
                    {
                        array<int, 3> a{ PosStr1, PosStr2 + 1, PosStrMix + 1 };
                        PosReserved.push_back(a);
                    }
                    ++PosStr1; ++PosStrMix;
                }
                else if (PosStr2 < Str2.size() && StrMix[PosStrMix] == Str2[PosStr2])
                {
                    ++PosStr2; ++PosStrMix;
                }
                else if (PosReserved.size() != 0)
                {
                    PosStr1 = PosReserved.back()[0]; PosStr2 = PosReserved.back()[1]; PosStrMix = PosReserved.back()[2];
                }
                else
                {
                    cout << "Data set " << Num << ": no" << endl; break;
                }
            }
        }
    }*/

    //Solution3
    cin >> NumDataSets;
    for (auto Num = 1; Num <= NumDataSets; ++Num)
    {
    cin >> Str1 >> Str2 >> StrMix;
    IsValid = false;
    Check(0, 0, 0);
    if(IsValid)
        cout <<"Data set "<<Num<< ": yes" << endl;
    else cout << "Data set " << Num << ": no" << endl;
    }
    //cout << Count << endl;
    return 0;
}

//handling from the end of string will pass
#include <iostream>
#include <string>
#include <vector>
#include <array>
using namespace std;
int NumDataSets;
string Str1, Str2, StrMix;
vector<array<int, 3>> PosReserved;
bool IsValid;
int Count; //just for testing the bug of training data, please ignore it


//bool Check(int PosStr1, int PosStr2, int PosStrMix)
//{
//    if (PosStrMix >= StrMix.length())
//        return true;
//    else
//    {
//        if (PosStr1<Str1.length() && StrMix[PosStrMix] == Str1[PosStr1])
//        {
//            ++Count;
//            if (PosStr2 < Str2.length() && StrMix[PosStrMix] == Str2[PosStr2])
//            {
//                ++Count;
//                return Check(PosStr1 - 1, PosStr2, PosStrMix - 1) || Check(PosStr1, PosStr2 - 1, PosStrMix - 1);
//            }
//            else return Check(PosStr1-1, PosStr2, PosStrMix-1);
//        }
//        else if (PosStr2 < Str2.length() && StrMix[PosStrMix] == Str2[PosStr2])
//        {
//            ++Count;
//            return Check(PosStr1, PosStr2-1, PosStrMix-1);
//        }
//        else return false;
//    }
//}

void Check(int PosStr1, int PosStr2, int PosStrMix)
{
    if (IsValid)
        return;
    if (PosStrMix == -1)
    {
        IsValid = true; return;
    }
    if (PosStr1<Str1.length() && StrMix[PosStrMix] == Str1[PosStr1])
    {
        //++Count;
        Check(PosStr1 - 1, PosStr2, PosStrMix - 1);
        //for the case of both str's current head char equals to the mixed
        //if the 1st is the right choice, there is no need to check the 2nd
        if (IsValid)
            return;
    }
    if (PosStr2 < Str2.length() && StrMix[PosStrMix] == Str2[PosStr2])
    {
        //++Count;
        Check(PosStr1, PosStr2 - 1, PosStrMix - 1);
    }
}

int main()
{
    /*Solution1*/
    /*cin >> NumDataSets;
    for (auto Num = 1; Num <= NumDataSets; ++Num)
    {
        cin >> Str1 >> Str2 >> StrMix;
        if (Check(Str1.size() - 1, Str2.size() - 1, StrMix.size() - 1))
            cout <<"Data set "<<Num<< ": yes" << endl;
        else cout << "Data set " << Num << ": no" << endl;
    }*/
    //cout << Count << endl;

    //Solution2
    /*cin >> NumDataSets;
    for (auto Num = 1; Num <= NumDataSets; --Num)
    {
        cin >> Str1 >> Str2 >> StrMix;
        int PosStr1 = 0, PosStr2 = 0, PosStrMix = 0;
        PosReserved.clear();
        while (true)
        {
            if (PosStrMix >= StrMix.size())
            {
                cout << "Data set " << Num << ": yes" << endl; break;
            }
            else
            {
                if (PosStr1<Str1.size() && StrMix[PosStrMix] == Str1[PosStr1])
                {
                    if (PosStr2 < Str2.size() && StrMix[PosStrMix] == Str2[PosStr2])
                    {
                        array<int, 3> a{ PosStr1, PosStr2 - 1, PosStrMix - 1 };
                        PosReserved.push_back(a);
                    }
                    --PosStr1; --PosStrMix;
                }
                else if (PosStr2 < Str2.size() && StrMix[PosStrMix] == Str2[PosStr2])
                {
                    --PosStr2; --PosStrMix;
                }
                else if (PosReserved.size() != 0)
                {
                    PosStr1 = PosReserved.back()[0]; PosStr2 = PosReserved.back()[1]; PosStrMix = PosReserved.back()[2];
                }
                else
                {
                    cout << "Data set " << Num << ": no" << endl; break;
                }
            }
        }
    }*/

    //Solution3
    cin >> NumDataSets;
    for (auto Num = 1; Num <= NumDataSets; ++Num)
    {
        cin >> Str1 >> Str2 >> StrMix;
        IsValid = false;
        Check(Str1.size()-1, Str2.size() - 1, StrMix.size() - 1);
        if (IsValid)
            cout << "Data set " << Num << ": yes" << endl;
        else cout << "Data set " << Num << ": no" << endl;
    }
    //cout << Count << endl;
    return 0;
}

