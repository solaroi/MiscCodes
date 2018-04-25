//============================================================================
// Name        : test.cpp
// Author      : solaroi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class B0{
public:
	B0() :PblB0(0), PrtB0(0), PrvB0(0) { cout << "default B0()" << endl; };
	B0(int Pbl, int Prt, int Prv) :PblB0(Pbl), PrtB0(Prt), PrvB0(Prv) { cout << "B0(arg)" << endl; };
	B0(const B0 &B0_0) :B0(B0_0.PblB0, B0_0.PrtB0, B0_0.PrvB0) { cout << "copy B0(B0)" << endl; };
	B0 &operator=(const B0 &B0_0);
	void PrintOtherB0(B0 &B0_0) { B0_0.PrintB0(); };
	void PrintB0() { cout << "Print B0" << endl; cout << PblB0 << " " << PrtB0 << " " << PrvB0 << endl; };
	void NonVtl() { cout << "NonVitual NonVtl() of B0" << endl; };
	void NonVtl(int a) { cout << "NonVitual NonVtl( " << a << " )of B0" << endl; };
	void BaseSpecial() { cout << "NonVitual BaseSpecial of B0" << endl; };
	virtual void Vtl0() { cout << "Virtual Vtl0() of B0" << endl; };
	virtual void Vtl1() { cout << "Virtual Vtl1() of B0" << endl; };
	virtual void Vtl2() { cout << "Virtual Vtl2() of B0" << endl; };
	int PblB0;
protected:
	int PrtB0;
private:
	int PrvB0;
};
B0 &B0::operator =(const B0 &B0_0)
{
	cout << "= copy B0" << endl;
	PblB0 = B0_0.PblB0;
	PrtB0 = B0_0.PrtB0;
	PrvB0 = B0_0.PrvB0;
	return *this;
};

class D0 :public B0 {
public:
	D0() :B0(), PblD0(0), PrtD0(0), PrvD0(0) { cout << "defalut D0()" << endl; };
	D0(int PblB, int PrtB, int PrvB, int PblD, int PrtD, int PrvD) :B0(PblB, PrtB, PrvB), \
		PblD0(PblD), PrtD0(PrtD), PrvD0(PrvD) { cout << "D0(arg)" << endl; };
	D0(const D0 &D0_0) :B0(D0_0), PblD0(D0_0.PblD0), PrtD0(D0_0.PrtD0), \
		PrvD0(D0_0.PrvD0) { cout << "copy D0(D0)" << endl; };
	D0 &operator=(const D0 &D0_0);
	void PrintD0() {
		cout << "Print D0" << endl; PrintB0(); cout << PblD0 << " " << PrtD0 << " " << PrvD0 << endl;
	};
	void PrintOtherD0(D0 &D0_0) { D0_0.PrintD0(); };
	void NonVtl() { cout << "NonVitual NonVtl() of D0" << endl; };
	void Vtl0() { cout << "Virtual Vtl0() of D0" << endl; };
	void Vtl1(int a) { cout << "non-Virtual Vtl( "<<a<<" ) of D0" << endl; };//non-virtual

	int PblD0;
protected:
	int PrtD0;
private:
	int PrvD0;
};
D0 &D0::operator=(const D0 &D0_0)
{

	cout << "= copy D0" << endl;
	B0::operator=(D0_0);
	PblD0 = D0_0.PblD0;
	PrtD0 = D0_0.PrtD0;
	PrvD0 = D0_0.PrvD0;
	return *this;
};

class D0D0: public D0{
public:
	D0D0():D0(), PblD0D0(0), PrtD0D0(0), PrvD0D0(0) {cout<<"defalut D0D0()"<<endl;};
	D0D0(int PblB, int PrtB, int PrvB, int PblD, int PrtD, int PrvD, int PblDD, int PrtDD, int PrvDD) :\
		D0(PblB, PrtB, PrvB, PblD, PrtD, PrvD), \
		PblD0D0(PblDD), PrtD0D0(PrtDD), PrvD0D0(PrvDD) { cout << "D0D0(arg)" << endl; };
	D0D0(const D0D0 &D0D0_0) :D0(D0D0_0), PblD0D0(D0D0_0.PblD0D0), PrtD0D0(D0D0_0.PrtD0D0), \
		PrvD0D0(D0D0_0.PrvD0D0) { cout << "copy D0D0(D0D0)" << endl; };
	D0D0 &operator=(const D0D0 &D0D0_0);
	int PblD0D0;
	void PrintD0D0() {
		cout << "Print D0D0" << endl; PrintD0(); cout << PblD0D0 << " " << PrtD0D0 << " " << PrvD0D0 << endl;
	};
	void PrintOtherD0D0(D0D0 &D0D0_0) { D0D0_0.PrintD0D0(); };
	void NonVtl() { cout << "NonVitual NonVtl() of DD0" << endl; };
	void Vtl1() { cout << "Virtual Vtl1() of D0D0" << endl; };
	void Vtl2() { cout << "Virtual Vtl2() of D0D0" << endl; };
protected:
	int PrtD0D0;
private:
	int PrvD0D0;
};
D0D0 &D0D0::operator=(const D0D0 &D0D0_0)
{

	cout << "= copy D0D0" << endl;
	D0::operator=(D0D0_0);
	PblD0D0 = D0D0_0.PblD0D0;
	PrtD0D0 = D0D0_0.PrtD0D0;
	PrvD0D0 = D0D0_0.PrvD0D0;
	return *this;
};

B0 CopyB0(B0 B0_0) { return B0_0; }

D0 CopyD0(D0 D0_0) { return D0_0; }


