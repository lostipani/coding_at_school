/*
 * A proper implementation of abstract class
 *
 * through a pure virtual function: virtual type name (params) =0;
 * that _has to_ be implemented in the derived class by overriding
 */

#include<iostream>
using namespace std;

class A{
	protected: int val; 
	public:
		A(int x): val(x) {}
 		virtual void print(void) =0;
};

class B: public A{
	public:
		B(int x): A(x) {}
		void print() { cout<< this->val <<endl; }
};

int main(int argc, char** argv){
     	A *a = new B {1};
	B *b = new B {2};
	a->print();
	b->print();

     return 0;
}
