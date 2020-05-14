#pragma once
#include "Exception.h"
#include "Monom.h"

using namespace std;

template<typename TKey, typename TData>
class TList
{
private:
	TNode<TKey, TData>* pFirst;
	TNode<TKey, TData>* pPrevious;
	TNode<TKey, TData>* pCurrent;
	TNode<TKey, TData>* pNext;
public:
	TList();
	TList(const TList<TKey, TData>& list);
	TList(TNode<TKey, TData>* node);
	~TList();

	TNode<TKey, TData>* Search(TKey key);
	TNode<TKey, TData>* Search(TNode<TKey, TData>* node);

	void InsertBegin(TKey new_key, TData data);
	void InsertEnd(TKey new_key, TData data);
	void InsertAfter(TKey key, TKey new_key, TData data);
	void InsertBefore(TKey key, TKey new_key, TData data);

	void InsertBegin(TNode<TKey, TData>* node);
	void InsertEnd(TNode<TKey, TData>* node);
	void InsertAfter(TKey key, TNode<TKey, TData>* node);
	void InsertBefore(TKey key, TNode<TKey, TData>* node);

	void Remove(TKey key);
	void Remove(TNode<TKey, TData>* node);

	// —лужебные операции
	bool IsEmpty() const;
	bool IsEnded() const;

	// Ќавигаци€
	void Reset();
	void Next();

	TNode<TKey, TData>* GetFirst() const;
	TNode<TKey, TData>* GetCurrent() const;

	friend ostream& operator<<(ostream& out, const TList<TKey, TData>& list)
	{
		TNode<TKey, TData>* tmp = list.GetFirst();
		int cnt = 1;
		while (tmp != nullptr)
		{
			out << *(tmp);
			if (tmp->pNext != nullptr)
			{
				out << "-->";
				if (cnt != 5)
					cnt++;
				else
				{
					cnt = 0;
					out << endl;
				}
			}
			tmp = tmp->pNext;
		}

		return out;
	}
};

template<typename TKey, typename TData>
TList<TKey, TData>::TList()
{
	pFirst = nullptr;
	pPrevious = nullptr;
	pCurrent = nullptr;
	pNext = nullptr;
}

template<typename TKey, typename TData>
TList<TKey, TData>::TList(const TList<TKey, TData>& list)
{
	if (list.IsEmpty())
	{
		pPrevious = nullptr;
		pCurrent = nullptr;
		pNext = nullptr;
		pFirst = nullptr;
		return;
	}
	pFirst = new TNode<TKey, TData>(*(list.pFirst));
	TNode<TKey, TData>* node = pFirst;
	TNode<TKey, TData>* tmp = list.pFirst;

	while (tmp->pNext != nullptr)
	{
		node->pNext = new TNode<TKey, TData>(*(tmp->pNext));
		node = node->pNext;
		tmp = tmp->pNext;
	}
	pPrevious = nullptr;
	pCurrent = pFirst;
	if (pFirst->pNext != nullptr)
		pNext = pFirst->pNext;
	else
		pNext = nullptr;
}

template<typename TKey, typename TData>
TList<TKey, TData>::TList(TNode<TKey, TData>* node)
{
	pFirst = new TNode<TKey, TData>(*node);
	pCurrent = pFirst;
	pPrevious = nullptr;
	pNext = nullptr;
}

template<typename TKey, typename TData>
TList<TKey, TData>::~TList()
{
	TNode<TKey, TData>* del_node = pFirst;
	TNode<TKey, TData>* next;
	while (del_node != nullptr) // пока не дошли до конца,
	{                           // удал€ем последовательно узлы
		next = del_node->pNext;
		delete del_node;
		del_node = next;
	}
}

template<typename TKey, typename TData>
bool TList<TKey, TData>::IsEmpty() const
{
	return (pFirst == nullptr);
}

template<typename TKey, typename TData>
bool TList<TKey, TData>::IsEnded() const
{
	return (pCurrent == nullptr);
}

