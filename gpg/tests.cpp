#include <iostream>
#include <cassert>
using namespace std;
#include <string.h>

#include "GpgManager.h"
#include "GpgKey.h"

int main()
{
    cout << "Running now" << endl;

    cout << "Sample key data being input:" << endl;
    GpgKey key("uid:u::::3735928559::NOTMYID::Leonid Krashanoff <leo@krashanoff.com>::::::::::0:");
    cout << "Printing..." << endl;
    key.print();

    // Verify field content.
    assert(key.recordType() == RECORDTYPE::UID);
    assert(key.validity() == 'u');
    assert(key.creationDate() == 0xdeadbeef);
    assert(key.expirationDate() == 0);
    assert(strcmp(key.certEtc(), "NOTMYID") == 0);
    assert(key.ownerTrust() == 0);
    assert(strcmp(key.userID(), "Leonid Krashanoff <leo@krashanoff.com>") == 0);

    cout << "----------------------"
         << endl
         << "BEGIN GPGMANAGER TESTS"
         << endl
         << "----------------------"
         << endl;

    GpgManager gpg;

    return 0;
}