#include <iostream>
#include <string>
#include "Polinom.h"

using namespace std;

int main()
{
	try
	{
		cout << "_____Polimos_____"<<endl;
		string s, s1;
		cout << "Enter first polinom: ";
		getline(cin, s);
		Polinom pol(s);
		cout << "Enter second polinom: ";
		getline(cin, s1);
		Polinom pol1(s1);
		cout << "Operations with polinoms: "<<endl;
		cout << "Polinom + Polinom:" << endl;
		cout << pol + pol1 << endl;
		cout << "Polinom - Polinom:" << endl;
		cout << pol - pol1 << endl;
		cout << "Polinom * Polinom:" << endl;
		cout << pol * pol1 << endl;
	}
	catch (const char* ex)
	{
		cout << ex << endl;
	}
	system("pause");
}