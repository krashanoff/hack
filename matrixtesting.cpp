#include "Vector.h"
#include "Matrix.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
	// Test a variety of Matrix sizes for memory leaks.
	Matrix<int> a(2, 3);
	Matrix<char> b(3, 2);

	b.mod(1,1,'a');
	b.mod(2,2,'b');
	b.print();

	Matrix<double> c(3, 3);

	c.mod(1,1,2.5);
	c.mod(2,2,5.98);
	c.print();

	int oldVec[5] = {0,1,2,3,4};
	Vector<int> newVec(oldVec, 5);
	newVec.print();

	return 0;
}