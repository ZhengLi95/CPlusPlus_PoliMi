#include "fibonacci.h"

unsigned long fib(unsigned long n){
	unsigned long fib0 = 0, fib1 = 1;
	for (unsigned int i = 2; i <= n; i++)
	{
		int tmp = fib0;
		fib0 = fib1;
		fib1 = tmp + fib1;
	}
	return (n > 0 ? fib1 : 0);
}