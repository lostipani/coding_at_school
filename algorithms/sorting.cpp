/*
Alcuni metodi di ordinamento e calcolo dei tempi computazionali.

Non fatto a lezione, ma utile per un ripasso.

NOTA: compilatori con risoluzione temporale non sufficiente, non
permettono di visualizzare correttamente il tempo computazionale;
-) g++ su linux funziona
-) notebook e.g. colab con qualche trick con le magics di ipython:
	%%writefile ordinamento.cpp
	{....questo codice....}
	
	%%shell
	g++ -std=c++11 ordinamento.cpp -o a.out
	./a.out
*/

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<chrono>

using namespace std;
using namespace std::chrono;

int N   {}; //array dimension
int MAX {50}; //max of rand
int MIN {1}; //shift of rand

int srtInsert(int v[], int w[]);
int srtBubble(int w[]);
int srtSelect(int w[]);
void srtQuick(int w[], int left, int right);
void swap(int w[], int a, int b);
void shiftR(int w[], int init, int last);
void copyarr(int v[], int w[]);
void printOut(int arr[], string title);
int min_ind(int w[], int init, int last);
int partition(int w[], int left, int right);
template<class T> void srtMerge(T*, std::size_t, std::size_t);
template<class T> void merger(T*, std::size_t, std::size_t, std::size_t);

int main(){	

	// take N from user
	cout << "Array extent? " << endl;
	cin >> N;

	int v[N]; // unsorted array
	int w[N]; // sorted array
	int texp; // expired time

	// initialize the two array, the first with random numbers in (0,50), the second with zeros
	srand(time(0));
	for(int ii=0; ii<N; ii++){
		*(v+ii)=rand()%(MAX-MIN+1) + MIN;
		*(w+ii)=0;
	}
	
	// print out original randomly-filled array
	printOut(v,"Original");

	/*
	Call sorting routines and print out results + time of execution
	*/
	
	// insert sorting
	texp=srtInsert(v,w);
	printOut(w,"Insert sort: ");
	cout << "Exec time: " << texp << "ns" << "\n =====" << endl;

	// selection sorting
	copyarr(v,w); // copy v into w to not overwrite the former
	texp=srtSelect(w);
	printOut(w,"Selection sort: ");
	cout << "Exec time: " << texp << "ns" << "\n =====" << endl;
	
	// bubble sorting
	copyarr(v,w); // copy v into w to not overwrite the former
	texp=srtBubble(w);
	printOut(w,"Bubble sort: ");
	cout << "Exec time: " << texp << "ns" << "\n =====" << endl;
	
	// quick sorting	
	copyarr(v,w); // copy v into w to not overwrite the former
	auto start=high_resolution_clock::now();
	srtQuick(w,0,N-1);
	auto stop=high_resolution_clock::now();
	auto duration=duration_cast<nanoseconds>(stop-start);
	printOut(w,"Quick sort: ");
	cout << "Exec time: " << duration.count() << "ns" << "\n =====" << endl;

	// merge sorting	
	copyarr(v,w); // copy v into w to not overwrite the former
	start=high_resolution_clock::now();
	srtMerge(w,0,N-1);
	stop=high_resolution_clock::now();
	duration=duration_cast<nanoseconds>(stop-start);
	printOut(w,"Merge sort: ");
	cout << "Exec time: " << duration.count() << "ns" << "\n =====" << endl;
}

/* FUNCTIONS */

// Insert sorter
int srtInsert(int v[], int w[]){
	auto start=high_resolution_clock::now();
	for(int ii=0; ii<N; ii++){
		/* 
		Run the index kk untill the number
		to be placed is smaller than the one already present
		or the sub-array (0 to ii) is over.
		Complexity: O(n^2)
		*/
		int kk=0;
		while((v[ii]>w[kk]) && (kk<ii)){
			kk++;
		}
		
		shiftR(w,kk,ii); // shift to the right all the other numbers already there
		w[kk]=v[ii]; // set the value at the now free position
	}	
	auto stop=high_resolution_clock::now();
	auto duration=duration_cast<nanoseconds>(stop-start);
	return duration.count();
}

// Right shift for Insert sorter
void shiftR(int w[], int init, int last){
	/*
	Shift from where I want to put the new number to the end of the sub-array,
	this has to be made from the bottom of the sub-array otherwise you're
	going to overwrite the following elements.
	Complexity: O(n^2)
	*/
	for(int jj=last-1; jj>=init; jj--){
		w[jj+1]=w[jj];
	}
}

