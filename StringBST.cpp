//StringBST.cpp
//COMP 11 HW 4
//By Rebecca Redelmeier
//Date: October 28, 2016
//Purpose: Implementation of StingBST class. Builds and uses a 
//	   tree of TreeNodes that contains strings and the number of times
//	   that the string has been added to the tree

#include<string>
#include<iostream>
#include"StringBST.h"

using namespace std;

////////////////////////////////////
//////////PUBLIC FUNCTIONS//////////
////////////////////////////////////

//Purpose: default constructor
//Arguments: none
//Returns: none
StringBST::StringBST()
{
	num_nodes = 0;
	root = NULL;
}

//Purpose: overloded constructor
//Arguments: string array, int
//Returns: none
StringBST::StringBST(string array[], int num)
{
        root = NULL;
        num_nodes = 0;

        for (int i = 0; i < num; i++)
                add(array[i]);
}

//Purpose: default destructor. Recycles/deletes all allocated memory
//Arguments: none
//Returns: none
StringBST::~StringBST()
{
	clear();
}

//Purpose: returns if tree is empty or not
//Arguments: none
//Returns: bool
bool StringBST::isEmpty()
{
	if (root == NULL)
		return true;

	return false;
}

//Purpose: clears tree, deletes all nodes
//Arguments: none
//Returns: none
void StringBST::clear()
{
        while (root != NULL) {
	        deleteTree(root);
	        root = NULL;
        }
}

//Purpose: returns the number of nodes in the tree
//Arguments: none
//Returns: int
int StringBST::size()
{
	return num_nodes;
}

//Purpose: prints the tree out for debugging
//Arguments: none
//Returns: none
void StringBST::print()
{
	printInOrder(root);
}

//Purpose: adds a string to the tree
//Arguments: string
//Returns: none
void StringBST::add(string to_add) 
{
        addHelper(root, to_add);
}

//Purpose: removes a string from the tree
//Arguments: string
//Returns: bool
bool StringBST::remove (string to_remove)
{
        if (!contains(to_remove))
                return false;
        if (decrement(root, to_remove))
                return true;
        num_nodes--; 
        removeHelper(root, to_remove);
        return true;
}

//Purpose: return min string in tree
//Arguments: none
//Returns: string
string StringBST::getMin()
{
        if (isEmpty())
                crash("getMin:empty_tree");
        
        return getMinNode(root)->s;
}

//Purpose: returns max string in tree
//Arguments: none
//Returns: string
string StringBST::getMax()
{
        if (isEmpty())
                crash("getMax:empty_tree");
        
        return getMaxNode(root)->s;
}

//Purpose: removes the min string from tree
//Arguments: none
//Returns: none
void StringBST::removeMin()
{
        remove(getMin());
}

//Purpose: removes the max string from the tree
//Arguments: none
//Returns: none
void StringBST::removeMax()
{
        remove(getMax());
}

//Purpose: returns whether or not the tree contains passed in string
//Arguments: string
//Returns: bool
bool StringBST::contains(string in)
{
        return containsHelper(root, in);
}

/////////////////////////////////////
//////////PRIVATE FUNCTIONS//////////
/////////////////////////////////////

//Purpose: creates a new node in the tree
//Arguments: string
//Returns: pointer to a TreeNode
StringBST::TreeNode* StringBST::newNode(string data)
{
	TreeNode *new_node = new TreeNode;
	new_node->s = data;
	new_node->times_added = 1;
	new_node->left = NULL;
	new_node->right = NULL;

	num_nodes++;

	return new_node;
}

//Purpose: helper function delete every node from the tree
//Arguments: treeNode pointer
//Returns: none
//source: http://stackoverflow.com/questions/8062080/
//		  deleting-the-entire-binary-search-tree-at-once
void StringBST::deleteTree(TreeNode *root)
{
	if (root->left != NULL)
		deleteTree(root->left);
	
	if (root->right != NULL)
		deleteTree(root->right);
	
	delete root;
        root = NULL;

}

//Purpose: helper function to print tree in order for debugging purposes
//Arguments: TreeNode pointer
//Returns: none 
void StringBST::printInOrder(TreeNode *curr)
{
	if (curr == NULL) {
                cout << "[]";
		return;
        }
        if (curr != NULL) {
	        cout << "[";
	        printInOrder(curr->left); 
	        cout  << " " << curr->s << " " << curr->times_added << " ";
	        printInOrder(curr->right);
	        cout << "]";
        }
}

//Purpose: helper function to add a node to the tree
//Arguments: pointer to the address to a TreeNode, string
//Returns: none
//source: http://www.cplusplus.com/forum/general/102887/
void StringBST::addHelper(TreeNode *curr, string to_add)
{
        if (root == NULL)
                root = newNode(to_add);

        else if (to_add < curr->s) {
                if (curr->left != NULL)
                        addHelper(curr->left, to_add);

                else 
                        curr->left = newNode(to_add);
        }
        else if (to_add > curr->s) {
                if (curr->right != NULL)
                        addHelper(curr->right, to_add);
                else 
                        curr->right = newNode(to_add);
        }
        else 
                curr->times_added++;
}

