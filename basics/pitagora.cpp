#include<iostream>

int inp(const char* t){
	int x;
	std::cout << t << std::endl;
	std::cin >> x;
	return x;
}

void makePitagora(int N){
	for (std::size_t i = 1; i <= N; ++i){
		for (std::size_t j = 1; j <= N; ++j){
			std::cout << (int) i*j << "\t";
		}
		std::cout << std::endl;
	}
}


int main(void)
{
	int N = inp("Inserire un numero naturale");

	makePitagora(N);

	return 0;
}
