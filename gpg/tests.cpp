#include <iostream>
#include <cassert>
using namespace std;
#include "GpgManager.h"
#include "GpgKey.h"

int main()
{
    cout << "Running now" << endl;

    cout << "Sample key data being input:" << endl;
    GpgKey key("uid:u::::3735928559::NOTMYID::Leonid Krashanoff <leo@krashanoff.com>::::::::::0:");
    cout << "Printing..." << endl;
    key.print();

    cout << "----------------------"
         << endl
         << "BEGIN GPGMANAGER TESTS"
         << endl
         << "----------------------"
         << endl;

    GpgManager gpg;

    return 0;
}