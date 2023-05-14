/*
Binary tree: make and visit
*/


#include<iostream>
#include<cstdlib>
#include<new>


// PRNG
const int MAX {20};
const int MIN {1};
const unsigned int SEED {0};
unsigned int rnd(void){
	return (unsigned int) rand()%(MAX-MIN+1) + MIN;
}

// input
int inp(const char *t){
	int x;
	std::cout << t << std::endl;
	std::cin >> x;
	return x;
}


// def node class
class Node{	
	public:	int key, level;
	public:	Node *left, *right;
		
	public:	Node(int k, int d): key(k), level(d), left(nullptr), right(nullptr) {}
};

// prototypes of routines
bool makeTree(Node*, int);
void showTree(Node*);
//void findKey(Node*, int, bool&);
int findKey(Node*, int, bool&);
void cutTree(Node*);
int sum(Node*);

int main(){
	
	srand(SEED);

	int num, depth;
	bool found = false;
	
	// make a tree
	Node* root = new Node(rnd(), inp("insert depth of tree"));	
	if (makeTree(root, root->level-1))
		std::cout << "tree successfully generated" << std::endl;

	// show tree
	showTree(root);
	
	// search key
	if(!findKey(root, inp("insert number to find"), found))
		std::cout << "value not found" << std::endl;

	// sum
	std::cout << "Sum over keys = " << sum(root) << std::endl;
	
	// cut tree
	std::cout << "cut tree" << std::endl;
	cutTree(root);
	showTree(root);

}

/* function definitions */
bool makeTree(Node* p, int n){
	try{
		if(n>0){
			p->left  = new Node(rnd(), n);
			p->right = new Node(rnd(), n);
			
			return makeTree(p->left, n-1) && makeTree(p->right, n-1);
		}
		else{ return true; }
	}
	catch(...){ return false; }
}

void showTree(Node* p){
	if(p != nullptr){
		std::cout << "level: " << p->level << " key = " << p->key << "\t address: node = " << p << "\t left = "<< p->left << "\t right = " << p->right << std::endl;
		showTree(p->left);
		showTree(p->right);
	}

}

void cutTree(Node* p){
	if (p != nullptr){
		if (p->left != nullptr){
			if (p->left->left == nullptr && p->left->right == nullptr){
				delete p->left;
				p->left = nullptr;
			}
			else
				cutTree(p->left);
		}
		if (p->right != nullptr){
			if (p->right->left == nullptr && p->right->right == nullptr){
				delete p->right;
				p->right = nullptr;
			}
			else
				cutTree(p->right);
		}
		p->level--;		
	}	
}

int sum(Node* p){
	if (p != nullptr)
		return p->key + sum(p->left) + sum(p->right);
	else
		return 0;
}


int findKey(Node* p, int val, bool& found){
        if (p != nullptr && !found){
		if (found = p->key == val){
			std::cout << "Key found in level: " << p->level << std::endl;
			return p->level;
		}
		else { return findKey(p->left, val, found) + findKey(p->right, val, found); }
        }
	else { return 0; } 
}

/*
void findKey(Node* p, int val, bool& found){
        if (p != nullptr){
                if (!found){
                        if (found = p->key == val)
                                std::cout << "Key found in level: " << p->level << std::endl;

                        findKey(p->left, val, found);
                        findKey(p->right, val, found);
                }
        }
}
*/
