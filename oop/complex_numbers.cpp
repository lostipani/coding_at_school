#include<iostream>
#include<cmath>

class Complex{

	float re, im;

	public: Complex(float r, float i): re(r), im(i) { }
		float abs(void) const  { return sqrt(re*re + im*im); }
		float ang(void) const  { return atan2(im, re); }
		float real(void) const { return re; }
		float imag(void) const { return im; }
		Complex* memadd(void)  { return this; } // return memory address of the instance
		Complex conj(void)     { Complex z {re, -im}; return z; } // yield conjugated complex number 
};

// sum of complex numbers
Complex operator+ (Complex& x, Complex& y)
{
	Complex z {x.real()+y.real(), x.imag()+y.imag()};
	return z;
}

// equality of complex numbers
bool operator== (Complex lhs, Complex rhs)
{
	return (lhs.real() == rhs.real()) && (lhs.imag() == rhs.imag());
}


int main(){

	Complex z {1.0, 1.0};
	std::cout << z.abs() << std::endl;

 	Complex	w = z.conj();
	std::cout << w.imag() << std::endl;

 	Complex	q = z + w;
	std::cout << q.real() << std::endl;
	
	return 0;
}
