#pragma once
#include "TMonom.h"
#include <string>

using namespace std;

class Polinom
{
private:
	TList<unsigned int, double>* polinom;
	void OrganizeL(); 
	void Simplification(); 
public:
	Polinom();
	Polinom(const string& str);
	Polinom(const Polinom& tmp); 
	Polinom(TList<unsigned int, double>* list);
	~Polinom();
	Polinom operator+(const Polinom&);
	Polinom operator-(const Polinom&);
	Polinom operator*(const Polinom&);
	bool operator==(const Polinom&) const;
	const Polinom& operator=(const Polinom&);
	Polinom operator-() const;
	Polinom operator*(const TNode<unsigned int, double>& monom);
	friend ostream& operator<<(ostream& out, const Polinom& pol);
};