template<typename TKey, typename TData>
void TList<TKey, TData>::Reset()
{
	pCurrent = pFirst;
	pPrevious = nullptr;
	if (pFirst != nullptr)
		pNext = pFirst->pNext;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::Next()
{
	if (IsEnded())
		throw Exception
		(" Error, Next() is impossible to perform, list ended\n");
	pPrevious = pCurrent;
	pCurrent = pNext;
	if (pNext != nullptr)
		pNext = pNext->pNext;
}

template<typename TKey, typename TData>
TNode<TKey, TData>* TList<TKey, TData>::Search(TKey key)
{
	if (pFirst == nullptr)
		throw Exception(" Error, List is empty\n");
	if (pFirst->key == key)
		return pFirst;

	TNode<TKey, TData>* tmp = pFirst;
	while ((tmp->pNext != nullptr) && (tmp->pNext->key != key))
		tmp = tmp->pNext;
	if (tmp->pNext == nullptr)
		throw Exception(" Error, key isn't found\n");
	return tmp->pNext;
}

template<typename TKey, typename TData>
TNode<TKey, TData>* TList<TKey, TData>::Search(TNode<TKey, TData>* node)
{
	if (pFirst == nullptr)
		throw Exception(" Error, List is empty\n");
	if (pFirst == node)
		return pFirst;

	TNode<TKey, TData>* tmp = pFirst;
	while ((tmp->pNext != nullptr) && (tmp->pNext != node))
		tmp = tmp->pNext;
	if (tmp->pNext == nullptr)
		throw Exception(" Error, node isn't found\n");
	return tmp->pNext;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertBegin(TKey new_key, TData data)
{
	if (pFirst == nullptr)
	{
		pFirst = new TNode<TKey, TData>(new_key, data);
		pCurrent = pFirst;
		return;
	}
	TNode<TKey, TData>* new_node = new TNode<TKey, TData>(new_key, data);
	new_node->pNext = pFirst;
	if (pCurrent == pFirst)
		pPrevious = new_node;
	pFirst = new_node;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertEnd(TKey new_key, TData data)
{
	if (pFirst == nullptr)
	{
		InsertBegin(new_key, data);
		return;
	}
	TNode<TKey, TData>* new_node = new TNode<TKey, TData>(new_key, data);
	TNode<TKey, TData>* tmp = pFirst;
	while (tmp->pNext != nullptr)
		tmp = tmp->pNext;
	tmp->pNext = new_node;
	if (pCurrent == tmp)
		pNext = new_node;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertAfter(TKey key, TKey new_key, TData data)
{
	if (pFirst == nullptr)
		throw Exception(" Error, List is empty\n");
	TNode<TKey, TData>* tmp = pFirst;
	while ((tmp != nullptr) && (tmp->key != key))
		tmp = tmp->pNext;
	if (tmp == nullptr)
		throw Exception(" Error, key isn't found\n");
	TNode<TKey, TData>* new_node = new TNode<TKey, TData>(new_key, data);
	new_node->pNext = tmp->pNext;
	tmp->pNext = new_node;
	if (pCurrent == tmp)
		pNext = new_node;
	if (pCurrent == new_node->pNext)
		pPrevious = new_node;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertBefore(TKey key, TKey new_key, TData data)
{
	if (pFirst == nullptr)
		throw Exception(" Error, List is empty\n");
	if (pFirst->key == key)
	{
		InsertBegin(new_key, data);
		return;
	}
	TNode<TKey, TData>* tmp = pFirst;
	while ((tmp->pNext != nullptr) && (tmp->pNext->key != key))
		tmp = tmp->pNext;
	if (tmp->pNext == nullptr)
		throw Exception(" Error, key isn't found\n");
	TNode<TKey, TData>* new_node = new TNode<TKey, TData>(new_key, data);
	new_node->pNext = tmp->pNext;
	tmp->pNext = new_node;
	if (pCurrent == tmp)
		pNext = new_node;
	if (pCurrent == new_node->pNext)
		pPrevious = new_node;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertBegin(TNode<TKey, TData>* node)
{
	InsertBegin(node->key, node->data);
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertEnd(TNode<TKey, TData>* node)
{
	InsertEnd(node->key, node->data);
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertAfter(TKey key, TNode<TKey, TData>* node)
{
	InsertAfter(key, node->key, node->data);
}

template<typename TKey, typename TData>
void TList<TKey, TData>::InsertBefore(TKey key, TNode<TKey, TData>* node)
{
	InsertBefore(key, node->key, node->data);
}

template<typename TKey, typename TData>
void TList<TKey, TData>::Remove(TKey key)
{
	if (pFirst == nullptr)
		throw Exception(" Error remove, List is empty\n");
	if (pFirst->key == key)
	{
		bool CurrentWasFirst = (pCurrent == pFirst);
		bool PreviousWasFirst = (pPrevious == pFirst);
		TNode<TKey, TData>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
		if (CurrentWasFirst)
		{
			pCurrent = pFirst;
			if (pCurrent != nullptr)
				pNext = pFirst->pNext;
		}
		if (PreviousWasFirst)
			pPrevious = nullptr;

		return;
	}
	TNode<TKey, TData>* tmp = pFirst;
	while ((tmp->pNext != nullptr) && (tmp->pNext->key != key))
		tmp = tmp->pNext;
	if (tmp->pNext == nullptr)
		throw Exception(" Error, key isn't found\n");

	TNode<TKey, TData>* node = tmp->pNext;
	bool PreviousWasNode = (pPrevious == node);
	bool CurrentWasNode = (pCurrent == node);
	bool NextWasNode = (pNext == node);

	tmp->pNext = tmp->pNext->pNext;
	delete node;

	if (PreviousWasNode)
		pPrevious = tmp;
	if (NextWasNode)
		pNext = tmp->pNext;
	if (CurrentWasNode)
	{
		pCurrent = tmp->pNext;
		if (pCurrent != nullptr)
			pNext = tmp->pNext->pNext;
	}
}

template<typename TKey, typename TData>
void TList<TKey, TData>::Remove(TNode<TKey, TData>* node)
{
	if (pFirst == nullptr)
		throw Exception(" Error remove, List is empty\n");

	if (pFirst == node)
	{
		bool CurrentWasFirst = (pCurrent == pFirst);
		bool PreviousWasFirst = (pPrevious == pFirst);
		TNode<TKey, TData>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
		if (CurrentWasFirst)
		{
			pCurrent = pFirst;
			if (pCurrent != nullptr)
				pNext = pFirst->pNext;
		}
		if (PreviousWasFirst)
			pPrevious = nullptr;

		return;
	}

	TNode<TKey, TData>* tmp = pFirst;
	while ((tmp->pNext != nullptr) && (tmp->pNext != node))
		tmp = tmp->pNext;
	if (tmp->pNext == nullptr)
		throw Exception(" Error, address of node isn't found\n");

	bool PreviousWasNode = (pPrevious == node);
	bool CurrentWasNode = (pCurrent == node);
	bool NextWasNode = (pNext == node);

	tmp->pNext = tmp->pNext->pNext;
	delete node;

	if (PreviousWasNode)
		pPrevious = tmp;
	if (NextWasNode)
		pNext = tmp->pNext;
	if (CurrentWasNode)
	{
		pCurrent = tmp->pNext;
		if (pCurrent != nullptr)
			pNext = tmp->pNext->pNext;
	}
}

template<typename TKey, typename TData>
TNode<TKey, TData>* TList<TKey, TData>::GetFirst() const
{
	if (pFirst == nullptr)
		throw Exception(" Error get, pFirst = nullptr\n");
	return pFirst;
}

template<typename TKey, typename TData>
TNode<TKey, TData>* TList<TKey, TData>::GetCurrent() const
{
	if (pCurrent == nullptr)
		throw Exception(" Error get, pCurrent = nullptr\n");
	return pCurrent;
}