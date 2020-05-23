#pragma once
#include <string>
#include <iostream>

using namespace std;
template<class ValueType>
class TStack
{
private:
	ValueType* elems;
	int size;
	int top;
public:
	TStack(int size);
	TStack(const TStack& s);
	~TStack();

	bool IsEmpty() const;
	bool IsFull() const;
	void Push(ValueType e);
	void Pop();
	ValueType Top() const;
};

template<class ValueType>
TStack<ValueType>::TStack(int size)
{
	this->size = size;
	this->top = -1;
	elems = new ValueType[size];
}

template<class ValueType>
TStack<ValueType>::TStack(const TStack<ValueType>& s)
{
	this->size = s.size;
	this->top = s.top;
	for (int i = 0; i < top; i++)
		this->elems[i] = s.elems[i];
}

template<class ValueType>
TStack<ValueType>::~TStack()
{
	top = -1;
	size = 0;
	delete[] elems;
}

template<class ValueType>
bool TStack<ValueType>::IsEmpty() const
{
	return(top == -1);
}

template<class ValueType>
bool TStack<ValueType>::IsFull() const
{
	return(top == (size - 1));
}

template<class ValueType>
void TStack<ValueType>::Push(ValueType e)
{
	if (IsFull())
		throw "Error";
	elems[++top] = e;
}

template<class ValueType>
void TStack<ValueType>::Pop()
{
	if (IsEmpty())
		throw "Error";
	top--;
}

template<class ValueType>
ValueType TStack<ValueType>::Top()const
{
	return elems[top];
};