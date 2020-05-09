#include "Polynom.h"
#include "Exception.h"
#include <iostream>

using namespace std;

//-2+5x^2y+z-yz+x^2yz
//2+y-2z+x^2y

int main()
{
	try
	{
		cout << "\n\n\t\t Tests for Polinom" << endl << endl;

		Monom m1(323, -4.5);
		TList<unsigned int, double> ListForPol_1(&m1);
		Monom m2(221, 3);
		Monom m3(323, -2);
		ListForPol_1.InsertEnd(&m2);
		ListForPol_1.InsertEnd(&m3);
		Polynom polynom_1(ListForPol_1);

		TList<unsigned int, double> ListForPol_2;
		ListForPol_2.InsertEnd(102, 9);
		ListForPol_2.InsertEnd(221, 6);
		ListForPol_2.InsertEnd(323, 10);
		Polynom polynom_2(ListForPol_2);

		cout << " Polynom 1: " << polynom_1 << endl;
		cout << " Polynom 2: " << polynom_2 << endl << endl;

		cout << " Addition of polynomials: " << polynom_1 + polynom_2 << endl;
		cout << " Subtraction of polynomials: " << polynom_1 - polynom_2 << endl;
		cout << " Multiplication of polynomials: " << polynom_1 * polynom_2
			<< endl << endl;

		Polynom pol_from_string;
		cin >> pol_from_string;
		cout << " Polynom from string: " << pol_from_string << endl;
	}
	catch (const Exception& ex)
	{
		cerr << ex.what() << endl;
	}

	system("pause");
	return 0;
}