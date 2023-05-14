/*
Static vs Dynamic allocation
comparison between arrays and lists
*/

#include<iostream>

struct Nodo{
	int val;
	Nodo* next; // necessario e sufficiente
	
	// costruttore per inizializzare gli attributi.		
	Nodo(int _val): val(_val), next(nullptr){}

};

void push_heap(Nodo* &p, int _val){
	Nodo* cur = new Nodo {_val}; // allocazione dinamica nella heap
	if (p != nullptr)
		cur->next = p;
	p = cur;
}

void push_stack(Nodo* &p, int _val){
	Nodo ncur {_val}; // this is automatic allocation, ncur falls out of scope of void block
	Nodo* cur = &ncur; // this is automatic allocation, cur (pointer) falls out of scope of void block 
	if (p != nullptr)
		cur->next = p;
	p = cur;
} // ncur is deallocated, hence p points to an address (referring to... nothing)

void iter(Nodo* p){
	if (p == nullptr)
		std::cout << "empty list" << std::endl;
	else{
		Nodo* it = p;
		while(it != nullptr){
			std::cout << it << " : " << it->val << std::endl;
			it = it->next;
		}
	}
}


int main(){
	
	/* sizeof */
	std::cout << "sizeof(node)=" << sizeof(Nodo) << std::endl;
	std::cout << "sizeof(int)=" << sizeof(int) << std::endl;
	
	/* ARRAY */
	int v[5] = {0,1,2,3,4};
	std::cout << "Array of 5 int, static allocation: " << std::endl;
	for(size_t i=0; i!=5; i++)
		std::cout << (v+i) << " : " << *(v+i) << std::endl;

	
	/* LIST */
	std::cout << "List of struct node, dynamic allocation: " << std::endl;
	Nodo* head = nullptr; // qui e' una lista vuota
	iter(head);
	push_heap(head, (int) 4);
	push_heap(head, (int) 3);
	push_heap(head, (int) 2);
	push_heap(head, (int) 1);
	push_heap(head, (int) 0);
	push_stack(head, (int) -1);
	iter(head);  // if push_stack is invoked before, this gives infinite loop since head points to nothing allocated and tmp->next is not accessible so equals to tmp itself
}
