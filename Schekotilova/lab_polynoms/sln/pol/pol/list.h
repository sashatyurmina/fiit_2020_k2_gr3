#pragma once
#pragma once
#include "node.h"

using namespace std;

template<typename TKey, typename TData>
class TList
{
public:
	TNode<TKey, TData>* pFirst;
	TNode<TKey, TData>* pCurr;
	TNode<TKey, TData>* pPrev;
	TNode<TKey, TData>* pNext;

	TList();
	TList(const TList&);
	TList(TNode<TKey, TData>* node);
	~TList();

	TNode<TKey, TData>* Search(TKey);
	void InsertBegin(TKey, TData);
	void InsertEnd(TKey, TData);
	void InsertAfter(TKey, TNode<TKey, TData>*);
	void InsertBefore(TKey, TNode<TKey, TData>*);

	void Remove(TKey);
	bool IsEmpty() const;
	bool IsEnded() const;
	void Reset();
	void Next();
	TNode<TKey, TData>* getFirst() const;
	TNode<TKey, TData>* getCurr() const;
	TNode<TKey, TData>* getNext() const;
	TNode<TKey, TData>* getPrev() const;
};

template<typename TKey, typename TData>
TList<TKey, TData>::TList()
{
	pFirst = nullptr;
	pPrev = nullptr;
	pPrev = nullptr;
	pNext = nullptr;
}

template<typename TKey, typename TData>
TList<TKey, TData>::TList(const TList<TKey, TData>& list)
{
	pCurr = nullptr;
	pPrev = nullptr;
	pNext = nullptr;
	if (!list.pFirst)
	{
		pFirst = nullptr;
	}
	else
	{
		pFirst = new TNode<TKey, TData>(*list.pFirst);
		TNode<TKey, TData>* node = pFirst;
		TNode<TKey, TData>* tmp = list.pFirst;
		while (tmp->pNext != nullptr)
		{
			node->pNext = new TNode<TKey, TData>(*(tmp->pNext));
			node = node->pNext;
			tmp = tmp->pNext;
		}
		Reset();
	}
}

template<typename TKey, typename TData>
TList<TKey, TData>::TList(TNode<TKey, TData>* node)
{
	pCurr = nullptr;
	pPrev = nullptr;
	pNext = nullptr;
	if (node == nullptr)
		pFirst == nullptr;
	else
	{
		pFirst = new TNode<TKey, TData>(*node);
		TNode<TKey, TData>* node1 = pFirst;
		TNode<TKey, TData>* tmp = node->pNext;
		while (tmp->pNext != nullptr)
		{
			node1->pNext = new TNode<TKey, TData>(*(tmp->pNext));
			node1 = node1->pNext;
			tmp = tmp->pNext;
		}
		Reset();
	}
}

template<typename TKey, typename TData>
TList<TKey, TData>::~TList()
{
	pCurr = nullptr;
	pPrev = nullptr;
	pNext = nullptr;
	while (!IsEnded())
	{
		pNext = pFirst->pNext;
		delete pFirst;
		pFirst = pNext;
	}
}

