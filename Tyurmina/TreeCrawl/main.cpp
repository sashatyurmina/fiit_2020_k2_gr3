#include <iostream>
#include "TStack.h"

using namespace std;

struct TNode
{
	int value;
	TNode* left;
	TNode*right;
	TNode(int val = 0, TNode* l = NULL, TNode* r = NULL) :
		value(val), left(l), right(r) {}
};

class Itr
{
	TStack<TNode*> st;
	TNode* root;
public:
	Itr(TNode* root1) :
		st(100)
	{
		root = root1;
	}
	bool HasNext()
	{
		return (root != NULL || !st.IsEmpty());
	}
	int next()
	{
		while (root != NULL)
		{
			st.Push(root);
			root = root->left;
		}
		root = st.Top();
		st.Pop();
		int val = root->value;
		root = root->right;
		return val;
	}
};

/*class Navigator
{
	TNode* root;
	TStack<TNode*> path;
public:
	Navigator(TNode* root1)
	{
		root = root1;
	}
	bool left()
	{
		if (root->left == NULL)
			return false;
		path.Push(root);
		root = root->left;
		return true;
	}
	bool right()
	{
		if (root->right == NULL)
			return false;
		path.Push(root);
		root = root->left;
		return true;
	}
	bool up()
	{
		if (path.IsEmpty())
			throw "Path is empty";
		root = path.Top();
		path.Pop();
		return true;
	}
};*/

/*void print(TNode* curr_t)
{
	if (curr_t == NULL) return;
	cout << curr_t->value << "";
	printTLR(curr_t->left);
	printTLR(curr_t->right);
}*/

void printTLR(TNode* curr_t)
{
	if (curr_t == NULL) return;
	cout << curr_t->value << "";
	printTLR(curr_t->left);
	printTLR(curr_t->right);
}

void printLTR(TNode* curr_t)
{
	if (curr_t == NULL) return;
	printLTR(curr_t->left);
	cout << curr_t->value << "";
	printLTR(curr_t->right);
}


void printItrTLR(TNode* root)
{
	TStack<TNode*> st;
	st.Push(root);
	while (!st.IsEmpty())
	{
		TNode* root = st.Top();
		st.Pop();
		cout << root->value << "";
		if (root->right != NULL)
			st.Push(root->right);
		if (root->left != NULL)
			st.Push(root->left);
	}
}

void printItrLTR(TNode* root)
{
	TStack<TNode*> st;
	while (root != NULL || st.IsEmpty() == 0)

	{
		if (root != NULL)
		{
			st.Push(root);
			root = root->left;
		}
		else
		{
			root = st.Pop();
			cout << root->value << "";
			root = root->right;
		}
	}
}



int main()
{
	TNode* p1 = new TNode(4);
	TNode* p2 = new TNode(7);
	TNode* p3 = new TNode(8);
	TNode* p4 = new TNode(5, p2, p3);
	TNode* p5 = new TNode(5, NULL, p3);
	TNode* p6 = new TNode(2, p1, p5);
	TNode* root = p6;
	/*Navigator n(root);
	bool f = true;
	int op;
	int n = 0;
	while (true)
	{
		cout << "f" << f<< endl;
		cout << "value" << n.value() << endl;
		cout << "1.left" << endl;
		cout << "2.right" << endl;
		cout << "3.up" << endl;
		cin >> op;
		try
		{
			if (op == 1)
				n.left();
			if (op == 2)
				n.right();
			if (op == 3)
				n.up();
		}
		catch (const char*str)
		{
			cout << str << endl;
			f = false;
		}
		catch (const char*str)
		{
			cout << str << endl;
			f = false;
		}
	}*/
	cout << "TLR" << endl;
	printTLR(root);
	cout << endl;
	cout << "LTR" << endl;
	printLTR(root);
	cout << endl;
	cout << "Iterator TLR" << endl;
	printItrTLR(root);
	cout << endl;
	cout << "Iterator LTR" << endl;
	printItrLTR(root);
	cout << endl;
	cout << "Iterator LTR2" << endl;
	Itr i(root);
	while (i.HasNext())
		cout << i.next() << " ";
	cout << endl;
	system("pause");
	return 0;
}