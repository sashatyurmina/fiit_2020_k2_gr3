#pragma once
#include "TMonom.h"
#include <string>

using namespace std;

class Polinom
{
private:
	TList<unsigned int, double>* polinom;

	void OrganizeList(); //упорядочивание по степеням(сортировка)
	void Simplification(); //упрощение(приведение подобных)
public:
	Polinom();
	Polinom(const string& str);
	Polinom(const Polinom& tmp); //контруктор копирования
	Polinom(TList<unsigned int, double>* list);
	~Polinom();

	Polinom operator+(const Polinom&);
	Polinom operator-(const Polinom&);
	Polinom operator*(const Polinom&);
	bool operator==(const Polinom&) const;
	const Polinom& operator=(const Polinom&);

	Polinom operator-() const; //унарный минус
	Polinom operator*(const TNode<unsigned int, double>& monom);//моном*полином

	friend ostream& operator<<(ostream& out, const Polinom& pol);
};

