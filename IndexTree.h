#pragma once

#include "Student.h"
#include "Date.h"
#include "ArrayList.h"

#include <memory>
#include <algorithm>

//represents one node of the linked list of indexes which is stored in each tree node
class IndexNode
{
public:

	int m_index;
	std::unique_ptr<IndexNode> m_next;

	IndexNode() = default;

	IndexNode(const IndexNode& other);

	IndexNode& operator=(const IndexNode& other);

	IndexNode(IndexNode&& other) = default;

	IndexNode& operator=(IndexNode&& other) = default;
};

//represents one node of the AVL index tree
template <typename Type>
class IndexTreeNode
{
public:

	Type m_key;
	std::unique_ptr<IndexNode> m_indexList;
	std::unique_ptr<IndexTreeNode> m_left;
	std::unique_ptr<IndexTreeNode> m_right;

	IndexTreeNode() = default;

	IndexTreeNode(const IndexTreeNode& other);

	IndexTreeNode& operator=(const IndexTreeNode& other);

	IndexTreeNode(IndexTreeNode&& other) = default;

	IndexTreeNode& operator=(IndexTreeNode&& other) = default;
};

template<typename Type>
inline IndexTreeNode<Type>::IndexTreeNode(const IndexTreeNode& other)
	: m_key(other.m_key)
{
	if (other.m_indexList != nullptr) m_indexList = std::make_unique<IndexNode>(*other.m_indexList);
	if (other.m_left != nullptr) m_left = std::make_unique<IndexTreeNode>(*other.m_left);
	if (other.m_right != nullptr) m_right = std::make_unique<IndexTreeNode>(*other.m_right);
}

template<typename Type>
inline IndexTreeNode<Type>& IndexTreeNode<Type>::operator=(const IndexTreeNode& other)
{
	if (&other == this)
	{
		return *this;
	}

	m_key = other.m_key;

	if (other.m_indexList != nullptr)
	{
		m_indexList = std::make_unique<IndexNode>(*other.m_indexList);
	}
	else
	{
		m_indexList = nullptr;
	}

	if (other.m_left != nullptr)
	{
		m_left = std::make_unique<IndexTreeNode>(*other.m_left);
	}
	else
	{
		m_left = nullptr;
	}

	if (other.m_right != nullptr)
	{
		m_right = std::make_unique<IndexTreeNode>(*other.m_right);
	}
	else
	{
		m_right = nullptr;
	}

	return *this;
}

//represents one result of a search in the AVL index tree
//contains a pointer to the linked list of indexes in the found node and number of accesses necessary to find that node
//if nothing was found, the pointer is nullptr
struct IndexSearchResult
{
	const IndexNode* m_indexList;
	int m_accesses;

	IndexSearchResult(const IndexNode* indexList = nullptr, int accesses = 0)
		: m_indexList(indexList), m_accesses(accesses) {}
};

//class representng an AVL index tree
template <typename Type>
class IndexTree
{
public:

	IndexTree() = default;

	IndexTree(const IndexTree& other);

	IndexTree& operator=(const IndexTree& other);

	IndexTree(IndexTree&& other) = default;

	IndexTree& operator=(IndexTree && other) = default;

	//search for a single value
	IndexSearchResult search(Type key) const;

	//range search for all values between key1 and key2 inclusive
	//accesses: for counting the total number of accesses even if the returned arraylist is empty
	ArrayList<IndexSearchResult> searchRange(Type key1, Type key2, int& accesses) const;

	//inserts a new key-index pair into the tree
	void insert(Type key, int index);

	//destroys the entire tree, freeing all allocated memory, the result is an empty tree
	void clear();

private:

	//the root node of the tree
	std::unique_ptr<IndexTreeNode<Type>> m_root;

	//returns the height of the subtree rooted at root
	int height(const std::unique_ptr<IndexTreeNode<Type>>& root) const;

	//returns the balance factor of the subtree rooted at root
	int getBalance(const std::unique_ptr<IndexTreeNode<Type>>& root) const;

	//function to right rotate subtree rooted with y
	std::unique_ptr<IndexTreeNode<Type>> rightRotate(std::unique_ptr<IndexTreeNode<Type>>& y);

	//function to left rotate subtree rooted with x
	std::unique_ptr<IndexTreeNode<Type>> leftRotate(std::unique_ptr<IndexTreeNode<Type>>& x);

	//inserts a new value-index pair into the subtree rooted at root and returns the new root of that subtree
	std::unique_ptr<IndexTreeNode<Type>> insert(std::unique_ptr<IndexTreeNode<Type>>& root, Type key, int index);

	//search for a single value in the subtree rooted at root
	//the result gets saved in the result variable
	void search(const std::unique_ptr<IndexTreeNode<Type>>& root, Type key, IndexSearchResult& result) const;

	//range search for all values between key1 and key2 inclusive in the subtree rooted at root
	//the results get saved in the results variable
	//accesses: for counting the total number of accesses even if the returned arraylist is empty
	void searchRange(const std::unique_ptr<IndexTreeNode<Type>>& root, Type key1, Type key2, ArrayList<IndexSearchResult>& results, int& accesses) const;
};

template<typename Type>
inline IndexTree<Type>::IndexTree(const IndexTree& other)
{
	if (other.m_root != nullptr) m_root = std::make_unique<IndexTreeNode>(*other.m_root);
}

template<typename Type>
inline IndexTree<Type>& IndexTree<Type>::operator=(const IndexTree& other)
{
	if (&other == this)
	{
		return *this;
	}

	if (other.m_root != nullptr)
	{
		m_root = std::make_unique<IndexTreeNode>(*other.m_root);
	}
	else
	{
		m_root = nullptr;
	}

	return *this;
}

