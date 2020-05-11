#pragma once
#include "TNode.h"
#include <iostream>

using namespace std;

template<class TKey, class TData>
class TList
{
public:
	TNode<TKey, TData>* pFirst;
	TNode<TKey, TData>* pCurrent;
	TNode<TKey, TData>* pPrevious;
	TNode<TKey, TData>* pNext;

	TList();
	TList(const TList&);
	TList(TNode<TKey, TData>* node);
	~TList();

	TNode<TKey, TData>* Search(TKey); //операция поиска
	void InsertBegin(TKey, TData); //вставка в начало
	void InsertEnd(TKey, TData); //вставка в конец
	void InsertAfter(TKey, TNode<TKey, TData>*);   //вставка после элемента с заданым ключем
	void InsertBefore(TKey, TNode<TKey, TData>*);  //до элемента

	void Remove(TKey); //удаление элемента с данным ключем
	bool IsEmpty() const; //проверка на пустоту
	bool IsEnded() const; //дошли ли мы до конца списка
	void Reset(); //устанавливает текущий указатель в начало
	void Next();   //передвигает текущий указатель на следующий элемент
	TNode<TKey, TData>* GetFirst() const; //возвращает первый элемент
	TNode<TKey, TData>* GetCurrent() const; //возвращает текущий элемент
};

template<class TKey, class TData>
TList<TKey, TData>::TList()
{
	pFirst = nullptr;
	pCurrent = nullptr;
	pPrevious = nullptr;
	pNext = nullptr;
}

