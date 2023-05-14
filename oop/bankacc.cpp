#include<iostream>
#include<cstdlib>
#include<string>
#include<map>

/* Party classes */

class Party{
	/*
	 * this is the abstract class for any party involved.
	 */

	protected: std::string name;
	
	public:    Party(const char* p): name(std::string(p)) {}
	
	public:    std::string getName(void) { 
			   return name; 
		   }
};

class Client: public Party{

	private: int insurance_number;
	
	public:  Client(const char* p): Party(p) {
			insurance_number = rand();
		 }
	
	public:  int getInsNumb(void) {
			 return insurance_number; 
		 }
};

class Bank: public Party{

	private: std::string swift;
	
	public:  Bank(const char* p, const char* s): Party(p) {
			swift = std::string(s);
		 }
};

/* Contract classes */

class Contract{ 
	/* 
	 * this is the abstract class for any relation between two Party instances.
	 */
	
	protected: Party one, two;
	
	public:    Contract(Party alice, Party bob): one(alice), two(bob) {}
};

class BankAccount: public Contract{
	
	private: int iban;
	private: float balance;
	
	public:  BankAccount(Client alice, Bank bob): Contract(alice, bob)
		 {
		 	iban    = rand();
			balance = 0.0;
		 }
	
	public:  void put(float x) { 
			 balance += x; 
		 }
	
	public:  void take(float x) { 
			 this->put(-x); 
		 }
	
	public:  void transfer(BankAccount &other, float x) {
			 this->take(x);
			 other.put(x);
		 }
	
	public:  float getBalance(void) { 
			 return balance; 
		 }

	public:  void printParties(void){
			 std::cout << "Client : " << one.getName() << std::endl;
			 std::cout << "Bank : " << two.getName() << std::endl;
		 }
};


/* Portfolio class */

class Portfolio{
	
	private: std::map <const char*, BankAccount> accounts;
	private: int size;

	public:  Portfolio(): size(0) {};
	
	public:  void add(const char* key, BankAccount x) {
		 	accounts.emplace(key, x);
			++size;
		 }
	
	public:  BankAccount get(const char* key) {
		 	return accounts.at(key);
		 }
	
	public:  void list(void){
			std::map <const char*, BankAccount>::iterator it = accounts.begin();
			std::cout << "balance of my accounts in portfolio:" << std::endl;
			for (; it != accounts.end(); ++it)
				std::cout << it->second.getBalance() << std::endl;
		 }
};

int main(){
	srand(0); // prng is used to initialize id numbers in objects

	// instantiating stuff
	Client smb  {"G.Kasparov"};
	Bank   bnk1 {"Deutsche Bank", "DB001"};
	Bank   bnk2 {"Citi Group", "CG209"};
	BankAccount first  {smb, bnk1};
	BankAccount second {smb, bnk2};

	// do act on instances and check by printing out
	first.put(100);
	first.transfer(second, 40);
	std::cout << smb.getInsNumb() << std::endl;
	std::cout << first.getBalance() << std::endl;
	std::cout << second.getBalance() << std::endl;
	std::cout << "----------------" << std::endl;

	// build a portfolio
	Portfolio myfolio;
	myfolio.add("dt", first);
	myfolio.add("cg", second);
	myfolio.list();
	myfolio.get("dt").printParties();


	return 0;
}
