#include<iostream>
#include<cstdlib>
#include<string>
#include<list>
#include<map>
#include<new>

/* Product
abstract product to be sold
*/
class Product{
	
	int id;
	
	public:
		std::string name;
		float price;
		int qty;

		Product(const char*, float, int);
		int getId(void);
};


Product::Product(const char* n, float p, int q){
	name  = std::string(n);
	price = p;
	qty   = q;
	id    = rand();
}
	
int Product::getId(void){
	return id;
}

/* Warehouse
to accommodate stock implemented as map
*/
class Warehouse{

	int size;
	std::map <std::string, Product> stock;
	
	public:
		Warehouse(void);
		void put_stock(const char*, float, int);
		int getSize(void);
};

Warehouse::Warehouse(void){
	size = 0;
}

void Warehouse::put_stock(const char* name, float price, int qty){
	Product* item = new Product(name, price, qty);
	this->stock.emplace(std::string(name), *item);
	this->size += qty;
}

int Warehouse::getSize(void){
	return this->size;
}

int main(){

	srand(0);

	Warehouse myshop {};
	std::cout << myshop.getSize() << std::endl;

	myshop.put_stock("snack", 2.50, 100);
	myshop.put_stock("water", 0.90, 300);
	std::cout << myshop.getSize() << std::endl;
	
	
	
	return 0;
}