template<typename TKey, typename TData>
TNode<TKey, TData>* TList<TKey, TData>::Search(TKey Key)
{
	if (pFirst == nullptr) throw "error493 (list is empty)";
	TNode<TKey, TData>* tmp = pFirst;
	while ((tmp != nullptr) && (tmp->key != Key))
		tmp = tmp->pNext;
	if (tmp == nullptr) throw "error0980(key isn't found)";
	return tmp;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertBegin(TKey key, TData data)
{
	TNode<TKey, TData>* tmp = new TNode<TKey, TData>(key, data);
	tmp->pNext = pFirst;
	if (pCurr == pFirst)
		pPrev = tmp;
	pFirst = tmp;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertEnd(TKey key, TData data)
{
	if (pFirst == nullptr)
	{
		InsertBegin(key, data);
		Reset();
		return;
	}
	TNode<TKey, TData>* prev = pPrev;
	TNode<TKey, TData>* next = pNext;
	TNode<TKey, TData>* curr = pCurr;
	Reset();
	while (!IsEnded())
		Next();
	pCurr = new TNode<TKey, TData>(key, data);
	pPrev->pNext = pCurr;
	if (curr == pPrev)
		pNext = pCurr;
	else
		pNext = next;
	pCurr = curr;
	pPrev = prev;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertAfter(TKey key, TNode<TKey, TData>* node)
{
	if (pFirst == nullptr) throw "error493 (list is empty)";
	TNode<TKey, TData>* prev = pPrev;
	TNode<TKey, TData>* next = pNext;
	TNode<TKey, TData>* curr = pCurr;
	Reset();
	TNode<TKey, TData>* tmp = Search(key);
	if (tmp == nullptr) throw "error0980 (key isn't found)";
	while (pCurr != tmp) Next();
	TNode<TKey, TData>* node_1 = new TNode<TKey, TData>(node->key, node->pData);
	pCurr->pNext = node_1;
	if (curr == pCurr) pNext = node_1;
	else pNext = next;
	if (curr == pNext) pPrev = node_1;
	else pPrev = prev;
	pCurr = curr;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertBefore(TKey key, TNode<TKey, TData>* node)
{
	if (pFirst == nullptr) throw "error493 (list is empty)";
	if (pFirst->key == key)
	{
		InsertBegin(node->key, node->pData);
		return;
	}
	TNode<TKey, TData>* prev = pPrev;
	TNode<TKey, TData>* next = pNext;
	TNode<TKey, TData>* curr = pCurr;
	Reset();
	TNode<TKey, TData>* tmp = Search(key);
	if (tmp == nullptr) throw "error0980 (key isn't found)";
	while (pCurr != tmp) Next();
	TNode<TKey, TData>* node_1 = new TNode<TKey, TData>(node->key, node->pData);
	pPrev->pNext = node_1;
	if (curr == pCurr) pPrev = node_1;
	else pPrev = prev;
	if (curr == pPrev) pNext = node_1;
	else pNext = next;
	pCurr = curr;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::Remove(TKey key)
{
	if (pFirst == nullptr) throw "error0980 (key isn't found)";
	if (pFirst->key == key)
	{
		if (pCurr == pFirst)
		{
			pCurr = pNext;
			if (pNext != nullptr)
				pNext = pNext->pNext;
			else
				pNext = nullptr;
			delete pFirst;
			return;
		}
		if (pCurr == pFirst->pNext)
		{
			pPrev = nullptr;
			delete pFirst;
			pFirst = pCurr;
			return;
		}
	}
	TNode<TKey, TData>* prev = pPrev;
	TNode<TKey, TData>* next = pNext;
	TNode<TKey, TData>* curr = pCurr;
	Reset();
	TNode<TKey, TData>* tmp = Search(key);
	if (tmp == nullptr) throw "error0980 (key isn't found)";
	while (pCurr != tmp) Next();
	pPrev->pNext = pNext;
	if (curr == pCurr)
	{
		pCurr = pNext;
		pNext = pCurr->pNext;
		delete tmp;
		return;
	}
	if (curr == pNext)
	{
		pCurr = pNext;
		pNext = pCurr->pNext;
		delete tmp;
		return;
	}
	if (curr == pPrev)
	{
		pCurr = pPrev;
		pPrev = prev;
		pNext = pCurr->pNext;
		delete tmp;
		return;
	}
	pNext = next;
	pCurr = curr;
	delete tmp;
	return;
}

template<typename TKey, typename TData>
bool TList<TKey, TData>::IsEmpty() const
{
	return (pFirst == nullptr);
}

template<typename TKey, typename TData>
bool TList<TKey, TData>::IsEnded() const
{
	return (pCurr == nullptr);
}

template<typename TKey, typename TData>
void TList<TKey, TData>::Reset()
{
	pCurr = pFirst;
	pPrev = nullptr;
	if (pFirst != nullptr)
		pNext = pCurr->pNext;
	else
		pNext = nullptr;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::Next()
{
	if (IsEnded()) throw"error560 (list is ended)";
	pPrev = pCurr;
	pCurr = pNext;
	if (pNext != nullptr)
		pNext = pNext->pNext;
	else
		pNext = nullptr;
}

template<typename TKey, typename TData>
TNode<TKey, TData>* TList<TKey, TData>::getFirst() const
{
	return pFirst;
}

template<typename TKey, typename TData>
TNode<TKey, TData>* TList<TKey, TData>::getCurr() const
{
	return pCurr;
}

template<class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData> ::getNext()const
{
	return pNext;
}

template<class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData> ::getPrev()const
{
	return  pPrev;
}