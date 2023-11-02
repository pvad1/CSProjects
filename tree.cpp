#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <iostream>
#include <vector>
using namespace std;


vector<int> inorderTraversal(TreeNode* travNode,vector<int> nodeList);
vector<int>  PreorderTreewalk(TreeNode* travNode, vector<int> nodeList);
vector<int>  PostorderTreewalk(TreeNode* travNode, vector<int> nodeList);
TreeNode* createNewNode( int value);
TreeNode* findNode(TreeNode* startNode, int value);
TreeNode* FindYoungest(TreeNode* node);
void printValues(vector<int> nodeList);
void printHelper(TreeNode* root, string indent, bool last);
TreeNode* findNodetoReplaceRemoveNode (TreeNode* toBeDeletedNode);
void swapValues(TreeNode *u, TreeNode *v) ;





void printHelper(TreeNode* root, string indent, bool last) {
    if (root != NULL) {
      cout << indent;
      if (last) {
        cout << "R----";
        indent += "   ";
      } else {
        cout << "L----";
        indent += "|  ";
      }

      string sColor = root->nodeColor ? "BLACK" : "RED";
      cout << root->GetValue() << "(" << sColor << ")" << endl;
      printHelper(root->GetLeft(), indent, false);
      printHelper(root->GetRight(), indent, true);
    }
  }


void printValues(vector<int> nodeList) {
    for(int i = 0; i < nodeList.size()-1; i++) {
        cout << nodeList.at(i) << " ";
     }
    cout << nodeList.at(nodeList.size()-1);
}




void Tree::leftRotate(TreeNode* x){
// new parent will be node's right child
	TreeNode *nParent = x->rightChild;

	// update root if current node is root
	if (x == GetRoot())
	rootNode = nParent;

    x->moveDown(nParent);

	// connect x with new parent's left element
	x->rightChild = nParent->leftChild;
	// connect new parent's left element with node
	// if it is not null
	if (nParent->leftChild != NULL)
	    nParent->leftChild->parent = x;

	// connect new parent with x
	nParent->leftChild = x;

     /*
    TreeNode* y = tempnode->GetRight();
    if(y != NULL ) {
        tempnode->SetRight(y->GetLeft());
        if (y->GetLeft() != NULL) {
        y->GetLeft()->SetParent(tempnode);
        }
        y->SetParent(tempnode->GetParent());
    }
    if (tempnode->GetParent() == NULL) {
      rootNode = y;
    } else if (tempnode == tempnode->GetParent()->GetLeft()) {
      tempnode->GetParent()->SetLeft(y);
    } else {
      tempnode->GetParent()->SetRight(y);
    }
    if(y != NULL ) {
        y->SetLeft(tempnode);
        }

    tempnode->SetParent(y);
    */
}

void Tree::rightRotate(TreeNode* x) {

    // new parent will be node's left child
	TreeNode *nParent = x->leftChild;

	// update root if current node is root
	if (x == GetRoot())
	rootNode = nParent;

	x->moveDown(nParent);

	// connect x with new parent's right element
	x->leftChild = nParent->rightChild;
	// connect new parent's right element with node
	// if it is not null
	if (nParent->rightChild != NULL)
	    nParent->rightChild->parent = x;

	// connect new parent with x
	nParent->rightChild = x;

   /* TreeNode* y = node->GetLeft();
    node->SetLeft(y->GetRight());
    if (y->GetRight() != NULL) {
      y->GetRight()->SetParent(node);
    }
    y->SetParent(node->GetParent());
    if (node->GetParent() == NULL) {
      rootNode = y;
    } else if (node == node->GetParent()->GetRight()) {
      node->parent->SetRight(y);
    } else {
      node->parent->SetLeft(y);
    }
    y->SetRight(node);
    node->SetParent(y); */
}


TreeNode* FindYoungest(TreeNode* node){
    //checks if node is null or its child is null
    if(node == NULL || node->GetRight() == NULL){
        return NULL;
    }
    //traverse left side until smallest val is found
    TreeNode* youngest = node->GetRight();
    while(youngest->GetLeft() != NULL){
        youngest = youngest->GetLeft();
    }
    return youngest;
}
 