template<typename Type>
inline IndexSearchResult IndexTree<Type>::search(Type key) const
{
	IndexSearchResult result;

	search(m_root, key, result);

	return result;
}

template<typename Type>
inline ArrayList<IndexSearchResult> IndexTree<Type>::searchRange(Type key1, Type key2, int& accesses) const
{
	ArrayList<IndexSearchResult> results;
	accesses = 0;

	searchRange(m_root, key1, key2, results, accesses);

	return results;
}

template<typename Type>
inline void IndexTree<Type>::insert(Type key, int index)
{
	m_root = insert(m_root, key, index);
}

template<typename Type>
inline void IndexTree<Type>::clear()
{
	m_root = nullptr;
}

template<typename Type>
inline int IndexTree<Type>::height(const std::unique_ptr<IndexTreeNode<Type>>& root) const
{
	if (root == nullptr) return 0;

	return std::max(height(root->m_left), height(root->m_right)) + 1;
}

template<typename Type>
inline int IndexTree<Type>::getBalance(const std::unique_ptr<IndexTreeNode<Type>>& root) const
{
	if (root == nullptr) return 0;

	return height(root->m_left) - height(root->m_right);
}

template<typename Type>
inline std::unique_ptr<IndexTreeNode<Type>> IndexTree<Type>::rightRotate(std::unique_ptr<IndexTreeNode<Type>>& y)
{
	std::unique_ptr<IndexTreeNode<Type>> x = std::move(y->m_left);
	std::unique_ptr<IndexTreeNode<Type>> T2 = std::move(x->m_right);

	y->m_left = std::move(T2);
	x->m_right = std::move(y);

	return x;
}

template<typename Type>
inline std::unique_ptr<IndexTreeNode<Type>> IndexTree<Type>::leftRotate(std::unique_ptr<IndexTreeNode<Type>>& x)
{
	std::unique_ptr<IndexTreeNode<Type>> y = std::move(x->m_right);
	std::unique_ptr<IndexTreeNode<Type>> T2 = std::move(y->m_left);

	x->m_right = std::move(T2);
	y->m_left = std::move(x);

	return y;
}

template<typename Type>
inline std::unique_ptr<IndexTreeNode<Type>> IndexTree<Type>::insert(std::unique_ptr<IndexTreeNode<Type>>& root, Type key, int index)
{
	if (root == nullptr)
	{
		std::unique_ptr<IndexTreeNode<Type>> newRoot = std::make_unique<IndexTreeNode<Type>>();
		newRoot->m_key = key;
		newRoot->m_left = nullptr;
		newRoot->m_right = nullptr;
		newRoot->m_indexList = std::make_unique<IndexNode>();
		newRoot->m_indexList->m_index = index;
		newRoot->m_indexList->m_next = nullptr;
		return newRoot;
	}

	if (key < root->m_key)
		root->m_left = insert(root->m_left, key, index);
	else if (key > root->m_key)
		root->m_right = insert(root->m_right, key, index);
	else 
	{
		IndexNode* current = root->m_indexList.get();
		while (current->m_next != nullptr)
		{
			current = current->m_next.get();
		}
		current->m_next = std::make_unique<IndexNode>();
		current->m_next->m_index = index;
		current->m_next->m_next = nullptr;

		return std::move(root);
	}

	int balance = getBalance(root);

	if (balance > 1 && key < root->m_left->m_key)
		return rightRotate(root);

	if (balance < -1 && key > root->m_right->m_key)
		return leftRotate(root);

	if (balance > 1 && key > root->m_left->m_key)
	{
		root->m_left = leftRotate(root->m_left);
		return rightRotate(root);
	}

	if (balance < -1 && key < root->m_right->m_key)
	{
		root->m_right = rightRotate(root->m_right);
		return leftRotate(root);
	}

	return std::move(root);
}

template<typename Type>
inline void IndexTree<Type>::search(const std::unique_ptr<IndexTreeNode<Type>>& root, Type key, IndexSearchResult& result) const
{
	if (root == nullptr) return;

	result.m_accesses++;

	if (key == root->m_key)
	{
		result.m_indexList = root->m_indexList.get();
	}
	else if (key < root->m_key)
	{
		search(root->m_left, key, result);
	}
	else
	{
		search(root->m_right, key, result);
	}
}

template<typename Type>
inline void IndexTree<Type>::searchRange(const std::unique_ptr<IndexTreeNode<Type>>& root, Type key1, Type key2, ArrayList<IndexSearchResult>& results, int& accesses) const
{
	if (root == nullptr)
	{
		return;
	}

	accesses++;
	int currentAccs = accesses;

	if (root->m_key < key1)
	{
		searchRange(root->m_right, key1, key2, results, accesses);
	}
	else if (root->m_key == key1)
	{
		results.insert(IndexSearchResult(root->m_indexList.get(), currentAccs));
		searchRange(root->m_right, key1, key2, results, accesses);
	}
	else if (root->m_key > key1 && root->m_key < key2)
	{
		searchRange(root->m_left, key1, key2, results, accesses);
		results.insert(IndexSearchResult(root->m_indexList.get(), currentAccs));
		searchRange(root->m_right, key1, key2, results, accesses);
	}
	else if (root->m_key == key2)
	{

		searchRange(root->m_left, key1, key2, results, accesses);
		results.insert(IndexSearchResult(root->m_indexList.get(), currentAccs));
	}
	else if (root->m_key > key2)
	{
		searchRange(root->m_left, key1, key2, results, accesses);
	}
}

