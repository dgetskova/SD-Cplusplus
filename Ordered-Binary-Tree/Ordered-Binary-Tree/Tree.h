#include <iostream>

template <class T>
struct node
{
	T data;
	int key;
	node<T>* left;
	node<T>* right;

	node() : data(0), key(0), left(NULL), right(NULL){}
	node(const T dataCame);//
	node(const node* nodeCame)
	{
		data = node->data;
		key = node->key;
		left = NULL;
		right = NULL;
	}
	node(const T dataCame, int keyCame)// need for main to create test data.
	{
		data = dataCame;
		key = keyCame;
		left = NULL;
		right = NULL;
	}
	~node()
	{
		delete left;
		delete right;
	}
};

template<class T>
class Tree
{
	node<T>* pointer;
private:
	void addNode(node<T>*& nodeTree, node<T>* newNode);
	T searchNode(node <T>*& nodeCame, int keyCame);
	node<T>*& Tree<T>::searchNodeBeforeConnection(node<T>*& nodeCame, int keyCame);
	void Tree<T>::returnAndDeleteMaxLeaf(node<T>*& nodeMoving, node<T>*& nodeToChange);
	
public:
	Tree() :pointer(NULL){}
	~Tree(){ delete pointer; }

public:
	T search(const T keyCame);
	void add(const node<T>& dataCame);
	void remove(int keyCame);
};

template<class T>
void Tree<T>::add(const node<T>& dataCame)
{
	node<T>* newNode = new node<T>(dataCame);
	addNode(this->pointer, newNode);
}

template <class T>
void Tree<T>::addNode(node<T>*& nodeCame, node<T>* nodeToFind)
{
	//found empty node
	if (nodeCame == NULL)
	{
		nodeCame = nodeToFind;
		return;
	}
	
	if (nodeCame->key >= nodeToFind->key)
		addNode(nodeCame->left, nodeToFind);

	if (nodeCame->key < nodeToFind->key)
		addNode(nodeCame->right, nodeToFind);
}

template<class T>
T Tree<T>::search(const T keyCame)
{
	return searchNode(this->pointer, keyCame);
}

template<class T>
T Tree<T>::searchNode(node <T>*& nodeCame, int keyCame)
{
	if (nodeCame->key == keyCame)
		return nodeCame->data;

	if (nodeCame->key >= keyCame)
		searchNode(nodeCame->left, keyCame);

	if (nodeCame->key < keyCame)
		searchNode(nodeCame->right, keyCame);
	else
		throw"Don't exist such a node";
}

template<class T>
void Tree<T>::remove(int keyCame)
{
	// for leaf(node with no child's) or node with one child
	node<T>*& nodeBeforeConnection = searchNodeBeforeConnection(this->pointer, keyCame);

	node<T>* currentNode = nodeBeforeConnection;

	//for leaf
	if (currentNode->left == NULL && currentNode->right == NULL)
	{
		delete nodeBeforeConnection;
		nodeBeforeConnection = NULL;
		//delete currentNode; 
		// i'm not sure if it's delete the memory wich is allocate for the node or just a copy of the node
		return;
	}
	// left have node
	if (currentNode->left != NULL && currentNode->right == NULL)
	{
		nodeBeforeConnection = currentNode->left;
		currentNode->left = NULL;
		delete currentNode;
		return;
	}
	// right have node
	if (currentNode->left == NULL && currentNode->right != NULL)
	{
		nodeBeforeConnection = currentNode->right;
		currentNode->right = NULL;
		delete currentNode;
		return;
	}

	// bouth nodes
	if (currentNode->left != NULL && currentNode->right != NULL)
		// max elem in the left side. It is smaller than Current Elem and biggest from his sons.
		returnAndDeleteMaxLeaf(nodeBeforeConnection->left, nodeBeforeConnection);
}

template<class T>
node<T>*& Tree<T>::searchNodeBeforeConnection(node<T>*& nodeCame, int keyCame)
{
	
	if (nodeCame-> left != NULL)
		if(nodeCame->left->key == keyCame)
			return nodeCame->left;
	if (nodeCame-> right != NULL)
		if (nodeCame->right->key == keyCame)
			return nodeCame->right;
	//if(nodeCame == keyCame)
	//	return;
	if (nodeCame->key >= keyCame)
		searchNode(nodeCame->left, keyCame);

	if (nodeCame->key < keyCame)
		searchNode(nodeCame->right, keyCame);
	else
		throw"Don't exist such a node";
}

template<class T>
void Tree<T>::returnAndDeleteMaxLeaf(node<T>*& nodeMoving, node<T>*& nodeToChange)
{
	if (nodeMoving->right == NULL)
	{
		// problem !!
		//if maxa have left sons
		//connection = nodeBefore(nodeMoving)
		nodeToChange->data = nodeMoving->data;
		nodeToChange->key = nodeMoving->key;
		// connection = nodeMoving->left ;
		// nodeMoving->left = NULL;
		delete nodeMoving;
		nodeMoving = NULL;
		return;
	}
	returnAndDeleteMaxLeaf(nodeMoving->right, nodeToChange);
}