//Purpose: helper function to remove a node from the tree
//Arguments: TreeNode pointer, string
//Returns: TreeNode pointer
//source help: http://www.algolist.net/Data_structures/Binary_search_tree/
//             Removal
StringBST::TreeNode* StringBST::removeHelper(TreeNode *curr, string to_remove)
{
        //recursively interate through tree to find the node with the string
        //to be removed
        if (to_remove < curr->s) { //if to_remove is smaller, go left
                if (curr->left != NULL)
                        return removeHelper(curr->left, to_remove);
                else 
                        return NULL;
        } else if (to_remove > curr->s) { //if to_remove is larger, go right
                if (curr -> right != NULL)
                        return removeHelper(curr->right, to_remove);
                else
                        return NULL;
        }

        //once node is found, remove it
        else {
               TreeNode* nodeParent = parent(root, to_remove); //get pointer to
                                                               //parent node
               //corner case: trying to remove the root
               if (curr->s == root->s) {
                       if (curr->left == NULL and curr->right == NULL) { 
                               root = NULL;
                       }
                       else if (curr->left == NULL)
                               root = curr->right;
                       else {
                               root = curr->left;
                        }
               }

               //trying to remove either a leaf or a node with no right child.
               //set the parent pointer that points to to_remove to to_remove's
               //l child. if left child is NULL (is a leaf), the parent pointer
               //will point to NULL.
               else if (curr->right == NULL) {
                      if (nodeParent->left != NULL and 
                                      nodeParent->left->s == to_remove)
                            nodeParent->left = curr->left;
                      else {
                            nodeParent->right = curr->left;
                      }
                      delete curr;
               }

               //trying to remove a node with no left child. Set parent pointer
               //that points to to_remove to to_remove's right child.
               else if (curr->left == NULL) {
                      if (nodeParent->left != NULL and 
                                      nodeParent->left->s == to_remove)
                            nodeParent->left = curr->right;
                      else
                            nodeParent->right = curr->right;
                      delete curr;        
              }

              //tring to remove a node with 2 children. Find the node's
              //predecessor (largest node in it's right tree) and save that
              //data in a temp. Then call delete on this node. Then replace
              //to_remove with the temp's data. This restores the invarient.
              else {
                      TreeNode temp;
                      temp.s = getMinNode(curr->right)->s;
                      temp.times_added = getMinNode(curr->right)->times_added;
                      removeHelper(curr->right, temp.s);
                      curr->s = temp.s;
                      curr->times_added = temp.times_added;
              }
              return NULL;
        }
}

//Purpose: returns whether or not string has > 1 times_added and therefore
//         can be decremented instead of removes. Does this decrementing.
//Arguments: TreeNode pointer, string
//Returns: bool
bool StringBST::decrement(TreeNode* curr, string to_find)
{
        if (curr == NULL)
                return false;

        if (curr->s > to_find)
                decrement(curr->left, to_find);

        else if (curr->s < to_find)
                decrement(curr->right, to_find);
 
        else {
                if (curr -> times_added > 1) {
                curr->times_added--;
                return true;
                }
        } 
        return false;
}

//Purpse: returns pointer to minimum node
//Arguments: TreeNode pointer
//Returns: TreeNode pointer
//source: http://code.runnable.com/VUTjJDME6nRv_HOe/
//        delete-node-from-bst-for-c%2B%2B
StringBST::TreeNode* StringBST::getMinNode(TreeNode *curr)
{
        if (curr == NULL)
                return NULL;

        else if (curr->left == NULL)
                return curr;

        return getMinNode(curr->left);
}

//Purpose: returns pointer to max node
//Arguments: TreeNode pointer
//Returns: TreeNode pointer
StringBST::TreeNode* StringBST::getMaxNode(TreeNode *curr)
{
        if (curr == NULL)
                return NULL;

        else if (curr->right == NULL) {
                return curr;
        }
        else
                return getMaxNode(curr->right);
}

//Purpose: helper function returns if the tree contains a passed in node or not
//Arguments: TreeNode pointer, string
//Returns: bool
bool StringBST::containsHelper(TreeNode *curr, string in)
{
        if (curr == NULL)
                return false;

        if (in > curr->s)
                return containsHelper(curr->right, in);

        if (in < curr->s)
                return containsHelper(curr->left, in);
 
        return true;
}

//Purpose: finds the parent of a passed in string
//Arguments: TreeNode*, string
//Returns: TreeNode*
StringBST::TreeNode* StringBST::parent(TreeNode *curr, string child)
{
        //corner case: string is the root node
        //base case: iterated through entire tree without finding the child
        if (curr == NULL or child == root->s) 
                return NULL;

        //curr points to child somehow, return curr
        else if ((curr->right != NULL and curr->right->s == child) or 
                        (curr->left != NULL and curr->left->s == child)) {
                return curr;
        }

        //curr is larger than child, recursively call parent on curr->left
        else if (curr->s > child) {
                return parent(curr->left, child);
        }

        //curr is smaller than child, recursively call parent on curr->right
        else {
                return parent(curr->right, child);
        }
}

int StringBST::crash(string error)
{
        throw runtime_error(error);
        
        return 0;
}
        

