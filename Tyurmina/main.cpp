#include "BinaryTree.h"
#include <time.h>

int main()
{
	cout << "_____Delete the node_____ " << endl;
	TNode node(50);
	BinaryTree tree(&node);
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		int number = rand() % 100;
		TNode node(number);
		tree.insert(&node);
	}
	cout << "Keys: " << tree << endl;
	int n;
	cout << "Select the number: ";
	cin >> n;
	cout << "Next node: ";
	cout << *(tree.SearchNext(tree.Search(n))) << endl;
	tree.remove(tree.Search(n));
	cout << "Keys after deleted: " << tree << endl;
	system("pause");
	return 0;
}