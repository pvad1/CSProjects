#ifndef TREE_H
#define TREE_H

#include "treeNode.h"

// Defines a binary tree.
class Tree {

private: 
	TreeNode *rootNode;

public:
	// Constructor/Destructor for Tree.
	Tree();
	~Tree();

	// Returns the root of the tree.
	TreeNode* GetRoot();

	// Returns the root of the tree.
	void SetRoot(TreeNode* root);

	// Adds the value to the tree.
	void AddValue(int value);

	// Returns the node with the specified value.
	TreeNode* GetNode(int value);

	// Removes the node with the specified value.
	void RemoveNode(int value);

	// Prints the list of values from the tree, using the specified order.
	void PrintTreeWalk(int orderNumber);

	void rightRotate(TreeNode* node);
	void leftRotate(TreeNode* tempnode);
	void swapNode(TreeNode* aNode, TreeNode* oneChild);
	void rebalanceDeleteNode(TreeNode* nodetoFix);
	void RemoveNode(TreeNode* removalNode);
};

#endif
