#include<iostream>
#include<cstdlib>
#include<ctime>
#include<chrono>

#define DIM 100 // array dimension
#define MAX 50 // range of rand
#define SHIFT 0 // shift of rand

using namespace std;
using namespace std::chrono;

int srcLinear(int v[], int num);
int srcBinary(int v[], int init, int last, int num);
void srtBubble(int w[]);
void swap(int w[], int a, int b);
void printOut(int arr[], string title);
void srtQuick(int w[], int left, int right);
int partition(int w[],int left, int right);

int main(){
	int v[DIM]; // unsorted array
    int texp; // expired time

    // initialize the array with random numbers
    srand(time(0));
    for(int ii=0; ii<DIM; ii++){
               *(v+ii)=(rand())%MAX + SHIFT;
        }

        // print out original randomly-filled array
        printOut(v,"Original");

	// Provide number to search
	int num, num_idx;
	cout << "Provide an integer to be searched" << endl;
	cin >> num;

	// Linear search
	texp=srcLinear(v,num);
	cout << "Exec time: " << texp << "ns" << "\n =====" << endl;
	
	// Binary search
	auto start=high_resolution_clock::now();
	srtQuick(v,0,DIM-1);
	num_idx=srcBinary(v,0,DIM-1,num);
	auto stop=high_resolution_clock::now();
        auto duration=duration_cast<nanoseconds>(stop-start);
	if(num_idx==-1)
		cout << "num = " << num << " not found" << endl;
	else
		cout << "num = " << num << " is at " << num_idx << "-th position" << endl;
	cout << "Exec time: " << duration.count() << "ns" << "\n =====" << endl;
}	

/* FUNCTIONS */

// Linear searcher
int srcLinear(int v[], int num){
	/*
	Look for the element by scanning the array. As soon as the num is found,
	a flag signals to the do/while to exit the loop. If flag never turned true
	the num was not found.
	Complexity: avg(search at each n position) = (n(n+1)/2 ) / n = O(n).

	The algorithm can exploit an additional flag iff sorted (!), that is
	while((kk<DIM AND found==false) OR v[kk]>num).
	*/
	bool found=false;
	int kk=0;

	auto start=high_resolution_clock::now();
	do{
		if(v[kk]==num)
			found=true;
		else
			kk++;

	}while((found==false) && (kk<DIM));
	auto stop=high_resolution_clock::now();
        auto duration=duration_cast<nanoseconds>(stop-start);

	if(found==true)
		cout << "num = " << num << " is at " << kk << "-th position" << endl;
	else
		cout << "num = " << num << " not found" << endl;

	return duration.count();
}

// Binary searcher (recursive)
int srcBinary(int v[], int init, int last, int num){
	/* Sorting of the array, divide et impera using middle value, go to left sub-array
	if searched num < v[middle] or go to right sub-array on the other hand.
	Complexity: number of steps O(log(n))
	*/
	int mid;
	if(init<last){
		mid=(init+last)/2;
		if(v[mid]==num)
			return mid;
		else{
			if(num>v[mid])
				return srcBinary(v,mid+1,last,num);
			else
				return srcBinary(v,init,mid-1,num);
		}
	}
	else{ return -1;}
}

void srtBubble(int w[]){
        /*
        Loop over array position, compare 2-by-2 and swap to sort;
        in the second loop the upper bound is (DIM-1)-(counter of first loop)
        so no need to check for the already placed values; a flag quit the loops
        if no swap ever occurred.
        Complexity: O(n^2)
        */
        bool anyswap;
        int kk=0;
        do{
                anyswap=false;
                for(int jj=0; jj<DIM-1-kk; jj++){
                        if(w[jj]>w[jj+1]){
                                swap(w,jj,jj+1);
                                anyswap=true;
                        }
                }
                kk++;
        }while(anyswap==true);
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
        for(int ii=0; ii<DIM; ii++){
                cout << arr[ii] << " ";
        }
        cout << endl;
}
