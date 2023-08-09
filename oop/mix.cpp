/*
 * Mixed examples of:
 *
 * 1) << operator overloading
 * 2) friendship
 * 3) static class member
 * 4) template class and function
 * 5) exception handling
 * 6) lambda function
 * 7) vector STL
 * 8) prng
 * 9) take number in input from main
 *
 * Summer 2023
 */

#include<iostream>
#include<random> // for std::default_random_engine, std::uniform_int_distribution
#include<vector>
#include<stdlib.h> // for strtol
#include<functional> // for std::bind
#include<algorithm> // for std::transform

template<class T> class Vec; // class declaration before << overloading

template<class T> std::ostream& operator<< (std::ostream&, const Vec<T>&); // only declaration because need to define the class first

template<class T, int N=1> Vec<T> transf_add_N(const Vec<T>&); // only declaration because need to define the class first


template<class T> class Vec // class definition
{
	static std::size_t count; // instance counter
	std::vector<T> data;

	public: Vec(void) { ++count; }
		
		void set(const T& val) { data.push_back(val); }
		
		T get(const std::size_t& i = 0) const { return data[i]; }
		
		static void show(void) { std::cout << "N. of instances: " << count << std::endl; } // this method is static to access count that is a static attribute
		
		friend std::ostream& operator<< <T> (std::ostream&, const Vec<T>&); // declaration in class requires specifying <T> for external template function

                friend Vec<T> transf_add_N <T> (const Vec<T>&); // template function w/ 2 parameters but second is by default =1
};

template<class T> std::size_t Vec<T>::count = 0; // initialize static class member, note class name with T usage

template<class T> std::ostream& operator<< (std::ostream& out, const Vec<T>& vec) // definition of << overloading using class member function
{
	for (std::size_t i=0; i != vec.data.size(); ++i)
		std::cout << vec.get(i) << " ";
	
	std::cout << std::endl;
	return out;
}

template<class T, int N=1> Vec<T> transf_add_N(const Vec<T>& orig) // default value for second parameter of template so no need to define a class template w/ 2 parameters!
{
    Vec<T> mod;
    mod = orig;
    std::transform(orig.data.begin(), orig.data.end(), mod.data.begin(), [] (T x) -> T { return x+N; }); // add N element-wise to a new vector
    std::sort(mod.data.begin(), mod.data.end()); // sort new vector
    return mod;
}


int main(int argc, char** argv){
	
	int N;
	try
	{	
		N = strtol(argv[1], nullptr, 10); // convert input #1 to int
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

	std::default_random_engine gen; // declare random generator
	std::uniform_int_distribution<int> unif(0,100); // declare random distribution
	auto draw = std::bind(unif, gen); // bind both objects to one functor
	
	Vec<int> myvec1 {};
	for (int k=0; k!= N; k++)
		myvec1.set(draw());

	Vec<int> myvec2;
        myvec2 = transf_add_N<int,1> (myvec1); //this makes a third instance of Vec<T> because one is myvec2 and the other is mod inside the function!
	std::cout << myvec1; // invoke overloaded << with class instance
	std::cout << myvec2; // print for comparison

	// print via static member class
	Vec<int>::show();

	return 0;

}
