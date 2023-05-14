/*
Breve guida al passaggio degli array alle routine. Ovvero come una routine C prende
un array (blocchi di memoria consecutivi di uno stesso tipo di variabile) e lo fa
decadere in un puntatore. 

NOTA 1: le due routine definite sotto, per mezzo del costrutto "template", possono
gestire array di tipo qualunque. Guardare nel main() come vec (array 1-dim) sia 
di tipo float, mentre mat (array 2-dim) di tipo int.

NOTA 2: size_t e' un tipo di variabile dedicato alle dimensioni degli array ed
all'indice usato per trovare la posizione degli elementi.

-----------------------
L. Stipani, 16.11.2021
*/

#include<iostream>

/* Mostra un vettore (array 1-dim): la lunghezza N e' un
parametro libero, ad ogni invocazione della routine puo' essere
cambiato, ma consistentemente con la definizione dell'array! */

template<class T> void showVector(T v[], size_t N){
	for(size_t j=0; j!=N; j++)
		std::cout << v[j] << std::endl;
}



/* Mostra una matrice (array 2-dim): la lunghezza N (num. di righe)
e' un parametro libero, cioe' ad ogni invocazione della routine puo' essere
cambiato, ma consistentemente con la definizione dell'array!

Al contrario M (num. di colonne) dev'essere una costante fissata prima
della definizione della routine. Utile quindi dichiararla come variabile
globale, cioe' fuori dal main(). Notare come nel parametro formale 
T m[][M], appunto la M dev'essere fornita e quindi essere gia' inizializzata. */

const size_t M = 3; // valore arbitrario ma costante
template<class T> void showMatrix(T m[][M], size_t N){
	for(size_t j=0; j!=N; j++){
		for(size_t k=0; k!=M; k++)
			std::cout << m[j][k] << "\t";
	
		std::cout << std::endl;
	}
}

int main(){
	const size_t nrow = 4;
	float vec[nrow] {5.54,0.5,9.1,1.42};
	int mat[nrow][M] {{4,6,1},{0,4,1},{8,2,6},{0,7,2}};

	std::cout << "==== This is a 1-dim array ====" << std::endl;
	showVector(vec, nrow);
	std::cout << "==== This ia a 2-dim array ====" << std::endl;
	showMatrix(mat, nrow);
		
}
