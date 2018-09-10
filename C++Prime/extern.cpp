#include <iostream>
using namespace std;

//put these definitions into another source file
/* 
int var1 = 1; // if no initializer is provided, var1 will be default inicialized
extern int var2 = 2; // when extern is added to a definition, an initializer must be provided
int var3 = 3;
extern const int const_var1 = 11; // extern const object must be defined with extern.
*/

extern int var1; // extern declaration£¬indicating the definition is in somewhere else
extern int var2;
int var4 = 4;
extern int var4; //extern declaration is pure declaration, it can be in the same place with the definition but means nothing
extern const int const_var1; 

void print_var()
{
	extern int var3; //var3 is declared as a local variable
	cout << var3 << "\n";
}

int main()
{
	cout << var1 << "\n";
	cout << var2 << "\n";
	print_var();
	//cout << var3 << "\n";
	//extern int var4 = 4; //extern definition can't appear inside any function
	cout << var4 << "\n";
	cout << const_var1 << endl;
	return 0;
}