int main() {
	////default, arg, copy constructor and assignment of class B0
	////D0 should call B0's corresponding func to operate on the base part
	////*******************************************
	//B0 B0_0; B0_0.PrintB0();
	//cout << endl;
	//B0 B0_1(B0_0); B0_1.PrintB0();
	//cout<<endl;
	//B0 B0_2 = B0_0; B0_2.PrintB0();
	//cout << endl;
	//B0 B0_3(1,2,3); B0_3.PrintB0();
	//cout << endl;
	//B0_2 = B0_3; B0_2.PrintB0();
	//cout << endl;
	//B0_0 = CopyB0(B0_3); B0_0.PrintB0();
	//cout << endl;

	//D0 D0_0; D0_0.PrintD0();
	//cout << endl;
	//D0 D0_1(D0_0); D0_1.PrintD0();
	//cout << endl;
	//D0 D0_2 = D0_0; D0_2.PrintD0();
	//cout << endl;
	//D0 D0_3(4,5,6,7,8,9); D0_3.PrintD0();
	//cout << endl;
	//D0_2 = D0_3; D0_2.PrintD0();
	//cout << endl;
	//D0_0 = CopyD0(D0_3); D0_0.PrintD0();
	//cout << endl;
	////********************************************


	//inheritance and scope: vitual and non-vitual
	//****************************************************************************************************
	//using a pointer or reference to call a function func: p->func(...) or p.func(...)
	//NameLookup(not TypeCheck) starts at the static type of a pointer or reference
	//if not found in the current class, then go to the closest base class
	//if a func is found in class A, then stop NameLookup
	//TypeCheck: search among all function with the name of func in A. if not matched, ERROR
	//if one func(...) matched: if it's non-virtual, compile to call it
	//if it's virtual, then the real function will be called must be defined in A and classes derived from A
	//compile to codes which call func determined at run time by the actual class binded to p
	//if no name found at last, error
	//     B0             D0              D0D0
	//    Vtl0()         Vtl0()        NOT DEFINED
	//    Vtl1()        Vtl1(int)        Vtl1()
	//    Vtl2()       NOT DEFINED       Vtl2()  
	B0 *p_B0; D0 *p_D0; D0D0 *p_D0D0;
	B0 B0_0; D0 D0_0; D0D0 D0D0_0;
	cout << endl << "Non-Vitual test" << endl;
	B0_0.NonVtl(); D0_0.NonVtl();//func in derived class hides same name func in base 
	//D0_0.NonVtl(1);//ERROR: Class D0 have no version NonVt(int), NonVt() hides NonVt(int) in the base part
	//thus, overload only happens in the same class                
	p_B0 = &B0_0; p_B0->NonVtl();
	p_B0 = &D0_0; p_B0->NonVtl(); //static binding
	p_B0->BaseSpecial();//however, if no name find in derived class, NameLookup will get into the base scope

	cout << endl << "Vitual test: pointer p_B0" << endl;
	B0_0.Vtl0(); D0_0.Vtl0();//virtual mechanism only works with dynamic binding
	p_B0 = &D0_0; p_B0->Vtl0();//Dynamic binding
	p_B0 = &D0D0_0;
	p_B0->Vtl0();//NameLookup found Vtl1 in B0, virtual, call D0D0.Vtl1() whcih leads to D0::Vtl1()
	             //WARRING: D0::Vtl1() must be accessable
	p_B0 = &D0_0; 
	p_B0->Vtl1();//NameLookup found Vtl1 in B0, virtual, call D0.Vtl1() whcih leads to B0::Vtl1()
	             //WARRING: B0::Vtl1() must be accessable
	//p_B0->Vtl1(1);//ERROR: NameLookup found Vtl1 in B0, TypeCheck failed

	cout << endl << "Vitual test: pointer p_D0" << endl;
	p_D0 = &D0_0; 
	p_D0->Vtl0();////call D0::Vtl0()
	//p_D0->Vtl1();//ERROR: NameLookup found Vtl1 in D0, TypeCheck failed
	p_D0->Vtl1(1);//static binding: NameLookup found Vtl1 in D0, TypeCheck succeed, non-virtual
	p_D0->Vtl2();// call B0::Vtl2()
	p_D0 = &D0D0_0;
	p_D0->Vtl0();//call D0::Vtl0()
	//p_D0->Vtl1();//ERROR: NameLookup found Vtl1 in D0, TypeCheck failed
	p_D0->Vtl1(1);//NameLookup found Vtl1 in D0, non-virtual, call D0D0.Vtl1(1) which leads to D0::Vtl1(1)
				  //WARRING: D0::Vtl1(int) must be accessable
	p_D0->Vtl2();//NameLookup found Vtl2 in B0, virtual, call D0D0.Vtl2() which leads to B0::Vtl2()
				 //WARRING: D0::Vtl1(int) must be accessable
	//p_D0D0 = &D0_0;//ERROR: derived to base conversion is illegal

	cout << endl << "Vitual test: pointer p_D0D0" << endl;
	p_D0D0 = &D0D0_0;
	p_D0D0->Vtl0();//NameLookup found Vtl0 in D0, virtual, call D0D0.Vtl0() which leads to D0::Vtl0()
				   //WARRING: D0::Vtl0()) must be accessable
	p_D0D0->Vtl1();//NameLookup found Vtl1 in D0D0, virtual, call D0D0.Vtl1()
	//p_D0D0->Vtl1(1);//ERROR: NameLookup found Vtl1 in D0D0, TypeCheck failed
	p_D0D0->Vtl2();//NameLookup found Vtl2 in D0D0, virtual, call D0D0.Vtl2()
	//******************************************************************************************************


	return 0;
}
