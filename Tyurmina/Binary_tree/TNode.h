#pragma once
#include <iostream>

using namespace std;

class TNode
{
private:
	int key;
	TNode* parent;
	TNode* Left;
	TNode* Right;
public:
	TNode();
	TNode(int _key);
	TNode(const TNode& copy);
	~TNode();
	TNode* getLeft() const;
	TNode* getRight() const;
	TNode* getParent() const;
	int getkey() const;
	void setLeft(TNode* left);
	void setRight(TNode* right);
	void setParent(TNode* _parent);
	void setkey(int _key);
	friend ostream& operator<<(ostream& out, const TNode& root)
	{
		out << " " << root.key;
		return out;
	}
};