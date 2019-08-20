#include "GpgManager.h"
#include "GpgKey.h"
#include <stdio.h>
#include <stdlib.h>

GpgManager::GpgManager()
{
    const char* command = "gpg -k --with-colons";

    // Get output to parse.
    FILE* output;
    output = popen(command, "r");

    // Throw an error in the event that our command doesn't
    // run.
    if (output == NULL)
    {
        perror("GpgManager construction error: ");
        return;
    }

    // Count lines of output.
    int lines = 0;
    char temp;
    while ((temp = fgetc(output)) != EOF)
        if (temp == '\n')
            lines++;
    m_db = new GpgKeyComplete*[lines];
    m_size = lines;

    // Reopen output pipe to rescan command output. There are a
    // few ways of accomplishing this, but none of them are too
    // elegant, unfortunately.
    pclose(output);
    output = popen(command, "r");

    // For every line of output:
    char buffer[128];
    int idx = 0;
    while (fgets(buffer, 128, output) != NULL)
    {
        // Process and enter the key.
        m_db[idx] = new GpgKeyComplete(buffer);
        idx++;
    }

    // Close our output now that we are done with it.
    pclose(output);
}

// Delete our linked list.
GpgManager::~GpgManager()
{
    for (int k = 0; k < m_size; k++)
        delete m_db[k];
    delete[] m_db;
}

GpgKeyComplete* GpgManager::getKeys() const
{
}


GpgKeyComplete* GpgManager::getSecretKeys() const
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