#include "polynom.h"
#include<string>
#include<iostream>

using namespace std;

int main()
{
	try
	{
		string s, ss;
		cout << "enter the 1st polynom:" << endl;
		getline(cin, s);
		Polynom polynom(s);
		cout << "enter the 2nd polynom:" << endl;
		getline(cin, ss);
		Polynom pol(ss);
		cout << "addition of two polynoms" << endl << endl;
		cout << polynom + pol << endl;
		cout << "subtraction of two polynoms" << endl << endl;
		cout << polynom - pol << endl;
		cout << "multiplication of two polynoms" << endl << endl;
		cout << polynom * pol << endl << endl;
	}
	catch (const char* a) { cout << a << endl; }
	system("pause");
}