vector<int> inorderTraversal(TreeNode* travNode, vector<int> nodeList) {
    if(travNode != NULL){
      nodeList =  inorderTraversal(travNode->GetLeft(),nodeList);
       nodeList.push_back(travNode->GetValue());
       //nodeList->push_back(travNode->GetValue() );
        //cout << travNode->GetValue() ;
       nodeList = inorderTraversal(travNode->GetRight(),nodeList);
    } 
    return nodeList;
}

vector<int> PreorderTreeWalk(TreeNode* travNode, vector<int> nodeList){
        if(travNode != NULL){
       // cout << travNode->GetValue() << " ";
        nodeList.push_back(travNode->GetValue() );
       nodeList =  PreorderTreeWalk(travNode->GetLeft(),nodeList);
       nodeList =  PreorderTreeWalk(travNode->GetRight(),nodeList);
        }

    return nodeList;
}

vector<int> PostorderTreewalk(TreeNode* travNode,vector<int> nodeList){
    if(travNode != NULL){
       nodeList = PostorderTreewalk(travNode->GetLeft(),nodeList);
      nodeList =  PostorderTreewalk(travNode->GetRight(),nodeList);
         nodeList.push_back(travNode->GetValue() );
       // cout << travNode->GetValue() << " ";
        }
    return nodeList;
}
//method to  find node by value by R
TreeNode* findNode(TreeNode* startNode, int value){
        if(startNode == NULL){
            return NULL;
        }
        if(startNode->GetValue() == value ){
            return startNode;
        }
        TreeNode*  fvar;
        if(startNode->GetValue() > value ){
            fvar = findNode(startNode->GetLeft(), value);
        }
        else{
            fvar = findNode(startNode->GetRight(), value);
        }
    return fvar;
}
void Tree::SetRoot(TreeNode* root){
    rootNode = root;
 }

Tree::Tree() {
    rootNode = NULL;
}

Tree::~Tree(){
   // set all the right/left child to null;

}

// Returns the root of the tree.
TreeNode* Tree::GetRoot(){
    if(rootNode == NULL){
        return NULL;
    }
    return rootNode;
}



// Adds the value to the tree.
void Tree::AddValue(int value){
    TreeNode*  newtttt = createNewNode(value);
    TreeNode* currentNode = GetRoot();
    TreeNode* y = NULL;
     /// insert here 
    while (currentNode != NULL) {
        y = currentNode;
        if (newtttt->GetValue() < currentNode->GetValue()) {
            currentNode =currentNode->GetLeft();
        } else {
            currentNode =currentNode->GetRight();
        }
    }
    newtttt->SetParent(y);
    if (y == NULL) {
      rootNode = newtttt;
    } else if (newtttt->GetValue() < y->GetValue()) {
      y->SetLeft(newtttt);
    } else {
      y->SetRight(newtttt);
    }

    if (newtttt->GetParent() == NULL) {
      newtttt->SetColor(true);
      return;
    }

    if (newtttt->GetParent()->GetParent() == NULL) {
      return;
    }

    // Fix RB-Insert-Fixup(T,z)
     while(newtttt->GetParent() && (newtttt->GetParent()->nodeColor == false)) { // true is black 
        TreeNode* uncle;
        TreeNode* grandParent = newtttt->GetParent()->GetParent();
       //Case-I: Current Node's parent is the right child of the Grandparent 
        // and if the uncle color is red, set uncle and current node parent color to black
        // grandparent to red, and grandparent is the current node
        if(newtttt->GetParent() == grandParent->GetRight()) {
            uncle = grandParent->GetLeft(); // when uncle is a left child 
            if(uncle !=NULL && uncle->nodeColor == false) {
                uncle->nodeColor = true;
                newtttt->GetParent()->SetColor(true);
                grandParent->SetColor(false);
                newtttt = grandParent;
            } else {
                //Case II: new node is the left child of the parent, then rightRotate
                if(newtttt == newtttt->GetParent()->GetLeft()) {
                    newtttt = newtttt->GetParent();
                    rightRotate(newtttt);
                }
                newtttt->GetParent()->SetColor(true);
                newtttt->GetParent()->GetParent()->SetColor(false);
                leftRotate( newtttt->GetParent()->GetParent());

            }

        } else {
            uncle = grandParent->GetRight(); //when uncle is a right child 
            if(uncle->nodeColor == false) {
                uncle->nodeColor = true;
                newtttt->GetParent()->SetColor(true);
                grandParent->SetColor(false);
                newtttt = grandParent;
            }else {
                if(newtttt == newtttt->GetParent()->GetRight()) {
                    newtttt = newtttt->GetParent();
                    leftRotate(newtttt);
                }
                newtttt->GetParent()->SetColor(true);
                newtttt->GetParent()->GetParent()->SetColor(false);
                rightRotate(newtttt->GetParent()->GetParent());
            }

        }
        if(newtttt == GetRoot()) {
            break;
        }

  }

  GetRoot()->SetColor(true);
}

