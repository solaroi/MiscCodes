#include <iostream>
using namespace std;

struct C {
public:
	C() :c(0) { cout << "default C()" << endl; };
	C(int x):c(x) {cout<< "arg C("<<x<<")" << endl;};
	struct A {
		explicit A() :a(0) { cout << "default A()" << endl; };
		explicit A(int x) :a(x) { cout << "arg A(" << x << ")" << endl; };
		int a;
		//void print() { cout << c << endl; };
		//void print() { cout << c << endl; };//ERROR: A is just defined in C, not a inner scope

	};
	int c;
private:
	struct B {
		B() :b(0) { cout << "default B()" << endl; };
		B(int x) :b(x) { cout << "arg B(" << x << ")" << endl; };
		int b;

	};
};

struct D {
public:
	//Members are initialized in the order in which they appear in the class definition
	//init list overrides the in-class initializer
	//in-class initializer: only {} or = can be used
	//watch out for init one member using the value of another
	
	D() :d(0),e(0) { cout << "default D()" << endl; };//order: d,C0,C1,C2,e
	D(int x) :e(150),d(x),C1(e) { cout << "arg D(" << x << ")" << endl; };//order unexpected
	D(int x,int y):C1(e),e(y), C2(e),d(x){ cout << "arg D(" << x<<" , "<<y << ")" << endl; };//order unexpected
	int d;
	C C0{ d };//only {} could be used, () illegal
	C C1{ 1 };
	C C2{ e };
	int e=200;
	//C::A A0(d);

};

int main()
{
	int a = 0;
	C C0(9);
	C::A{ 1 };//() or {} is valid, {} is not an implicit conversion
	//C::B(2);//DRROR: class B is private in C, inaccessible
	cout << endl;
	D D0;
	cout << D0.d << " " << D0.C0.c << " " << D0.C1.c << " " << D0.C2.c << " " << D0.e << endl << endl;
	D D1{ 100 };
	cout << D1.d << " " << D1.C0.c << " " << D1.C1.c << " " << D1.C2.c << " " << D1.e << endl << endl;
	D D2{ 300,400 }; 
	cout << D2.d << " " << D2.C0.c << " " << D2.C1.c << " " << D2.C2.c << " " << D2.e << endl << endl;
	return 0;
}

