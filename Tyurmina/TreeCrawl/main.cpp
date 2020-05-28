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
		st.Push(root);
	}
	bool HasNext()
	{
		return (root != NULL || !st.IsEmpty());
	}
	int next()
	{
		TNode* curr_t = st.Top();
		st.Pop();
		int value = curr_t->value;
		if (root->right != NULL)
			st.Push(root->right);
		if (root->left != NULL)
			st.Push(root->left);
		return value;
	}
};

/*void printTLR(TNode* curr_t) //TopLeftRight(верх-лево-право) - рек
{
	if (curr_t == NULL) return;
	cout << curr_t->value << "";
	printTLR(curr_t->left);
	printTLR(curr_t->right);
}

void printLTR(TNode* curr_t) //LeftTopRight(лево-верх-право) -рек
{
	if (curr_t == NULL) return;
	printLTR(curr_t->left);
	cout << curr_t->value << "";
	printLTR(curr_t->right);
}*/


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
	TNode* p1 = new TNode(4); //лист со значением 4
	TNode* p2 = new TNode(6); //лист со значением 6
	TNode* p3 = new TNode(3); //лист со значением 3
	TNode* p4 = new TNode(5, NULL, p2); //лист со значением 5, лев=0, прав=6
	TNode* p5 = new TNode(2, p1, p4); //лист со значением 2, лев=4 прав=5
	TNode* p6 = new TNode(1, p5, p3); //лист со значением 1, лев=2,прав=3
	TNode* root = p6;
	
	cout << "Itr TLR" << endl;
	printItrTLR(root);
	cout << endl;
	cout << "Itr TLR" << endl;
	printItrTLR(root);
	cout << "Iterator" << endl;
	Itr i(root);
	while (i.HasNext())
		cout << i.next() << " ";
	cout << endl;
	system("pause");
	return 0;
}
