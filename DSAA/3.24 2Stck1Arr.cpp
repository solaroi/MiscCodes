#include <iostream>
using namespace std;
//problem: achieve 2 stacks in 1 array
//solution 1: 
class LStack {
public:
	LStack(double *Arr0 = nullptr, size_t *Size0 = nullptr, size_t *LSize0 = nullptr, size_t *RSize0 = nullptr) {
		Arr = Arr0; Size = Size0; LSize = LSize0; RSize = RSize0;};
	bool empty() { return *LSize == 0; };
	size_t size() { return *LSize; };
	double back() { if (!*LSize == 0) return *(Arr + *LSize); else cout << "LStack Empty!" << endl; return 0; }
	void push(double x);
	double pop();
	double *Arr;
	size_t *Size, *LSize, *RSize;
};
void LStack::push(double x)
{
	if (*LSize + *RSize < *Size)
	{
		++*LSize;
		*(Arr + *LSize) = x;
	}
	else cout << "LStack Full!" << endl;
}
double LStack::pop()
{
	if (!*LSize == 0)
	{
		--*LSize;
		return *(Arr + 1 + *LSize);

	}
	else cout << "LStack Empty!" << endl;
	return 0;
}

class RStack {
public:
	RStack(double *Arr0 = nullptr, size_t *Size0 = nullptr, size_t *LSize0 = nullptr, size_t *RSize0 = nullptr) {
		Arr = Arr0; Size = Size0; LSize = LSize0; RSize = RSize0;
	};
	double *Arr;
	bool empty() { return *RSize == 0; };
	size_t size() { return *RSize; };
	double back() { if (!*RSize == 0) return *(Arr + *Size - *RSize+1); else cout << "RStack Empty!" << endl; return 0; }
	void push(double x);
	double pop();
	size_t Curr, *Size, *LSize, *RSize;
};
void RStack::push(double x)
{
	if (*LSize + *RSize < *Size)
	{
		++*RSize;
		*(Arr + *Size - *RSize+1) = x;
	}
	else cout << "RStack Full!" << endl;
}
double RStack::pop()
{
	if (!*RSize == 0)
	{
		--*RSize;
		return *(Arr + *Size - *RSize);
	}
	else cout << "RStack Empty!" << endl;
	return 0;
}

class DblStack {
public:
	DblStack(size_t size = 0);
	bool empty() { return (*LSize == 0 && *RSize == 0); };
	bool full() { return *LSize + *RSize == *Size; };
	LStack *lstack;
	RStack *rstack;
private:
	double *Arr;
	size_t *Size, *LSize, *RSize;
};
DblStack::DblStack(size_t size)
{

	Arr = new double[size + 1];
	Size = new size_t; *Size = size;
	LSize = new size_t; *LSize = 0;
	RSize = new size_t; *RSize = 0;
	lstack = new LStack(Arr, Size, LSize, RSize);
	rstack = new RStack(Arr, Size, LSize, RSize);
}

int main()
{
	DblStack s0(100);
	cout << s0.lstack->size() << " " << s0.rstack->size() << endl;
	for (auto i = 1; i <= 100; ++i)
	{
		if (!(i % 2 == 0))
			s0.lstack->push(i);
		else
			s0.rstack->push(i);
	}
	cout << s0.lstack->size() << " " << s0.rstack->size() << endl;
	cout << s0.full() << endl;
	cout << s0.lstack->back() << " " << s0.rstack->back() << endl;
	while (!s0.empty())
	{
		cout << s0.lstack->pop() << endl;
		cout << s0.rstack->pop() << endl;
	}
	return 0;
}

