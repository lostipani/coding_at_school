/*
Binary search tree

argv: number of nodes, each node with a random integer

provide print out of ordered elements as visited
 
*/

#include<cstdlib>
#include<iostream>
#include<new>

class node{
	public:
		unsigned int key;
		node* left;
		node* right;

		node(unsigned int key):
			key(key), left(nullptr), right(nullptr)
			{}
};

void ins(node* &p, unsigned int val){
	if (p == nullptr)
		p = new node {val};
	else
		(val <= p->key) ? ins(p->left, val) : ins(p->right, val);
}

void show(node* p){
	if (p != nullptr){
		if (p->left != nullptr)
			show(p->left);
		std::cout << p->key << std::endl;

		if (p->right != nullptr)
			show(p->right);
	}
	else
		std::cout << "empty tree" << std::endl;
}

int main(int argc, char **argv){
	const unsigned int MAX  = 100;
	const unsigned int MIN  = 10;
	const unsigned int seed = 0; 
	
	unsigned int N = std::stoi(argv[1]);

	if (N>0){
		srand(seed);
		node* root = nullptr;

		for(int i=0; i<N; i++)
			ins(root, rand()%(MAX-MIN+1)+MIN);

		show(root);

		delete root;
	}
	
	return 0;
}