// Returns the node with the specified value.
TreeNode* Tree::GetNode(int value){
     TreeNode* rootex = GetRoot();
     if(rootex == NULL) {
        return NULL;
    }
     rootex = findNode(rootex,value);
     if(rootex == NULL){
        return NULL;
     }
 return rootex;
}

/**
 * Helper method to swap, the node to be deleted aNode with one of its non empty child oneChild.
*/
void Tree::swapNode(TreeNode* aNode, TreeNode* oneChild) {
    if(aNode->GetParent() == NULL ) {
        rootNode = oneChild;
    } else if (aNode == aNode->GetParent()->GetLeft()) { // is the aNode the left child, swap that aNode with left child
        aNode->GetParent()->SetLeft(oneChild);
    } else { // is the aNode the right child, swap that aNode with right child, swap that aNode with right child
        aNode->GetParent()->SetRight(oneChild);
    }
    if( oneChild != NULL )
        oneChild->parent = aNode->parent; // update the parent of the child to the aNode's parent
}

/**
 * Node to replaced by 
*/
TreeNode* findNodetoReplaceRemoveNode (TreeNode* toBeDeletedNode) {
    if(toBeDeletedNode->GetLeft() != NULL && toBeDeletedNode->GetRight() !=NULL) {
        TreeNode *temp = toBeDeletedNode; 
        while (temp->GetLeft() != NULL) { //find the left most node
            temp = temp->GetLeft();
        }
        return temp;       
    }

    // leaves nodes are Null 
    if (toBeDeletedNode->GetLeft() == NULL and toBeDeletedNode->GetRight() == NULL)
      return NULL;

    // has atleast 1 child
    if (toBeDeletedNode->GetLeft() != NULL)
      return toBeDeletedNode->GetLeft() ;
    else
      return toBeDeletedNode->GetRight();

}

// Removes the node with the specified value.
void Tree::RemoveNode(int value){
     if(GetRoot() == NULL ) {
        return ; // empty tree
    }
    TreeNode* removalNode = findNode(GetRoot(), value);
     if(removalNode == NULL) {
        return; //did not find the value 
    }
    RemoveNode(removalNode);
}

void Tree::RemoveNode(TreeNode* removalNode){

    TreeNode* replacedBy = findNodetoReplaceRemoveNode(removalNode);

    bool replacedAndRemovalNodeBothBlack = (replacedBy == NULL or replacedBy->nodeColor) and (removalNode->nodeColor);
    TreeNode*  parent =removalNode->GetParent();
    if (replacedBy == NULL) {
        // replacedBy is NULL therefore removalNode is leaf
        if(removalNode == GetRoot()) {
            rootNode = NULL;
        } else {
            if(replacedAndRemovalNodeBothBlack) {
                //replacedBy and removalNode(leaf) both black fix double black at removalNode
                rebalanceDeleteNode(removalNode);
            } else {
                //replacedBy or removalNode is red
                if (removalNode->GetSibling() != NULL) {
                    // sibling is not null, make it red"
                    removalNode->GetSibling()->SetColor(false);
                }
                // delete v from the tree 
                if(parent != NULL ) {
                     if (removalNode == parent->GetLeft()) {
                        parent->SetLeft(NULL);
                    } else {
                        parent->SetRight(NULL);
                    }
                }  
            }
            //if(parent == GetRoot()) {
                if (removalNode == parent->GetLeft()) {
                    parent->SetLeft(NULL);
                } else {
                    parent->SetRight(NULL);
                }
            //}
           
            delete removalNode;
            return;
        }
    }
    if (removalNode->GetLeft() == NULL or removalNode->GetRight() == NULL) {
	// v has 1 child
	if (removalNode == GetRoot()) {
		// removalNode is root, assign the value of replacedBy to removalNode, and delete replacedBy
		removalNode->nodeValue = replacedBy->nodeValue;
		removalNode->leftChild = removalNode->rightChild = NULL;
		delete replacedBy;
	} else {
		// Detach removalNode from tree and move replacedBy up
		if (removalNode->isOnLeft()) {
		    parent->leftChild = replacedBy;
		} else {
            if(parent != NULL )
		        parent->rightChild = replacedBy;
		}
		delete removalNode;
        if(replacedBy != NULL )
		    replacedBy->parent = parent;
		if (replacedAndRemovalNodeBothBlack) {
		// u and v both black, fix double black at u
		rebalanceDeleteNode(replacedBy);
		} else {
		// u or v red, color u black
         if(replacedBy != NULL )
		    replacedBy->nodeColor = true;
		}
	}
	return;
	}

	// v has 2 children, swap values with successor and recurse
	swapValues(replacedBy, removalNode);
	RemoveNode(replacedBy);

}

