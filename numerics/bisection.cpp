#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<fstream>
#include<iostream>

const int PRECVERB = 20; // number of digits in verbose output
const int PRECFILE = 10; // number of digits in file output

// default function is a parabola y = x^2 - 2
double f(double x, float a=1.0, float b=0.0, float c=-2.0){
    return a*std::pow(x, 2) + b*x + c;
}


int main(int argc, char** argv){

    // parse input
    double a   = std::atof(argv[1]);
    double b   = std::atof(argv[2]);
    double err = std::atof(argv[3]);

    // instantiate ofstream object
    std::ofstream File("dump.dat");

    // bisection iterations
    int count  = 1;
    double mid = (a+b)/2;
    bool incr  = f(b) > f(a);
    do{
	count++;

	// verbose output
        std::cout << "Bisection:: iteration n " << count << ": \t approx zero \t" << std::setprecision(PRECVERB) << mid << std::endl;
       
	// write to file
        if (File.is_open())    
            File << std::setprecision(PRECFILE) << a << "\t" << mid << "\t" << b << std::endl; 
       
	// bracketing
        if (f(mid) > 0)
            (incr) ? b = mid : a = mid;
        else
            (incr) ? a = mid : b = mid;
        mid = (a+b)/2;
    
    } while(std::abs(b-a) > 2*err); // check if bracket is smaller than precision 

    // verbose output
    std::cout << "True value of sqrt(2): \t \t \t \t1.41421356237309504880168872420969807856967187537694807317667973799" << std::endl;
    std::cout << "Bisection:: converged at " << count-1 << "-th iteration. Data dumped into file." << std::endl;

    // close file and terminate
    File.close();
    return 0;
}
