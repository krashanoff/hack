#include "Matrix.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
	Matrix<int> a;

	assert(a.insert(1, 1, 2));

	return 0;
}