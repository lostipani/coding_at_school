/*
STL container samples for a bookshelf.
*/

#include<iostream>

#include<list>
#include<vector>
#include<map>

using namespace std;

class Book{
	public:
		string title {};
		string author {};
		int id;
		
		Book(string _t, string _a, int _id):
			title(_t), author(_a), id(_id)
		{
			cout << "ho instanziato l'oggetto" << endl;
		}
};

int main(){
	
	Book item1 {"Il deserto dei Tartari", "Buzzati", 1};
	Book item2 {"Au bout de la nuit", "Celine", 2};
	Book item3 {"American Pastoral", "Roth", 3};
	
	/* ------------------------------------------------------------------------------------------------------------------------
	List of books
	
	LIST allocates dynamically in non-contiguous memory blocks. For its double-link feature, it may iterate in both directions,
	whereas FORWARD_LIST can iterate from begin() to end(), solely.
	Constant time manipulation of nodes (ins/rem). No direct access to nodes by offsetting memory blocks.
	 */
	list<Book> bookshelf1;

	bookshelf1.push_front(item1); // push
	bookshelf1.push_back(item2); // append

	list<Book>::iterator it = bookshelf1.begin();
	advance(it, (bookshelf1.size())/2);
	bookshelf1.insert(it, item3); // in the middle of the list
	
	bookshelf1.pop_front(); // remove first node

	// show bookshelf
	cout << "my LIST bookshelf reads:" << endl;
  	for (list<Book>::iterator it=bookshelf1.begin(); it!=bookshelf1.end(); it++)
    	cout << it->id << "\t" << it->title << endl;
	cout << endl;	
		
		
	/* ------------------------------------------------------------------------------------------------------------------------
	Vector of books 
	
	VECTOR allows dynamical allocation in C-style array contiguous memory blocks. Hence easy to access nodes by offsetting
	references, add a new node (by means of a log buffer) on tail. It performs worse than other containers when manipulating
	nodes somewhere else other than at end().
	*/
	vector<Book> bookshelf2;
	
	bookshelf2.push_back(item1); // append
	bookshelf2.push_back(item2); // append
	bookshelf2.insert(bookshelf2.begin(), item3); // push (front) i.e. before the begin()
	
	// show bookshelf
	cout << "my VECTOR bookshelf, made of " << bookshelf2.size() << " books, reads:" << endl;
  	for (vector<Book>::iterator it=bookshelf2.begin(); it!=bookshelf2.end(); it++)
    	cout << it->id << "\t" << it->title << endl;
	cout << endl;	
	
	
	/* ------------------------------------------------------------------------------------------------------------------------
	Map of books
	
	MAP is an associative container, implemented as a balanced binary tree to dramatically ease and speed-up looking up.
	*/
	map<unsigned int, Book> bookshelf3;
	
	bookshelf3.emplace(item1.id, item1);
	bookshelf3.emplace(item2.id, item2);
	bookshelf3.emplace(item3.id, item3);
	
	// show bookshelf
	cout << "my MAP bookshelf reads:" << endl;
	for(map<unsigned int, Book>::iterator it = bookshelf3.begin(); it!=bookshelf3.end(); ++it)
		cout << it->first << "\t" << it->second.title << endl;
}
