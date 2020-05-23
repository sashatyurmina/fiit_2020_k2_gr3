#pragma once
#include "TNode.h"

class BinaryTree
{
private:
	TNode* root;
	TNode* Min(TNode* root);
public:
	BinaryTree(TNode* _root = nullptr) : root(_root) {};
	void remove(TNode* z);//óäàëåíèå âåðøèíû
	TNode* SearchNext(TNode* curr);
	TNode* SearchMin();
	TNode* Search(int _key);
	void insert(TNode* node);
	static void print(const TNode* root);
	friend ostream& operator<<(ostream& out, const BinaryTree& Tree)
	{
		if (Tree.root != nullptr)
			BinaryTree::print(Tree.root);
		return out;
	}
};