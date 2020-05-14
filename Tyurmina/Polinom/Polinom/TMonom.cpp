#include "TMonom.h"
#include <iostream>

using namespace std;

TNode<unsigned int, double>::TNode()
{
	degree = 0;
	coeff = 0;
	pNext = nullptr;
}

TNode<unsigned int, double>::TNode(const TNode<unsigned int, double>& n)
{
	degree = n.degree;
	coeff = n.coeff;
	pNext = nullptr;
}

TNode<unsigned int, double>::TNode(unsigned int deg, double coef, TNode<unsigned int, double> * node)
{
	degree = deg;
	coeff = coef;
	pNext = node;
}

TNode<unsigned int, double>::~TNode()
{
	degree = 0;
	coeff = 0;
	pNext = nullptr;
}

bool TNode<unsigned int, double>::operator <(const TNode& monom) const
{
	return(this->degree < monom.degree);
}

bool TNode<unsigned int, double>::operator!=(const TNode& monom) const
{
	return(this->degree != monom.degree);
}

bool TNode<unsigned int, double>::operator==(const TNode& monom) const
{
	return((this->degree == monom.degree) && (this->coeff == monom.coeff));
}

TNode<unsigned int, double>* TNode<unsigned int, double>::operator*(const TNode<unsigned int, double>& monom)
{
	TNode<unsigned int, double>* result = new TNode<unsigned int, double>();

	unsigned int deg_x1 = monom.degree / 100;
	unsigned int deg_y1 = (monom.degree % 100) / 10;
	unsigned int deg_z1 = monom.degree % 10;

	unsigned int deg_x2 = this->degree / 100;
	unsigned int deg_y2 = (this->degree % 100) / 10;
	unsigned int deg_z2 = this->degree % 10;

	if ((deg_x1 + deg_x2 > 9) || (deg_y1 + deg_y2 > 9) || (deg_z1 + deg_z2 > 9))
		throw "Degree shouldn't be > 9";
	result->degree = this->degree + monom.degree;
	result->coeff = this->coeff * monom.coeff;
	return result;
}
