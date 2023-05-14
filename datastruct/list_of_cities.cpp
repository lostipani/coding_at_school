/*
creare una lista di citta dove vengono
ordinate alfabeticamente

head -> [atlanta] -> [geneva] -> nullptr
inseriamo [bari]
head -> [atlanta] -> [bari] -> [geneva] -> nullptr
*/

#include<iostream>
#include<string>
#include<new>

using namespace std;

class City{
	public:
		string name {};
        City *prev; // primo nodo prev == nullptr
        City *next; // ultimo nodo next == nullptr
        
        City(string _n): name(_n){ //constructor for the struct
        	prev = nullptr;
        	next = nullptr;
		}
};

// insert city by increasing alphabetical order (no capital letters)
void ins(City* &head, string _n){
	City *cur = new City {_n};
	// cur->name = _n;
	
	if (head == nullptr){
		head = cur;
		cout << cur->name << " successfully inserted" << endl;
	}
	else{
		City *it = head;
		unsigned int k = 0; // counter for which node of the list we do insert prior to
		bool flag = false;
		do{
			if (flag = it->name == cur->name){ // adding a city already there... discard
				cout << cur->name << " already there... not inserted" << endl;
				delete cur; //de-allocate node in heap mem.
			}
			else if (flag = it->name > cur->name){ // found where to put it
				cur->prev = it->prev;
				cur->next = it;
				(k==0) ? head = cur : it->prev->next = cur; // if counter did not move, head should point to new city's node
				it->prev = cur;
				cout << cur->name << " successfully inserted" << endl;
			}
			else{ // iterate over list
				it = it->next;
				k++;
			}
		} while(it->next != nullptr && !flag); // loop untill either last node is reached or new city already inserted or discarded
		
		// if last node was reached and new city has yet to be inserted, now is the time
		if(!flag){
			cur->next = nullptr;
			cur->prev = it;
			it->next = cur; 
			cout << cur->name << " successfully inserted" << endl;
		}
	}
}

void show(City* head){
	if(head == nullptr)
		cout << "empty list" << endl;
	else{
		cout << "====\nhere are the cities... " << endl;
		City* it = head;
		while(it != nullptr){
			cout << it->name << endl;
			it = it->next;
		}
	}
}

int main()
{
	
	City* head = nullptr;
	show(head);
	ins(head, "milan");
	ins(head, "milan");
	ins(head, "geneva");
	ins(head, "zagreb");
	ins(head, "atlanta");
	show(head);
	
	return 0;
}


