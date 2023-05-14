/*
Inizializzazione di array con numeri pseudo-random
da Linear Congruential Generator con semi vicini per
osservare comportamento caotico.

Accesso ad elementi degli array per mezzo di [] oppure
deferenziamento ed aritmetica del puntatore.

3Asa, 14.10.2021, aula 404
*/

#include<iostream>	
#include<ctime>	

using namespace std;

int main(){

	const int LEN {20};
	const int RANGE {200};
	const int SHIFT {0};
	
	long seed = time(0);

	float v1[LEN], v2[LEN];

	// riempi v1 con pseudo-random da seed
	cout << "Seme 1: " << seed << endl;
	srand(seed);
	for(int ii=0; ii<LEN; ii++){
		v1[ii] = rand()%RANGE + SHIFT; // accesso ad elementi array per []
	}

	// riempi v2 con pseudo-random da seed+1
	cout << "Seme 2: " << seed+1 << endl;
	srand((seed+1));
	for(int ii=0; ii<LEN; ii++){
		*(v2+ii) = rand()%RANGE + SHIFT; // accesso ad elementi array per deferenziamento ed aritmetica puntatore
	}

	// stampa differenze elementi successivi in una sequenza di numeri prodotti da LCG: numeri pseudo-random
	cout << "-----\n diff(LCG1)" << endl;
	for(int ii=0; ii<LEN-1; ii++){ // il loop for va fino a (LEN-1) escluso perché la differenza riduce la lunghezza dell'array, e.g. diff([4,2,1,3]) = [4-2,2-1,1-3] = [2,1,-2]
		cout << (*(v1+ii+1) - *(v1+ii)) << endl;
	}
	
	// stampa differenze elementi tra due sequenze di numeri prodotti da LCG con semi vicini: comportamento caotico
	cout << "-----\n LCG2 - LCG1" << endl;
	for(int ii=0; ii<LEN; ii++){
		cout << (*(v1+ii) - *(v2+ii)) << endl;
	}
	
}
