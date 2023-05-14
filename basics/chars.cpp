#include<iostream>

// references for ASCII algebra
const char C0 = 'A'; 
const char c0 = 'a';

void upper(char* p){
	for (; *p; p++)
		(*p >= c0) ? *p += -c0 +C0 : *p += 0;
}

void lower(char* p){
	for (; *p; p++)
		(*p < c0) ? *p += -C0 +c0 : *p += 0;
}

int main(void){

	char w[] = {'T', 'e', 'S', 't', '\0'};
	char v[] = "thIswillBeATESt";

	upper(w);
	std::cout << w << std::endl;
	
	lower(v);
	std::cout << v << std::endl;

	return 0;
}
