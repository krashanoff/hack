#include <cassert>
#include <math.h>
#include "vector.h"

int main()
{
    double arr1[3] = {1.0, 2.0, 3.0};
    vector<double> v1(3, arr1);
    assert(v1[0] == 1.0 && v1[1] == 2.0 && v1[2] == 3.0);
    assert(v1.length() == sqrt(14));

    double arr2[2] = {4.0, 1.0};
    vector<double> v2(2, arr2);
    vector<double> v3 = v1 + v2;
    assert(v3.dim() == 2 && v3[0] == 5.0 && v3[1] == 3.0);
    assert(v3.length() == sqrt(34));

    return 0;
}