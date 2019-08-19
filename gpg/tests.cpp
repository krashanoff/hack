#include <iostream>
using namespace std;
#include "GpgManager.h"
#include "GpgKey.h"

int main()
{
    cout << "Running now" << endl;

    GpgKeyComplete key("uid:Leonid Krashanoff <leo@krashanoff.com>::");

    char* a = key[RECORDTYPE];
    key.print();
    printf("Trying to print out a subscripted field: %s\n", a);
    
    return 0;
}