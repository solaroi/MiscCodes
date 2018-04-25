#include<iostream>
#include<memory>
#include<vector>
#include<string>
using namespace std;

shared_ptr<vector<string>> func0(shared_ptr<vector<string>> DyVct0_f0)
{
	cout << "func0: *****************************************" << endl;
	shared_ptr<vector<string>> DyVct1_f0;
	DyVct0_f0->push_back("func0");
	for (auto str : *DyVct0_f0)
		cout << str << " ";
	cout << endl;
	cout << "counter for DyVct0_f0(=DyVct_shr): " << DyVct0_f0.use_count() << endl;
	DyVct1_f0 = DyVct0_f0;
	cout << DyVct0_f0 << " " << DyVct1_f0 << endl;
	cout << "counter for DyVct1_f0(=DyVct0_f0): " << DyVct1_f0.use_count() << endl;
	return DyVct1_f0;
}

vector<string> *func1(shared_ptr<vector<string>> DyVct0_f1)
{
	cout << "func1: *****************************************"<<endl;
	cout << "counter for DyVct0_f1(=DyVct1_f0): " << DyVct0_f1.use_count() << endl;
	*((DyVct0_f1->end())-1) = "func1";
	for (auto str : *DyVct0_f1)
		cout << str << " ";
	cout << endl;
	vector<string> *DyVct1_f1 = new vector<string>;//default initialized
	for (auto str : *DyVct0_f1)//a pointer to vector, able to be derefered
		DyVct1_f1->push_back(str);
	cout << DyVct0_f1 << " " << DyVct1_f1 << endl;
	return DyVct1_f1;//mem not deleted
}

shared_ptr<vector<string>> func2(vector<string> *DyVct0_f2)
{
	cout << "func2: *****************************************" << endl;
	vector<string> *DyVct1_f2 = new vector<string>(*DyVct0_f2);//copy initalize
	(*DyVct1_f2)[DyVct1_f2->size() - 1] = "func2";
	for (auto str : *DyVct1_f2)
		cout << str << " ";
	cout << endl;
	cout << DyVct0_f2 << " " << DyVct1_f2 << endl;
	shared_ptr<vector<string>> DyVct2_f2(DyVct1_f2);
	cout << "counter for DyVct2_f2(=new DyVct1_f2): " << DyVct2_f2.use_count() << endl;
	//  delete mem created in func1 in case of mem leak
	//  no need to delete DyVct1_f2 as DyVct2_f2 take the charge the mem's administration
	delete DyVct0_f2;
	return DyVct2_f2;
}

int main()
{

	shared_ptr<vector<string>> DyVct0,DyVct1;
	//copy initialization: initializor is a temper vector<string>
	//not support direct initialization: make_shared<vector<string>>("this", "is")
	//make_shared<vector<string>>(vector<string>( "this", "is" )) cause same error as above
	//make_shared<vector<string>>({"this", "is"}) is illegal
	DyVct0 = make_shared<vector<string>>(vector<string>({ "this", "is" }));
	DyVct1 = func2(func1(func0(DyVct0)));
	cout << "counter for DyVct0: " << DyVct0.use_count() << endl;
	cout << "counter for DyVct1: " << DyVct1.use_count() << endl;
	return 0;
}