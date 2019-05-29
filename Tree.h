#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<assert.h>
#include<cstdlib>

using namespace std;
enum Color{ Red, Black};
template<typename TM>
struct Node
{
	TM data;
	int Color;
	Node<TM>*left;
	Node<TM>*right;
};

template<typename TM>
class Red_Black_Tree
{
private:
	Node<TM>*root;
	Node<TM>*new_node(TM value)
	{
		Node<TM>* n = new Node<TM>;
		n->data = value;
		n->Color = Red;
		n->left = NULL;
		n->right = NULL;
		return n;
	}
	void setColor(Node<TM>*leaf, int Clr)
	{
		if (leaf == NULL)
			return;
		leaf->Color = Clr;
	}
	int getColor(Node<TM>*leaf)
	{
		if (leaf == NULL)
			return Black;
		return leaf->Color;
	}
	Node<TM>* findparent_recursive(Node<TM>*leaf, Node<TM>*root)
	{
		if (root->right == leaf || root->left == leaf)
			return root;

		else if (leaf->data > root->data)
		{
			return findparent_recursive(leaf, root->right);
		}
		else if (leaf->data < root->data)
		{
			return findparent_recursive(leaf, root->left);
		}
		else
		{
			return NULL;
		}
	}
	void rotateleft(Node<TM>*&leaf,Node<TM>*&parent, Node<TM>*&grand_parent)
	{
		if (leaf == parent->right) // right left
		{
			leaf = grand_parent->right;
			grand_parent->right = leaf;
			parent = leaf->right;
			leaf->right = parent;
		}
		if (leaf == parent->left) // right right
		{
			Node<TM>*grand_grand_parent = findparent(grand_parent);
			if (grand_grand_parent != NULL)
			{
				grand_grand_parent->right = leaf;
			}
			grand_parent = leaf->left;
			leaf->left = grand_parent;
		}
		
	}
	void rotateright(Node<TM>*&leaf, Node<TM>*&parent, Node<TM>*&grand_parent)
	{	
		if (leaf == parent->left) // left right
		{
			leaf = grand_parent->left;
			grand_parent->left = leaf;
			parent = leaf->left;
			leaf->left = parent;

		}
		else if (leaf == parent->right) // left left
		{
			Node<TM>*grand_grand_parent = findparent(grand_parent);
			if (grand_grand_parent != NULL)
			{
				grand_grand_parent->left = parent;
			}
			grand_parent = parent->right;
			parent->right = grand_parent;
		}
		
	}
protected:
	Node<TM>* findparent(Node<TM>*leaf)
	{
		return findparent_recursive(leaf, root);
	}
	void fix_tree(Node<TM>*leaf)
	{
		if (leaf == root)
		{
			setColor(leaf, Black);
			return;
		}
		Node<TM>*parent=findparent(leaf);
		if (parent == NULL)
		{
			return;
		}
		Node<TM>*grand_parent = findparent(parent);
		while (leaf !=root && getColor(leaf) != Black && getColor(parent) != Black)
		{
			if (parent == grand_parent->right) // check right side of the tree
			{
				Node<TM>*uncle = grand_parent->left;
				if (getColor(uncle) != Black) // if the uncle is red
				{
					setColor(grand_parent, Red);
					setColor(parent, Black);
					setColor(grand_parent->left, Black);
					leaf =  grand_parent;
				}
				else
				{
					// if the uncle is black 
					// and node is right child of its parent
					if (getColor(uncle) != Red || leaf == parent->right || uncle == NULL)
					{
						// rotate left
						rotateleft(leaf,parent, grand_parent);
						leaf = parent;
						parent = grand_parent;
					}
					else
					{
						rotateright(leaf, parent, grand_parent);
						swap(parent->Color, grand_parent->Color);
						leaf = parent;
					}
				}
			
			}
			else
			{
				if (parent == grand_parent->left)
				{
					// left side of tree
					Node<TM>*uncle = grand_parent->right;
					if (getColor(uncle) != Black) // if the uncle is red
					{
						setColor(grand_parent, Red);
						setColor(parent, Black);
						setColor(grand_parent->right, Black);
						leaf = grand_parent;
					}
					else
					{
						// if the uncle is black 
						// and node is left child of its parent
						if (getColor(uncle) != Red || leaf == parent->right || uncle == NULL)
						{
							// rotate right
							rotateright(leaf, parent, grand_parent);
							leaf = parent;
							parent = grand_parent;
						}
						else
						{
							rotateleft(leaf, parent, grand_parent);
							swap(parent->Color, grand_parent->Color);
							leaf = parent;
						}
					}
				}
			}
		}
		setColor(root, Black);
	}
	Node<TM>*addleaf(Node<TM>* root, Node<TM>*key)
	{
		if (root == NULL)
		{
			return key;
		}
		if (key->data > root->data)
		{
			root->right = addleaf(root->right, key);
		}
		else if (key->data < root->data)
		{
			root->left = addleaf(root->left, key);
		}
		return root;
	} 
	void Inorder_recursive(Node<TM>*root)
	{
		if (empty())
		{
			cout << "tree is empty\n";
			return;
		}
		else if (root != NULL)
		{
			if (root->left != NULL)
			{
				Inorder_recursive(root->left);
			}
			cout << root->data << setw(4)<<root->Color <<endl;
			if (root->right != NULL)
			{
				Inorder_recursive(root->right);
			}

		}
	}
	void Preorder_recursive(Node<TM>*root)
	{
		if (empty())
		{
			cout << "tree is empty\n";
			return;
		}
		else
		{
			if (root->left != NULL)
			{
				Preorder_recursive(root->left);
			}
			if (root->right != NULL)
			{
				Preorder_recursive(root->right);
			}
			cout << root->data << setw(4);
		}
	}
	void Postorder_recursive(Node<TM>*root)
	{
		if (empty())
		{
			cout << "tree is empty\n";
			return;
		}
		else
		{
			cout << root->data << setw(4);

			if (root->left != NULL)
			{
				Postorder_recursive(root->left);
			}
			if (root->right != NULL)
			{
				Postorder_recursive(root->right);
			}
		}
	}
	
public:
	Red_Black_Tree()
	{
		root = NULL;
	}
	bool empty()
	{
		return root == NULL;
	}
	void insert(TM var)
	{
		Node<TM>*n = new_node(var);
		root = addleaf(root, n);
		fix_tree(n);
	}
	void print_Inorder()
	{
		cout << "In order\n";
		assert(root != NULL);
		Inorder_recursive(root);
		cout << endl;
	}
	void print_Postorder()
	{
		cout << "Post Order\n";
		assert(root != NULL);
		Postorder_recursive(root);
		cout << endl;
	}
	void print_Preorder()
	{
		cout << "pre Order\n";
		assert(root != NULL);
		Preorder_recursive(root);
		cout << endl;
	}
	TM getroot()
	{
		return root->data;
	}
	int black_leaf()
	{
		return getBlackHeight_right(root)+ getBlackHeight_left(root);
	}

};