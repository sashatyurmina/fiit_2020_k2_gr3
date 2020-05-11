#pragma once
#include "TList.h"
#include <iostream>

using namespace std;

template<>
class TNode<unsigned int, double>
{
public:
	unsigned int degree;
	double coeff;
	TNode<unsigned int, double>* pNext;

	TNode();
	TNode(const TNode<unsigned int, double>&);
	TNode(unsigned int deg, double coef, TNode<unsigned int, double>* node = nullptr);
	~TNode();

	bool operator<(const TNode&) const;
	bool operator!=(const TNode& monom) const;
	bool operator==(const TNode& monom) const;
	TNode<unsigned int, double>* operator*(const TNode<unsigned int, double>& monom); //моном*моном
};

