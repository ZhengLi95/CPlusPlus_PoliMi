#include <iostream>
#include "fibonacci.h"

int main()
{
	long int n, r;
	std::cout << "Fibonacci Series Calculator\n\nPlease insert the position in the series:\n\n" << std::flush;
	std::cin >> n;
	r = fib(n);
	std::cout << "\nThe " << n << "th number in the series is " << r << std::endl; 
	return 0;	
}
