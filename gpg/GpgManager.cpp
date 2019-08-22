#include "GpgManager.h"
#include "GpgKey.h"
#include <stdio.h>

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
    m_db = new GpgKey*[lines];
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
        m_db[idx] = new GpgKey(buffer);
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

// Returns the database.
GpgKey** GpgManager::getKeys() const
{
    return m_db;
}


GpgKey* GpgManager::getSecretKeys() const
{
}

int GpgManager::keyCount() const
{
    return m_size;
}


bool GpgManager::sign(const char* filePath, bool clearSign) const
{
    return false;
}


bool GpgManager::verify(const char* key) const
{
    return false;
}