/*
 * Design Patterns - BSTIterator
 * Author: Yehya
 * Description: Implementation of the BSTIterator pattern in C++.
 */

#include <iostream>


using namespace std;

template<typename T> struct BinaryTree;

template<typename T> 
struct Node
{
	T value = T();
	Node<T>* left{ nullptr };
	Node<T>* right{ nullptr };
	Node<T>* parent{ nullptr };

	BinaryTree<T>* tree{ nullptr };

	Node(T value) :value(value) {}

	Node(T value, Node<T>*left, Node<T> *right):value(value),left(left),right(right)
	{
		this->left->tree = this->right->tree = tree;
		this->left->parent = this->right->parent = this;
	}

	void set_tree(BinaryTree<T>* t)
	{
		tree = t;
		if (left)
		{
			left->set_tree(t);
		}
		if (right)
		{
			left->set_tree(t);
		}
	}

	~Node()
	{
		if (left) delete left;
		if (right) delete right;
	}
};

template<typename T> 
struct BinaryTree
{
	Node<T>* root{ nullptr };

	BinaryTree(Node<T>* root) :root(root)
	{
		root->set_tree(this);
	}

	~BinaryTree() 
	{
		if (root) delete root;
	}

	template<typename U>
	struct PreOrderIterator
	{
		Node<U>* current;
		PreOrderIterator(Node<U>* current) :current(current) {}

		bool operator!=(const PredOrder<U>& other)
		{
			return current != other.current;
		}

		PreOrderIterator<U>& operator++()
		{
			if (current->right)
			{
				current = current->right;
				while (current->left)
					current = current->left;

			}
			else
			{
				Node<T>* p = current->parent;
				while (p && current == p->right)
				{
					current = p;
					p = p->parent;
				}
				current = p;
			}
			return *this;
		}

		Node<U>& operator*() {
			return *current;
		}
	};//preorder iterator

	typedef PreOrderIterator<T> iterator;

	iterator begin()
	{
		Node<T>* n = root;
		if (n)
			while (n->left)
				n = n->left;

		return iterator{ n };
	}

	iterator end()
	{
		return iterator{ nullptr };
	}
};


int main()
{
	BinaryTree<string> family
	{
		new Node<string>{"me",
		new Node<string>{"mother's mother"},
		new Node<string>{"mother's father"},
		new Node<string>{"father"}
		}
	};

	for (auto it = family.begin(); it != family.end(); it++)
	{
		cout << (*it).value << "\n";
	}


	for (const auto& it : family.pre_order)
	{
		//...
	}
	return 0;
}