// Selection sorter
int srtSelect(int w[]){
	/*
	The array is filled one at a time with the minimum 
	of each sub-array.
	Complexity: O(n^2)
	*/
	auto start=high_resolution_clock::now();
	for(int ii=0; ii<N-1; ii++){
		int jj=0;
		jj=min_ind(w,ii,N);
		swap(w,ii,jj);
	}
	auto stop=high_resolution_clock::now();
	auto duration=duration_cast<nanoseconds>(stop-start);
	return duration.count();
}

// Find index of minimum in array for given boundaries, for Selection sorter
int min_ind(int w[],int init, int last){
	int idx=init;
	for(int kk=init; kk<last; kk++){
		if(w[kk]<w[idx]){ idx=kk;}
	}
	return idx;
}

// Bubble sorter
int srtBubble(int w[]){
	/*
	Loop over array position, compare 2-by-2 and swap to sort;
	in the second loop the upper bound is (N-1)-(counter of first loop)
	so no need to check for the already placed values; a flag quit the loops
	if no swap ever occurred.
	Complexity: O(n^2)
	*/
	auto start=high_resolution_clock::now();
	bool anyswap;
	int kk=0;
	do{
		anyswap=false;
		for(int jj=0; jj<N-1-kk; jj++){
			if(w[jj]>w[jj+1]){
				swap(w,jj,jj+1);
				anyswap=true;
			}
		}
		kk++;
	}while(anyswap==true);
	auto stop=high_resolution_clock::now();
	auto duration=duration_cast<nanoseconds>(stop-start);
	return duration.count();
}

// Quick sorter (recursive)
void srtQuick(int w[], int left, int right){
	/*
	Partition does the job, that is comparisons, swaps and sub-array splitting;
	then srtQuick is called recursively for each sub-array (left-hand visiting).
	*/
	int q; // partition index

	if(left < right) // check if the array dimension is not a singleton
	{
		// partition: swap untill (right < left) then split array
		q=partition(w,left,right);
		// recursive calls for left and right sub-arrays
		srtQuick(w,left,q-1);
		srtQuick(w,q+1,right);
	}
}

// for Quick sorter
int partition(int w[],int left, int right){
	int pvt, idx_pvt; // value and index of pivot
	idx_pvt=left; // set pivot to middle of array
	pvt=w[idx_pvt];
	// swap untill (right<left)
	while(left<right){ 
		while((w[left]<=pvt) && (left<right)){ left++;} // increase left untill value>pivot or end of array
		while(w[right]>pvt) { right--;} // increase right untill value<=pivot (no need to check for array dim since pivot value is accepted to halt the while)
		if(left<right){ 
			swap(w,left,right);
			// these two lines below are required to account for any swap of the pivot before left>right happens, this occurs when pivot is not the first element!!!
			if(left==idx_pvt){ idx_pvt=right;}
			if(right==idx_pvt){ idx_pvt=left;}
		}
	}
	// now swap pivot with element at index right and return the latter
	swap(w,idx_pvt,right);
	return right;
}


// Merge sort
template<class T> void srtMerge(T* v, std::size_t init, std::size_t last){
	if (init < last){
		std::size_t mid = (last+init)/2;
		srtMerge(v, init, mid);
		srtMerge(v, mid+1, last);
		merger(v, init, mid, last);
	}
}

template<class T> void merger(T* v, std::size_t init, std::size_t mid, std::size_t last){
	
	// create auxiliary sub-arrays left and right with copied values
	std::size_t nl = mid - init + 1;
	std::size_t nr = last - mid;
	T vl[nl];
        T vr[nr];

        for (std::size_t i = 0; i < nl; i++)
		vl[i] = v[init + i];
	for (std::size_t j = 0; j < nr; j++)
		vr[j] = v[mid + 1 + j];

	// loop over sub-arrays to populate original
	std::size_t i = 0;
	std::size_t j = 0;
	std::size_t k = init;
	while (i < nl && j < nr){
        	
		if (vl[i] <= vr[j]){
        		v[k] = vl[i];
        		i++;
		}
		else{
        		v[k] = vr[j];
            		j++;
		}
        	
		k++;
    	}

	// complete populating if one of two sub-arrays was not fully visited
	while (i < nl){
		v[k] = vl[i];
		i++;
		k++;
    	}
    	while (j < nr){
		v[k] = vr[j];
		j++;
		k++;
    	}
}

// Copy v into w
void copyarr(int v[], int w[]){
	for(int ii=0; ii<N; ii++) 
		w[ii]=v[ii];

}

// Swap ii-th and jj-th elements of array, for Selection sorter
void swap(int w[], int a, int b){
	int tmp;
	tmp=w[b];
	w[b]=w[a];
	w[a]=tmp;
}

// Routine to print out results onto terminal
void printOut(int arr[], string title){
	cout << title << endl;
	for(int ii=0; ii<N; ii++){
		cout << arr[ii] << " ";
	}
	cout << endl;
}
