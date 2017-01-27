//StringBST.h
//COMP 11 HW 4
//By Rebecca Redelmeier
//Date: October 28, 2016
//Purpose: Header file for StringBST class. Builds and uses a tree of TreeNodes
//         that contains srrings and the number of times that the string has 
//         been added to the tree.

#include<string>

using namespace std;

class StringBST 
{
	public:
		StringBST(); //default constructor

		StringBST(string[], int); //overloaded constructor	

		~StringBST(); //default destructor

		bool isEmpty(); //returns if tree is empty or not

		void clear(); //clears the tree

		int size(); //returns size of the tree

                void print(); //prints tree in order

                void add(string); //adds a string to the BST

                bool remove(string); //removes a string from the BST

		string getMin(); //returns minimum string

		string getMax(); //returns largest string

		void removeMin(); //removes min string from tree

		void removeMax(); //removes minimum string from tree

		bool contains(string); //returns if passed string is in tree


	private:
                int num_nodes;

                struct TreeNode {
			string s;
			int times_added;
			TreeNode *left;
			TreeNode *right;
		};

		TreeNode *root;

		TreeNode* newNode(string); //builds new node

		void deleteTree(TreeNode*); //deletes every node from tree

		void printInOrder(TreeNode*); //print helper

                void addHelper(TreeNode*, string); 

                TreeNode* removeHelper(TreeNode*, string);

                bool decrement(TreeNode*, string); //returns whether Node can
                                                   //be decremented
                                                   //(num_elements > ) and 
                                                   //decrements if so

                TreeNode* getMinNode(TreeNode*);

                TreeNode* getMaxNode(TreeNode*);

                bool containsHelper(TreeNode*, string);

                TreeNode* parent(TreeNode*, string); //returns parent to passed
                                                     //in string
                
                int crash(string); //throws runtime error with passed in 
                                   //message
};
