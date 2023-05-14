/*

   Tree class
   with Node class

*/

#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

const int MAX = 1;
const int MIN = 0;


/* class of nodes */
class Node{
	int key;
	int level;
	Node* left;
	Node* right;
	
	public:
		Node(){
			key   = 0;
			level = 0;
			left  = nullptr;
			right = nullptr;
		}
		
		Node(int val, int _level, Node* _left, Node* _right){
			key   = val;
			level = _level;
			left  = _left;
			right = _right;
		}
		
		void makeNodes(int n);
		void showNodes(int n);
		friend bool compareNodes(Node* a, Node* b);
};

void Node::makeNodes(int n){
	if(n>0){
		Node* LL = new Node{rand()%(MAX-MIN+1) + MIN, n, nullptr, nullptr};
		Node* RR = new Node{rand()%(MAX-MIN+1) + MIN, n, nullptr, nullptr};
		left = LL;
		right = RR;
		
		left->makeNodes(n-1);
		right->makeNodes(n-1);
	}
}

void Node::showNodes(int n){
	if(n>0){
		left->showNodes(n-1);
		right->showNodes(n-1);
	}
	cout << "level: " << this->level << " key = " << this->key << endl;
}

bool compareNodes(Node* a, Node* b){
	if((a == nullptr) && (b == nullptr))
		return true;
	if ((a == nullptr) || (b == nullptr))
		return false;
	else
		return ((a->key == b->key) && compareNodes(a->left, b->left) && compareNodes(a->right, b->right));
}



/* Class: binary tree */
class BinTree{
	
	protected:
		Node *root = nullptr;
		int depth, seed;
		
	public:			
		BinTree(){
			depth = 0;
			root  = nullptr;
		}
		
		BinTree(int d, int s): depth(d), seed(s){
			srand(seed);
			root  = new Node {rand()%(MAX-MIN+1) + MIN, 0, nullptr, nullptr};
			root->makeNodes(depth);
		}
		
		void showTree(){
			root->showNodes(depth);
		}
		
		friend bool operator== (BinTree &x, BinTree &y); 
};

// def. of comparison operator
bool operator== (BinTree &x, BinTree &y){
	if((x.root == nullptr) && (y.root == nullptr))
		return true;
	else
		return compareNodes(x.root,y.root);
}


int main(){
	BinTree lemon {2,2};
	BinTree peach {2,2};

	cout << "\n Lemon tree:" << endl;
	lemon.showTree();
	
	cout << "\n Peach tree:" << endl;
	peach.showTree();
	
	if (lemon == peach)
		cout << "lemon tastes like peach" << endl;
	else
		cout << "lemon trees can't be peach trees" << endl;
		
}