void swapValues(TreeNode *u, TreeNode *v) {
	int temp;
	temp = u->nodeValue;
	u->nodeValue = v->nodeValue;
	v->nodeValue = temp;
}

/***
 * helper method to rebalance a subtree, after its parent is delted
*/
void Tree::rebalanceDeleteNode(TreeNode* nodetoFix) {
    if (nodetoFix == GetRoot())
      // Reached root
      return;
    TreeNode *sibling = nodetoFix->GetSibling(), *parent = nodetoFix->GetParent();
    if (sibling == NULL) {
      // No sibiling, double black pushed up
      rebalanceDeleteNode(parent);
    } else {
        if (!sibling->nodeColor) {
            // Sibling red
            parent->nodeColor = false;
            sibling->nodeColor = true;
            if (sibling->isOnLeft()) {
                // left case
                rightRotate(parent);
            } else {
            // right case
                leftRotate(parent);
            }
            rebalanceDeleteNode(nodetoFix);
	    } else {
            	// Sibling black
		if (sibling->hasRedChild()) {
		// at least 1 red children
		if (sibling->GetLeft() != NULL and !sibling->GetLeft()->nodeColor) {
			if (sibling->isOnLeft()) {
			// left left
			sibling->GetLeft()->nodeColor= sibling->nodeColor;
			sibling->nodeColor = parent->nodeColor;
			rightRotate(parent);
			} else {
			// right left
			sibling->GetLeft()->nodeColor = parent->nodeColor;
			rightRotate(sibling);
			leftRotate(parent);
			}
		} else {
			if (sibling->isOnLeft()) {
			// left right
			sibling->GetRight()->nodeColor = parent->nodeColor;
			leftRotate(sibling);
			rightRotate(parent);
			} else {
			// right right
			sibling->GetRight()->nodeColor = sibling->nodeColor;
			sibling->nodeColor = parent->nodeColor;
			leftRotate(parent);
			}
		}
		parent->nodeColor = true;
		} else {
		// 2 black children
		sibling->nodeColor = false; //REDs
		if (parent->nodeColor)
			rebalanceDeleteNode(parent);
		else
			parent->nodeColor = true;
		}
        }        
    }

}


/**
 * Create a new node with default color as red and parent, children as NULL
*/
TreeNode* createNewNode( int value) {
    TreeNode* temp = new TreeNode();
    temp->SetValue(value);
    temp->SetColor(false);  // set color as red default
    temp->SetLeft(NULL);
    temp->SetRight(NULL);
    temp->SetParent(NULL);
    return temp;
}

// Prints the list of values from the tree, using the specified order.
void Tree::PrintTreeWalk(int orderNumber){
      //Cout
 /* if (GetRoot()) {
      printHelper(this->GetRoot(), "", true);
    }*/

    switch(orderNumber){

        case 1: {
            // Inorder tree walk
            if(rootNode != NULL){
                vector<int> nodeList;
                nodeList= inorderTraversal(rootNode,nodeList);
                printValues(nodeList);
            } 
            break;
        }
       case 2: {
            //Preorder tree walk
            vector<int> nodeList;
            if(rootNode != NULL){
               nodeList = PreorderTreeWalk(rootNode,nodeList);
                printValues(nodeList);
            } 
            break;
       }
       case 3: {
            //Postorder tree walk
             vector<int> nodeList;
            if(rootNode != NULL){
              nodeList = PostorderTreewalk(rootNode,nodeList);
                printValues(nodeList);
            }
            break;
       }
       
       default: {
        break;
       }

    }
}