#include "Matrix.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
	// Test a variety of Matrix sizes for memory leaks.
	Matrix<int> a(2, 3);
	Matrix<char> b(3, 2);
	Matrix<double> c(3, 3);

	c.mod(1,1,2.5);

	c.print();

	return 0;
}