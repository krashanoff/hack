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

    // Check for proper ID.
    const char* id = key.userID();
    const char* otherId = "Leonid Krashanoff <leo@krashanoff.com>";
    for (int k = 0; id[k] != '\0'; k++)
        assert(id[k] == otherId[k]);

    assert(key.recordType() == RECORDTYPE::UID);
    assert(key.validity() == 'u');

    cout << "----------------------"
         << endl
         << "BEGIN GPGMANAGER TESTS"
         << endl
         << "----------------------"
         << endl;

    GpgManager gpg;

    return 0;
}