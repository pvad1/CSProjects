#ifndef TREE_NODE_H
#define TREE_NODE_H

// Defines a node of a tree.
class TreeNode {
public:
	int nodeValue;
	bool nodeColor;
	TreeNode* parent;
	TreeNode* leftChild;
	TreeNode* rightChild;

	// Constructor/Destructor for Tree.
	TreeNode();
	~TreeNode();

	// Returns the value of the node.
	int GetValue();

	// Sets the value of the node.
	void SetValue(int value);

	// Sets the color of the node.
	void SetColor(bool isBlack);

	// Returns the parent of the node.
	TreeNode* GetParent();

	// Returns the left of the node.
	TreeNode* GetLeft();

	// Returns the right of the node.
	TreeNode* GetRight();

	// Returns the parent of the node.
	void SetParent(TreeNode* addParent);

	// Returns the left of the node.
	void SetLeft(TreeNode* addLeft);

	// Returns the right of the node.
	void SetRight(TreeNode* addRight);

	// Returns sibling.
	TreeNode* GetSibling();

	bool isOnLeft();

	bool hasRedChild();

	void moveDown(TreeNode *nParent);

};
#endif

