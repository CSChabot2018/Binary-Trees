
//Name :Abayjeet Singh
//Assignment 4
//Date : 3/08/18
#include<iostream>
#include<iomanip>
#include<ctime>
#include<queue>
#include<vector>
using namespace std;

static vector<int> bst;

struct Node
{

	int data;
    Node *left, *right;
};
Node * createNode(int data, Node * left = nullptr, Node * right = nullptr) {
	Node * root = new Node;
	root->data = data;
	root->left = left; 
	root->right = right;
	return root;
}

// make a random tree with height <= maxheight  
Node * makeTree(int maxheight) {
	if (maxheight <= 0) return nullptr;
	Node * p = rand() % 5 != 0 ? makeTree(maxheight - 1) : nullptr;
	Node * q = rand() % 5 != 0 ? makeTree(maxheight - 1) : nullptr;
	return createNode(rand() % 16, p, q);
}
void drawTree(Node * p, int indentation = 0) {
	int dashes = 3;
	for (int i = 0; i < indentation; i++)
		cout << " ";
	if (p != nullptr) {
		for (int i = 0; i < dashes; i++) cout << "-";
		cout << p->data << endl;
		drawTree(p->left, indentation + 5);
	    drawTree(p->right, indentation + 5);
	}
	else
		cout << "~" << endl;
	
}
int height(Node * root)
{
	if (root == nullptr )
	{
		return 0;
	}
	int h1 = height(root->left);
	int h2 = height(root->right);
	if (h1 > h2)
		return h1 + 1;
	return h2 + 1;


}
int size(Node *root)
{
	if (root == nullptr)
	{
		return 0;
	}
	return 1 + size(root->left) + size(root->right);



}
bool isPerfect(Node *root)
{
	if (root == nullptr)
		return true;
	int h = height(root);
	int s = size(root);
	int x = int(round(pow(2, h))) - 1;
	return x == s;

}
bool isBalanced(Node *root)
{
	if (root == nullptr)
		return true;
	int h1 = height(root->left);
	int h2 = height(root->right);
	if (h1 - h2 > 1 || h2 - h1 > 1)
	{
		return false;
	}
	return isBalanced(root->left) && isBalanced(root->right);
}
bool isComplete(Node *root)
{
	
	if(root==nullptr)
	{
		return true;
	}
	int h1 = height(root->left);
	int h2 = height(root->right);
	
	if (!((h1 == h2) || h1 == h2 + 1))
		return false;
	
	
	if (h1 == h2)
	{
		return isPerfect(root->left) && isComplete(root->right);
	}
	return isComplete(root->left) && isPerfect(root->right);
}

bool isdegenerate(Node *root)
{
	if (root == nullptr)
	{
		return true;
    }
	int s = size(root);
	int h = height(root);
	if (s == h)
	{
		return true;
	}
	return false;
}

void inOrder(Node *root)
{
	 

	if (root != nullptr)

	{
		inOrder(root->left);
		cout << root->data << " ";
		bst.push_back( root->data);
		inOrder(root->right);

	}
}
void Postorder(Node *root)
{
	if (root != nullptr)
	{
		Postorder(root->left);
		Postorder(root->right);
		cout << root->data << " ";
    }

	
}
void PreOrder(Node *root)
{
	if (root != nullptr)
	{
		cout << root->data << " ";
		PreOrder(root->left);
		PreOrder(root->right);
	}
}
void LevelOrder(Node *root)
{
	if (root == nullptr)
	{
		return;
	}
	queue<Node*> q;
	q.push(root);
	while(!q.empty())
	{
		Node *current = q.front();
		cout << current->data << " ";
		if (current->left != nullptr)
			q.push(current->left);
		if (current->right != nullptr)
			q.push(current->right);
		q.pop();
	
	
	}


}
int getmax(Node *root)
{    
	int high = -1;
	for (int i = 0; i < size(root); i++)
	{
		if (bst[i] > high)
			high = bst[i];
	}
	 
	
	return high;

	
	
}

	void Deletetree(Node *root)
	{ 
		
	
		if (root == nullptr)
		{
			return;
		}
		
		Deletetree(root->left);
		Deletetree(root->right);
		delete root->left;
		delete root->right;
		root->left = nullptr;
		root->right = nullptr;

    }

	void deleteTree( Node** node)
	{
		Deletetree(*node);
		*node = nullptr;
	}


	int shortestpath(Node *root)
	{
		int h = 0;
		if (root == nullptr)
		{
			return h;
		}
		queue<Node*> q;
		q.push(root);
		while (!q.empty())
		{
			Node *current = q.front();
			
			if (current->left != nullptr)
			{  
				q.push(current->left);
			}
			if (current->right != nullptr)
				q.push(current->right);
			if (current->left == nullptr &&current->right == nullptr)
			{
				return h+1;
			}
			if (current->left != nullptr || current->right != nullptr)
			{
				h++;
			}
			q.pop();


		}

	}
	bool isBST(Node *root)//Inorder traversal of a binary search tree is sorted
	{
		for (int i = 0; i < size(root)-1; i++)
		{
			if (bst[i] > bst[i + 1])
				return false;
		}
		return true;
	}


int main()
{    
	srand(unsigned int (time(0)));
	bool done = false;
	while (!done)
	{
		int maxHeight;
		std::cout << "maximum height? (or -1 to quit): ";
		cin >> maxHeight;
		if (maxHeight <= -1)
			done = true;
		else {
			Node * tree = makeTree(maxHeight);
			drawTree(tree);
			cout << "Now Displaying Info about the above Binary tree  : " << endl;
			cout <<"The height of tree is : "<< height(tree) << endl;
			cout <<"The size of tree is :"<< size(tree) << endl;
			if (isPerfect(tree))
			{
				cout << " This tree is Perfect" << endl;
			}
			if (isBalanced(tree))
			{
				cout << "This tree is Balanced" << endl;
			}
			if (isdegenerate(tree))
			{
				cout << "This tree is degenerate" << endl;
			}
			cout << "Inorder Traversal : ";
			inOrder(tree);
			cout << endl;
			cout << "Post Order Traversal :";
			Postorder(tree);
			cout << endl;
			cout << "Pre Order Traversal ";
			PreOrder(tree);
			cout << endl;
			cout << "Level Order Traversal : ";
			LevelOrder(tree);
		
			cout << endl;
			cout << "The max value of tree is : " << getmax(tree) << endl;
			cout << " The Shortest path to leaf : " << shortestpath(tree) << endl;
			if (!isBST(tree))
			{
				cout << "This Binary tree is not a Binary Search Tree" << endl;
			}
			else
			{
				cout << " This Binary tree is a Binary Search Tree" << endl;
			}
			if (isComplete(tree))
			{
				cout << "This tree is complete" << endl;
			}
			deleteTree(&tree);
			cout << endl;
			cout << "Displaying  Height and size of tree after emptying tree :" << endl;
			cout << height(tree) << " ";
			cout << size(tree);
			
			drawTree(tree);
			system("pause");


		}


		

	}
}