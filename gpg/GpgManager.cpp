#include "GpgManager.h"
#include "GpgKey.h"
#include <stdio.h>
#include <stdlib.h>

GpgManager::GpgManager()
{
    // Get output to parse.
    FILE* output = popen("gpg -k --with-colons", "r");

    // Throw an error in the event that our command doesn't
    // run.
    if (output == NULL)
    {
        perror("GpgManager construction error: ");
        return;
    }

    char buffer[128];
    while (fgets(buffer, 128, output))
        printf("%s", buffer);

    // Close our output now that we are done with it.
    pclose(output);
}

// Delete our linked list.
GpgManager::~GpgManager()
{
}

void GpgManager::getKeys() const
{
}


void GpgManager::getSecretKeys() const
{
}


bool GpgManager::sign(const char* filePath, bool clearSign)
{
    return false;
}


bool GpgManager::verify(const char* key)
{
    return false;
}


FILE* GpgManager::decryptThenRead(const char* inPath) const
{}


FILE* GpgManager::decrypt(const char* inPath, const char* outPath) const
{}

FILE* GpgManager::encrypt(const char* inPath, const char* outPath, const char* recipientID, bool armored) const
{}