template<class TKey, class TData>
TList<TKey, TData>::TList(const TList<TKey, TData>& list)
{
	pCurrent = nullptr;
	pPrevious = nullptr;
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

template<class TKey, class TData>
TList<TKey, TData>::TList(TNode<TKey, TData>* node)
{
	pCurrent = nullptr;
	pPrevious = nullptr;
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

template<class TKey, class TData>
TList<TKey, TData>::~TList()
{
	pCurrent = nullptr;
	pPrevious = nullptr;
	pNext = nullptr;
	while (!IsEnded())
	{
		pNext = pFirst->pNext;
		delete pFirst;
		pFirst = pNext;
	}
}

template<class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Search(TKey key)
{
	if (pFirst == nullptr)
		throw "list is empty";
	TNode<TKey, TData>* tmp = pFirst;
	while ((tmp != nullptr) && (tmp->degree != key))
		tmp = tmp->pNext;
	if (tmp == nullptr)
		cout << "there is no such key";
	return tmp;
}

template<class TKey, class TData>
void TList<TKey, TData>::InsertBegin(TKey key, TData data)
{
	TNode<TKey, TData>* tmp = new TNode<TKey, TData>(key, data);
	tmp->pNext = pFirst;
	if (pCurrent == pFirst)
		pPrevious = tmp;
	pFirst = tmp;
}

template<class TKey, class TData>
void TList<TKey, TData>::InsertEnd(TKey key, TData data)
{
	if (pFirst == nullptr)
	{
		InsertBegin(key, data);
		Reset();
		return;
	}
	TNode<TKey, TData>* prev = pPrevious;
	TNode<TKey, TData>* next = pNext;
	TNode<TKey, TData>* curr = pCurrent;
	Reset();
	while (!IsEnded())
		Next();
	pCurrent = new TNode<TKey, TData>(key, data);
	pPrevious->pNext = pCurrent;
	if (curr == pPrevious)
		pNext = pCurrent;
	else
		pNext = next;
	pCurrent = curr;
	pPrevious = prev;
}

template<class TKey, class TData>
void TList<TKey, TData>::InsertAfter(TKey key, TNode<TKey, TData>* node)
{
	if (pFirst == nullptr)
		throw"list is empty";
	TNode<TKey, TData>* prev = pPrevious;
	TNode<TKey, TData>* next = pNext;
	TNode<TKey, TData>* curr = pCurrent;
	Reset();
	TNode<TKey, TData>* tmp = Search(key);
	if (tmp == nullptr)
		throw"Key isn't found";
	while (pCurrent != tmp)
		Next();
	TNode<TKey, TData>* node_1 = new TNode<TKey, TData>(node->key, node->pData);
	pCurrent->pNext = node_1;
	if (curr == pCurrent)
		pNext = node_1;
	else
		pNext = next;
	if (curr == pNext)
		pPrevious = node_1;
	else
		pPrevious = prev;
	pCurrent = curr;
}

template<class TKey, class TData>
void TList<TKey, TData>::InsertBefore(TKey key, TNode<TKey, TData>* node)
{
	if (pFirst == nullptr)
		throw"list is empty";
	if (pFirst->key == key)
	{
		InsertBegin(node->key, node->pData);
		return;
	}
	TNode<TKey, TData>* prev = pPrevious;
	TNode<TKey, TData>* next = pNext;
	TNode<TKey, TData>* curr = pCurrent;
	Reset();
	TNode<TKey, TData>* tmp = Search(key);
	if (tmp == nullptr)
		throw"Key isn't found";
	while (pCurrent != tmp)
		Next();
	TNode<TKey, TData>* node_1 = new TNode<TKey, TData>(node->key, node->pData);
	pPrevious->pNext = node_1;
	if (curr == pCurrent)
		pPrevious = node_1;
	else
		pPrevious = prev;
	if (curr == pPrevious)
		pNext = node_1;
	else
		pNext = next;
	pCurrent = curr;
}

template<class TKey, class TData>
void TList<TKey, TData>::Remove(TKey key)
{
	if (pFirst == nullptr)
		throw "list is empty";
	if (pFirst->degree == key)
	{
		if (pCurrent == pFirst)
		{
			pCurrent = pNext;
			if (pNext != nullptr)
				pNext = pNext->pNext;
			else
				pNext = nullptr;
			delete pFirst;
			return;
		}
		if (pCurrent == pFirst->pNext)
		{
			pPrevious = nullptr;
			delete pFirst;
			pFirst = pCurrent;
			return;
		}
	}
	TNode<TKey, TData>* prev = pPrevious;
	TNode<TKey, TData>* next = pNext;
	TNode<TKey, TData>* curr = pCurrent;
	Reset();
	TNode<TKey, TData>* tmp = Search(key);
	if (tmp == nullptr)
		throw"Key isn't found 1";
	while (pCurrent != tmp)
		Next();
	pPrevious->pNext = pNext;
	if (curr == pCurrent)
	{
		pCurrent = pNext;
		pNext = pCurrent->pNext;
		delete tmp;
		return;
	}
	if (curr == pNext)
	{
		pCurrent = pNext;
		pNext = pCurrent->pNext;
		delete tmp;
		return;
	}
	if (curr == pPrevious)
	{
		pCurrent = pPrevious;
		pPrevious = prev;
		pNext = pCurrent->pNext;
		delete tmp;
		return;
	}
	pNext = next;
	pCurrent = curr;
	delete tmp;
	return;
}

template<class TKey, class TData>
bool TList<TKey, TData>::IsEmpty() const
{
	return (pFirst == nullptr);
}

template<class TKey, class TData>
bool TList<TKey, TData>::IsEnded() const
{
	return (pCurrent == nullptr);
}

template<class TKey, class TData>
void TList<TKey, TData>::Reset()
{
	pCurrent = pFirst;
	pPrevious = nullptr;
	if (pFirst != nullptr)
		pNext = pCurrent->pNext;
	else
		pNext = nullptr;
}

template<class TKey, class TData>
void TList<TKey, TData>::Next()
{
	if (IsEnded())
		throw"End of list";
	pPrevious = pCurrent;
	pCurrent = pNext;
	if (pNext != nullptr)
		pNext = pNext->pNext;
	else
		pNext = nullptr;
}

template<class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::GetFirst() const
{
	return pFirst;
}

template<class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::GetCurrent() const
{
	return pCurrent;
}
