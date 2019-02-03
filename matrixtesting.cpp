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

	cerr << "Identity matrix test:" << endl;
	Matrix<double> j = c.identity();
	j.print();

	cerr << "Construct from array test:" << endl;
	int oldVec[5] = {0,1,2,3,4};
	Vector<int> newVec(oldVec, 5);
	newVec.print();

	cerr << "Row operations tests:" << endl;
	int dArray[5][5] =
	{
		{0,1,2,3,4,},
		{5,6,7,8,9},
		{10,11,12,13,14},
		{15,16,17,18,19},
		{20,21,22,23,24}
	};
	Matrix<int> d(dArray, 5, 5);
	cerr << "Start:" << endl;
	d.print();
	cerr << "Add row 2 to row 1:" << endl;
	d.addRows(1, 2);
	d.print();
	cerr << "Swap rows:" << endl;
	d.swapRows(1,2);
	d.print();

	return 0;
}