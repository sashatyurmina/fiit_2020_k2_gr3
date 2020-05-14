#pragma once
#include <iostream>

using namespace std;

template<class TKey, class TData>
class TNode
{
public:
	TKey key;
	TData* pData;
	TNode<TKey, TData>* pNext;

	TNode();
	TNode(const TNode<TKey, TData>&);
	TNode(TKey, TData*);
	~TNode();
};

template<class TKey, class TData>
TNode<TKey, TData>::TNode()
{
	key = 0;
	pData = nullptr;
	pNext = nullptr;
}

template<class TKey, class TData>
TNode<TKey, TData>::TNode(const TNode<TKey, TData>& node)
{
	this->key = node.key;
	this->pData = new TData(*node.pData);
	pNext = nullptr;
}

template<class TKey, class TData>
TNode<TKey, TData>::TNode(TKey key, TData* data)
{
	pNext = nullptr;
	this->key = key;
	this->pData = new TData(*data.pData);
}

template<class TKey, class TData>
TNode<TKey, TData>::~TNode()
{
	key = 0;
	pNext = nullptr;
	delete pData;
}
