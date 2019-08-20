#include <iostream>
#include <cassert>
using namespace std;
#include "GpgManager.h"
#include "GpgKey.h"

int main()
{
    cout << "Running now" << endl;

    GpgKeyComplete key("uid:Leonid Krashanoff <leo@krashanoff.com>::");
    cout << "Read in key with the following information:" << endl;
    key.print();

    const char* a = key[RECORDTYPE];
    cout << "Trying to print out a subscripted field: " << a << endl;

    GpgManager gpg;

    cout << "Printing out all stored keys:" << endl;
    GpgKeyComplete** keyList = gpg.getKeys();
    int count = gpg.keyCount();
    for (int k = 0; k < count; k++)
        keyList[k]->print();

    return 0;
}