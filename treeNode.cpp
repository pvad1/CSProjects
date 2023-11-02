#include <stdio.h>
#include <stdlib.h>
#include "treeNode.h"
#include <iostream>
using namespace std;


TreeNode::TreeNode() {
	nodeColor=false;
	parent= NULL;
	leftChild=NULL;
	rightChild=NULL;
}
/**
 * Method to implement desructor
*/
TreeNode::~TreeNode() {
	parent= NULL;
	leftChild=NULL;
	rightChild=NULL;

}

int TreeNode::GetValue(){
	return nodeValue;
}

void TreeNode::SetValue(int value) {
	nodeValue = value;
}

	// Sets the color of the node.
void TreeNode::SetColor(bool isBlack){
	if(isBlack){
		nodeColor = true;
	} else {
		nodeColor = false;
	}

}

	// Returns the parent of the node.
TreeNode* TreeNode::GetParent(){
	return parent;
}

	// Returns the left of the node.
TreeNode* TreeNode::GetLeft(){
	return leftChild;
}

	// Returns the right of the node.
TreeNode* TreeNode::GetRight(){
	return rightChild;
}

// Returns the parent of the node.
void TreeNode::SetParent(TreeNode* addParent) {
	parent = addParent;
}

// Returns the left of the node.
void TreeNode::SetLeft( TreeNode* addLeft) {
	leftChild = addLeft;
}

// Returns the right of the node.
void TreeNode::SetRight(TreeNode* addRight) {
	rightChild = addRight;
}

TreeNode* TreeNode::GetSibling(){
	if( parent == NULL )  {
		return NULL;
	}
	if(GetParent()->GetLeft() == this) {
		return GetParent()->GetRight();
	}
	return GetParent()->GetLeft();
}

bool TreeNode::isOnLeft() {
	if( parent == NULL )  {
		return false;
	}
	if(this == parent->GetLeft()){
		return true;
	}
	return false;
}

bool TreeNode::hasRedChild() {
	
	return (GetLeft()!= NULL and (!GetLeft()->nodeColor)) or
		(GetRight() != NULL and (!GetRight()->nodeColor));
}

// moves node down and moves given node in its place
void TreeNode::moveDown(TreeNode *nParent) {
	if (parent != NULL) {
	if (isOnLeft()) {
		parent->leftChild = nParent;
	} else {
		parent->rightChild = nParent;
	}
	}
	nParent->parent = parent;
	parent = nParent;
}


