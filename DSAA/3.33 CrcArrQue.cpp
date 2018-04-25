#include <iostream>
using namespace std;
//Page 119 3.33
//list in a circle array
//when fixed memory array is used as prototype to construct other data structures
//reload the operator [] will be  very useful
//the private member SIZ will be the only record to control iteration loop and justify empty or full
//no memory units actually be delete or create when add or pop element, everthing is controlled by SIZ

struct CrcArrQue
{
public:
	CrcArrQue(size_t len = 0);
	CrcArrQue(CrcArrQue &clc) :Len(clc.Len), header(clc.header), tail(clc.tail),siz(clc.siz){ delete Arr; Arr = clc.Arr; };
	bool empty() { return siz == 0; };
	bool full() { return siz == Len; };//return the node prior to which contains x
	size_t size() { return siz; };
	//size_t next(size_t itr) {};
	size_t prev(size_t itr);
	long &operator[](size_t itr);
	//size_t FindPos(long x);//re turn x's pos
	CrcArrQue &pop();//if x not exits, insert it
	CrcArrQue &push(long x);//if x exits, remove it

	void Print();
private:
	size_t Len, header, tail, siz;
	long *Arr;
};


long& CrcArrQue::operator[](size_t itr)
{
	if (itr < siz)
	{
		if (Len != 1)
		{
			if (header + itr <= Len)
				return *(Arr + header + itr);
			else return *(Arr + header + itr - Len);
		}
		//only one element
		else return *(Arr + header);
	}
	else
	{
		cout << "subscript of CrcList is out of range" << endl;
		cin.get();
	}
}


CrcArrQue::CrcArrQue(size_t len)
{
	Len = len; Arr = nullptr; siz = 0;
	if (len > 0)
	{
		Arr = new long[len + 1];
		header = 1; tail = 1;

	}
	else cout << "size must be larger than 0" << endl;
}

//previous position of itr in a circle mode
//if need to get the next pos: itr = (itr+1)%Len + 1 
size_t CrcArrQue::prev(size_t itr)
{
	if (itr == 1)
			return Len;
	else return itr-1;
}

void CrcArrQue::Print()
{
	for (size_t itr=0; itr < siz; ++itr)
		cout << operator[](itr) << " ";
	cout << endl;
}

CrcArrQue& CrcArrQue::push(long x)
{
	if (!full())
	{
		if (siz == 0)
		{
			*(Arr + header) = x;
			if (Len > 1)
				++tail;
		}
		else
		{
			header = prev(header);
			*(Arr + header) = x;
		}
		++siz;
	}
	else cout <<"failed to push "<< x << ", list fulled" << endl;
	return *this;
}


CrcArrQue &CrcArrQue::pop()
{
	if (!empty())
	{
		if (Len > 1)
			tail = prev(tail);
		--siz;
	}
	else cout <<"pop failed, List is empty" << endl;
	return *this;
}
int main()
{
	CrcArrQue crc(20);
	for (auto i = 1; i <= 20; ++i)
		crc.push(i);
	crc.Print();
	for (auto i = 0; i < 20; ++i)
		if(!(i%2))
			crc[i]=4*crc[i];
	crc.Print();
	for (auto i = 0; i < 10; ++i)
		crc.pop();
	crc.Print();
	return 0;
}

