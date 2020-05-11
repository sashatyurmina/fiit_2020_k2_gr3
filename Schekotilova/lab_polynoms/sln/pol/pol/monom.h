#pragma once
#include "list.h"

using namespace std;

template<>
class TNode<unsigned int, float>
{
public:
	unsigned int key;
	float pData;
	TNode<unsigned int, float>* pNext;

	TNode();
	TNode(const TNode<unsigned int, float>&);
	TNode(unsigned int, float, TNode<unsigned int, float>* node = nullptr);
	~TNode();

	bool operator<(const TNode&) const;
	bool operator!=(const TNode&) const;
	bool operator==(const TNode&) const;
	TNode<unsigned int, float>* operator*(const TNode<unsigned int, float>&);
};



TNode<unsigned int, float>::TNode()
{
	key = 0;
	pData = 0;
	pNext = nullptr;
}

TNode<unsigned int, float>::TNode(const TNode<unsigned int, float>& n)
{
	key = n.key;
	pData = n.pData;
	pNext = nullptr;
}

TNode<unsigned int, float>::TNode(unsigned int deg, float coeff, TNode<unsigned int, float>* node)
{
	key = deg;
	pData = coeff;
	pNext = node;
}

TNode<unsigned int, float>::~TNode()
{
	key = 0;
	pData = 0;
	pNext = nullptr;
}

bool TNode<unsigned int, float>::operator <(const TNode& monom) const
{
	return(this->key < monom.key);
}

bool TNode<unsigned int, float>::operator!=(const TNode& monom) const
{
	return(this->key != monom.key);
}

bool TNode<unsigned int, float>::operator==(const TNode& monom) const
{
	return((this->key == monom.key) && (this->pData == monom.pData));
}

TNode<unsigned int, float>* TNode<unsigned int, float>::operator*(const TNode<unsigned int, float>& monom)
{
	TNode<unsigned int, float>* result = new TNode<unsigned int, float>();

	unsigned int d_x1 = monom.key / 100;
	unsigned int d_y1 = (monom.key % 100) / 10;
	unsigned int d_z1 = monom.key % 10;

	unsigned int d_x2 = this->key / 100;
	unsigned int d_y2 = (this->key % 100) / 10;
	unsigned int d_z2 = this->key % 10;

	if (d_x1 + d_x2 > 9 || d_y1 + d_y2 > 9 || d_z1 + d_z2 > 9) throw "error809 (incorrect key (> 9))";
	result->key = this->key + monom.key;
	result->pData = this->pData * monom.pData;
	return result;
}