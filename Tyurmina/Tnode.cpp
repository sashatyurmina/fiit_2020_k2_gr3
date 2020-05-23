#include "TNode.h"

TNode::TNode()
{
	key = 0;
	parent = nullptr;
	Left = nullptr;
	Right = nullptr;
}

TNode::TNode(int _key)
{
	key = _key;
	parent = nullptr;
	Left = nullptr;
	Right = nullptr;
}

TNode::~TNode()
{
	key = 0;
	parent = nullptr;
	Left = nullptr;
	Right = nullptr;
};

TNode::TNode(const TNode& copy)
{
	key = copy.key;
	parent = copy.parent;
	Left = copy.Left;
	Right = copy.Right;
}

TNode* TNode::getLeft() const 
{ 
	return Left;
}

TNode* TNode::getRight() const 
{ 
	return Right;
}

TNode* TNode::getParent() const 
{ 
	return parent;
}

int TNode::getkey() const
{ 
	return key;
}
void TNode::setLeft(TNode* left) 
{ 
	Left = left;
}

void TNode::setRight(TNode* right)
{ 
	Right = right;
}

void TNode::setParent(TNode* _parent) 
{
	parent = _parent;
}

void TNode::setkey(int _key) 
{ 
	key = _key;
}