/*
C-style in C++ personal library for dealing with numerical arrays.
Here, typically, array stands for 1-dimensional structure (aka vector).
 */

#include<iostream>
#include<cstdlib>
#include<cmath>

/* Function signatures */

template<class T> void swap(T*, std::size_t, std::size_t);
template<class T> void fill(T*, std::size_t, unsigned int, T, T, bool verb=true);
template<class T> void print(T*, std::size_t);
template<class T> void fliplr(T* v, std::size_t);
template<class T> T dist(T*, T*, std::size_t, unsigned int);
template<class T> T maxOccurr_sorted(T*, std::size_t);
template<class T> T maxOccurr_notsorted(T*, std::size_t);
template<class T> T conv(T* v, T*, std::size_t);
	

/* Main */	

int main(){

	const int N = 4;
	int v[N], w[N];
	fill(v, N, 0, 0, 10, false);
	print(v, N);
	fill(w, N, 1, 0, 10, false);
	print(v, N);

	std::cout << "----------" << std::endl;	
	std::cout << conv(v, w, N) << std::endl;

	return 0;
}


/* Function definitions */

template<class T> void swap(T* v, std::size_t a, std::size_t b){
	int z = v[a];
	v[a]  = v[b];
	v[b]  = z;
}

template<class T> void fill(T* v, std::size_t N, unsigned int seed, T min, T max, bool verb){
	srand(seed);
	if (verb) std::cout << "PRNG initialized\n"; 

	for(std::size_t i=0; i!=N; ++i)
		v[i] = rand()%(max-min+1) + min;

	if (verb) std::cout << "Array filled with random numbers in given interval\n";
}

template<class T> void print(T* v, std::size_t N){
	for(std::size_t i=0; i!=N; ++i)
		std::cout << v[i] << "\t";
	std::cout << std::endl;
}

template<class T> void fliplr(T* v, std::size_t N){
	for(std::size_t i=0; i<N/2; ++i)
		swap(v, i, N-1-i);
}

template<class T> T dist(T* v, T* w, std::size_t N, unsigned int opt){
/*
 DIST evaluates the distance between two 1-dim equally-long arrays.
 opt = 0: Euclidean distance 
 opt = 1: min(abs(diff))
 */	
	T res = 0;

	switch (opt){
		case 0:
			for(std::size_t i=0; i!=N; ++i)
				res += std::pow(v[i]-w[i], 2.0);
			break;
		case 1:
			for(std::size_t i=0; i!=N; ++i){
				if (std::abs(v[i]-w[i]) < res)
					res = std::abs(v[i]-w[i]);
			}
			break;
	}

	return (T) res;
}


template<class T> T maxOccurr_sorted(T* v, std::size_t N){
	unsigned int counter   = 0;
	unsigned int max_count = 0;
	T max;

	for (std::size_t i=0; i<N-1; i++){
		if(v[i] == v[i+1])
			counter++;
		else{
			if (counter >= max_count){
				max_count = counter;
				max = v[i];
			}
			counter = 1;
		}

	}

	return max;
}


template<class T> T maxOccurr_notsorted(T* v, std::size_t N){
	unsigned int counter   = 0;
	unsigned int max_count = 0;
	T curr, max = v[0];

	for (std::size_t i=0; i<N; i++){
		if(v[i] != max) { // avoid double counting elements already checked
			curr    = v[i];
			counter = 0;

			for(std::size_t j=0; j<N; j++){
				if(curr == v[j])
					counter++;
			}

			if(counter > max_count){
				max_count = counter;
				max = curr;
			}
		}
	}

	return max;
}


// Convolution (or polynomial) product 
template<class T> T conv(T* v, T* w, std::size_t N){
	T mat[N][N];
	T res = 0.;
	
	for (std::size_t i=0; i<N; ++i){
		for(std::size_t j=i; j<N; ++j){
			mat[i][j] = v[i]*w[j];			
			mat[j][i] = mat[i][j];
			
			res += ( (i==j) ? mat[i][j] : 2*mat[i][j] );

			std::cout << mat[i][j] << "\t";
		}			
		std::cout << std::endl;
	}

	return res;
}


