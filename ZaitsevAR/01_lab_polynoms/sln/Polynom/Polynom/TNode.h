#pragma once
#include <iostream>

using namespace std;

template<typename TKey, typename TData>
struct TNode
{
	TKey key;
	TData data;
	TNode<TKey, TData>* pNext;

	TNode();
	TNode(TKey key, TData data);
	TNode(const TNode<TKey, TData>& node);
	~TNode();

	bool operator==(const TNode<TKey, TData>& node) const;
	const TNode<TKey, TData>& operator=(const TNode<TKey, TData>& node);

	friend ostream& operator<<(ostream& out, const TNode<TKey, TData>& node)
	{
		out << " {" << node.key << ", " << node.data << "} ";
		return out;
	}
};

template<typename TKey, typename TData>
TNode<TKey, TData>::TNode()
{
	key = 0;
	pNext = nullptr;
}

template<typename TKey, typename TData>
TNode<TKey, TData>::TNode(TKey key, TData data)
{
	this->key = key;
	this->data = data;
	pNext = nullptr;
}

template<typename TKey, typename TData>
TNode<TKey, TData>::TNode(const TNode<TKey, TData>& node)
{
	pNext = nullptr;
	key = node.key;
	data = node.data;
}

template<typename TKey, typename TData>
TNode<TKey, TData>::~TNode()
{
	pNext = nullptr;
}

template<typename TKey, typename TData>
bool TNode<TKey, TData>::operator==(const TNode<TKey, TData>& node) const
{
	return ((key = node.key) && (data = node.data));
}

template<typename TKey, typename TData>
const TNode<TKey, TData>& TNode<TKey, TData>::operator=
(const TNode<TKey, TData>& node)
{
	if (*this == node)
		return *this;
	key = node.key;
	data = node.data;
	return *this;
}