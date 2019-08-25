#include "strTools.h"
#include "numTools.h"
using namespace util;

#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    // Test encodeInto for basic functionality.
    char c0[8] = { 'D', 'E', 'A', 'D', 'B', 'E', 'E', 'F' };

    // One only needs to supply the return type.
    long* lo = encodeInto<long>(c0, 8);
    assert(lo != nullptr && *lo == 0x4445414442454546);

    // Test decodeInto for basic functionality.
    char* c1 = decodeInto<char>(*lo);
    assert(c1 != nullptr);
    for (int k = 0; k < 8; k++)
        assert(c1[k] == c0[k]);

    // Same test, just with a different variable type.
    int* i0 = decodeInto<int>(*lo);
    assert(i0 != nullptr);
    assert(i0[0] == 0x44454144);
    assert(i0[1] == 0x42454546);

    // Free memory following call of encodeInto and decodeInto.
    delete lo;
    delete[] i0;
    delete[] c1;

    // Test encodeInto for failure case.
    const char* c2 = "STRINGSTRING";
    lo = encodeInto<long>(c2, 13);
    assert(lo == nullptr);

    // Test decodeInto for failure case.
    char c3 = 'c';
    assert(decodeInto<double>(c3) == nullptr);

    // We don't need to free memory in this case as we failed
    // to create our result.

    // Test copyString for basic functionality.
    const char* c4 = "Test string";
    char* c5 = copyString(c4);
    for (int k = 0; c5[k] != '\0'; k++)
        assert(c4[k] == c5[k]);
    delete[] c5;

    // Test copyString for failure case.
    assert(copyString(nullptr) == nullptr);

    // Test getNum for basic functionality.
    const char* c6 = "520122";
    assert(getNum<int>(c6) == 520122);
    const char* c7 = "2147483647";
    assert(getNum<long>(c7) == 2147483647);

    return 0;
}