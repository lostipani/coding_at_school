/*
C-style in C++ personal library of routines for dealing with char arrays (1-dim) aka strings.
Basically, bypass cstring.h and learn how to do it.

Some of them are able to parse array of char pointers (e.g. argv).

String is a (const) char pointer null-terminated.
*/

#include<iostream>
#include<new>

/* Function signatures */

void concat(char*, char*, char*);
std::size_t len(char*);
int compare(char*, char*);
unsigned int countComm(char*, char*);
bool anyVowel(char*);
bool allVowel(char*);
bool hasDouble(char*);
bool isSorted(char*);
void match(char* t, char* p);
void show(char**, std::size_t, std::size_t);
void swap(char**, std::size_t, std::size_t);
void sort(char**, std::size_t, std::size_t);

/* Main */

int main(int argc, char** argv){
/*
	show(argv,0,argc);
	sort(argv,0,argc);
	show(argv,0,argc);
	
	// to concatenate, need to find lengths of two strings, allocate new one
	std::size_t len_a = len(argv[1]);
	std::size_t len_b = len(argv[2]);
	char* c = new char[len_a + len_b + 1]; // by <new> due to unknown (at comp time) len_c
	concat(argv[1], argv[2], c);
	std::cout << c;
*/
	// check pattern match
	match(argv[1], argv[2]);

	return 0;
}

/* Function definitions */


// Concatenate 2 strings into 1
void concat(char* a, char* b, char* c){
/*
Parameters should be pointers to allocated chars with proper size to accommodate values.
Non-abelian, i.e. (a,b) --> a+b != b+a

*/
	std::size_t k = 0;

	for(std::size_t i=0; a[i]!='\0'; ++i, ++k)
		*(c+k) = a[i];
	for(std::size_t i=0; b[i]!='\0'; ++i, ++k)
		*(c+k) = b[i];
	*(c+k) = '\0';
}

// Length of array
std::size_t len(char* a){
	if (*a)
		return 1 + len(a+1);
	else
		return 0;
}


// Check if string has minuscule vowel
bool anyVowel(char* s){
	if (!(*s))
		return false;
	else if (*s == 'a' || *s == 'e' || *s == 'i' || *s == 'o' || *s == 'u')
		return true;
	else
		return false || anyVowel(s+1);
}


// Check if string has all minuscule vowels
bool allVowel(char* s){
	if (!(*s))
		return false;
	else if (*s == 'a' || *s == 'e' || *s == 'i' || *s == 'o' || *s == 'u'){
		if (!(s[1]))
			return true;
		else
			 return anyVowel(s+1);
	}
	else
		return false;
}


// Find pattern in text
void match(char* t, char* p){
	std::size_t len_t = len(t);
	std::size_t len_p = len(p);
	bool flag = false;

	char aux[len_p+1];
	for (std::size_t i=0; i<len_t-len_p+1; ++i){
		if (t[i] == p[0]){
			// strip array from i to len_p
			for (std::size_t k=0; k<len_p; ++k)
				aux[k] = t[i+k];
			aux[len_p] = '\0';
			
			if (compare(aux,p) == 0){
				std::cout << "Pattern found from: " << i << std::endl;
				flag = true;
			}
		}
	}

	if (!flag)
		std::cout << "Pattern not found" << std::endl;
}


// Check if string has double (consecutive equal chars)
bool hasDouble(char* s){
	if (*s){
		if (*(s+0) == *(s+1))
			return true;
		else
			return false || hasDouble(s+1);
	}
	else
		return false;
}


// Check if array is sorted (<)
bool isSorted(char* s){
	if (s[0] != '\0'){
		if (s[1] == '\0')
			return true;
		else if (s[0] > s[1])
			return false;
		else
			return true && isSorted(s+1);
	}
	else
		return true;
}


// Count how many chars are shared
unsigned int countComm(char* a, char* b){
	unsigned int k = 0;

	for(std::size_t i=0; a[i]!='\0'; ++i){
		for(std::size_t j=0; b[j]!='\0'; ++j){
			if (a[i] == b[j])
				k++;
		}
	}
	return k;
}

// Compare strings by alphabetical order and length
int compare(char* a, char* b){
	/*
	 a > b: +1
	 a = b: 0
	 a < b: -1
	 */
	if      (!(*a) && !(*b))
		return 0;
	else if (!(*a) || *a < *b)
		return -1;
	else if (!(*b) || *a > *b)
		return 1;
	else
		return compare(a+1, b+1);
}


// Print out strings in array
void show(char** p, std::size_t init, std::size_t N){
	for(std::size_t i = init; i<N; ++i){
		std::cout << *(p+i) << std::endl;
	}
	std::cout << "-----------" << std::endl;
}


// Swap char pointers in array of strings
void swap(char** p, std::size_t i, std::size_t j){
	char* aux = p[i];
	p[i]      = p[j];
	p[j]      = aux;
}


// sort strings in array of char pointers
void sort(char** p, std::size_t init, std::size_t N){
/*
Flagged- resized- bubble sort for array of strings.
*/
	bool anyswap = false;
        int k = 0;
        do{
                for(int j = 0; j < N-1-k; ++j){
                        if(compare(p[j], p[j+1]) == 1){
                                swap(p, j, j+1);
                                anyswap = true;
                        }
                }
                ++k;
        }while(anyswap);
}
